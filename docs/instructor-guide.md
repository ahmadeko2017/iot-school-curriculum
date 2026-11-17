# Panduan Instruktur & Guru: Workshop IoT ESP32 (Sesi 90 Menit)

Panduan praktis untuk mendampingi guru dan fasilitator dalam menyelenggarakan sesi belajar interaktif 90 menit tanpa kepanikan teknis.

---

## 1. Manajemen Kelas & Pembagian Peran

Agar sesi 90 menit berjalan tertib dan setiap siswa terlibat aktif, gunakan formasi kelompok kecil berisi 2 hingga 3 siswa per meja peraga.

### Tiga Peran Kunci dalam Kelompok
1. **Hardware Architect**: Bertanggung jawab memasang kabel jumper, memeriksa breadboard, dan memastikan polaritas VCC/GND tidak terbalik.
2. **Lead Coder**: Bertanggung jawab mengetik atau memodifikasi kode di Arduino IDE atau Thonny IDE, serta mengunggah firmware.
3. **Quality Tester**: Memperhatikan serial monitor, menguji respons tombol, mengamati layar OLED, dan mencatat hasil pada Lembar Kerja Siswa.

Peran dapat dirotasi setiap kali berpindah materi eksperimen.

---

## 2. Susunan Waktu Sesi 90 Menit (Rundown Terstruktur)

| Alokasi Waktu | Durasi | Agenda Pembelajaran | Target Capaian |
| :--- | :--- | :--- | :--- |
| **Menit 00 - 15** | 15 Menit | Pembukaan, Ice Breaking & Demo Interaktif | Rasa penasaran siswa bangkit melihat demo walkie-talkie menyala |
| **Menit 15 - 35** | 20 Menit | Perakitan Hardware (Wiring Terpandu) | Breadboard terpasang rapi: OLED, Tombol, Buzzer |
| **Menit 35 - 55** | 20 Menit | Penjelasan Logika & Flashing Firmware Pertama | Board terdeteksi di COM port dan firmware berhasil diunggah |
| **Menit 55 - 75** | 20 Menit | Eksperimen Komunikasi Broadcast ESP-NOW | Siswa berhasil berkirim pesan antar-meja tanpa router Wi-Fi |
| **Menit 75 - 85** | 10 Menit | Tantangan Modifikasi Kreatif (Mini Challenge) | Menambahkan variasi nada buzzer atau pesan teks unik |
| **Menit 85 - 90** | 5 Menit | Refleksi, Evaluasi & Pengemasan Alat | LKS diisi, komponen dirapikan ke dalam kotak praktikum |

---

## 3. Trik Instalasi Driver USB UART (CH340 & CP2102)

Kendala paling umum di lab komputer sekolah adalah board mikrokontroler tidak terdeteksi pada daftar port serial.

### Identifikasi Chip Komunikasi di Board ESP32
- **WCH CH340G / CH340C**: Chip persegi panjang kecil dengan tulisan "WCH" atau "CH340". Banyak ditemukan pada board ekonomis.
- **Silicon Labs CP2102**: Chip persegi kecil dengan permukaan datar dan logo Silicon Labs.

### Solusi Praktis per Sistem Operasi
1. **Windows**:
   - Buka *Device Manager* (`devmgmt.msc`).
   - Cari bagian **Ports (COM & LPT)**. Jika terdapat tanda seru kuning atau perangkat tidak dikenal, pasang installer resmi *CH341SER.EXE* atau *CP210x_Windows_Drivers*.
   - Jika port berubah setiap kali cabut-colok, tetapkan port USB yang sama di hub komputer lab.
2. **macOS**:
   - Pasang driver CH34xVCPDriver versi modern yang kompatibel dengan macOS Sonoma / Sequoia.
   - Izinkan ekstensi sistem di menu *System Settings > Privacy & Security*.
3. **Linux / ChromeOS Lab**:
   - Pengguna Linux biasanya tidak memerlukan instalasi driver, tetapi memerlukan izin akses grup serial:
     ```bash
     sudo usermod -a -G dialout $USER
     ```

---

## 4. Trik Jitu Mengatasi Masalah Flashing & Hardware

### Masalah 1: "A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header"
- **Penyebab**: Kapasitor otomatis reset (auto-download circuit) pada beberapa board DOIT 30-Pin bernilai terlalu kecil.
- **Trik Instruktur**:
  1. Saat Arduino IDE menampilkan tulisan `Connecting........_____.....`, minta siswa **menekan dan menahan tombol BOOT** pada board ESP32.
  2. Lepas tombol BOOT seketika setelah proses `Writing at 0x00010000... (10 %)` dimulai.

### Masalah 2: Layar OLED SSD1306 Tetap Gelap (Blank)
- **Cek 1 (Alamat I2C)**: Sebagian besar OLED menggunakan alamat `0x3C`, namun beberapa pabrikan menggunakan `0x3D`. Jalankan skrip *I2C Scanner* jika layar tidak bereaksi.
- **Cek 2 (Kabel Tertukar)**: Pastikan kabel SDA masuk ke GPIO 21 dan SCL masuk ke GPIO 22 pada ESP32.
- **Cek 3 (Tegangan VCC)**: Beberapa OLED memerlukan 5V, sementara sebagian lain bekerja di 3.3V. Gunakan pin 3.3V terlebih dahulu untuk keamanan.

### Masalah 3: Buzzer Berbunyi Terus Menerus Tanpa Henti
- **Penyebab**: Siswa menggunakan Buzzer Aktif pada pin yang memiliki logika default HIGH, atau polaritas terbalik.
- **Solusi**: Pastikan pin GPIO didefinisikan sebagai OUTPUT dan diberi nilai `LOW` pada fungsi `setup()`.

---

## 5. Tips Pedagogis untuk Guru
- **Jangan Berikan Solusi Instan**: Ajak siswa menganalisis diagram wiring saat terjadi galat, misalnya "Coba telusuri kabel warna kuning ini, dari mana jalurnya dan ke lubang mana ia bermuara?".
- **Rayakan Kegagalan Kecil**: Jika layar tidak menyala, sampaikan bahwa mencari kutub kabel yang tertukar adalah pekerjaan nyata insinyur elektronika sehari-hari.
