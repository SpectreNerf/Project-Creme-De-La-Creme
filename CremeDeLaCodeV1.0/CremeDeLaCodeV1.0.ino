/* This code is derived from the FDL-3 Firmware V1.04 by Project FDL.
  This is not used with intent of profiting and will be made available
  when its reliability has been ensured.

  Do not use this code with intent to harm others. This is not
  for use with weaponry.

  Creme De La Creme code - a project for modular HPA blasters.
  Written by Spectre Armaments with aid from Project FDL.


*/
#include <MicroView.h>
#include <Encoder.h>
#include <EEPROM.h>

const float VersionNumber = 1.00;
const unsigned char SpectreArmaments [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
  0x20, 0x90, 0xD0, 0xE8, 0xE0, 0xF4, 0xF0, 0xF2, 0xFA, 0xF8, 0xF8, 0xF8, 0xFD, 0x01, 0x01, 0xFF,
  0x01, 0x01, 0xFC, 0xF8, 0xF8, 0xF8, 0xFA, 0xF0, 0xF4, 0xE4, 0xE0, 0xC8, 0xD0, 0x80, 0x20, 0x40,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x10, 0xC4, 0xF2, 0xF9, 0xFC, 0xFE,
  0xFF, 0x7F, 0x1F, 0x0F, 0x07, 0x07, 0x03, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x3F,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01, 0x03, 0x07, 0x0F, 0x0F, 0x3F, 0x7F, 0xFF, 0xFE,
  0xFC, 0xF9, 0xE2, 0x88, 0x10, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x83, 0xB0, 0xBF, 0x3F, 0x3F, 0x3F, 0x3F, 0x3B,
  0x30, 0x30, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x30, 0x30, 0x39, 0x3F,
  0x3F, 0x3F, 0x3F, 0x3F, 0xBE, 0x00, 0x86, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x0C, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xC0,
  0x00, 0x00, 0x04, 0x04, 0x0C, 0x0C, 0x1C, 0x1C, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0x3C, 0x1C, 0x0C, 0x0C, 0x04, 0x04, 0x04, 0x00, 0x80, 0xE0,
  0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x00, 0x60, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x23, 0x4F, 0x9F, 0x3F, 0x7F,
  0xFF, 0xFE, 0xF8, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFC,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0xFF, 0x7F,
  0x3F, 0x9F, 0x47, 0x11, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
  0x04, 0x09, 0x03, 0x17, 0x07, 0x2F, 0x0F, 0x4F, 0x5F, 0x1F, 0x1F, 0x1F, 0xBF, 0x80, 0x80, 0xFF,
  0x80, 0x80, 0xBF, 0x1F, 0x1F, 0x1F, 0x40, 0x00, 0x00, 0x20, 0x00, 0x10, 0x0B, 0x01, 0x04, 0x02,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const int Tdet = A2;
const int Kdet = A1;
const int Trigger = A0;
const int EncSwitch = 2;
const int Solenoid = 6;

int brightnessValue = 100;
int ShotCounter = 15;
int CycleCounter = 0;
int DwellTime = 55;
int btnPress = 0;
int magCap = 15;

bool firstMenuRun = true;
bool liveKnobScrollMode = false;
bool CoreCheckDown = false;
bool btnDown = false;
bool TriggerDown = false;
bool TriggerLock = false;
bool TriggerPulled(){
  if (digitalRead(Trigger) == 1 && TriggerLock == false){
    return true;
  }
  else {
    return false;    
    CycleCounter = 0;
  }
}
bool magLoad = true;

long encoderChange = 0;

Encoder myEnc(3,5);
MicroViewWidget *mainGauge;

//MENUS
#define knobMenuLength 8
String knobMenuArray[knobMenuLength] = 
{
   "Semi",
   "Burst",
   "Auto",
   "Binary",
   "Ramping",
   "Core",
   "MagCap"
   ,"AmmoCt"
};
byte knobMenuIndex = 0;

#define burstMenuLength 5
String burstMenuArray[burstMenuLength] = {"1","2","3","4","5"};
byte burstMenuIndex = 0;
int burstValue = 3;

#define autoMenuLength 15
String autoMenuArray[autoMenuLength] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
byte autoMenuIndex = 9;
int autoValue = 10;

#define CoreMenuLength 3
String CoreMenuArray[CoreMenuLength] = {"SUPER-CB", "SUPER-OB", "SNIPER"};
byte CoreMenuIndex = 0;

#define BinaryMenuLength 1
String BinaryMenuArray[BinaryMenuLength] = {"Ready"};
byte BinaryMenuIndex = 0;

#define RampingMenuLength 10
String RampingMenuArray[RampingMenuLength] = {"1","2","3","4","5","6","7","8","9","10"};
byte RampingMenuIndex = 0;
int RampFrequency = 5; // The number of darts per second required to activate / sustain ramping
byte CurrentRampCount = 0; // 
byte RampThreshold = 3;
int RampCounter = 0;
bool isRamping = false;

static unsigned long LastShotTime = 0;
static unsigned long LastTriggerPull = 0; // Used to store the last trigger pull for the Ramping mode
unsigned long lastSettingsSave = 0;

#define PulseMenuLength 2
String PulseMenuArray[PulseMenuLength] = {"On", "Off"};
byte PulseMenuIndex = 0;

bool PulseMenuOn() {
  if(PulseMenuIndex == 0) {
    return true;
  } else {
    return false;
  }
}

struct BlasterSettings {
  int VersionNumber;
  int DwellTime;
  int burstValue;
  int autoValue;
  int RampFrequency;
  int CoreMenuIndex;
  int magCap;
};
BlasterSettings currentSettings = { 1.00, 55, 3, 10, 3, 1, 15 };
BlasterSettings defaultSettings = { 1.00, 55, 3, 10, 3, 1, 15 };

bool talonMag(){
  if (digitalRead(Tdet) == HIGH && digitalRead(Kdet) == LOW){
    return true;
  } else {
    return false;
  }
}

bool katanaMag() {
  if(digitalRead(Tdet) == LOW && digitalRead(Kdet) == HIGH) {
    return true;
  } else {
    return false;
  }
}

bool magIn() {
  if(digitalRead(Tdet) == HIGH && digitalRead(Kdet) == HIGH) {
    TriggerDown = false;
    return true;
  } else {
    return false;
  }
}

bool magOut() {
  if(digitalRead(Tdet) == LOW && digitalRead(Kdet) == LOW) {
    TriggerDown = false;
    return true;
  } else {
    return false;
  }
}

void setup() {
  uView.begin();
  uView.clear(PAGE);


  uView.drawBitmap(SpectreArmaments);
  uView.display();
  pinMode(Tdet, INPUT);
  pinMode(Kdet, INPUT);
  pinMode(Trigger, INPUT);
  pinMode(EncSwitch, INPUT);
  pinMode(Solenoid, OUTPUT);
  delay(2000);

  if (digitalRead(EncSwitch) == HIGH) {
     while(digitalRead(EncSwitch) == HIGH){};
    delay(50);
    uView.clear(PAGE);
    uView.setCursor(0,0);
    uView.print("Click knob");
    uView.setCursor(0,14);
    uView.print("to clear");
    uView.setCursor(0,28);
    uView.print("settings");
    uView.display();

    long currMills = millis();
    while(millis() < currMills + 2000){
      if(digitalRead(EncSwitch) == HIGH){
        clearSettings();
        break;
      }
    }
  }
  uView.clear(PAGE);
  uView.setCursor(10,7);
  uView.print("Turn gas");
  uView.setCursor(10,21);
  uView.print("lever on");
  uView.setCursor(25,35);
  uView.print("now.");
  uView.display();
  delay(2000);

  mainGauge = new MicroViewGauge(16, 30, 0, 100, WIDGETNOVALUE);

  mainGauge->reDraw();

  loadSettings(0);
  uView.clear(PAGE);
  renderScreen();
}

void loop() {
PulseCounter();
renderScreen();

if(lastSettingsSave != 0 && millis() - lastSettingsSave < 1000) {
  //don't save
} else {
  writeSettings(0);
  lastSettingsSave = millis();
}

}