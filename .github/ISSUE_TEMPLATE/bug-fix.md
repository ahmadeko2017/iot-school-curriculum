---
name: Laporan Bug Hardware atau Kode
about: Laporkan kesalahan kode, wiring, atau inkonsistensi hardware
title: "[BUG]: "
labels: ["bug", "triage"]
assignees: ""
---

## Deskripsi Masalah
Jelaskan kendala yang dialami secara singkat dan jelas.

## Perangkat & Lingkungan Uji
- Board ESP32: NodeMCU DevKit V1 Type-C (DOIT 30-Pin / ESP-WROOM-32)
- Driver USB: CH340 / CP2102
- Sistem Operasi: Windows / Linux / macOS
- Lingkungan Pengembangan: Arduino IDE 2.x / Thonny IDE (MicroPython)
- Modul Terkait: (Contoh: modules/00-starter-workshop)

## Langkah Reproduksi
1. Rangkai sirkuit sesuai diagram wiring modul.
2. Unggah kode `*.ino` atau `*.py`.
3. Buka Serial Monitor pada baud rate 115200.
4. Perhatikan perilaku error atau output serial.

## Perilaku yang Diharapkan
Jelaskan apa yang seharusnya terjadi jika sistem bekerja normal.

## Bukti Log / Tangkapan Layar
Tempelkan log serial monitor atau foto rangkaian hardware di sini.
