/*Yury Ereshchenko 114012010
This codes controls the RGB light
When clicking you can change color, Double clicking turns the LED ON/OFF


05/10/2025

*/


//Setup Arduino pins
const int RedLEDPin = 9;
const int GreenLEDPin = 10;
const int BlueLEDPin = 11;

const int pushButton = 2;
int pushButtonState = 0;
int ledCounter = 1;

bool buttonPressed = false;

String currentColor = "OFF";

bool ledState = HIGH;
unsigned long previousMillis_blink = 0;
const long interval_blink = 1000;

unsigned long previousMillis_DClick = 0;
const long interval_DClick = 250;
int clickNum = 1;
bool PowerFlag = LOW;


// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(9600);

  pinMode(RedLEDPin, OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(BlueLEDPin, OUTPUT);

  pinMode(pushButton, INPUT);
}




// the loop function runs over and over again forever
void loop() {

  //////////////////////////////////////////////////////////////////////////////////
  //Inverse the state becuase module gives the opposite
  pushButtonState = digitalRead(pushButton);
    if (pushButtonState == LOW) {
    pushButtonState = HIGH;
  } else if (pushButtonState == HIGH) {
    pushButtonState = LOW;
  }


  Serial.print("Current Color : ");
  Serial.println(currentColor);
  Serial.println(PowerFlag);


  //Millis for ON/OFF finction for double click
  unsigned long currentMillis_DClick = millis();
  
  if (pushButtonState == HIGH && !buttonPressed) {
    ledCounter++;
    buttonPressed = true;
    delay(5);  //Debounce

     if (currentMillis_DClick - previousMillis_DClick < interval_DClick) {
    clickNum++;
    }

    if (clickNum == 2){
      PowerFlag = !PowerFlag;
      clickNum = 0;
    }

    else {
      clickNum = 1;
    }

    previousMillis_DClick = currentMillis_DClick;

  } else if (pushButtonState == LOW && buttonPressed) {
    buttonPressed = false;
    delay(5);  //Debounce
  }
  ///////////////////////////////////////////////////////////////////////////////////



  // //Millis for blinking function
  // unsigned long currentMillis_blink = millis();
  // if (currentMillis_blink - previousMillis_blink >= interval_blink) {
  //   previousMillis_blink = currentMillis_blink;
  //   if (ledState == LOW) {
  //     ledState = HIGH;
  //   } else {
  //     ledState = LOW;
  //   }
  // }




 


  //RED
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

  //GREEN
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

  //BLUE
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

  //YELLOW
  else if (ledCounter == 4 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorON(RedLEDPin);
      TurnColorON(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }

    else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }

    currentColor = ("YELLOW");
  }

  //PURPLE
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

  //CYAN
  else if (ledCounter == 6 && !PowerFlag) {
    if (ledState == HIGH) {
      TurnColorOFF(RedLEDPin);
      TurnColorON(GreenLEDPin);
      TurnColorON(BlueLEDPin);
    }

    else {
      TurnColorOFF(RedLEDPin);
      TurnColorOFF(GreenLEDPin);
      TurnColorOFF(BlueLEDPin);
    }

    currentColor = "CYAN";
  }

  //WHITE
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

  else if (ledCounter == 8) {
    ledCounter = 1;
  }

    //OFF
  if (PowerFlag) {
    TurnColorOFF(RedLEDPin);
    TurnColorOFF(GreenLEDPin);
    TurnColorOFF(BlueLEDPin);
    currentColor = "OFF";
    ledCounter = 0;
  }


}

void TurnColorON(int color) {
  digitalWrite(color, LOW);  // turn the led (HIGH is the voltage level)
}

void TurnColorOFF(int color) {
  digitalWrite(color, HIGH);  // turn the led (HIGH is the voltage level)
}
