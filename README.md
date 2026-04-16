# Color Detection System with Audio Feedback
 
An Arduino-based system that detects the color of an object using an RGB sensor and announces it through a speaker. Built as part of our Microprocessors & Microcontrollers (MPMC) course.
 
---
 
## Hardware Required
 
| Component | Purpose |
|---|---|
| Arduino (Uno/Nano) | Microcontroller |
| TCS34725 RGB Sensor | Color detection |
| DFPlayer Mini | MP3 playback module |
| Speaker (8Ω) | Audio output |
| MicroSD Card | Stores MP3 files |
| Jumper Wires | Connections |
 
---
 
## Wiring
 
| DFPlayer Mini | Arduino |
|---|---|
| TX | Pin 11 |
| RX | Pin 10 |
| VCC | 5V |
| GND | GND |
 
TCS34725 connects via I2C (SDA → A4, SCL → A5 on Uno).

---

## Circuit Diagram


---

## SD Card Setup
 
Place MP3 files inside a folder named `mp3` on the SD card, named exactly as follows:
 
```
mp3/
├── 0001.mp3   → "Red"
├── 0002.mp3   → "Green"
├── 0003.mp3   → "Blue"
├── 0004.mp3   → "White"
├── 0005.mp3   → "Black"
└── 0006.mp3   → "System Ready"
```
 
---
 
## Libraries
 
Install these via Arduino Library Manager:
 
- `Adafruit TCS34725`
- `DFRobotDFPlayerMini`
- `SoftwareSerial` (built-in)
 
---
 
## How It Works
 
1. On startup, the system plays all audio tracks as a self-test
2. In the main loop, the sensor takes 5 readings and averages them for accuracy
3. Raw values are normalized as a percentage of total light
4. Color is classified using threshold logic:
 
| Condition | Detected Color |
|---|---|
| All channels > 60% | White |
| All channels < 20% | Black |
| Total light < 50 | Black (too dark) |
| Red dominates | Red |
| Green dominates | Green |
| Default | Blue |
 
5. The matching audio track plays through the speaker
 
---
 
## Known Fix
 
The DFPlayer Mini requires a **120ms delay** after each play command inside a loop, otherwise it silently drops the command. This is accounted for in `playTrack()`.
 
---
 
## Use Case
 
While built as a college project, this system has real potential as a low-cost assistive device for visually impaired individuals to identify colors without needing a smartphone.
