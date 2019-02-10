/*
   RadioLib Morse Transmit Example

   This example sends Morse code message using 
   SX1278's FSK modem.

   Other modules that can be used for Morse:
    - SX1272/73/76/77/79
    - RF69
    - SX1231
    - CC1101
*/

// include the library
#include <RadioLib.h>

// SX1278 module is in slot A on the shield
SX1278 fsk = RadioShield.ModuleA;

// create Morse client instance using the FSK module
MorseClient morse(&fsk);

void setup() {
  Serial.begin(9600);

  // initialize SX1278
  Serial.print(F("[SX1278] Initializing ... "));
  // carrier frequency:           434.0 MHz
  // bit rate:                    48.0 kbps
  // frequency deviation:         50.0 kHz
  // Rx bandwidth:                125.0 kHz
  // output power:                13 dBm
  // current limit:               100 mA
  // sync word:                   0x2D  0x01
  int state = fsk.beginFSK();
  if(state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }

  // initialize Morse client
  Serial.print(F("[Morse] Initializing ... "));
  // base frequency:              434.0 MHz
  // speed:                       20 words per minute
  state = morse.begin(434.0);
  if(state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}

void loop() {
  Serial.print(F("[Morse] Sending Morse data ... "));

  // MorseClient supports all methods of the Serial class
  // NOTE: Characters that do not have ITU-R M.1677-1
  //       representation will not be sent! Lower case
  //       letters will be capitalized.

  // send start signal first
  morse.startSignal();
  
  // Arduino String class
  String aStr = "Arduino String";
  morse.print(aStr);

  // character array (C-String)
  morse.print("C-String");

  // character
  morse.print('c');
  
  // byte
  // formatting DEC/HEX/OCT/BIN is supported for
  // any integer type (byte/int/long)
  morse.print(255, HEX);

  // integer number
  int i = 1000;
  morse.print(i);

  // floating point number
  // NOTE: When using println(), the transmission will be 
  //       terminated with cross signal (.-.-.).
  float f = -3.1415;
  morse.println(f, 3);

  Serial.println(F("done!"));

  // wait for a second before transmitting again
  delay(1000);
}