/* kort måde at lave if else stataments: i stedet for at skrive 
if(x==1){dothis();
}
else(){dothat();
}

Så kan du gøre:

x==1 ? dothis() : dothat()

*/

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4Encoders encoders;
Zumo32U4OLED oled;
Zumo32U4Buzzer buzzer;

#define NUM_SENSORS 3
uint16_t lineSensorValue[NUM_SENSORS];
int speed = 100;

int threshold = 1500;
int thresholdmid = 600;

int hvemRamt = 0;

int venstreRamtStreg = 0;
int hoejreRamtStreg = 0;

int maalStregStart = 250;
int maalStregSlut = 550;


void (*maalHandling)() = NULL;  // pointer til maalV() eller maalH()


void setup() {
  lineSensors.initThreeSensors();
  Serial.begin(9600);
}

void loop() {
  lineSensors.read(lineSensorValue);
  motors.setSpeeds(speed, speed);

  if (hvemRamt == 0) {
    if (lineSensorValue[0] > threshold) { hvemRamt = 1; }  //venstre
    else if (lineSensorValue[2] > threshold) {
      hvemRamt = 2;
    }  //højre
  }

  switch (hvemRamt) {
    case 1:

      maalHandling = &maalV;  // assign pointer til venstre mål

      if (lineSensorValue[0] > threshold) {
        venstreRamtStreg = 1;
      }

      if (lineSensorValue[0] > threshold && lineSensorValue[1] > thresholdmid) {
        while (lineSensorValue[1] > thresholdmid) {
          lineSensors.read(lineSensorValue);
          turnRight();
        }
      }

      if (venstreRamtStreg == 1) {
        while (lineSensorValue[0] < threshold) {
          lineSensors.read(lineSensorValue);
          if (lineSensorValue[2] > maalStregStart && lineSensorValue[2] < maalStregSlut) {
            if (maalHandling) { (*maalHandling)(); }  // kald via pointer & tjekker ift NULL
          }
          turnLeft();
        }
      }
      break;

    case 2:
      // assign pointer til højre mål
      maalHandling = &maalH;

      if (lineSensorValue[2] > threshold) {
        hoejreRamtStreg = 1;
      }

      if (lineSensorValue[2] > threshold && lineSensorValue[1] > thresholdmid) {
        while (lineSensorValue[1] > thresholdmid) {
          lineSensors.read(lineSensorValue);
          turnLeft();
        }
      }

      if (hoejreRamtStreg == 1) {
        while (lineSensorValue[2] < threshold) {
          lineSensors.read(lineSensorValue);
          if (lineSensorValue[0] > maalStregStart && lineSensorValue[0] < maalStregSlut) {
            if (maalHandling) { (*maalHandling)(); }  // kald via pointer & tjekker ift NULL
          }
          turnRight();
        }
      }
      break;
  }
}


void maalH() {
  motors.setSpeeds(-300, -300);
  delay(200);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(-300, 300);
  delay(150);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, 300);
  delay(300);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, -300);
  delay(150);
  motors.setSpeeds(300, 300);
  delay(300);
  motors.setSpeeds(0, 0);
  celebrate();
}

void maalV() {
  motors.setSpeeds(-300, -300);
  delay(200);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, -300);
  delay(150);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, 300);
  delay(300);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(-300, 300);
  delay(150);
  motors.setSpeeds(300, 300);
  delay(300);
  motors.setSpeeds(0, 0);
  celebrate();
}


void celebrate() {
  buzzer.play("T120 L8 c>e>g>c4 g>c<g e>c4");
  while (buzzer.isPlaying())
    ;
  buzzer.play("T150 L16 g>g>g>c4");
  while (buzzer.isPlaying())
    ;
  motors.setSpeeds(300, -300);
  delay(2000);
  stopzumo();
}

void turnRight() {
  motors.setSpeeds(300, -300);
  delay(50);
  motors.setSpeeds(200, 200);
  delay(30);
  motors.setSpeeds(0, 0);
  delay(50);
}
void turnLeft() {
  motors.setSpeeds(-300, 300);
  delay(50);
  motors.setSpeeds(200, 200);
  delay(30);
  motors.setSpeeds(0, 0);
  delay(50);
}
void stopzumo() {
  while (1 == 1) { motors.setSpeeds(0, 0); }
}
