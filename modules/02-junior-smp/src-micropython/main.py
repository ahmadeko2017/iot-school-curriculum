"""
main.py: Stasiun Cuaca Mandiri Menggunakan MicroPython

Tanggung Jawab:
- Membaca data suhu dan kelembapan dari sensor DHT11 (GPIO 15).
- Menampilkan metrik lingkungan ke layar OLED SSD1306 (GPIO 21 & 22).
- Menyediakan tombol pemilih tampilan (GPIO 18) untuk navigasi halaman.
- Membunyikan buzzer (GPIO 4) saat suhu melampaui ambang batas bahaya.

Target Hardware:
- ESP32 NodeMCU DevKit V1 Type-C
- Layar OLED SSD1306 I2C (128x64)
- Sensor DHT11: GPIO 15
- Tombol Halaman: GPIO 18 (Pull-up)
- Buzzer Alarm: GPIO 4
"""

import time
import dht
from machine import Pin, SoftI2C

PIN_SDA = 21
PIN_SCL = 22
PIN_DHT = 15
PIN_TOMBOL = 18
PIN_BUZZER = 4
BATAS_PANAS = 33.0


def bunyikan_buzzer(pin_buzzer, durasi_ms=80):
    """Membunyikan nada peringatan singkat."""
    pin_buzzer.value(1)
    time.sleep_ms(durasi_ms)
    pin_buzzer.value(0)


def evaluasi_status(suhu):
    """Menentukan teks kategori indeks kenyamanan suhu."""
    if suhu < 24.0:
        return "Sejuk"
    if suhu <= 32.0:
        return "Nyaman"
    return "PANAS!"


def tampilkan_data_ringkas(oled, suhu, lembap, status):
    """Menampilkan halaman metrik teks utama."""
    if not oled:
        return
    oled.fill(0)
    oled.text("STASIUN CUACA", 0, 0)
    oled.hline(0, 10, 128, 1)
    oled.text("Suhu  : {:.1f} C".format(suhu), 0, 18)
    oled.text("Lembap: {:.1f} %".format(lembap), 0, 32)
    oled.text("Status: {}".format(status), 0, 48)
    oled.show()


def tampilkan_grafis_batang(oled, lembap):
    """Menampilkan halaman grafik horizontal kelembapan."""
    if not oled:
        return
    oled.fill(0)
    oled.text("KELEMBAPAN (%)", 0, 0)
    oled.hline(0, 10, 128, 1)
    oled.text("Nilai: {:.1f} %".format(lembap), 0, 20)
    oled.rect(0, 36, 120, 14, 1)
    lebar_isi = int((min(max(lembap, 0), 100) / 100) * 116)
    oled.fill_rect(2, 38, lebar_isi, 10, 1)
    oled.show()


def perbarui_sensor(sensor_dht, data_state, buzzer):
    """Membaca data fisik dari sensor dengan interval minimal 2 detik."""
    sekarang = time.ticks_ms()
    if time.ticks_diff(sekarang, data_state["waktu_baca"]) < 2000:
        return
    data_state["waktu_baca"] = sekarang
    try:
        sensor_dht.measure()
        data_state["suhu"] = sensor_dht.temperature()
        data_state["lembap"] = sensor_dht.humidity()
    except OSError:
        pass
    if data_state["suhu"] > BATAS_PANAS:
        bunyikan_buzzer(buzzer, 100)


def periksa_tombol_mode(tombol, data_state, buzzer):
    """Mendeteksi tombol navigasi dan berganti mode halaman."""
    if tombol.value() != 0:
        return
    data_state["mode"] = 1 if data_state["mode"] == 0 else 0
    bunyikan_buzzer(buzzer, 40)
    time.sleep_ms(300)


def perbarui_layar(oled, data_state):
    """Memilih rendering tampilan berdasarkan mode aktif."""
    if data_state["mode"] == 0:
        status = evaluasi_status(data_state["suhu"])
        tampilkan_data_ringkas(oled, data_state["suhu"], data_state["lembap"], status)
        return
    tampilkan_grafis_batang(oled, data_state["lembap"])


def inisialisasi_layar():
    """Menginisialisasi driver SSD1306 via bus I2C software."""
    try:
        import ssd1306
        i2c = SoftI2C(sda=Pin(PIN_SDA), scl=Pin(PIN_SCL))
        return ssd1306.SSD1306_I2C(128, 64, i2c)
    except Exception as galat:
        print("Peringatan: Layar OLED tidak terdeteksi:", galat)
        return None


def main():
    """Loop eksekusi utama stasiun cuaca MicroPython."""
    oled = inisialisasi_layar()
    buzzer = Pin(PIN_BUZZER, Pin.OUT, value=0)
    tombol = Pin(PIN_TOMBOL, Pin.IN, Pin.PULL_UP)
    sensor = dht.DHT11(Pin(PIN_DHT))

    data_state = {"suhu": 25.0, "lembap": 60.0, "mode": 0, "waktu_baca": 0}
    bunyikan_buzzer(buzzer, 80)

    while True:
        periksa_tombol_mode(tombol, data_state, buzzer)
        perbarui_sensor(sensor, data_state, buzzer)
        perbarui_layar(oled, data_state)
        time.sleep_ms(50)


if __name__ == "__main__":
    main()
