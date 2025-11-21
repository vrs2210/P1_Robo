/*
Baud is 'Bits per second', so 9600Baud is 9600 bits per second in communication.
The advantages of higher baud rate is reducing the bottlenecks within the code when it waits for any delays.
The disadvantages of higher baud rate is reduced signal integrity, higher power usage and general increased noise.
These disadvantags are however changed due to technological advancesm which has lead to 115200 basically being equal to 9600.

The ranges of baud rates are;
1. 300
2. 600
3. 1200
4. 2400
5. 9600
6. 14400
7. 19200
8. 28800
9. 31250
10. 38400.
11. 57600
12. 115200

9600 has become the standard due to its balance between reliability and speed for serial communication.
This doesn't mean you can't use anything below or above.

If it shows up as weird symbols in the serial monitor, chang ethe Baud rate to the one you set, 9600 is the default.
*/

const int BAUD_RATE = 9600;

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  Serial.println("I'm bauding my rate till i print? (LOUD INCORRECT BUZZER)"); 
}
