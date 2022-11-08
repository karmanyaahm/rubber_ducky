#include "DigiKeyboard.h"
#include "./VAR.h"

#define DOMAINS "ipfs.io cloudflare-ipfs.com"

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

  DigiKeyboard.sendKeyStroke(KEY_SPACE, MOD_GUI_LEFT);
  DigiKeyboard.delay(1500);
  DigiKeyboard.print("terminal");
    DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(3000);
  DigiKeyboard.print(F("cd Applications\n"));
  DigiKeyboard.delay(2000);  DigiKeyboard.sendKeyStroke(KEY_ENTER);
DigiKeyboard.delay(1000);
  DigiKeyboard.print(F("for i in " DOMAINS "; do curl https://$i" LINK " --output /Users/Shared/oreo.jpg && break; done; osascript -e 'tell application \"Finder\" to set desktop picture to POSIX file \"/Users/Shared/oreo.png\"';exit\n"));
  DigiKeyboard.delay(50);

  done++;
}
