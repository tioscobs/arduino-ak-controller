#define TRIGGER_PIN A0
#define TRIGGER_MS 400
#define BUTTON_PIN A1

bool trigger_down = false;
bool trigger_hold = false;

bool button_down = false;

int mode = 0; 
int mode_leds[2] = {2, 3};

// Util functions

void switch_mode(){
  if(mode == 0) mode = 1;
  else mode = 0;
}

// Main functions
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Trigger firing system (Serial writing)
  if(analogRead(TRIGGER_PIN) > 0){
    if(!(trigger_down)){
      trigger_down = true;
      Serial.println("1"); // One-click
      delay(TRIGGER_MS);
    }else if (!(trigger_hold) && !(mode == 0)){
      trigger_hold = true;
      Serial.println("2"); // Holding
    }
  }else if(analogRead(TRIGGER_PIN) <= 0 && trigger_down){
    trigger_down = false;
    if(trigger_hold) trigger_hold = false;
  }

  // Switching mode system
  if(analogRead(BUTTON_PIN) > 300 && !(button_down)){
    button_down = true;
  }else if(analogRead(BUTTON_PIN) <= 0 && button_down){
    button_down = false;
    switch_mode();
  }
  for(int i = 0; i < 2; i++){
    digitalWrite(mode_leds[i == mode ? mode : i], i == mode ? HIGH : LOW);
  }
}
