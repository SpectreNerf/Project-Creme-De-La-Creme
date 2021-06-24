// This space deals primarily with EEPROM details.
void boundSettings() {
  DwellTime = constrain(DwellTime, 0, 100);
  burstValue = constrain(burstValue, 1, 5);
  autoValue = constrain(autoValue, 1, 15);
  RampFrequency = constrain(RampFrequency, 0, 10);
  magCap = constrain(magCap, 1, 20);
}

void writeSettings(int presetNumber) {
//  struct BlasterSettings {
//  int DwellTime;
//  int burstValue;
//  int autoValue;
//  int RampFrequency;
//  int CoreMenuIndex;
//  int magCap;
//};

  if( currentSettings.VersionNumber != VersionNumber || 
      currentSettings.DwellTime != DwellTime ||
      currentSettings.burstValue != burstValue ||
      currentSettings.autoValue != autoValue ||
      currentSettings.RampFrequency != RampFrequency ||
      currentSettings.CoreMenuIndex != CoreMenuIndex ||
      currentSettings.magCap != magCap ) {
        currentSettings = {
          VersionNumber,
          DwellTime,
          burstValue,
          autoValue,
          RampFrequency,
          CoreMenuIndex,
          magCap
        };

      int memLoc = presetNumber * 100;

      EEPROM.put(memLoc, currentSettings);
      }
}

void loadSettings(int presetNumber){
  int memLoc = presetNumber * 100;
  EEPROM.get(memLoc, currentSettings);

  if(currentSettings.VersionNumber == -1  || currentSettings.VersionNumber != VersionNumber) {
    currentSettings = defaultSettings;
  }

  DwellTime = currentSettings.DwellTime;
  burstValue = currentSettings.burstValue;
  autoValue = currentSettings.autoValue;
  RampFrequency = currentSettings.RampFrequency;
  CoreMenuIndex = currentSettings.CoreMenuIndex;
  magCap = currentSettings.magCap;
  
}

void clearSettings(){

  uView.clear(PAGE);// clear page
  uView.setCursor(0,0);
  uView.print("Clearing");
  uView.setCursor(0,14);
  uView.print("settings");
  uView.display();
  
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}
