# Modul 03: Tingkat Sekolah Menengah Atas (SMA) - Server IoT & Telemetri Mandiri

Modul pembelajaran tingkat lanjut untuk siswa SMA/SMK yang memperkenalkan arsitektur Jaringan Komputer, Protokol HTTP, Pembuatan Web Server Tertanam (*Embedded Web Server*), dan REST API mandiri tanpa koneksi internet.

---

## 🎯 Capaian Pembelajaran
1. Memahami arsitektur *Client-Server* pada sistem embedded.
2. Mengonfigurasi ESP32 sebagai Wi-Fi Access Point (AP Mode) mandiri.
3. Membangun antarmuka dashboard monitoring berbasis web (HTML/CSS ringan) yang disajikan langsung oleh chip ESP32 ke peramban komputer lab.
4. Membuat endpoint REST API sederhana dengan format respons JSON untuk otomatisasi pompa irigasi 5V DC.

---

## 📦 Komponen Hardware
- 1x ESP32 NodeMCU DevKit V1 Type-C
- 1x Sensor Kelembapan Tanah Kapasitif (atau Modul Potensiometer/LDR Simulasi)
- 1x Modul Relai 5V DC Beban Rendah (Hanya dihubungkan ke LED atau Pompa Mini 5V DC)
- 1x Layar OLED SSD1306 0.96 inci I2C
- 1x Buzzer (Sinyal Alarm Air Habis)
- 1x Breadboard & Kabel Jumper

> [!IMPORTANT]
> **Standar Keselamatan 5V DC**: Modul relai pada praktikum ini HANYA boleh mengendalikan pompa mini 5V DC atau lampu LED 5V DC. DILARANG KERAS menyambungkan kabel terminal relai ke colokan listrik PLN 220V AC.

---

## 🔌 Pemetaan Pin GPIO

| Komponen | Pin ESP32 | Tipe Pin | Keterangan |
| :--- | :--- | :--- | :--- |
| **OLED SDA** | GPIO 21 | I2C Data | Menampilkan IP Server (192.168.4.1) |
| **OLED SCL** | GPIO 22 | I2C Clock | Sinyal clock layar |
| **Sensor Tanah** | GPIO 34 | Analog Input (ADC1) | Deteksi kadar air tanah (0 - 4095) |
| **Kendali Pompa (Relai)** | GPIO 26 | Digital Output | Pengendali aktif pompa 5V DC |
| **LED Indikator Pompa** | GPIO 27 | Digital Output | Lampu indikator status irigasi |
| **Buzzer Alarm** | GPIO 4 | Digital Output | Sinyal peringatan tanah terlalu kering |

---

## 🌐 Arsitektur Jaringan Mandiri (Offline Access Point)
- **Nama Sinyal Wi-Fi (SSID)**: `ESP32-SmartFarm-Lab`
- **Kata Sandi Wi-Fi**: `edukasi123` (Kredensial lab umum non-rahasia)
- **Alamat IP Default ESP32**: `192.168.4.1`
- **Cara Akses**:
  1. Hubungkan Wi-Fi laptop lab ke jaringan `ESP32-SmartFarm-Lab`.
  2. Buka web browser (Chrome / Edge / Firefox) dan kunjungi `http://192.168.4.1`.
  3. Siswa dapat memantau grafik kelembapan dan menekan tombol sakelar pompa langsung dari browser.
