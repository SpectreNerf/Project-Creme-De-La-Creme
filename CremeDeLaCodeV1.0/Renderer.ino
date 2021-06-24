// RENDERING SHTUFF //
// Rendering knob scroll menu
void renderKnobScrollMenu(){

  encoderChange += myEnc.read();
  myEnc.write(0);
  
  if(abs(encoderChange) >= 4){
    if(!(knobMenuIndex == 0 && encoderChange < 0)){
      knobMenuIndex += encoderChange / 4;//was 4
      knobMenuIndex = constrain(knobMenuIndex, 0, knobMenuLength - 1);
    }
    encoderChange = 0;

  }

  uView.setCursor(0,0);
  uView.print("Mode");

  int txtWidth = uView.getFontWidth() * (knobMenuArray[knobMenuIndex].length() + 1);
  int txtHeight = uView.getFontHeight();
  int availSpace = 56;
  int txtLocX = constrain((availSpace - txtWidth) / 2 - 1, 0, availSpace / 2);

  uView.rectFill(0, 26, 55, 26 + txtHeight, BLACK, NORM);
  
  uView.setCursor(txtLocX,26);
  uView.print(knobMenuArray[knobMenuIndex]);
  
  uView.display();
  firstMenuRun = false;
  uView.setFontType(0);
  
}

// Assign gauge for other menu values
void renderGauge(int &gaugeValue, String label, int gaugeMin, int gaugeMax, int valueMin, int valueMax, int detPerMove){

  mainGauge->setMinValue(gaugeMin);
  mainGauge->setMaxValue(gaugeMax);
  
  if(firstMenuRun){
    mainGauge->reDraw();
    //myEnc.write(gaugeValue);
    firstMenuRun = false;
  }

  uView.setCursor(0,4);
  uView.print(label);

  encoderChange += myEnc.read(); //--
  myEnc.write(0); //--

  if(abs(encoderChange) >= detPerMove){
    gaugeValue += encoderChange / detPerMove;
    gaugeValue = constrain(gaugeValue, valueMin, valueMax);
    encoderChange = 0;
  }

  uView.setCursor(30,40);
  
  uView.print(gaugeValue);
  if(gaugeValue < 10){
    uView.print(" ");
  }
  if(gaugeValue < 100){
    uView.print(" ");
  }

  mainGauge->setValue(gaugeValue);
//  uView.setCursor(0,10);
//  uView.print(label);
  uView.display();
}

//Render Menus
void renderMenu(byte &menuIndex, String label, String menu[], int menuLength){

  encoderChange += myEnc.read();
  myEnc.write(0);
  
  if(abs(encoderChange) >= 4){
    if(!(menuIndex == 0 && encoderChange < 0)){
      menuIndex += encoderChange / 4;
      menuIndex = constrain(menuIndex, 0, menuLength - 1);
    }
    encoderChange = 0;
  }

  uView.setCursor(0,0);
  uView.print(label);

  uView.setFontType(0);

  int txtWidth = uView.getFontWidth() * (menu[menuIndex].length() + 1);
  int txtHeight = uView.getFontHeight();
  int availSpace = 56;
  int txtLocX = constrain((availSpace - txtWidth) / 2 - 1, 0, availSpace / 2);

  uView.rectFill(0, 26, 55, 26 + txtHeight, BLACK, NORM);
  
  uView.setCursor(txtLocX, 26);
  uView.print(menu[menuIndex]);
  
  uView.display();
  firstMenuRun = false;
  uView.setFontType(0);
}



void renderScreen(){
  if (liveKnobScrollMode) {
    renderKnobScrollMenu();
  }
  else{
  switch(knobMenuIndex) {
    case 0:
    renderGauge(DwellTime, F("Dwell"), 1, 100, 1, 100, 4);
    if (TriggerPulled() && CycleCounter == 0) {
      FireCycle();
    }
    else if (!TriggerPulled()) {
      CycleCounter = 0;
    }
    break;
    case 1:
    renderGauge(burstValue, F("Burst"), 1, burstMenuLength, 1, burstMenuLength, 4);
    if (TriggerPulled() && CycleCounter <= (burstValue-1)) {
      for (int i = 0; i <= (burstValue - 1); i++) {
      FireCycle();
      if(ShotCounter == 0) {
        break;
      }
      }
    }
    else if (!TriggerPulled()) {
      CycleCounter = 0;
    }
    break;
    case 2:
    renderGauge(autoValue, F("Auto"), 1, autoMenuLength, 1, autoMenuLength, 4);
        if (TriggerPulled()) {
        FireCycle();
        }
    break;
    case 3:
    renderMenu(BinaryMenuIndex, F("Binary"), BinaryMenuArray, BinaryMenuLength);
    if(TriggerPulled() && !TriggerDown) {
        FireCycle();
        TriggerDown = true;
      } else if(!TriggerPulled() && TriggerDown && ShotCounter != 0){
          FireCycle();
          TriggerDown = false;
      }
    break;
    case 4:
    renderGauge(RampFrequency, F("RampDPS"), 1, RampingMenuLength, 1, RampingMenuLength, 4);
    if(TriggerPulled() && CycleCounter == 0) {
      if(!TriggerDown) {
//      LastShotTime = millis();
      TriggerDown = true;
      }
      if((millis() - LastShotTime) < (1000 / RampFrequency)) {
        if (RampCounter >= RampThreshold) {
          isRamping = true;
          while(isRamping && TriggerPulled()){
          FireCycle();
          if (ShotCounter == 0) {
            break;  
          }
          } 
        } else {
          FireCycle();
          RampCounter++;
          LastShotTime = millis();
        }
      } else {
        FireCycle();
        RampCounter++;
        LastShotTime = millis();
      }
       
    } else if(!TriggerPulled()){
      CycleCounter = 0;
      if(TriggerDown) {
        LastTriggerPull = millis();
        TriggerDown = false;
      }
      if((millis() - LastTriggerPull) > 2000) {
        RampCounter = 0;
        isRamping = false;
      }
    }
    break;
    case 5:
    renderMenu(CoreMenuIndex, F("FireCycle"), CoreMenuArray, CoreMenuLength);
    break;
    case 6:
    renderGauge(magCap, F("Mag Cap"), 1, 20, 1, 20, 4);
    break;
    case 7:
    renderMenu(PulseMenuIndex, F("AmmoCt"), PulseMenuArray, PulseMenuLength);
    break;
    default:
    break;
  }
 }
  int encoderPress = digitalRead(EncSwitch);

  if (encoderPress != 0) {
      if (btnDown == false) {
      liveKnobScrollMode = !liveKnobScrollMode;
      uView.clear(PAGE);
      firstMenuRun = true;
      myEnc.write(0);
      }  
  btnDown = true;
  delay(100); 
  } 
  else {
    btnDown = false;
  }

}
