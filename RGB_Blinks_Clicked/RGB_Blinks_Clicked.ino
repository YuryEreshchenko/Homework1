/*
 * Yury Ereshchenko 114012010
 * RGB LED Controller with Button Interface
 * 
 * Single click: Cycle through colors
 * Double click: Toggle LED ON/OFF
 * The LED color and state are indiciated in the serial monitor
 * 
 * Date: 14/10/2025
 */

// Pin configuration
const int RedLEDPin = 9;
const int GreenLEDPin = 10;
const int BlueLEDPin = 11;
const int pushButton = 2;

// Button state variables
int pushButtonState = 0;
int ledCounter = 1;           // Tracks current color (1-7)
bool buttonPressed = false;   // Prevents multiple triggers from single press

String currentColor = "OFF";

// LED state (currently always HIGH since blinking is disabled)
bool ledState = HIGH;

// Double-click detection variables
unsigned long previousMillis_DClick = 0;
const long interval_DClick = 250;     // Max time (ms) between clicks for double-click
int clickNum = 1;
bool PowerFlag = LOW;                 // Power state: LOW = on, HIGH = off


// !!!Blinking functionality (disabled)!!!!
// Uncomment to make LEDs blink at 1-second intervals
/* Blinking variables (currently disabled)
unsigned long previousMillis_blink = 0;
const long interval_blink = 1000; 
*/

void setup() {
  Serial.begin(9600);

  pinMode(RedLEDPin, OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(BlueLEDPin, OUTPUT);
  pinMode(pushButton, INPUT);
}

void loop() {

  // Invert button state because hardware module gives opposite logic
  pushButtonState = digitalRead(pushButton);
  if (pushButtonState == LOW) {
    pushButtonState = HIGH;
  } else if (pushButtonState == HIGH) {
    pushButtonState = LOW;
  }

  // Debug output
  Serial.print("Current Color : ");
  Serial.println(currentColor);
  Serial.println(PowerFlag);

  // Double-click detection and color cycling
  unsigned long currentMillis_DClick = millis();
  
  // Detect button press
  if (pushButtonState == HIGH && !buttonPressed) {
    ledCounter++;              // Advance to next color
    buttonPressed = true;
    delay(5);                  // Debounce

    // Check if this press is within double-click window
    if (currentMillis_DClick - previousMillis_DClick < interval_DClick) {
      clickNum++;
    }

    // Double-click detected - toggle power
    if (clickNum == 2) {
      PowerFlag = !PowerFlag;
      clickNum = 0;
    }
    else {
      clickNum = 1;
    }

    previousMillis_DClick = currentMillis_DClick;

  } 
  // Detect button release
  else if (pushButtonState == LOW && buttonPressed) {
    buttonPressed = false;
    delay(5);                  // Debounce
  }

  // Blinking functionality (disabled)
  // Uncomment to make LEDs blink at 1-second intervals
  /*
  unsigned long currentMillis_blink = millis();
  if (currentMillis_blink - previousMillis_blink >= interval_blink) {
    previousMillis_blink = currentMillis_blink;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
  */

  // Color selection - only active if power is ON (!PowerFlag)
  
  // RED
  if (ledCounter == 1 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorON(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    } else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }
    currentColor = "RED";
  }

  // GREEN
  else if (ledCounter == 2 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorOFF(RedLEDPin);
      TurnColorON(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    } else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }
    currentColor = "GREEN";
  }

  // BLUE
  else if (ledCounter == 3 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorON(BlueLEDPin);
    } else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }
    currentColor = "BLUE";
  }

  // YELLOW (Red + Green)
  else if (ledCounter == 4 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorON(RedLEDPin);
      TurnColorON(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    } else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }
    currentColor = "YELLOW";
  }

  // PURPLE (Red + Blue)
  else if (ledCounter == 5 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorON(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorON(BlueLEDPin);
    } else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }
    currentColor = "PURPLE";
  }

  // CYAN (Green + Blue)
  else if (ledCounter == 6 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorOFF(RedLEDPin);
      TurnColorON(GreenLEDPin);
      TurnColorON(BlueLEDPin);
    } else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }
    currentColor = "CYAN";
  }

  // WHITE (Red + Green + Blue)
  else if (ledCounter == 7 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorON(RedLEDPin);
      TurnColorON(GreenLEDPin);
      TurnColorON(BlueLEDPin);
    } else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }
    currentColor = "WHITE";
  }

  // Reset counter to cycle back to first color
  else if (ledCounter == 8) {
    ledCounter = 1;
  }

  // Power OFF - turn off all LEDs
  if (PowerFlag) {
    TurnColorOFF(RedLEDPin);
    TurnColorOFF(GreenLEDPin);
    TurnColorOFF(BlueLEDPin);
    currentColor = "OFF";
    ledCounter = 0;
  }
}

// Functions to Turn ON and OFF led to make code more readable
// Note: Uses LOW to turn ON and HIGH to turn OFF (common anode RGB LED)
void TurnColorON(int color) {
  digitalWrite(color, LOW);
}

void TurnColorOFF(int color) {
  digitalWrite(color, HIGH);
}