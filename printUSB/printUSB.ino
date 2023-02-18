

#define FINGERPRINT_SIZE 80
unsigned char fingerPrint[FINGERPRINT_SIZE] = {0};
unsigned char fingerPrintLength = 0;
#include <DigiKeyboard.h>

#define KEY_ARROW_UP 0x52

void setup()
{
    DigiKeyboard.delay(2000);
   // DigiKeyboard.write("HIIII\n");
   // DigiKeyboard.delay(2000);
   // DigiKeyboard.print((int)fingerPrintLength);
   // DigiKeyboard.print("\n");

    //for (int i = 0; i < FINGERPRINT_SIZE / 8; i++)
    //{
    //    for (int j = 0; j < 8; j++)
    //    {
    //        DigiKeyboard.printf("%03d\t", (unsigned int)fingerPrint[i * 8 + j]);
    //    }
    //    DigiKeyboard.print("\n");
    //}
    DigiKeyboard.write("https://docs.google.com/spreadsheets/d/1PwbZ9qDcFp-lsfXqmGaZO1mDOQxvpiPUU8AVCTKzeY8/edit\n");
    DigiKeyboard.delay(2000);
    //DigiKeyboard.sendKeyStroke(KEY_ARROW_UP);
    DigiKeyboard.delay(1000);
    for (int i = 0; i < FINGERPRINT_SIZE; i++)
        DigiKeyboard.printf("%02x", (unsigned int)fingerPrint[i]);

    DigiKeyboard.print("\n");
}
void loop()
{
}
