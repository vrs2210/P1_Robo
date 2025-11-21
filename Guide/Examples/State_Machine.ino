/*
  Possibly used for a moveable robot of some kind?
*/
const int BAUD_RATE = 9600; // We define baud_rate out here, as it's easier to change if its easily accessible.

// We define a state variable with every possible state the board can be in.
enum State {IDLE, SCAN, MOVE, STOP};
State state = IDLE; // We initialize the state to be 'IDLE', normally we would do this in setup, but it's fine out here.

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  switch (State) { // Normally, we'd use a 'default' in this switch case, but due to the type, it is never going to be anything BUT any of the defined cases.
    case IDLE: // Just standing still waiting for input.
      Serial.println("Waiting for input...")
      break;
    case SCAN: // Scanning using a reading device of some kind, likely changes to MOVE if nothing was found, and to IDLE if something WAS found.
      Serial.println("Scanning!")
      break;
    case MOVE: // Moving based on some logic.
      Serial.println("Moving to next location...")
      break;
    case STOP: // In here, we would immediately change State to idle, as STOP is just used to stop the board (like a Zumo32U4.)
      Serial.println("Stop!")
      break;
  }
}
