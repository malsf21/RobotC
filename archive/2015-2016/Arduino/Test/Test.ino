int motor1 = 12;
int motor2 = 3;
int button = 13;
int buttonState = 0; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(button);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
}
