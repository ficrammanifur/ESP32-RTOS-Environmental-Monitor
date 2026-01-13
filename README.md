<h1 align="center">🌍 Real-Time Environmental Sentinel</h2>
<p align="center">
Dual-Core FreeRTOS Multi-Sensor Acquisition & IoT Reporting on ESP32
</p>

<p align="center">
  <img src="https://img.shields.io/badge/ESP32-Dual%20Core-red" />
  <img src="https://img.shields.io/badge/FreeRTOS-Real--Time-blue" />
  <img src="https://img.shields.io/badge/IoT-ThingSpeak-green" />
  <img src="https://img.shields.io/badge/Language-C%2FC%2B%2B-orange" />
  <img src="https://img.shields.io/badge/Status-Stable-success" />
</p>

---

## 🎯 Fitur Utama
- 🔁 Akuisisi multi-sensor secara real-time
- 🧠 Sensor fusion suhu (LM35 + DHT22)
- ⚙️ FreeRTOS multi-task (dual-core ESP32)
- 🌐 WiFi auto-configuration menggunakan **WiFiManager**
- ☁️ Pengiriman data ke **ThingSpeak**
- 💡 LED indikator *task alive*
- 📊 Monitoring lingkungan berbasis dashboard IoT

---

## 🔧 Perangkat Keras (Hardware)
| Komponen | Fungsi |
|--------|-------|
| ESP32 DevKitC | Mikrokontroler utama |
| MQ-135 | Sensor gas (ADC) |
| LM35 | Sensor suhu analog |
| DHT22 | Sensor suhu & kelembaban |
| LDR + Resistor 2kΩ | Sensor cahaya |
| LED (GPIO33) | Indikator sistem |
| Casing | Desain portable |

---

## 🔌 Konfigurasi Pin
| Sensor | GPIO |
|------|------|
| MQ-135 | GPIO35 (ADC) |
| LM35 | GPIO32 (ADC) |
| LDR | GPIO34 (ADC) |
| DHT22 | GPIO27 |
| LED | GPIO33 |

---

## 🧠 Arsitektur Sistem
- **Core 0**  
  - Task Sensor (MQ-135, LM35, DHT22, LDR)
- **Core 1**  
  - Task IoT (HTTP POST ke ThingSpeak)
- **Queue** → komunikasi antar task  
- **Mutex** → proteksi akses Serial Monitor

---

## 🖥️ Perangkat Lunak (Software)
- Bahasa: **C/C++**
- Framework: **Arduino ESP32**
- RTOS: **FreeRTOS**
- Library:
  - WiFiManager
  - DHT Sensor Library
  - HTTPClient

---

## 🌐 Platform IoT
**ThingSpeak**
- Field 1: Temperature (°C)
- Field 2: Humidity (%)
- Field 3: Gas (MQ-135 ADC)
- Field 4: Light Intensity (%)

Data dikirim setiap **15 detik** sesuai batas minimum ThingSpeak.

---

## 🚀 Cara Menjalankan
1. Clone repository:
   ```bash
   git clone https://github.com/username/Real-Time-Environmental-Sentinel.git
Buka project di Arduino IDE

Install library yang dibutuhkan

Upload kode ke ESP32

Saat ESP32 menyala:

Hubungkan ke WiFi ESP32-EnvSentinel

Buka browser → 192.168.4.1

Konfigurasi WiFi

Pantau data di ThingSpeak Dashboard

📊 Output Sistem
Serial Monitor menampilkan data sensor

LED indikator berkedip menandakan task aktif

Dashboard ThingSpeak menampilkan data real-time

🎥 Demo
📹 Video demo menunjukkan:

Sistem menyala

Sensor terbaca

Data tampil di Serial Monitor

Data muncul di dashboard ThingSpeak

📁 Struktur Repository
css
Copy code
Real-Time-Environmental-Sentinel/
├── src/
│   └── main.ino
├── docs/
│   └── laporan.pdf
├── diagrams/
│   └── block_diagram.png
├── media/
│   └── demo_video.mp4
└── README.md
👥 Tim Pengembang
Maks. 3 Mahasiswa

Program Studi Teknik Elektro / Embedded Systems

📜 Lisensi
Proyek ini dibuat untuk keperluan akademik dan pembelajaran.
