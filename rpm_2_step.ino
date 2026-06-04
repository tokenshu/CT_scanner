#define STEP_PIN_1 6  // STEP Pin from motor
#define DIR_PIN_1 5   // DIR Pin for motor

#define LED1 9 // diode 1
#define LED2 8 // diode 2
#define LED3 7 // diode 3
#define LED4 12 // diode 4
#define LED5 11 // diode 5
#define LED6 10 // diode 6

float rpmValue = 0.0f;

void setup() {
    pinMode(STEP_PIN_1, OUTPUT);
    pinMode(DIR_PIN_1, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
    Serial.begin(115200); //baudrate set
    Serial.setTimeout(1);
}

void loop() {

    if (Serial.available()) { // check for incoming serial data
        rpmValue = Serial.readString().toInt(); // read RPM value sent from GUI
    }

    if (rpmValue == 0) {
        return;
    }

    if (rpmValue > 0) {
        digitalWrite(DIR_PIN_1, HIGH);
    } else {
        digitalWrite(DIR_PIN_1, LOW); 
    } // set motor direction based on RPM sign

    float rpmAbs = abs(rpmValue);

    rpmAbs = constrain(rpmAbs, 1.0f, 300.0f); // limit RPM to valid range

    float speedDelay1 = 750.0 / rpmAbs; // convert RPM to step pulse delay (200 steps/rev)

    stepMotor(STEP_PIN_1, (unsigned int)speedDelay1);

    updateLEDs(rpmAbs);
}

// step motor function with dynamic speed
void stepMotor(int stepPin, unsigned int delayTime) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
}
// LED speed signalization
void updateLEDs(int rpm)
{
    digitalWrite(LED1, rpm >= 1);
    digitalWrite(LED2, rpm >= 2);
    digitalWrite(LED3, rpm >= 3);
    digitalWrite(LED4, rpm >= 4);
    digitalWrite(LED5, rpm >= 5);
    digitalWrite(LED6, rpm >= 6);
}

