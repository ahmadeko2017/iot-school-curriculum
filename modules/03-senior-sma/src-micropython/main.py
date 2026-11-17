"""
main.py: Server Web IoT Mandiri Pertanian Cerdas Menggunakan MicroPython

Tanggung Jawab:
- Menjalankan Access Point Wi-Fi lokal (SSID: ESP32-SmartFarm-Lab).
- Melayani permintaan HTTP socket untuk web dashboard dan REST API lokal.
- Membaca sensor kelembapan tanah analog (GPIO 34).
- Mengendalikan aktuator relai pompa 5V DC (GPIO 26) dan LED indikator (GPIO 27).
- Menampilkan IP dan metrik pada layar OLED SSD1306.

Target Hardware:
- ESP32 NodeMCU DevKit V1 Type-C
- Sensor Kelembapan: GPIO 34 (ADC 12-bit)
- Relai Pompa 5V: GPIO 26
- LED Pompa: GPIO 27
- Buzzer Alarm: GPIO 4
- Layar OLED: SDA GPIO 21, SCL GPIO 22
"""

import time
import socket
import network
from machine import Pin, ADC, SoftI2C

PIN_SDA = 21
PIN_SCL = 22
PIN_SENSOR = 34
PIN_RELAI = 26
PIN_LED = 27
PIN_BUZZER = 4


def bunyikan_buzzer(buzzer_pin, durasi_ms=60):
    """Membunyikan buzzer nada konfirmasi."""
    buzzer_pin.value(1)
    time.sleep_ms(durasi_ms)
    buzzer_pin.value(0)


def atur_pompa(pins, aktif):
    """Mengubah status relai dan lampu indikator pompa."""
    pins["relai"].value(1 if aktif else 0)
    pins["led"].value(1 if aktif else 0)
    bunyikan_buzzer(pins["buzzer"], 50)


def baca_kelembapan(adc):
    """Membaca nilai analog dan mengonversi ke persentase 0-100%."""
    raw = adc.read()
    persen = int((4095 - raw) / (4095 - 1500) * 100)
    return min(max(persen, 0), 100)


def perbarui_oled(oled, lembap, status_pompa):
    """Memperbarui visual informasi di layar OLED."""
    if not oled:
        return
    oled.fill(0)
    oled.text("SMART FARM SERVER", 0, 0)
    oled.hline(0, 10, 128, 1)
    oled.text("IP: 192.168.4.1", 0, 18)
    oled.text("Lembap: {} %".format(lembap), 0, 32)
    oled.text("Pompa : {}".format("AKTIF" if status_pompa else "MATI"), 0, 48)
    oled.show()


def buat_html(lembap, pompa_aktif):
    """Menghasilkan dokumen HTML responsif untuk peramban komputer lab."""
    status_teks = "MENYIRAM" if pompa_aktif else "STANDBY"
    return (
        "<!DOCTYPE html><html><head><meta charset='utf-8'>"
        "<meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<title>Smart Farm ESP32</title>"
        "<style>body{font-family:sans-serif;text-align:center;padding:24px;background:#eef2f5;}"
        ".kotak{background:#fff;padding:20px;border-radius:10px;display:inline-block;}"
        "button{padding:12px 24px;background:#0d6efd;color:#fff;border:none;border-radius:6px;cursor:pointer;}"
        "</style></head><body><div class='kotak'>"
        "<h2>Monitoring Smart Farm</h2>"
        "<p>Kelembapan Tanah: <b>" + str(lembap) + "%</b></p>"
        "<p>Status Pompa: <b>" + status_teks + "</b></p>"
        "<form action='/toggle' method='POST'><button type='submit'>Sakelar Pompa</button></form>"
        "</div></body></html>"
    )


def tangani_klien(client, state, pins, oled):
    """Menerima dan memproses HTTP request dari peramban."""
    try:
        req = client.recv(1024).decode("utf-8")
        if "POST /toggle" in req:
            state["pompa"] = not state["pompa"]
            atur_pompa(pins, state["pompa"])
            perbarui_oled(oled, state["lembap"], state["pompa"])
            client.send("HTTP/1.1 303 See Other\r\nLocation: /\r\n\r\n")
            return
        if "GET /api/status" in req:
            resp = '{{"kelembapan": {}, "pompa": {}}}'.format(state["lembap"], "true" if state["pompa"] else "false")
            client.send("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" + resp)
            return
        html = buat_html(state["lembap"], state["pompa"])
        client.send("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + html)
    except Exception as galat:
        print("Galat soket klien:", galat)
    finally:
        client.close()


def inisialisasi_ap():
    """Mengaktifkan Wi-Fi Access Point mandiri."""
    ap = network.WLAN(network.AP_IF)
    ap.active(True)
    ap.config(essid="ESP32-SmartFarm-Lab", password="edukasi123")
    print("Access Point Aktif. IP:", ap.ifconfig()[0])
    return ap


def inisialisasi_oled():
    """Menginisialisasi modul layar OLED via I2C."""
    try:
        import ssd1306
        i2c = SoftI2C(sda=Pin(PIN_SDA), scl=Pin(PIN_SCL))
        return ssd1306.SSD1306_I2C(128, 64, i2c)
    except Exception:
        return None


def inisialisasi_server_socket():
    """Menginisialisasi socket TCP port 80 dengan timeout 0.5 detik."""
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind(("", 80))
    srv.listen(5)
    srv.settimeout(0.5)
    return srv


def main():
    """Loop eksekusi utama web server mandiri."""
    oled = inisialisasi_oled()
    pins = {
        "relai": Pin(PIN_RELAI, Pin.OUT, value=0),
        "led": Pin(PIN_LED, Pin.OUT, value=0),
        "buzzer": Pin(PIN_BUZZER, Pin.OUT, value=0),
    }
    adc = ADC(Pin(PIN_SENSOR))
    adc.atten(ADC.ATTN_11DB)
    inisialisasi_ap()
    srv = inisialisasi_server_socket()

    state = {"lembap": 50, "pompa": False}
    perbarui_oled(oled, state["lembap"], state["pompa"])

    while True:
        state["lembap"] = baca_kelembapan(adc)
        perbarui_oled(oled, state["lembap"], state["pompa"])
        try:
            cl, _ = srv.accept()
            tangani_klien(cl, state, pins, oled)
        except OSError:
            pass


if __name__ == "__main__":
    main()
