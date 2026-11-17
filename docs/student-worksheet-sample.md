# Lembar Kerja Siswa (LKS): Eksperimen Komunikasi IoT Mandiri

Nama Kelompok: ____________________________________  
Nama Anggota:  
1. ___________________________ (Peran: Hardware Architect)  
2. ___________________________ (Peran: Lead Coder)  
3. ___________________________ (Peran: Quality Tester)  

Kelas / Jenjang : ____________________________________  
Tanggal Sesi    : ____________________________________  
Nomor Modul     : Modul 00 (Starter Workshop - Walkie-Talkie ESP-NOW)  

---

## 🎯 Sasaran Belajar
1. Memahami cara menghubungkan layar OLED SSD1306 dengan komunikasi I2C.
2. Mengamati proses pengiriman sinyal radio nirkabel ESP-NOW tanpa router Wi-Fi.
3. Melakukan debugging rangkaian jika terjadi kendala hardware atau logika.

---

## 🔍 Bagian 1: Checklist Pemeriksaan Rangkaian (Safety Check)
Beri tanda centang (v) sebelum kabel USB dicolokkan ke komputer:

- [ ] Kabel USB dilepas saat menyusun komponen di breadboard.
- [ ] Pin `VCC` pada layar OLED terhubung ke pin `3V3` atau `VIN` ESP32 (bukan ke pin data).
- [ ] Pin `GND` pada layar OLED, tombol, dan buzzer terhubung ke pin `GND` ESP32.
- [ ] Pin `SDA` OLED terhubung ke pin `GPIO 21`, dan pin `SCL` ke pin `GPIO 22`.
- [ ] Rangkaian telah diperiksa bersama guru atau fasilitator kelas.

---

## 🧪 Bagian 2: Lembar Pengujian dan Data Eksperimen

Lakukan pengujian tombol siaran pesan, lalu catat apa yang terjadi pada layar OLED dan buzzer:

| Percobaan Ke- | Tombol yang Ditekan | Pesan Muncul di Layar Teman? (Ya / Tidak) | Buzzer Berbunyi? (Ya / Tidak) | Jarak Antar Meja (Perkiraan Meter) |
| :---: | :---: | :---: | :---: | :---: |
| 1 | Tombol 1 (Halo Sobat!) | [ ] Ya &nbsp; [ ] Tidak | [ ] Ya &nbsp; [ ] Tidak | 1 Meter |
| 2 | Tombol 2 (Misi Siaga!) | [ ] Ya &nbsp; [ ] Tidak | [ ] Ya &nbsp; [ ] Tidak | 3 Meter |
| 3 | Tombol 3 (Pesan Rahasia) | [ ] Ya &nbsp; [ ] Tidak | [ ] Ya &nbsp; [ ] Tidak | 5 Meter (Luar Pintu Kelas) |

---

## 💡 Bagian 3: Pertanyaan Analisis & Logika Komputasi

Jawablah pertanyaan berikut dengan berdiskusi bersama anggota kelompokmu:

1. **Mengapa walkie-talkie ini bisa mengirim pesan meskipun tidak ada koneksi internet atau router Wi-Fi di sekolah kita?**  
   *Jawaban Kelompok:*  
   __________________________________________________________________________________________  
   __________________________________________________________________________________________  

2. **Apa yang terjadi jika kabel SDA pada pin GPIO 21 dicabut saat program sedang berjalan?**  
   *Jawaban Kelompok:*  
   __________________________________________________________________________________________  
   __________________________________________________________________________________________  

3. **Tantangan Kreatif**: Jika kamu ingin menambahkan pesan baru nomor 4, bagian baris kode mana yang harus kamu modifikasi?  
   *Jawaban Kelompok:*  
   __________________________________________________________________________________________  
   __________________________________________________________________________________________  

---

## ⭐ Bagian 4: Refleksi Pengalaman Belajar
- Apa bagian yang paling menyenangkan dari percobaan hari ini?  
  __________________________________________________________________________________________  
- Apa kesulitan terbesar yang berhasil kelompok kalian selesaikan?  
  __________________________________________________________________________________________  

**Tanda Tangan Instruktur / Guru:** _______________________
