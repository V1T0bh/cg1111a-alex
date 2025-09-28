/* Function to determine the state of the line follower
   Returns:
   0 - Both sensors detect the black line (no light)
   1 - Only the right sensor detects the black line (right light)
   2 - Only the left sensor detects the black line (left light)
   3 - Both sensors do not detect the black line (both light)
*/
int sensor_state(){
  return(lineFollower.readSensors()); 
}


 
