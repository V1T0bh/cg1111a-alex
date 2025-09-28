// Code to calibrate the RGB values

//placeholder values used
float whiteArray[3] = {932.80, 983.60, 954.20}; // Calibrated RGB values for the upper limit
float blackArray[3] = {873.80, 863.60, 840.40}; // Calibrated RGB values for the lower limit
float greyDiff[3] = {59.00, 120.00, 113.80}; // Difference between the upper and lower limit
float colourArray[3] = {0, 0, 0}; // Array to temporarily store the calibrated RGB values for each colour

// Function to calculate the average of 'times' analog readings from the LDR for the R, G, B components
float getAvgReading(int times)
{
  float sum = 0;
  for (int i = 0; i < times; i += 1)
  {
    sum += analogRead(LDR);
    delay(LDRWait);
  }
  return sum / (float) times; // Return the average value
}

// Function to measure and output the RGB values for the white sample
void getWhiteArray(float *whiteArray){
  Serial.println("Put White Sample for Calibration ...");
  delay(10000); // Delay to allow placement of white sample
  
  for (int i = 0; i < 3; i++){
    shine_LED(i); // Activate the LED (R, G, B) depending on the value of i
    delay(RGBWait); // Wait for the LDR to stablise
    whiteArray[i] = getAvgReading(5); // Measure the RGB values
    delay(1000); 
  }

  // Output the measured RGB values for the white sample
  Serial.println("Data For White Sample");
  Serial.println(whiteArray[0]);
  Serial.println(whiteArray[1]);
  Serial.println(whiteArray[2]);
}

// Function to measure and output the RGB values for the black sample
void getBlackArray(float *blackArray){
  Serial.println("Put Black Sample for Calibration ...");
  delay(10000); // Delay to allow placement of black sample
  
  for (int i = 0; i < 3; i++){
    shine_LED(i); // Activate the LED (R, G, B) depending on the value of i
    delay(RGBWait); // Wait for the LDR to stablise
    blackArray[i] = getAvgReading(5); // Measure the RGB values
    delay(1000); 
  }

  // Output the measured RGB values for the black sample
  Serial.println("Data For Black Sample");
  Serial.println(blackArray[0]);
  Serial.println(blackArray[1]);
  Serial.println(blackArray[2]);
}

// Calibrates white and black samples, then reads and outputs RGB values based on white and black
void setBalance()
{
  // Measure and output the RGB values for white sample
  getWhiteArray(whiteArray);

  // Measure and output the RGB values for black sample
  getBlackArray(blackArray);

  // Calculate and output the values in the greyDiff array
  for (int j = 0; j < 3; j += 1)
  {
    greyDiff[j] = whiteArray[j] - blackArray[j];
  }

  // Output the calculated RGB values for the greyDiff array
  Serial.println("Data For greyDiff array");
  Serial.println(greyDiff[0]);
  Serial.println(greyDiff[1]);
  Serial.println(greyDiff[2]);

  // Prompt user to prepare the colour sample for data collection
  Serial.println("Colour Sample for Data Collection ...");
  delay(2000);

  // Loop through to get the RGB values for each colour sample
  for (int k = 0; k < 7; k += 1)
  {
    Serial.print("Prepare Colour  ");
    Serial.print(k+1);
    Serial.println("For Data Collection ...");
    delay(10000);
    
    // Measure and normalise the RGB values for the colour sample on a range 0-255
    readColour(colourArray, blackArray, greyDiff);

    // Output the measured RGB values for each colour sample
    Serial.print("Data for colour ");
    Serial.println(k+1);
    Serial.print("{");
    Serial.print(colourArray[0]);
    Serial.print(",");
    Serial.print(colourArray[1]);
    Serial.print(",");
    Serial.print(colourArray[2]);
    Serial.print("}");
  }
}