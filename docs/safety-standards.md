# Standar Operasional Prosedur (SOP) Keselamatan Listrik 5V DC di Laboratorium Sekolah

Dokumen ini memuat panduan keselamatan wajib bagi guru, instruktur, dan peserta didik selama melaksanakan praktikum mikrokontroler dan Internet of Things (IoT).

---

## 1. Kebijakan Mutlak Tegangan Rendah (5V DC Only)

Keselamatan peserta didik adalah prioritas tertinggi dalam kurikulum ini. Semua kegiatan eksperimen dirancang hanya menggunakan arus searah bertegangan ekstra rendah (SELV - *Safety Extra-Low Voltage*).

### Batasan Tegangan Resmi
- **Tegangan Operasional Maksimal**: 5.0 Volt Direct Current (DC).
- **Tegangan Logika GPIO ESP32**: 3.3 Volt DC (Toleransi input maksimal 3.6V DC).
- **Arus Maksimal per Pin GPIO**: 12 mA (Rekomendasi aman: 6 mA).

### Larangan Keras (Zero Tolerance)
1. **Dilarang Menghubungkan ke Jala-Jala Listrik PLN (220V AC)**: Modul relay atau sakelar apapun DILARANG dikaitkan ke stopkontak dinding, lampu penerangan rumah tangga, atau beban 220V AC.
2. **Dilarang Menggunakan Catu Daya Tidak Teregulasi**: Hindari penggunaan trafo non-stabil atau aki kendaraan tanpa regulator tegangan step-down yang teruji.
3. **Dilarang Membuka Casing Adaptor**: Jangan pernah membongkar pengisi daya USB (charger) di lingkungan sekolah.

---

## 2. Sumber Daya yang Diizinkan

Seluruh modul dan alat peraga wajib ditenagai oleh salah satu dari sumber berikut:

1. **Port USB Komputer / Laptop Lab**:
   - Standar port USB 2.0 / USB 3.0 dengan pembatas arus otomatis (500 mA s.d. 900 mA).
2. **Powerbank Berkualitas dengan Proteksi Sirkuit**:
   - Powerbank bersertifikasi resmi yang memiliki sirkuit proteksi arus lebih (OCP) dan proteksi hubung singkat (SCP).
3. **Adaptor USB 5V DC Terisolasi**:
   - Menggunakan adaptor dinding 5V 1A hingga 2A dengan insulasi ganda dan label SNI/CE.

---

## 3. Pencegahan Hubung Singkat (Short Circuit)

ESP32 NodeMCU memiliki chip regulator onboard (AMS1117-3.3 atau ME6211) yang rentan rusak permanen bila terjadi hubung singkat antara pin `VIN`/`5V` atau `3V3` dengan `GND`.

### Aturan Merangkai Sirkuit
- **Matikan Daya Saat Merangkai**: Kabel USB Type-C WAJIB dicabut dari komputer sebelum peserta didik memasang atau memindahkan kabel jumper di atas breadboard.
- **Pemeriksaan Jalur Bersama Instruktur**: Sebelum kabel USB dicolokkan kembali, peserta didik wajib memeriksa jalur polaritas positif (VCC) dan negatif (GND) bersama rekan kelompok atau guru.
- **Kabel Jumper Berkualitas**: Ganti kabel dupont jumper yang ujung pinnya longgar, serabutnya terkelupas, atau isolasinya retak.
- **Pemisahan Breadboard**: Pastikan papan breadboard diletakkan di atas permukaan isolator (kayu, karet, atau plastik), bebas dari serpihan kawat konduktor atau klip kertas logam.

---

## 4. Prosedur Tanggap Darurat Lab

Jika terjadi kesalahan perakitan komponen atau kegagalan perangkat:

1. **Tindakan Pertama (Cabut Seketika)**:
   - Segera lepaskan kabel USB dari komputer atau powerbank tanpa ragu.
2. **Identifikasi Suhu Komponen**:
   - Jangan menyentuh chip mikrokontroler jika tercium aroma hangus atau muncul asap tipis. Tunggu selama 1 menit hingga komponen dingin.
3. **Pemberitahuan Instruktur**:
   - Siswa wajib melapor kepada guru pengampu tanpa rasa takut disalahkan. Kesalahan perakitan adalah bagian dari proses belajar.
4. **Isolasi Modul Bermasalah**:
   - Tandai modul yang terindikasi rusak untuk dilakukan pengujian resistansi menggunakan multimeter digital oleh teknisi lab sebelum digunakan kembali.

---

## 5. Perlindungan Privasi & Bebas Data Pribadi (Zero PII)

Sesuai Undang-Undang Perlindungan Data Pribadi (UU PDP):
- Seluruh kode program, firmware ESP-NOW, dan dashboard lokal DILARANG meminta, menyimpan, atau menyiarkan nama lengkap siswa, NISN, nomor telepon, atau data identitas pribadi.
- Identifikasi perangkat dalam jaringan eksperimen wajib menggunakan nama samaran kelompok atau ID acak (contoh: `STASIUN-A`, `TIM-01`).
