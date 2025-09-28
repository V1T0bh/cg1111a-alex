#define motorSpeed 200 // Speed for left and right motors
#define time90 450 // Calibrated time for 90-degreen turn
#define timeSqr 875 // Calibrated time for moving forward after the first left/right turn when PINK/LIGHT BLUE is detected

// The left motor has reversed polarity, hence we negate the speed
void mLeft(int16_t speed){
  motorLeft.run(-speed); // Run left motor
}


void mRight(int16_t speed){
  motorRight.run(speed); // Run right motor
}

// Function to stop both motors
void stopMotor() {
  motorLeft.run(0);  // Stop left motor
  motorRight.run(0); // Stop right motor
}

// Function to move forward
void moveForward() {
  mLeft(motorSpeed); // Move left motor forward
  mRight(motorSpeed); // Move right motor forward
}

// Function to move backward (when an unknown colour is detected)
void moveBackward() {
  mLeft(-motorSpeed); // Move left motor backward
  mRight(-motorSpeed); // Move right motor backward
}

// Function to turn left (RED detected)
void turnLeft() {
  mLeft(-motorSpeed); // Move left motor backward
  mRight(motorSpeed); // Move right motor forward
  delay(time90); // Turn for the defined time
  stopMotor(); // Stop both motors
}

// Function to turn right (GREEN detected)
void turnRight() {
  mLeft(motorSpeed); // Move left motor forward
  mRight(-motorSpeed); // Move right motor backward
  delay(time90); // Turn for the defined time
  stopMotor(); // Stop both motors
}

// Function to make a u-turn (ORANGE detected)
void uTurn() {
  mLeft(-motorSpeed); // Move left motor forward
  mRight(motorSpeed); // Move right motor backward
  delay(time90*2); // Turn for the defined time
  stopMotor(); // Stop both motors
}

// Function to make a double left turn (PINK detected)
void doubleLeftTurn() {
  turnLeft(); // First left turn
  moveForward(); // Move forward after the first turn
  delay(timeSqr); // Move for the defined time
  turnLeft(); // Second left turn
  moveForward(); // Move forward
}

// Function to make a double right turn (LIGHT BLUE detected)
void doubleRightTurn() {
  turnRight(); // First right turn
  moveForward(); // Move forward after the first turn
  delay(timeSqr); // Move for the defined time
  turnRight(); // Second right turn
  moveForward(); // Move forward
}

// Function to nudge the mBot slightly to the left
void nudgeLeft() {
  if (sensor_state() != 0){ // Check if the black line is detected
    mLeft(motorSpeed-45); // Reduce speed of left motor
    mRight(motorSpeed+55); // Increase speed of right motor
    delay(100); // Nudge for 100ms
    moveForward(); // Move forward
  } else {
    stopMotor(); // Stop both motors
  }
}

// Function to nudge the mBot slightly to the right
void nudgeRight() {
  if (sensor_state() != 0){ // Check if the black line is detected
    mLeft(motorSpeed+55); // Increase speed of left motor
    mRight(motorSpeed-55); // Reduce speed of right motor
    delay(100); // Nudge for 100ms
    moveForward(); // Move forward
  } else {
    stopMotor(); // Stop both motors
  }
}