/**
 * weather_station.ino: Stasiun Cuaca Mandiri Edukasi SMP
 *
 * Tanggung Jawab:
 * - Membaca data suhu dan kelembapan udara dari sensor DHT11/DHT22.
 * - Mengolah data untuk menentukan indeks kenyamanan lingkungan.
 * - Menampilkan metrik pada layar OLED SSD1306 dalam 2 mode halaman.
 * - Memicu alarm buzzer jika suhu melampaui batas aman (33 C).
 *
 * Perangkat Keras:
 * - ESP32 NodeMCU DevKit V1 (DOIT 30-Pin)
 * - Sensor DHT: Pin GPIO 15
 * - OLED SSD1306: SDA GPIO 21, SCL GPIO 22
 * - Tombol Pindah Halaman: GPIO 18 (INPUT_PULLUP)
 * - Buzzer Alarm: GPIO 4
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define LEBAR_OLED 128
#define TINGGI_OLED 64
#define PIN_DHT 15
#define TIPE_DHT DHT11
#define PIN_TOMBOL 18
#define PIN_BUZZER 4
#define BATAS_SUHU_PANAS 33.0

Adafruit_SSD1306 oled(LEBAR_OLED, TINGGI_OLED, &Wire, -1);
DHT dht(PIN_DHT, TIPE_DHT);

int mode_halaman = 0;
unsigned long waktu_baca_terakhir = 0;
float suhu_terakhir = 0.0;
float lembap_terakhir = 0.0;

void bunyikan_alarm(int durasi_ms) {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(durasi_ms);
  digitalWrite(PIN_BUZZER, LOW);
}

const char* evaluasi_kenyamanan(float suhu) {
  if (suhu < 24.0) {
    return "Sejuk";
  }
  if (suhu <= 32.0) {
    return "Nyaman";
  }
  return "PANAS!";
}

void gambar_bilah_persen(int x, int y, int lebar, int tinggi, float persen) {
  oled.drawRect(x, y, lebar, tinggi, SSD1306_WHITE);
  int lebar_isi = (int)((persen / 100.0) * (lebar - 4));
  if (lebar_isi > (lebar - 4)) {
    lebar_isi = lebar - 4;
  }
  oled.fillRect(x + 2, y + 2, lebar_isi, tinggi - 4, SSD1306_WHITE);
}

void tampilkan_halaman_data(float suhu, float lembap, const char* status) {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("STASIUN CUACA MINI");
  oled.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  oled.setCursor(0, 18);
  oled.print("Suhu    : ");
  oled.print(suhu, 1);
  oled.println(" C");

  oled.setCursor(0, 32);
  oled.print("Lembap  : ");
  oled.print(lembap, 1);
  oled.println(" %");

  oled.setCursor(0, 48);
  oled.print("Status  : ");
  oled.println(status);
  oled.display();
}

void tampilkan_halaman_grafis(float suhu, float lembap) {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("GRAFIK KELEMBAPAN");
  oled.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  oled.setCursor(0, 20);
  oled.print("Nilai: ");
  oled.print(lembap, 1);
  oled.println("%");

  gambar_bilah_persen(0, 35, 120, 16, lembap);
  oled.display();
}

void periksa_tombol_navigasi() {
  if (digitalRead(PIN_TOMBOL) == LOW) {
    mode_halaman = (mode_halaman == 0) ? 1 : 0;
    bunyikan_alarm(40);
    delay(300);
  }
}

void perbarui_pembacaan_sensor() {
  if (millis() - waktu_baca_terakhir < 2000) {
    return;
  }
  waktu_baca_terakhir = millis();
  float s = dht.readTemperature();
  float l = dht.readHumidity();
  if (!isnan(s) && !isnan(l)) {
    suhu_terakhir = s;
    lembap_terakhir = l;
  }
  if (suhu_terakhir > BATAS_SUHU_PANAS) {
    bunyikan_alarm(100);
  }
}

void perbarui_tampilan_aktif() {
  const char* status = evaluasi_kenyamanan(suhu_terakhir);
  if (mode_halaman == 0) {
    tampilkan_halaman_data(suhu_terakhir, lembap_terakhir, status);
    return;
  }
  tampilkan_halaman_grafis(suhu_terakhir, lembap_terakhir);
}

void inisialisasi_sistem() {
  pinMode(PIN_TOMBOL, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  Wire.begin(21, 22);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();
}

void setup() {
  Serial.begin(115200);
  inisialisasi_sistem();
  bunyikan_alarm(100);
}

void loop() {
  periksa_tombol_navigasi();
  perbarui_pembacaan_sensor();
  perbarui_tampilan_aktif();
  delay(50);
}
