#include  <Wlkata_Mega_Sensor_Shield.h>

void setup() {
  // put your setup code here, to run once:
  shieldInit();//Shield Initialization
  for(int i =0;i<3;i++){  //Buzzer Warning
    shieldBuzzer(ON);
    delay(200);
    shieldBuzzer(OFF);
    delay(200);
  }

  shieldRgb(GREEN);
}

void loop() {
  // put your main code here, to run repeatedly:

}
