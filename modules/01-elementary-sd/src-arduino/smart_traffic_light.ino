/**
 * smart_traffic_light.ino: Lampu Lalu Lintas Pintar Edukasi SD
 *
 * Tanggung Jawab:
 * - Mengatur siklus lampu lalu lintas (Merah, Kuning, Hijau).
 * - Membaca sensor cahaya LDR untuk beralih ke mode malam otomatis.
 * - Merespons tombol penyeberangan pejalan kaki dengan alert buzzer.
 *
 * Perangkat Keras:
 * - ESP32 NodeMCU DevKit V1 (DOIT 30-Pin)
 * - LED: Merah (GPIO 25), Kuning (GPIO 26), Hijau (GPIO 27)
 * - Sensor Cahaya LDR: Analog GPIO 34 (ADC1)
 * - Tombol Penyeberangan: Digital GPIO 18 (INPUT_PULLUP)
 * - Buzzer Suara: Digital GPIO 4
 */

const int PIN_LED_MERAH = 25;
const int PIN_LED_KUNING = 26;
const int PIN_LED_HIJAU = 27;
const int PIN_SENSOR_LDR = 34;
const int PIN_TOMBOL_CROSS = 18;
const int PIN_BUZZER = 4;

const int AMBANG_BATAS_MALAM = 1500;
unsigned long waktu_siklus = 0;

void atur_lampu(bool merah, bool kuning, bool hijau) {
  digitalWrite(PIN_LED_MERAH, merah ? HIGH : LOW);
  digitalWrite(PIN_LED_KUNING, kuning ? HIGH : LOW);
  digitalWrite(PIN_LED_HIJAU, hijau ? HIGH : LOW);
}

void bunyikan_bip(int jumlah_ketukan, int jeda_ms) {
  for (int i = 0; i < jumlah_ketukan; i++) {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(jeda_ms);
    digitalWrite(PIN_BUZZER, LOW);
    delay(jeda_ms);
  }
}

void jalankan_fase_penyeberangan() {
  atur_lampu(false, true, false);
  delay(1500);
  atur_lampu(true, false, false);
  bunyikan_bip(5, 200);
  delay(1000);
}

void jalankan_mode_malam() {
  atur_lampu(false, true, false);
  delay(500);
  atur_lampu(false, false, false);
  delay(500);
}

void jalankan_siklus_normal() {
  atur_lampu(false, false, true);
  for (int i = 0; i < 40; i++) {
    if (digitalRead(PIN_TOMBOL_CROSS) == LOW) {
      jalankan_fase_penyeberangan();
      return;
    }
    delay(100);
  }
  atur_lampu(false, true, false);
  delay(1500);
  atur_lampu(true, false, false);
  delay(3000);
}

void inisialisasi_hardware() {
  pinMode(PIN_LED_MERAH, OUTPUT);
  pinMode(PIN_LED_KUNING, OUTPUT);
  pinMode(PIN_LED_HIJAU, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_TOMBOL_CROSS, INPUT_PULLUP);
  atur_lampu(false, false, false);
  digitalWrite(PIN_BUZZER, LOW);
}

void setup() {
  Serial.begin(115200);
  inisialisasi_hardware();
  bunyikan_bip(2, 80);
  Serial.println("Sistem Lampu Lalu Lintas Siap Beroperasi.");
}

void loop() {
  int nilai_cahaya = analogRead(PIN_SENSOR_LDR);
  if (nilai_cahaya < AMBANG_BATAS_MALAM) {
    jalankan_mode_malam();
    return;
  }
  jalankan_siklus_normal();
}
