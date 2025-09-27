const int soundSensorPin = 2;  // Pin connected to the sound sensor
const int relayPin = 3;        // Pin connected to the relay
const int ledRedPin = 4;       // Pin for red LED (indicating pump off)
const int ledBluePin = 5;      // Pin for blue LED (indicating pump on)

int soundState = 0;            // Variable to store sound sensor state
int lastSoundState = 0;        // Variable to store the previous state of sound sensor
bool pumpState = false;        // Variable to track pump state (on/off)

void setup() {
  pinMode(soundSensorPin, INPUT);  // Set sound sensor pin as input
  pinMode(relayPin, OUTPUT);       // Set relay pin as output
  pinMode(ledRedPin, OUTPUT);      // Set red LED pin as output
  pinMode(ledBluePin, OUTPUT);     // Set blue LED pin as output
  
  digitalWrite(ledRedPin, HIGH);  // Turn on red LED to indicate pump is off
  digitalWrite(ledBluePin, LOW);  // Turn off blue LED to indicate pump is off
  digitalWrite(relayPin, LOW);    // Ensure the relay is off initially
}

void loop() {
  soundState = digitalRead(soundSensorPin);  // Read the state of the sound sensor
  
  // If a clap is detected (a HIGH state change in the sound sensor)
  if (soundState == HIGH && lastSoundState == LOW) {
    // Toggle the pump state
    pumpState = !pumpState;  
    
    // Control the relay based on pump state
    if (pumpState) {
      digitalWrite(relayPin, HIGH);  // Turn the pump (fountain) on
      digitalWrite(ledRedPin, LOW);  // Turn off red LED
      digitalWrite(ledBluePin, HIGH); // Turn on blue LED
    } else {
      digitalWrite(relayPin, LOW);   // Turn the pump (fountain) off
      digitalWrite(ledRedPin, HIGH); // Turn on red LED
      digitalWrite(ledBluePin, LOW); // Turn off blue LED
    }
    
    delay(500);  // Debounce delay to avoid multiple toggles from one clap
  }
 
  lastSoundState = soundState;  // Store the current state for the next loop
}
