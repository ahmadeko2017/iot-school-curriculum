# Kurikulum Edukasi IoT Berbasis ESP32 NodeMCU (No-Smartphone)

Repositori resmi kurikulum pembelajaran *Internet of Things* (IoT) dan mikrokontroler bertingkat untuk jenjang SD, SMP, dan SMA berbasis mikrokontroler ESP32 NodeMCU DevKit V1 Type-C.

---

## 🎯 Filosofi Edukasi: No-Smartphone

Kurikulum ini dirancang dengan prinsip **100% Bebas Ketergantungan Smartphone**. Dalam kebanyakan lokakarya IoT konvensional, siswa kerap diminta memasang aplikasi Blynk, Tuya, atau MQTT viewer di ponsel masing-masing, yang berujung pada hilangnya fokus belajar akibat notifikasi media sosial atau kendala kompatibilitas sistem operasi ponsel.

Pada kurikulum ini:
1. **Interaksi Fisik Nyata**: Peserta didik berinteraksi langsung dengan perangkat keras: tombol mekanik, rotary encoder, potensiometer, dan sakelar geser.
2. **Umpan Balik Visual Lokal**: Informasi ditampilkan pada layar OLED SSD1306 0.96 inci I2C atau display LED lokal tanpa memerlukan layar ponsel.
3. **Komunikasi Nirkabel Mandiri**: Menggunakan protokol ESP-NOW (mesh peer-to-peer 2.4 GHz) untuk komunikasi antar-alat tanpa membutuhkan router Wi-Fi sekolah atau koneksi internet.
4. **Fokus Penuh pada Pemecahan Masalah**: Siswa mempelajari logika komputasi, struktur data, dan rekayasa elektronika dasar secara terarah di laptop atau komputer lab.

---

## 🏫 Struktur Silabus Jenjang Pendidikan

Kurikulum ini dirancang bertahap (scaffolded learning) dari konsep dasar hingga konsep jaringan tingkat lanjut:

| Jenjang / Modul | Durasi | Konsep Utama | Hardware Kunci | Proyek Akhir |
| :--- | :--- | :--- | :--- | :--- |
| **00. Starter Workshop** | 90 Menit | ESP-NOW Broadcast, Komunikasi Peer-to-Peer, I2C OLED | ESP32, OLED SSD1306, Tombol, Buzzer | Walkie-Talkie Teks ESP-NOW Mandiri |
| **01. Sekolah Dasar (SD)** | 4 Pertemuan | Input-Proses-Output, Sensor Cahaya (LDR), Logika Visual | ESP32, LDR, Modul Lampu Lalu Lintas LED | Lampu Lalu Lintas Pintar Otomatis |
| **02. Menengah Pertama (SMP)** | 6 Pertemuan | Variabel, Pembacaan Analog/Digital, Sensor Suhu/Lembap | ESP32, DHT11/DHT22, Layar OLED, Buzzer | Stasiun Cuaca Mini Mandiri |
| **03. Menengah Atas (SMA)** | 8 Pertemuan | Arsitektur Client-Server, Web Server Lokal, REST API | ESP32 (AP Mode), Sensor Kapasitif Tanah, Relai 5V DC | Telemetri Smart Farming Lokal |

---

## ⚡ Standar Perangkat Keras & Keselamatan 5V DC

Kesehatan dan keselamatan kerja (K3) peserta didik adalah prioritas mutlak. Seluruh modul dalam repositori ini tunduk pada aturan keselamatan ketat:

- **Batas Tegangan 5V DC**: Seluruh modul hanya menggunakan daya dari port USB Type-C laptop atau powerbank 5V DC bersertifikasi.
- **Nol Tegangan Tinggi AC (Zero 220V AC)**: Dilarang keras menghubungkan relai atau kabel ke jala-jala listrik PLN rumah atau sekolah.
- **Pinout Standar**: Dirancang spesifik untuk modul DOIT 30-Pin ESP32 NodeMCU DevKit V1 dengan spacing ramah breadboard.

Dokumentasi lengkap mengenai SOP keselamatan dapat dibaca pada [docs/safety-standards.md](file:///c:/project/project-iot/docs/safety-standards.md).

---

## 💻 Pendekatan Dual-Stack: Arduino C++ & MicroPython

Setiap modul pembelajaran menyediakan dua jalur implementasi kode sumber yang setara:
- **Arduino C++ (`.ino`)**: Cocok untuk memahami konsep register mikrokontroler, efisiensi memori, dan ekosistem industri C/C++.
- **MicroPython (`.py`)**: Sangat efektif bagi pemula yang mempelajari logika pemrograman Python dengan siklus *read-eval-print loop* (REPL) yang cepat via Thonny IDE.

---

## 📁 Struktur Repositori

```text
project-iot/
├── .github/
│   ├── ISSUE_TEMPLATE/       # Template pengajuan modul & bug
│   └── PULL_REQUEST_TEMPLATE.md
├── docs/
│   ├── safety-standards.md   # Standar K3 Lab & Pembatasan 5V DC
│   ├── instructor-guide.md   # Panduan Mengajar & Solusi Driver CH340
│   └── student-worksheet-sample.md # Template LKS Siswa Interaktif
├── modules/
│   ├── 00-starter-workshop/  # Lokakarya 90 Menit: Walkie-Talkie Teks ESP-NOW
│   │   ├── README.md
│   │   ├── wiring-diagram.md
│   │   ├── src-arduino/
│   │   └── src-micropython/
│   ├── 01-elementary-sd/     # Modul Siswa SD: Lampu Lalu Lintas Cerdas
│   │   ├── README.md
│   │   ├── src-arduino/
│   │   └── src-micropython/
│   ├── 02-junior-smp/        # Modul Siswa SMP: Stasiun Cuaca Mandiri
│   │   ├── README.md
│   │   ├── src-arduino/
│   │   └── src-micropython/
│   └── 03-senior-sma/        # Modul Siswa SMA: Web Server IoT Telemetri
│       ├── README.md
│       ├── src-arduino/
│       └── src-micropython/
├── .gitignore
├── LICENSE
└── README.md
```

---

## 🚀 Panduan Memulai Cepat untuk Instruktur

1. Pasang driver USB UART (CH340 atau CP2102) pada komputer lab.
2. Siapkan Arduino IDE 2.x dengan *board package* ESP32 by Espressif, atau pasang Thonny IDE untuk MicroPython.
3. Buka folder [modules/00-starter-workshop](file:///c:/project/project-iot/modules/00-starter-workshop) untuk menjalankan uji coba komunikasi instan tanpa konfigurasi Wi-Fi sekolah.
4. Baca panduan guru pada [docs/instructor-guide.md](file:///c:/project/project-iot/docs/instructor-guide.md).

---

## 📄 Lisensi

Proyek ini dirilis di bawah lisensi terbuka [MIT License](file:///c:/project/project-iot/LICENSE) dan bebas digunakan oleh institusi pendidikan, sekolah, serta komunitas robotika di seluruh Indonesia.
