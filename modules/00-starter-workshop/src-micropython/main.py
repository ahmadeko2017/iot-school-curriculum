"""
main.py: Walkie-Talkie Teks ESP-NOW Menggunakan MicroPython

Tanggung Jawab:
- Mengendalikan komunikasi peer-to-peer tanpa router via modul espnow.
- Menampilkan pesan status dan teks masuk pada layar OLED SSD1306.
- Membaca penekanan tombol tactile dengan proteksi debounce waktu.
- Memberikan sinyal suara alert menggunakan buzzer aktif/pasif.

Target Hardware:
- ESP32 NodeMCU DevKit V1 Type-C (DOIT 30-Pin)
- OLED I2C: SDA=GPIO 21, SCL=GPIO 22
- Tombol: GPIO 18, GPIO 19, GPIO 23 (Pull-up internal)
- Buzzer: GPIO 4
"""

import time
import network
import espnow
from machine import Pin, SoftI2C
import ssd1306

PIN_SDA = 21
PIN_SCL = 22
PIN_BTN_1 = 18
PIN_BTN_2 = 19
PIN_BTN_3 = 23
PIN_BUZZER = 4
MAC_BROADCAST = b"\xff\xff\xff\xff\xff\xff"
DEBOUNCE_MS = 300


def bunyikan_buzzer(buzzer_pin, durasi_ms=100):
    """Membunyikan buzzer selama durasi tertentu."""
    buzzer_pin.value(1)
    time.sleep_ms(durasi_ms)
    buzzer_pin.value(0)


def perbarui_tampilan(oled, judul, baris1, baris2=""):
    """Menampilkan teks 3 baris pada layar OLED SSD1306."""
    if not oled:
        return
    oled.fill(0)
    oled.text(judul, 0, 0)
    oled.hline(0, 10, 128, 1)
    oled.text(baris1, 0, 22)
    oled.text(baris2, 0, 42)
    oled.show()


def inisialisasi_layar():
    """Menginisialisasi bus I2C dan layar OLED."""
    try:
        i2c = SoftI2C(sda=Pin(PIN_SDA), scl=Pin(PIN_SCL))
        oled = ssd1306.SSD1306_I2C(128, 64, i2c)
        perbarui_tampilan(oled, "ESP-NOW WALKIE", "Siap beraksi!", "Tekan tombol 1-3")
        return oled
    except Exception as galat:
        print("Galat inisialisasi OLED:", galat)
        return None


def inisialisasi_espnow():
    """Mengaktifkan antarmuka Wi-Fi STA dan protokol ESP-NOW."""
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.disconnect()

    en = espnow.ESPNow()
    en.active(True)
    try:
        en.add_peer(MAC_BROADCAST)
    except OSError:
        pass
    return en


def kirim_siaran(en, oled, buzzer, pesan):
    """Mengirim pesan broadcast dan memperbarui tampilan."""
    try:
        en.send(MAC_BROADCAST, pesan)
        perbarui_tampilan(oled, "TERKIRIM (SIARAN)", pesan, "Menunggu balasan...")
        bunyikan_buzzer(buzzer, 50)
    except Exception as galat:
        print("Galat pengiriman pesan:", galat)


def proses_pesan_masuk(en, oled, buzzer):
    """Mengecek paket pesan yang masuk via ESP-NOW."""
    host, pesan = en.recv(0)
    if not pesan:
        return
    teks = pesan.decode("utf-8") if isinstance(pesan, bytes) else str(pesan)
    perbarui_tampilan(oled, "PESAN MASUK!", teks, "Dari: Teman Lab")
    bunyikan_buzzer(buzzer, 150)


def tangani_tombol(pin, teks_pesan, konteks):
    """Mendeteksi tombol ditekan dengan proteksi debouncing."""
    if pin.value() != 0:
        return
    sekarang = time.ticks_ms()
    if time.ticks_diff(sekarang, konteks["waktu_terakhir"]) < DEBOUNCE_MS:
        return
    konteks["waktu_terakhir"] = sekarang
    kirim_siaran(konteks["en"], konteks["oled"], konteks["buzzer"], teks_pesan)


def periksa_input(tombol_list, konteks):
    """Memindai seluruh tombol daftar pesan."""
    for pin, pesan in tombol_list:
        tangani_tombol(pin, pesan, konteks)


def main():
    """Fungsi utama program walkie-talkie MicroPython."""
    oled = inisialisasi_layar()
    buzzer = Pin(PIN_BUZZER, Pin.OUT, value=0)
    en = inisialisasi_espnow()

    tombol_list = [
        (Pin(PIN_BTN_1, Pin.IN, Pin.PULL_UP), "Halo Sobat!"),
        (Pin(PIN_BTN_2, Pin.IN, Pin.PULL_UP), "Siaga Lab!"),
        (Pin(PIN_BTN_3, Pin.IN, Pin.PULL_UP), "Misi Sukses!"),
    ]
    konteks = {"en": en, "oled": oled, "buzzer": buzzer, "waktu_terakhir": 0}

    bunyikan_buzzer(buzzer, 80)
    while True:
        proses_pesan_masuk(en, oled, buzzer)
        periksa_input(tombol_list, konteks)
        time.sleep_ms(20)


if __name__ == "__main__":
    main()
