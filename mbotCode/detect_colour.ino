// Define RGB values for known colours as arrays
//calibrated values used
const float RED_arr[] = {273.15, 121.12, 82.01}; // Calibrated RGB values for Red
const float GREEN_arr[] = {128.80, 226.95, 179.26}; // Calibrated RGB values for Green
const float ORANGE_arr[] = {283.53, 187.00, 86.49}; // Calibrated RGB values for Orange
const float PINK_arr[] = {288.71, 232.48, 218.25}; // Calibrated RGB values for Pink
const float LIGHT_BLUE_arr[] = {97.68, 220.58, 233.94}; // Calibrated RGB values for Light Blue
const float WHITE_arr[] = {284.39, 252.45, 252.31}; // Calibrated RGB values for White
const float BLACK_arr[] = {-2.59, 7.23, 0.45}; // Calibrated RGB values for Black
const float GREY_arr[] = {59.00, 120.00, 113.80}; // Calibrated RGB values for Grey

// Define an array containing all colour arrays for easier access
const float* colourArrays[] = {
  RED_arr, GREEN_arr, ORANGE_arr, PINK_arr,
  LIGHT_BLUE_arr, WHITE_arr, BLACK_arr, GREY_arr
};

// Define a corresponding array of names of colour
const char* colourNames[] = {
  "Red", "Green", "Orange", "Pink",
  "Light Blue", "White", "Black", "Grey"
};

// Total number of colours
const int colourCount = 8;

/* Function to calculate Euclidean distance between a measured colour and a reference colour
   Parameters
   - colourArray: RGB values of the measured colour
   - referenceArray: RGB values of the reference colour
  Returns
  - Euclidean distance between the two colours
*/
float calculateEuclideanDistance(float colourArray[3], const float referenceArray[3]) {
  float distance = 0;
  for (int i = 0; i < 3; i++) {
    distance += pow(colourArray[i] - referenceArray[i], 2);
  }
  return sqrt(distance);
}

/* Function to identify closest matching colour
   Parameters:
   - colourArray: RGB values of the measured colour
   Returns
   - Index of the closest matching colour
*/
int identifyColour(float colourArray[3]) {
  float minDistance = calculateEuclideanDistance(colourArray, colourArrays[0]);
  int closestColourIndex = 0;

  // Loop through all known colours to find the closest match
  for (int i = 1; i < colourCount; i++) {
    float distance = calculateEuclideanDistance(colourArray, colourArrays[i]);
    if (distance < minDistance) {
      minDistance = distance; // Update minimum distance
      closestColourIndex = i; // Update closest colour index
    }
  }
  
  // Return the best match colour index
  return closestColourIndex;
}

/* Function to read and normalise the RGB values from the sensor on a scale from 0-255
   Parameters
   - colourArray: Array to store the normalised RGB values
   - blackArray: Calibrated RGB values representing the lower limit
   - greyDiff: Difference between corresponding RGB values in blackArray and whiteArray
*/ 
void readColour(float *colourArray, float *blackArray, float *greyDiff) {
  for (int i = 0; i < 3; i++){
    shine_LED(i);
    delay(RGBWait); 
    colourArray[i] = getAvgReading(5);
    colourArray[i] = (colourArray[i] - blackArray[i]) / (greyDiff[i]) * 255;
  }
}

/* Function to detect the colour of the paper underneath the mBot
   Returns: Index of the detected colour
*/
int detectColour() {
  // Sample colour reading (replace this with actual sensor reading code)
  readColour(colourArray, blackArray, greyDiff);

  // Detect the colour based on the Euclidean distance method
  int detectedColour = identifyColour(colourArray);

  return detectedColour;
}
