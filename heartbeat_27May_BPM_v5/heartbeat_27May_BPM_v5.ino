// definitions
const int HR_RX = 2; // initialising sensor to pin 2
const int buzzer = 3; // initialising buzzer to pin 2
byte oldSample, sample; // byte size variables (0-255)
int BPM; // heart rate variable
long pulseTime, lastPulseTime; // variables for measuring difference time between pulse signals
const char* colour;
int goal = random(70,150);
int match;
bool score = false;

// averaging
unsigned long currentMillis = 0;
unsigned long prevMillis = 0;
const long interval = 5000;
int totalBPM;
int countBPM;

// LEDs
int ledRed = 8;
int ledGreen = 9;
int ledBlue = 10;

int goalRed = 5;
int goalGreen = 6;
int goalBlue = 7;

int redValue = 0;
int blueValue = 0;
int greenValue = 0;

// initialise variables for circular buffer
volatile int diff1 = 0;
volatile int diff2 = 0;
volatile int diff3 = 0;
volatile int diff4 = 0;
volatile int diff5 = 0;
volatile int diff6 = 0;
volatile int diff7 = 0;
volatile int diff8 = 0;
volatile int diff9 = 0;
volatile int diff10 = 0;

void setup() {
  Serial.begin(9600); // sets data rate in bits per second
  pinMode(HR_RX, INPUT); //sets signal pin to input
  pinMode(buzzer, OUTPUT); //set buzzer to output
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  pinMode(goalRed, OUTPUT);
  pinMode(goalGreen, OUTPUT);
  pinMode(goalBlue, OUTPUT);

  allOff();
  
  digitalWrite(ledRed, LOW);
  delay(1000);
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  delay(1000);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledBlue, LOW);
  delay(1000);
  digitalWrite(ledBlue, HIGH);

  digitalWrite(goalRed, LOW);
  delay(1000);
  digitalWrite(goalRed, HIGH);
  digitalWrite(goalGreen, LOW);
  delay(1000);
  digitalWrite(goalGreen, HIGH);
  digitalWrite(goalBlue, LOW);
  delay(1000);
  digitalWrite(goalBlue, HIGH);

  digitalWrite(ledRed, LOW);
  digitalWrite(goalRed, LOW);
  delay(200);
  digitalWrite(ledRed, HIGH);
  digitalWrite(goalRed, HIGH);
  delay(200);
  digitalWrite(ledRed, LOW);
  digitalWrite(goalRed, LOW);
  delay(200);
  digitalWrite(ledRed, HIGH);
  digitalWrite(goalRed, HIGH);
  
  
  Serial.println("Waiting for heart beat..."); // prints loading message to serial monitor
  while (!digitalRead(HR_RX)) {}; // wait till heart beat detected

  Serial.println("Heart beat detected!");
}

void loop() {
  sample = digitalRead(HR_RX); // store signal output
  // if there is a sample, and it does not equal the old sample
  if(sample && (oldSample != sample)) { 
    Serial.print("BPM: ");
    Serial.print(BPM);
    Serial.print("; ");
    Serial.print("Goal: ");
    Serial.println(goal);
    HRpulse(); // use HRpulse (see below) to determine BPM)
    if(BPM > (goal - 2) && BPM < (goal + 2)) {
      match = goal;
      colourPicker(match, ledRed, ledGreen, ledBlue);
      colourPicker(match, goalRed, goalGreen, goalBlue);
      party(); // let wearer and viewer know that the goal has been met
      goal = random(60,150); // choose a new goal
      guide(); // play a sound to indicate if new goal is higher or lower than current BPM
    }
  }
  colourPicker(BPM, ledRed, ledGreen, ledBlue); // use colourPicker (see below) to set BPM colour
  colourPicker(goal, goalRed, goalGreen, goalBlue); //use colourPicker to set goal colour
  oldSample = sample; //store last signal received
}

void party() {
  int t = 0;
  while(t < 3) {
    allOff();
    delay(200);
    tone(buzzer, 500);
    colourPicker(match, ledRed, ledGreen, ledBlue);
    colourPicker(match, goalRed, goalGreen, goalBlue);
    delay(200);
    noTone(buzzer);
    t++;
  }
}

void guide() {
  if(goal > BPM) {
    tone(buzzer, 1000);
  }
  else {
    tone(buzzer, 200);
  }
  delay(500);
  noTone(buzzer);
}
  
void HRpulse() {
  pulseTime = millis();
  rollBuffer();
  diff1 = pulseTime - lastPulseTime;
  if (diff10 != 0) {
    BPM = 60000 / ((diff1 + diff2 + diff3 + diff4 + diff5 + diff6 + diff7 + diff8 + diff9 + diff10)/10);
  }
  lastPulseTime = pulseTime;
}

void rollBuffer() {
  diff10 = diff9;
  diff9 = diff8;
  diff8 = diff7;
  diff7 = diff6;
  diff6 = diff5;
  diff5 = diff4;
  diff4 = diff3;
  diff3 = diff2;
  diff2 = diff1;
  diff1 = 0;
}

void allOff() {
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledBlue,HIGH);
  digitalWrite(goalRed,HIGH);
  digitalWrite(goalGreen,HIGH);
  digitalWrite(goalBlue,HIGH);
}

void colourPicker(int driver, int redLed, int greenLed, int blueLed) {
  if (driver < 40) {
    colourRGB(0, 0, 0, redLed, greenLed, blueLed);
  }
    else if (driver >= 40 && driver <= 49) {
    colourRGB(0, 0, 255, redLed, greenLed, blueLed);
  }
  else if (driver >= 50 && driver <= 59) {
    colourRGB(0, 50, 220, redLed, greenLed, blueLed);
  }
  else if (driver >= 60 && driver <= 69) {
    colourRGB(0, 100, 200, redLed, greenLed, blueLed);
  }
  else if (driver >= 70 && driver <= 79) {
    colourRGB(25, 150, 150, redLed, greenLed, blueLed);
  }
  else if (driver >= 80 && driver <= 89) {
    colourRGB(25, 200, 75, redLed, greenLed, blueLed);
  }
  else if (driver >= 90 && driver <= 99) {
    colourRGB(50, 255, 0, redLed, greenLed, blueLed); 
  }
  else if (driver >= 100 && driver <= 109) {
    colourRGB(220, 200, 20, redLed, greenLed, blueLed);
  }
  else if (driver >= 110 && driver <= 119) {
    colourRGB(180, 200, 70, redLed, greenLed, blueLed); 
  }
  else if (driver >= 120 && driver <= 129) {
    colourRGB(240, 100, 20, redLed, greenLed, blueLed);
  }
  else if (driver >= 130 && driver <= 139) {
    colourRGB(255, 50, 0, redLed, greenLed, blueLed);
  }
  else if (driver >= 140 && driver <= 149) {
    colourRGB(255, 25, 0, redLed, greenLed, blueLed);
  }
  else if (driver >= 150 && driver <= 159) {
    colourRGB(255, 0, 100, redLed, greenLed, blueLed);
  }
  else if (driver >= 160 && driver <= 169) {
    colourRGB(255, 0, 255, redLed, greenLed, blueLed);
  }

  else if (driver >= 170 && driver <= 179) {
    colourRGB(255, 50, 220, redLed, greenLed, blueLed);
  }
  else {
    colourRGB(255, 100, 200, redLed, greenLed, blueLed);
  } 
}

void colourRGB(int red, int green, int blue, int redLed, int greenLed, int blueLed) {
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(redLed, constrain(red,0,255));
  analogWrite(greenLed, constrain(green,0,255));
  analogWrite(blueLed, constrain(blue,0,255));
}
