MeBuzzer buzzer;

// Function to play Star Wars theme
void celebrate() {
  buzzer.tone(440, 250);  // A4 (440 Hz)
  delay(250);
  buzzer.tone(440, 250);  // A4 (440 Hz)
  delay(250);
  buzzer.tone(440, 250);  // A4 (440 Hz)
  delay(250);
  buzzer.tone(349, 175);  // F4 (349 Hz)
  delay(175);
  buzzer.tone(523, 75);   // C5 (523 Hz)
  delay(75);
  buzzer.tone(440, 250);  // A4 (440 Hz)
  delay(250);
  buzzer.tone(349, 175);  // F4 (349 Hz)
  delay(175);
  buzzer.tone(523, 75);   // C5 (523 Hz)
  delay(75);
  buzzer.tone(440, 500);  // A4 (440 Hz)
  delay(500);

  buzzer.tone(659, 250);  // E5 (659 Hz)
  delay(250);
  buzzer.tone(659, 250);  // E5 (659 Hz)
  delay(250);
  buzzer.tone(659, 250);  // E5 (659 Hz)
  delay(250);
  buzzer.tone(698, 175);  // F5 (698 Hz)
  delay(175);
  buzzer.tone(523, 75);   // C5 (523 Hz)
  delay(75);
  buzzer.tone(415, 250);  // G#4 (415 Hz)
  delay(250);
  buzzer.tone(349, 175);  // F4 (349 Hz)
  delay(175);
  buzzer.tone(523, 75);   // C5 (523 Hz)
  delay(75);
  buzzer.tone(440, 500);  // A4 (440 Hz)
  delay(500);
}
