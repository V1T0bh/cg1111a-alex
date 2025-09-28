#include <MeMCore.h>

MeDCMotor motorLeft(M1); // Left motor connected to port M1
MeDCMotor motorRight(M2); // Right motor connected to port M2
MeLineFollower lineFollower(PORT_1); // Line follower connected to port 1
MeUltrasonicSensor ultrasonicSensor(PORT_2); // Ultrasonic sensor connected to port 2

// Define RJ25 pin mappings
#define rgb0 A0 // S1 on first RJ25 adapter
#define rgb1 A1 // S2 on first RJ25 adpater
#define IR A2 // S1 on second RJ25 adpater
#define LDR A3 // S2 on second RJ25 adpater

// Define wait times
#define LDRWait 10 // Wait time for LDR reading reading
#define RGBWait 200 // Wait time for LED reading stabalisation
#define NudgeWait 300 // Period for nudging mBot


/* Function to control the activation of the LEDs and IR emitter
   Enable is always LOW (power on) because its connected to ground (complete circuit)
*/
void shine_LED(int i){
  int select[4][2] = {
    {LOW, HIGH}, // i = 0, shine RED
    {HIGH, HIGH}, // i = 1, shine GREEN
    {HIGH, LOW}, // i = 2, shine BLUE
    {LOW, LOW} // i = 3, turn on IR Emitter
  };
  digitalWrite(rgb0, select[i][0]);
  digitalWrite(rgb1, select[i][1]);
}

// Configure pins for A0, A1, A2, A3 to initialise communication
void setup() 
{
  Serial.begin(9600);
  pinMode(rgb0, OUTPUT); // rgb0 as output
  pinMode(rgb1, OUTPUT); // rgb1 as output
  digitalWrite(rgb0, LOW); // rgb0 is set to LOW
  digitalWrite(rgb1, LOW); // rgb1 is set to LOW
}

 // NOTE: Multiple checks for sensor_state are used to minimise delay in detecting the black line
void loop() 
{
  int16_t start = millis(); // Record the start time (time now)
  while ((sensor_state() != 0)){ // Check if the black line has been detected
    int16_t time = millis(); // Get the current time
    if (time - start >= NudgeWait){ // Nudge at 300 ms intervals
      moveForward(); // Move forward
      
      if (sensor_state() == 0) { // Stop looping when black line detected
        break;
      }

      if(ultrasonic_distance() < 9.5  || difference_IR() < 105) // Check if mBot is too close to the left wall
      {
        nudgeRight();
      }

      if (sensor_state() == 0) { // Stop looping when black line detected
        break;
      }

      if(ultrasonic_distance() > 10.5 || difference_IR() > 115) // Check if mBot is too close to the right wall
      {
        nudgeLeft();
      }
      
      if (sensor_state() == 0) { // Stop looping when black line detected
        break;
      }
      moveForward();
      start = millis(); // Reset start time
    }
  }

  // {sensor_state() == 0}
  // Code below executes when black line is detected
  stopMotor();
  int colour = detectColour(); // Identify the colour underneath the mBot

  switch (colour) {
    case 0: // RED - Turn left
      turnLeft();
      break;

    case 1: // GREEN - Turn right
      turnRight();
      break;

    case 2: // ORANGE - U-turn
      uTurn();
      break;

    case 3: // PINK - Double left turn
      doubleLeftTurn();
      break;

    case 4: // LIGHT BLUE - Double right turn
      doubleRightTurn();
      break;

    case 5: // WHITE - Stop and celebrate
      stopMotor(); 
      celebrate();
      break;

    default: // INVALID - unknown colour detected
      Serial.println("Unknown colour detected");
      moveBackward();
      break;
  }
}