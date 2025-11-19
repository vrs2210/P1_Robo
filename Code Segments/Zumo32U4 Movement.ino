#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4Encoders encoders;
Zumo32U4OLED oled;
Zumo32U4Buzzer buzzer;

#define NUM_SENSORS 3  //definer numre af linjesensore
uint16_t lineSensorValue[NUM_SENSORS];
int speed = 100;

int threshold = 1500;
int thresholdmid = 600;

int hvemRamt = 0;

int venstreRamtStreg = 0;
int hoejreRamtStreg = 0;

int maalStregStart = 350;
int maalStregSlut = 500;

void setup() {
  lineSensors.initThreeSensors();
  Serial.begin(9600);
}

void loop() {
  lineSensors.read(lineSensorValue);
  motors.setSpeeds(speed, speed);



  //fra starten af er hvemRamt sat til 0, dvs hverken højre eller venstre sensor har ramt en sort streg.
  //Så nu tjekker den konstant om enten højre eller venstre sensor har ramt en sort streg, og hvis den gør,
  //bliver ramtStreg ændret til enten 1 eller 2. Da hele statementet kun kører hvis hvemRamt er 0, vil
  //hvemRamt aldrig ændre sin værdi fra den nye 1 eller 2.
  if (hvemRamt == 0) {
    if (lineSensorValue[0] > threshold) { hvemRamt = 1; }  //venstre
    else if (lineSensorValue[2] > threshold) {
      hvemRamt = 2;
    }  //højre
  }

  switch (hvemRamt) {
    case 1:  //hvis venstre sensor rammer først
      //sætter variablen venstreRamtSTreg til noget som ikke er 0, så vi kan bruge den til at bestemme hvor stregen er senere
      if (lineSensorValue[0] > threshold) {
        venstreRamtStreg = 1;
      }



      //det her kode tjekker om venstre og midt sensor rammer tapen, og drejer robotten til højre hvis de gør.
      if (lineSensorValue[0] > threshold && lineSensorValue[1] > thresholdmid) {
        while (lineSensorValue[1] > thresholdmid) {
          lineSensors.read(lineSensorValue);  //læs linjeværdier
          turnRight();
        }
      }
      //dette kode tjekker først om robotten har ramt stregen på venstre side, hvis ja og hvis robotten
      //har kørt for meget til højre, drejer den bare robotten tilbage
      if (venstreRamtStreg == 1) {
        while (lineSensorValue[0] < threshold) {
          lineSensors.read(lineSensorValue);                                                //læs linjeværdier
          if (lineSensorValue[2] > maalStregStart && lineSensorValue[2] < maalStregSlut) {  //hvis venstre sensor er mellem 350-500(aka den rammer målstregen)
            maalV();
          }
          turnLeft();
        }
      }
      break;



    case 2:                                  //hvis højre sensor rammer først
      if (lineSensorValue[2] > threshold) {  //ændrer højreRamtStreg værdien så snart den rammer stregen
        hoejreRamtStreg = 1;
      }



      //det her kode tjekker om højre og midt sensor rammer tapen, og drejer robotten til venstre hvis de gør.
      if (lineSensorValue[2] > threshold && lineSensorValue[1] > thresholdmid) {
        while (lineSensorValue[1] > thresholdmid) {
          lineSensors.read(lineSensorValue);  //læs linjeværdier
          turnLeft();
        }
      }
      //dette kode tjekker først om robotten har ramt stregen på højre side, hvis ja og hvis robotten
      //har kørt for meget til venstre, drejer den bare robotten tilbage
      if (hoejreRamtStreg == 1) {
        while (lineSensorValue[2] < threshold) {
          lineSensors.read(lineSensorValue);                                                //læs linjeværdier
          if (lineSensorValue[0] > maalStregStart && lineSensorValue[0] < maalStregSlut) {  //hvis venstre sensor er mellem 350-500(aka den rammer målstregen)
            maalH();
          }
          turnRight();
        }
      }
      break;
  }
}

void maalH() {
  motors.setSpeeds(-300, -300);  //bak væk
  delay(200);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(-300, 300);  //drej til venstre
  delay(150);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, 300);  //kør ligeud
  delay(300);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, -300);  //drej til højre
  delay(150);
  motors.setSpeeds(300, 300);
  delay(300);
  motors.setSpeeds(0, 0);
  celebrate();
}

void maalV() {
  motors.setSpeeds(-300, -300);  //bak væk
  delay(200);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, -300);  //drej til højre
  delay(150);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(300, 300);  //kør ligeud
  delay(300);
  motors.setSpeeds(0, 0);
  delay(40);
  motors.setSpeeds(-300, 300);  //drej til venstre
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

void turnRight() {  //som navnet siger, drejer til højre men med små intervaller
  motors.setSpeeds(300, -300);
  delay(50);
  motors.setSpeeds(200, 200);
  delay(30);
  motors.setSpeeds(0, 0);
  delay(50);
}

void turnLeft() {  //som navnet siger, drejer til venstre men med små intervaller
  motors.setSpeeds(-300, 300);
  delay(50);
  motors.setSpeeds(200, 200);
  delay(30);
  motors.setSpeeds(0, 0);
  delay(50);
}
void stopzumo() {
  while (1 == 1) {
    motors.setSpeeds(0, 0);
  }
}
