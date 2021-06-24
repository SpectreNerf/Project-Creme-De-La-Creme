// This space mostly focuses on the pulse counter functionality and bolt lock feature.
bool MagEmpty() {
  if(ShotCounter == 0){
    return true;
  }
  else {
    return false;
  }
}

void PulseCounter(){
  if(PulseMenuOn() == true) {
    uView.setCursor(57,16);
    uView.print("A"); 
    uView.setCursor(57,24);
    uView.print("M"); 
    uView.setCursor(57,32);
    uView.print("M");
    uView.setCursor(57,40);
    uView.print("O");
    if(talonMag() || katanaMag()) {
      if (magLoad){
      ShotCounter = magCap;
      TriggerLock = false;
      magLoad = false;
      }
      if(MagEmpty()) {
        boltLock();
      }
  } else if (magOut() == true || magIn() == true) {
    ShotCounter = 0;
    TriggerLock = true;
    magLoad = true;
  }
  uView.setCursor(51,0);
  if(ShotCounter < 10) {
    uView.print("0");
  }
  uView.print(ShotCounter);
  }
  else if(!PulseMenuOn()) {
  TriggerLock = false;
  uView.setCursor(51,0);
  uView.print("NA");
  }
}

  
void boltLock() {
  switch(CoreMenuIndex) {
    case 0:
    digitalWrite(Solenoid, LOW);
    break;
    case 1:
    digitalWrite(Solenoid, LOW);
    break;
    case 2: 
    digitalWrite(Solenoid, HIGH);
    break;
  }
  TriggerLock = true;
}

 
