/**
 * offline_iot_server.ino: Server Web IoT Offline Pertanian Cerdas SMA
 *
 * Tanggung Jawab:
 * - Menjalankan Wi-Fi Access Point mandiri (SSID: ESP32-SmartFarm-Lab).
 * - Menyajikan antarmuka web monitoring HTML dan REST API lokal.
 * - Membaca sensor kelembapan tanah analog pada GPIO 34.
 * - Mengendalikan pompa air 5V DC melalui relai terisolasi pada GPIO 26.
 * - Menampilkan alamat IP dan status operasional pada layar OLED.
 *
 * Perangkat Keras:
 * - ESP32 NodeMCU DevKit V1 (DOIT 30-Pin)
 * - Sensor Kelembapan: Analog GPIO 34 (ADC1)
 * - Relai Pompa 5V: Digital GPIO 26
 * - LED Indikator: Digital GPIO 27
 * - Buzzer: Digital GPIO 4
 * - OLED SSD1306: SDA GPIO 21, SCL GPIO 22
 */

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int PIN_SENSOR_TANAH = 34;
const int PIN_RELAI_POMPA = 26;
const int PIN_LED_POMPA = 27;
const int PIN_BUZZER = 4;

const char* NAMA_SSID = "ESP32-SmartFarm-Lab";
const char* KATA_SANDI = "edukasi123";

Adafruit_SSD1306 display_oled(128, 64, &Wire, -1);
WebServer server_lokal(80);

bool status_pompa_aktif = false;
unsigned long waktu_baca_sensor = 0;
int kelembapan_terakhir = 50;

void bunyikan_buzzer(int durasi_ms) {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(durasi_ms);
  digitalWrite(PIN_BUZZER, LOW);
}

void atur_pompa(bool aktif) {
  status_pompa_aktif = aktif;
  digitalWrite(PIN_RELAI_POMPA, aktif ? HIGH : LOW);
  digitalWrite(PIN_LED_POMPA, aktif ? HIGH : LOW);
  bunyikan_buzzer(50);
}

int hitung_persentase_kelembapan() {
  int nilai_raw = analogRead(PIN_SENSOR_TANAH);
  int persen = map(nilai_raw, 4095, 1500, 0, 100);
  return constrain(persen, 0, 100);
}

void perbarui_oled(int lembap, bool pompa) {
  display_oled.clearDisplay();
  display_oled.setTextSize(1);
  display_oled.setTextColor(SSD1306_WHITE);
  display_oled.setCursor(0, 0);
  display_oled.println("SMART FARM SERVER");
  display_oled.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  display_oled.setCursor(0, 16);
  display_oled.println("IP: 192.168.4.1");
  display_oled.setCursor(0, 32);
  display_oled.print("Kelembapan: ");
  display_oled.print(lembap);
  display_oled.println(" %");

  display_oled.setCursor(0, 48);
  display_oled.print("Pompa     : ");
  display_oled.println(pompa ? "AKTIF (MENYIRAM)" : "STANDBY");
  display_oled.display();
}

void tangani_halaman_root() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Smart Farm ESP32</title>";
  html += "<style>body{font-family:sans-serif;text-align:center;padding:20px;background:#f4f7f6;}";
  html += ".card{background:white;padding:24px;border-radius:12px;display:inline-block;box-shadow:0 2px 6px rgba(0,0,0,0.1);}";
  html += "button{padding:12px 24px;font-size:16px;border:none;border-radius:8px;background:#0d6efd;color:white;cursor:pointer;}";
  html += "</style></head><body><div class='card'>";
  html += "<h2>Monitoring Irigasi Pintar</h2>";
  html += "<p>Kelembapan Tanah: <strong>" + String(kelembapan_terakhir) + "%</strong></p>";
  html += "<p>Status Pompa: <strong>" + String(status_pompa_aktif ? "MENYIRAM" : "MATI") + "</strong></p>";
  html += "<form action='/toggle' method='POST'><button type='submit'>Sakelar Pompa</button></form>";
  html += "</div></body></html>";
  server_lokal.send(200, "text/html", html);
}

void tangani_api_status() {
  String json = "{";
  json += "\"kelembapan\":" + String(kelembapan_terakhir) + ",";
  json += "\"pompa\":" + String(status_pompa_aktif ? "true" : "false");
  json += "}";
  server_lokal.send(200, "application/json", json);
}

void tangani_toggle_pompa() {
  atur_pompa(!status_pompa_aktif);
  server_lokal.sendHeader("Location", "/");
  server_lokal.send(303);
}

void inisialisasi_hardware() {
  pinMode(PIN_RELAI_POMPA, OUTPUT);
  pinMode(PIN_LED_POMPA, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  atur_pompa(false);

  Wire.begin(21, 22);
  display_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  perbarui_oled(0, false);
}

void inisialisasi_jaringan() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(NAMA_SSID, KATA_SANDI);

  server_lokal.on("/", HTTP_GET, tangani_halaman_root);
  server_lokal.on("/api/status", HTTP_GET, tangani_api_status);
  server_lokal.on("/toggle", HTTP_POST, tangani_toggle_pompa);
  server_lokal.begin();
}

void setup() {
  Serial.begin(115200);
  inisialisasi_hardware();
  inisialisasi_jaringan();
  bunyikan_buzzer(100);
}

void loop() {
  server_lokal.handleClient();
  if (millis() - waktu_baca_sensor >= 1000) {
    waktu_baca_sensor = millis();
    kelembapan_terakhir = hitung_persentase_kelembapan();
    perbarui_oled(kelembapan_terakhir, status_pompa_aktif);
  }
}
