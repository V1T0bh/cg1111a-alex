// Function to get ambient IR value (IR emitter is off)
int ambient_IR()
{
  shine_LED(0); // Off IR emitter
  delay(5);
  return analogRead(IR);
}

// Function to get reflected IR value (IR emitter is on)
int reflected_IR()
{
  shine_LED(3); // On IR emitter
  delay(5);
  return analogRead(IR);
}

// Function to calculate the difference between the reflected and ambient IR values
int difference_IR()
{
  return (reflected_IR() - ambient_IR());
}