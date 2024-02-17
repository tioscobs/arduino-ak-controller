#define TRIGGER_PIN A0 // Analogic trigger pin (maybe this is obvious)
#define SEND_MS 300 // Serial writing delay in milisseconds

void setup() {
  pinMode(TRIGGER_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(TRIGGER_PIN) > 0 ? "1\n" : "0\n"); // Ternary operation that writes the bytes "X\n" on serial based on the trigger analogic read
  delay(SEND_MS); // Slimeball curse
}
