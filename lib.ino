const int irPin1 = 7;
const int irPin2 = 8;
const int soundSensorPin = A0;
const int buzzerPin = 9;
int count = 0;
boolean state1 = true;
boolean state2 = true;
boolean outsideIr = false;
boolean isPeopleExiting = false;
int i = 1;
boolean isCountUpdated = false;
boolean isFullCapacity = false;
void setup() {
Serial.begin(9600);
pinMode(irPin1, INPUT);
pinMode(irPin2, INPUT);
pinMode(buzzerPin, OUTPUT);
}
void loop() {
// IR Sensor Logic
if (!digitalRead(irPin1) && i == 1 && state1) {
outsideIr = true;
delay(100);
i++;
state1 = false;
}
if (!digitalRead(irPin2) && i == 2 && state2) {
outsideIr = true;
delay(100);
i = 1;
if (count < 10) {
count++;
Serial.print("People Inside: ");
Serial.println(count);
}
if (count == 10) {
isFullCapacity = true;
Serial.println("Full Capacity");
}
state2 = false;
}
if (!digitalRead(irPin2) && i == 1 && state2) {
outsideIr = true;
delay(100);
i = 2;
state2 = false;
}
if (!digitalRead(irPin1) && i == 2 && state1) {
outsideIr = true;
delay(100);
if (count > 0) {
count--;
Serial.print("People Inside: ");
Serial.println(count);
}
i = 1;
state1 = false;
}
if (digitalRead(irPin1)) {
state1 = true;
}
if (digitalRead(irPin2)) {
state2 = true;
}
// Sound Sensor Logic
int soundLevel = analogRead(soundSensorPin);
if (soundLevel > 36) {
for (int i = 0; i < 3000; i += 100) {
tone(buzzerPin, 1000);
delay(100);
noTone(buzzerPin);
delay(100);
 }
}
delay(100);
}
