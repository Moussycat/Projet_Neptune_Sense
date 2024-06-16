/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-led-blink
 */

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin GPIO18 as an output.
  pinMode(26, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(26, HIGH); // turn the LED on
  delay(500);             // wait for 500 milliseconds
  digitalWrite(26, LOW);  // turn the LED off
  delay(500);             // wait for 500 milliseconds
}
