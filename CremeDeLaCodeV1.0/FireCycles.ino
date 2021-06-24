//Use this space to make the SUPER CB, OB and SNIPER Core fire cycles
void FireCycle(){
  switch(CoreMenuIndex){
    case 0:
    SUPER_CB();
    break;
    case 1:
    SUPER_OB();
    break;
    case 2:
    SNIPER();
    break;
  }
}
void SUPER_CB(){
    digitalWrite(Solenoid, LOW);
    delay (DwellTime);
    digitalWrite(Solenoid, HIGH);
    delay ((1000/autoValue - DwellTime));
    ShotCounter--;
    CycleCounter++;
}

void SUPER_OB(){
    digitalWrite(Solenoid, HIGH);
    delay (DwellTime);
    digitalWrite(Solenoid, LOW);
    delay ((1000/autoValue - DwellTime));
    ShotCounter--;
    CycleCounter++;
}

void SNIPER(){
    digitalWrite(Solenoid, LOW);
    delay (DwellTime);
    digitalWrite(Solenoid, HIGH);
    delay ((1000/autoValue - DwellTime));
    ShotCounter--;
    CycleCounter++;
}
