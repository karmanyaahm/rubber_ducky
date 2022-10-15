#include "DigiKeyboard.h"
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

  DigiKeyboard.sendKeyStroke(0);
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

  DigiKeyboard.print(F("wget https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/Oreo-Two-Cookies.png/1200px-Oreo-Two-Cookies.png -OutFile ~/oreo.png;"
                      // " reg add \"HKCU\\Control Panel\\Desktop\" /v WallPaper /d \"%USERPROFILE%\\oreo.png\" /f;"
                       " $wshell = New-Object -ComObject wscript.shell; $wshell.Run(\"%USERPROFILE%/oreo.png\"); sleep 4; $wshell.SendKeys(\"^l\"); sleep 4;"
                       " kill -Force -Name \"Microsoft.Photos\";"
                       //" logoff; "
                       " exit;\n" ));

  done++;
}
