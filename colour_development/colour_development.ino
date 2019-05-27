// definitions
const char* colour;

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

void setup() {
  Serial.begin(9600);
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledBlue,HIGH);

  digitalWrite(ledRed, LOW);
  delay(1000);
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  delay(1000);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledBlue, LOW);
  delay(1000);
  digitalWrite(ledBlue, HIGH);
}

void loop() {
  int var = 30;
  while (var < 200) {
  colourPicker(var, ledRed, ledGreen, ledBlue);
  colourPicker(var, goalRed, goalGreen, goalBlue);
  Serial.println(colour);
  delay(100);
  var++;
  } 
}

void colourPicker(int driver, int redLed, int greenLed, int blueLed) {
  if (driver < 40) {
    colourRGB(0, 0, 0, redLed, greenLed, blueLed);
    colour = "none";
  }
    else if (driver >= 40 && driver <= 49) {
    colourRGB(0, 0, 255, redLed, greenLed, blueLed);
    colour = "40-49: Pure Blue";
  }
  
  else if (driver >= 50 && driver <= 59) {
    colourRGB(0, 50, 220, redLed, greenLed, blueLed);
    colour = "50-59: Dark Blue";
  }
  else if (driver >= 60 && driver <= 69) {
    colourRGB(0, 100, 200, redLed, greenLed, blueLed);
    colour = "60-69: Blue Green";
  }
  else if (driver >= 70 && driver <= 79) {
    colourRGB(25, 150, 150, redLed, greenLed, blueLed);
    colour = "70-79: Green Blue";
  }
  else if (driver >= 80 && driver <= 89) {
    colourRGB(25, 200, 75, redLed, greenLed, blueLed);
    colour = "80-89: Green";
  }
  else if (driver >= 90 && driver <= 99) {
    colourRGB(50, 255, 0, redLed, greenLed, blueLed); 
    colour = "90-99: Dark Green";
  }
   else if (driver >= 100 && driver <= 109) {
    colourRGB(220, 200, 20, redLed, greenLed, blueLed); 
    colour = "100-109: Yellow Green";
  }
  else if (driver >= 110 && driver <= 119) {
    colourRGB(180, 200, 70, redLed, greenLed, blueLed); 
    colour = "110-119: Mint Green";
  }
  else if (driver >= 120 && driver <= 129) {
    colourRGB(240, 100, 20, redLed, greenLed, blueLed);
    colour = "120-129: Orange Pink";
  }
  else if (driver >= 130 && driver <= 139) {
    colourRGB(255, 50, 0, redLed, greenLed, blueLed);
    colour = "130-139: Pink";
  }
  else if (driver >= 140 && driver <= 149) {
    colourRGB(255, 25, 0, redLed, greenLed, blueLed);
    colour = "140-149: Pink Red";
  }
    else if (driver >= 150 && driver <= 159) {
    colourRGB(255, 0, 100, redLed, greenLed, blueLed);
    colour = "150-159: Pure Red";
  }

  else if (driver >= 160 && driver <= 169) {
    colourRGB(255, 0, 255, redLed, greenLed, blueLed);
    colour = "160-169: Dark Purple";
  }

  else if (driver >= 170 && driver <= 179) {
    colourRGB(255, 50, 220, redLed, greenLed, blueLed);
    colour = "170-179: Light Purple";
  }

  else {
    colourRGB(255, 100, 200, redLed, greenLed, blueLed);
    colour = "Max; Lilac";
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
