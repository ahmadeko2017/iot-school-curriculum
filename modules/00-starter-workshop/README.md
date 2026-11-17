# Modul 00: Starter Workshop (Walkie-Talkie Teks ESP-NOW)

Panduan praktikum kilat 90 menit merakit perangkat komunikator teks nirkabel berbasis protokol ESP-NOW tanpa membutuhkan kuota internet, router Wi-Fi, atau smartphone.

---

## 🎯 Tujuan Pembelajaran
1. Memahami konsep komunikasi nirkabel *peer-to-peer* menggunakan frekuensi radio 2.4 GHz ESP-NOW.
2. Mempelajari antarmuka display I2C (Inter-Integrated Circuit) pada layar OLED SSD1306.
3. Mengimplementasikan pembacaan tombol mekanik dengan teknik pencegahan *debouncing*.
4. Memberikan umpan balik audio dengan nada alert melalui buzzer.

---

## 📦 Daftar Komponen Per Kelompok (Hardware Kit)
- 1x ESP32 NodeMCU DevKit V1 Type-C (30-Pin)
- 1x Layar OLED 0.96 inci I2C SSD1306 (Resolusi 128x64)
- 3x Tombol Push Button Tactile (Pilihan Pesan 1, 2, 3)
- 1x Buzzer Pasif atau Aktif 5V
- 1x Breadboard 400 atau 830 titik
- 10x Kabel Jumper Male-to-Male
- 1x Kabel Data USB Type-C ke USB-A

---

## 🔌 Pemetaan Pin GPIO

| Komponen | Pin Komponen | Pin ESP32 NodeMCU | Keterangan Fungsi |
| :--- | :--- | :--- | :--- |
| **OLED SSD1306** | VCC | 3V3 (atau VIN 5V) | Jalur Daya Positif |
| | GND | GND | Jalur Ground Bersama |
| | SCL | GPIO 22 | Sinyal Clock I2C |
| | SDA | GPIO 21 | Sinyal Data I2C |
| **Tombol 1** | Pin A | GPIO 18 | Pesan: "Halo Sobat!" (INPUT_PULLUP) |
| | Pin B | GND | Terhubung ke Ground |
| **Tombol 2** | Pin A | GPIO 19 | Pesan: "Misi Siaga!" (INPUT_PULLUP) |
| | Pin B | GND | Terhubung ke Ground |
| **Tombol 3** | Pin A | GPIO 23 | Pesan: "Kode Rahasia" (INPUT_PULLUP) |
| | Pin B | GND | Terhubung ke Ground |
| **Buzzer** | Anoda (+) | GPIO 4 | Nada Notifikasi Pesan |
| | Katoda (-) | GND | Terhubung ke Ground |

Diagram wiring lengkap visual karakter dapat dilihat pada berkas [wiring-diagram.md](file:///c:/project/project-iot/modules/00-starter-workshop/wiring-diagram.md).

---

## 🚀 Langkah Instalasi & Uji Coba

### Opsi A: Menggunakan Arduino IDE
1. Buka file `src-arduino/esp_now_walkie_talkie.ino`.
2. Pasang library pihak ketiga melalui Library Manager:
   - **Adafruit SSD1306** by Adafruit
   - **Adafruit GFX Library** by Adafruit
3. Pilih board **DOIT ESP32 DEVKIT V1**.
4. Hubungkan ESP32 via kabel USB dan pilih port COM yang sesuai.
5. Klik **Upload** dan buka Serial Monitor pada baud rate **115200**.

### Opsi B: Menggunakan MicroPython & Thonny IDE
1. Pastikan firmware MicroPython telah terpasang pada ESP32.
2. Buka Thonny IDE dan sambungkan ke interpreter MicroPython (ESP32).
3. Salin berkas driver `src-micropython/ssd1306.py` ke dalam root direktori ESP32.
4. Buka berkas `src-micropython/main.py`, lalu klik tombol Run atau unggah sebagai `main.py`.

---

## 🔬 Cara Kerja Protokol ESP-NOW
ESP-NOW dikembangkan oleh Espressif Systems untuk pertukaran paket data cepat berukuran kecil (hingga 250 byte) tanpa melalui proses negosiasi *handshake* yang lama seperti koneksi Wi-Fi standar. Pada modul ini, pesan disiarkan secara *broadcast* ke alamat MAC `FF:FF:FF:FF:FF:FF` sehingga semua alat teman di satu ruangan kelas dapat langsung menerima pesan secara serempak.
