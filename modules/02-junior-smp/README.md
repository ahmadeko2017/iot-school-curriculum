# Modul 02: Tingkat Sekolah Menengah Pertama (SMP) - Stasiun Cuaca Mandiri

Modul pembelajaran untuk siswa SMP yang berfokus pada pengolahan data sensor lingkungan fisik, visualisasi pada layar OLED grafis, dan logika pengkondisian bersyarat (If-Else & Ambang Batas).

---

## 🎯 Capaian Pembelajaran
1. Memahami cara kerja sensor digital satu-kabel (*single-wire digital*) DHT11/DHT22.
2. Mempelajari konsep variabel, tipe data desimal (*float*), dan konversi satuan fisik (Celsius & Persentase).
3. Merancang antarmuka informasi grafis pada layar OLED SSD1306 tanpa ketergantungan pada layar ponsel.
4. Menerapkan sistem peringatan dini (*early warning alert*) audio-visual jika suhu ruangan melebihi batas nyaman.

---

## 📦 Komponen Hardware
- 1x ESP32 NodeMCU DevKit V1 Type-C
- 1x Sensor Suhu & Kelembapan DHT11 atau DHT22
- 1x Layar OLED SSD1306 0.96 inci I2C (128x64)
- 1x Tombol Push Button (Ganti Tampilan Layar: Halaman Detail vs Status Ringkas)
- 1x Buzzer (Alarm Peringatan Suhu Panas)
- 1x Resistor 4.7k - 10k ohm (Pull-up data DHT jika menggunakan sensor 4-pin mentah)
- 1x Breadboard & Kabel Jumper

---

## 🔌 Pemetaan Pin GPIO

| Komponen | Pin ESP32 | Tipe Pin | Keterangan |
| :--- | :--- | :--- | :--- |
| **OLED SDA** | GPIO 21 | I2C Data | Jalur data layar |
| **OLED SCL** | GPIO 22 | I2C Clock | Jalur clock layar |
| **Sensor DHT Data** | GPIO 15 | Digital Bi-directional | Pembacaan sinyal suhu & lembap |
| **Tombol Halaman** | GPIO 18 | Digital Input (Pull-up) | Tombol ganti tampilan UI |
| **Buzzer Alarm** | GPIO 4 | Digital Output | Alarm peringatan suhu tinggi |

---

## 💡 Fitur Perangkat Lunak
- **Halaman 1 (Ringkasan)**: Menampilkan Suhu (C), Kelembapan (%), dan Indeks Kenyamanan ("Sejuk", "Nyaman", atau "Panas").
- **Halaman 2 (Bar Grafis)**: Menampilkan visualisasi persentase kelembapan dalam bentuk kotak indikator grafis.
- **Alarm Ambang Batas**: Jika suhu melampaui 33.0 derajat Celsius, buzzer berbunyi berkala dan indikator bahaya berkedip di layar.
