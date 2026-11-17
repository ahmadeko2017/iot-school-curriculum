# Panduan & Diagram Wiring: Walkie-Talkie Teks ESP-NOW

Panduan visual perakitan kabel breadboard untuk siswa dan guru. Ikuti petunjuk warna kabel untuk memudahkan pengecekan bersama teman satu kelompok.

---

## 🎨 Kode Warna Kabel yang Dianjurkan
- **Kabel Merah**: Jalur Daya Positif (VCC / 3V3 / 5V)
- **Kabel Hitam**: Jalur Negatif / Ground (GND)
- **Kabel Kuning**: Jalur Sinyal SCL (Clock I2C)
- **Kabel Hijau**: Jalur Sinyal SDA (Data I2C)
- **Kabel Biru / Oranye**: Jalur Sakelar Tombol & Buzzer

---

## 🗺️ Skema Koneksi Breadboard (Tabel Rujukan)

| Dari Modul / Komponen | Kaki / Pin Komponen | Menuju Pin ESP32 NodeMCU | Warna Rekomendasi |
| :--- | :--- | :--- | :--- |
| **Layar OLED SSD1306** | GND | GND | Hitam |
| | VCC | 3V3 (atau VIN) | Merah |
| | SCL | GPIO 22 | Kuning |
| | SDA | GPIO 21 | Hijau |
| **Tombol 1 (Pesan A)** | Kaki Kiri | GPIO 18 | Biru |
| | Kaki Kanan | GND | Hitam |
| **Tombol 2 (Pesan B)** | Kaki Kiri | GPIO 19 | Biru |
| | Kaki Kanan | GND | Hitam |
| **Tombol 3 (Pesan C)** | Kaki Kiri | GPIO 23 | Biru |
| | Kaki Kanan | GND | Hitam |
| **Buzzer** | Kaki Positif (+) | GPIO 4 | Oranye |
| | Kaki Negatif (-) | GND | Hitam |

---

## 📐 Diagram Tata Letak Pinout ESP32 (DOIT 30-Pin)

```text
               +---------------------------+
               |     [USB TYPE-C PORT]     |
               |                           |
         EN [ ]|                           |[ ] GPIO 23 <--- Tombol 3 (Pesan C)
    GPIO 36 [ ]|                           |[ ] GPIO 22 <--- SCL (OLED)
    GPIO 39 [ ]|                           |[ ] GPIO 1  (TX0)
    GPIO 34 [ ]|                           |[ ] GPIO 3  (RX0)
    GPIO 35 [ ]|                           |[ ] GPIO 21 <--- SDA (OLED)
    GPIO 32 [ ]|                           |[ ] GPIO 19 <--- Tombol 2 (Pesan B)
    GPIO 33 [ ]|                           |[ ] GPIO 18 <--- Tombol 1 (Pesan A)
    GPIO 25 [ ]|                           |[ ] GPIO 5
    GPIO 26 [ ]|                           |[ ] GPIO 17
    GPIO 27 [ ]|                           |[ ] GPIO 16
    GPIO 14 [ ]|       ESP32 NodeMCU       |[ ] GPIO 4  <--- Buzzer (+)
    GPIO 12 [ ]|       DEVKIT V1 30P       |[ ] GPIO 0
    GPIO 13 [ ]|                           |[ ] GPIO 2
        GND [ ]|=== Jalur GND Bersama =====|[ ] GPIO 15
        VIN [ ]|                           |[ ] 3V3     <--- VCC (OLED 3.3V)
               +---------------------------+
```

---

## 💡 Tips Penting Saat Perakitan

1. **Gunakan Rel Daya Breadboard (Power Rail)**:
   - Hubungkan pin `GND` dari ESP32 ke garis biru/hitam bertanda minus (-) pada breadboard. Seluruh kaki negatif komponen (OLED, Tombol, Buzzer) dapat ditancapkan ke jalur ini.
2. **Kaki Tombol Push-Button**:
   - Push button memiliki 4 kaki yang terhubung secara berpasangan. Tancapkan tombol melintasi parit tengah breadboard agar kedua sisinya tidak saling hubung singkat.
3. **Internal Pull-Up**:
   - Program menggunakan `INPUT_PULLUP` secara perangkat lunak, sehingga kamu tidak memerlukan resistor eksternal 10k ohm pada tombol.
