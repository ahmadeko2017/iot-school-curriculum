/**
 * esp_now_walkie_talkie.ino: Walkie-Talkie Teks ESP-NOW Edukasi
 *
 * Tanggung Jawab:
 * - Menginisialisasi komunikasi peer-to-peer ESP-NOW mode broadcast.
 * - Membaca tombol masukan untuk memilih dan mengirim pesan teks.
 * - Menampilkan status dan pesan masuk pada layar OLED SSD1306.
 * - Membunyikan buzzer sebagai sinyal notifikasi pesan masuk/keluar.
 *
 * Perangkat Keras:
 * - ESP32 NodeMCU DevKit V1 (DOIT 30-Pin)
 * - OLED SSD1306 0.96 inci I2C (SDA: GPIO 21, SCL: GPIO 22)
 * - Tombol Pesan (GPIO 18, GPIO 19, GPIO 23) dengan INPUT_PULLUP
 * - Buzzer (GPIO 4)
 */

#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LEBAR_LAYAR 128
#define TINGGI_LAYAR 64
#define RESET_OLED -1
#define ALAMAT_OLED 0x3C

#define PIN_TOMBOL_1 18
#define PIN_TOMBOL_2 19
#define PIN_TOMBOL_3 23
#define PIN_BUZZER 4

typedef struct struct_pesan {
  char pengirim[16];
  char isi_pesan[32];
} struct_pesan;

Adafruit_SSD1306 display(LEBAR_LAYAR, TINGGI_LAYAR, &Wire, RESET_OLED);
uint8_t mac_broadcast[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned long waktu_tekan_terakhir = 0;
const unsigned long DEBOUNCE_MS = 300;

void bunyikan_buzzer(int durasi_ms) {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(durasi_ms);
  digitalWrite(PIN_BUZZER, LOW);
}

void perbarui_tampilan(const char* judul, const char* teks1, const char* teks2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(judul);
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println(teks1);
  display.setCursor(0, 40);
  display.println(teks2);
  display.display();
}

#if defined(ESP_IDF_VERSION_MAJOR) && (ESP_IDF_VERSION_MAJOR >= 5)
#define PARAM_RECV const esp_now_recv_info_t *info
#else
#define PARAM_RECV const uint8_t *mac
#endif

void saat_data_diterima(PARAM_RECV, const uint8_t *data_masuk, int pjg) {
  if (pjg != sizeof(struct_pesan)) {
    return;
  }
  struct_pesan pesan_terima;
  memcpy(&pesan_terima, data_masuk, sizeof(pesan_terima));
  perbarui_tampilan("PESAN MASUK!", pesan_terima.pengirim, pesan_terima.isi_pesan);
  bunyikan_buzzer(150);
}

void daftarkan_peer_broadcast() {
  esp_now_peer_info_t info_peer = {};
  memcpy(info_peer.peer_addr, mac_broadcast, 6);
  info_peer.channel = 0;
  info_peer.encrypt = false;
  esp_now_add_peer(&info_peer);
}

void kirim_pesan(const char* teks) {
  struct_pesan paket_keluar;
  strncpy(paket_keluar.pengirim, "ESP32-Sobat", sizeof(paket_keluar.pengirim));
  strncpy(paket_keluar.isi_pesan, teks, sizeof(paket_keluar.isi_pesan));
  esp_now_send(mac_broadcast, (uint8_t *)&paket_keluar, sizeof(paket_keluar));
  perbarui_tampilan("TERKIRIM (SIARAN)", paket_keluar.isi_pesan, "Menunggu balasan...");
  bunyikan_buzzer(50);
}

void tangani_tombol(int pin, const char* pesan) {
  if (digitalRead(pin) != LOW) {
    return;
  }
  if (millis() - waktu_tekan_terakhir < DEBOUNCE_MS) {
    return;
  }
  waktu_tekan_terakhir = millis();
  kirim_pesan(pesan);
}

void periksa_semua_tombol() {
  tangani_tombol(PIN_TOMBOL_1, "Halo Teman!");
  tangani_tombol(PIN_TOMBOL_2, "Siaga Eksperimen!");
  tangani_tombol(PIN_TOMBOL_3, "Misi Selesai!");
}

void inisialisasi_pin() {
  pinMode(PIN_TOMBOL_1, INPUT_PULLUP);
  pinMode(PIN_TOMBOL_2, INPUT_PULLUP);
  pinMode(PIN_TOMBOL_3, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
}

void inisialisasi_oled() {
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, ALAMAT_OLED)) {
    Serial.println("Galat: Layar OLED tidak ditemukan!");
    return;
  }
  perbarui_tampilan("ESP-NOW WALKIE", "Siap berkirim pesan", "Tekan tombol 1-3");
}

void inisialisasi_jaringan_espnow() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    Serial.println("Galat: Inisialisasi ESP-NOW gagal!");
    return;
  }
  esp_now_register_recv_cb(saat_data_diterima);
  daftarkan_peer_broadcast();
}

void setup() {
  Serial.begin(115200);
  inisialisasi_pin();
  inisialisasi_oled();
  inisialisasi_jaringan_espnow();
  bunyikan_buzzer(100);
}

void loop() {
  periksa_semua_tombol();
  delay(20);
}
