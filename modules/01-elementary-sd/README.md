# Modul 01: Tingkat Sekolah Dasar (SD) - Lampu Lalu Lintas Pintar

Modul pembelajaran mikrokontroler untuk siswa jenjang Sekolah Dasar dengan penekanan pada konsep komputasi dasar: **Input, Proses, dan Output (IPO)**.

---

## 🎯 Capaian Pembelajaran
1. Memahami alur kerja logika komputasi: Input (Sensor/Tombol) -> Proses (ESP32) -> Output (Lampu/Buzzer).
2. Mengenal perbedaan sinyal Digital (Tombol ditekan/dilepas) dan sinyal Analog (Tingkat kecerahan cahaya LDR).
3. Melatih keterampilan motorik halus dan ketelitian dalam merangkai kabel breadboard.

---

## 📦 Komponen Hardware
- 1x ESP32 NodeMCU DevKit V1 Type-C
- 1x Modul LED Lampu Lalu Lintas (Merah, Kuning, Hijau) atau 3 buah LED terpisah + resistor 220 ohm
- 1x Sensor Cahaya LDR (Photoresistor) + Resistor 10k ohm (atau Modul LDR 3-pin)
- 1x Push Button Tactile (Tombol Penyeberang Jalan / Pelican Crossing)
- 1x Buzzer (Sinyal Suara Ramah Tunanetra)
- 1x Breadboard & Kabel Jumper

---

## 🔌 Pemetaan Pin GPIO

| Komponen | Pin ESP32 | Tipe Pin | Fungsi |
| :--- | :--- | :--- | :--- |
| **LED Merah** | GPIO 25 | Digital Output | Lampu Stop Kendaraan |
| **LED Kuning** | GPIO 26 | Digital Output | Lampu Peringatan Hati-Hati |
| **LED Hijau** | GPIO 27 | Digital Output | Lampu Kendaraan Berjalan |
| **Sensor LDR** | GPIO 34 | Analog Input (ADC1) | Deteksi Siang vs Malam Otomatis |
| **Tombol Menyeberang** | GPIO 18 | Digital Input (Pull-up) | Permintaan Pejalan Kaki Menyeberang |
| **Buzzer** | GPIO 4 | Digital Output | Sinyal Bunyi Penyeberangan Aman |

---

## 🧠 Skenario Logika Proyek
1. **Mode Normal Siang**: Lampu bergantian hijau (5 detik), kuning (1.5 detik), merah (4 detik).
2. **Mode Malam (Sensor LDR Gelap)**: Jika kondisi ruangan gelap (malam hari), lampu kuning berkedip lambat (peringatan hati-hati) untuk menghemat energi.
3. **Tombol Penyeberangan Ditekan**: Saat pejalan kaki menekan tombol di GPIO 18, lampu hijau segera beralih ke kuning dan merah, buzzer berbunyi 'bip-bip-bip' berulang kali untuk memandu penyeberang jalan.
