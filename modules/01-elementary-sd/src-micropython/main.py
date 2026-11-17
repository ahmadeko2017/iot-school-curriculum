"""
main.py: Lampu Lalu Lintas Pintar Menggunakan MicroPython

Tanggung Jawab:
- Mengendalikan lampu lalu lintas interaktif dengan logika Input-Proses-Output.
- Membaca nilai analog LDR (GPIO 34) untuk deteksi kondisi malam.
- Mendeteksi tombol penyeberang jalan (GPIO 18) dan membunyikan alarm suara.

Target Hardware:
- ESP32 NodeMCU DevKit V1 Type-C
- LED: Merah (GPIO 25), Kuning (GPIO 26), Hijau (GPIO 27)
- Sensor LDR: GPIO 34 (ADC 12-bit)
- Tombol: GPIO 18 (Pull-up)
- Buzzer: GPIO 4
"""

import time
from machine import Pin, ADC

PIN_LED_MERAH = 25
PIN_LED_KUNING = 26
PIN_LED_HIJAU = 27
PIN_LDR = 34
PIN_TOMBOL = 18
PIN_BUZZER = 4
AMBANG_MALAM = 1500


def atur_lampu(merah_pin, kuning_pin, hijau_pin, m, k, h):
    """Mengatur status hidup-mati ketiga lampu indikator."""
    merah_pin.value(1 if m else 0)
    kuning_pin.value(1 if k else 0)
    hijau_pin.value(1 if h else 0)


def bunyikan_bip(buzzer_pin, jumlah, jeda_ms=100):
    """Membunyikan buzzer berulang kali sebagai sinyal penyeberangan."""
    for _ in range(jumlah):
        buzzer_pin.value(1)
        time.sleep_ms(jeda_ms)
        buzzer_pin.value(0)
        time.sleep_ms(jeda_ms)


def jalankan_penyeberangan(pins):
    """Fase aman bagi pejalan kaki menyeberang jalan."""
    atur_lampu(pins["m"], pins["k"], pins["h"], False, True, False)
    time.sleep_ms(1500)
    atur_lampu(pins["m"], pins["k"], pins["h"], True, False, False)
    bunyikan_bip(pins["buzzer"], 5, 150)
    time.sleep_ms(1000)


def jalankan_mode_malam(pins):
    """Lampu kuning berkedip lambat untuk tanda hati-hati di malam hari."""
    atur_lampu(pins["m"], pins["k"], pins["h"], False, True, False)
    time.sleep_ms(500)
    atur_lampu(pins["m"], pins["k"], pins["h"], False, False, False)
    time.sleep_ms(500)


def cek_permintaan_seberang(pins):
    """Mengecek apakah pejalan kaki menekan tombol saat lampu hijau."""
    for _ in range(40):
        if pins["tombol"].value() == 0:
            jalankan_penyeberangan(pins)
            return True
        time.sleep_ms(100)
    return False


def jalankan_siklus_normal(pins):
    """Siklus pergantian lampu standar siang hari."""
    atur_lampu(pins["m"], pins["k"], pins["h"], False, False, True)
    if cek_permintaan_seberang(pins):
        return
    atur_lampu(pins["m"], pins["k"], pins["h"], False, True, False)
    time.sleep_ms(1500)
    atur_lampu(pins["m"], pins["k"], pins["h"], True, False, False)
    time.sleep_ms(3000)


def main():
    """Inisialisasi komponen dan loop utama sistem lampu lalu lintas."""
    pins = {
        "m": Pin(PIN_LED_MERAH, Pin.OUT, value=0),
        "k": Pin(PIN_LED_KUNING, Pin.OUT, value=0),
        "h": Pin(PIN_LED_HIJAU, Pin.OUT, value=0),
        "buzzer": Pin(PIN_BUZZER, Pin.OUT, value=0),
        "tombol": Pin(PIN_TOMBOL, Pin.IN, Pin.PULL_UP),
    }
    adc_ldr = ADC(Pin(PIN_LDR))
    adc_ldr.atten(ADC.ATTN_11DB)

    bunyikan_bip(pins["buzzer"], 2, 80)
    while True:
        cahaya = adc_ldr.read()
        if cahaya < AMBANG_MALAM:
            jalankan_mode_malam(pins)
            continue
        jalankan_siklus_normal(pins)


if __name__ == "__main__":
    main()
