

#define FINGERPRINT_SIZE 80
unsigned char fingerPrint[FINGERPRINT_SIZE] = {0};
unsigned char fingerPrintLength = 0;
#include <DigiKeyboard.h>

static char *Encode(char* ret, const unsigned char* data, size_t in_len)
{
    // https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594
    static constexpr char sEncodingTable[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'};

    size_t out_len = 4 * ((in_len + 2) / 3);

    ret[out_len] = '\0';
    size_t i;
    char *p = ret;

    for (i = 0; i < in_len - 2; i += 3)
    {
        *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
        *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
        *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2) | ((int)(data[i + 2] & 0xC0) >> 6)];
        *p++ = sEncodingTable[data[i + 2] & 0x3F];
    }
    if (i < in_len)
    {
        *p++ = sEncodingTable[(data[i] >> 2) & 0x3F];
        if (i == (in_len - 1))
        {
            *p++ = sEncodingTable[((data[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else
        {
            *p++ = sEncodingTable[((data[i] & 0x3) << 4) | ((int)(data[i + 1] & 0xF0) >> 4)];
            *p++ = sEncodingTable[((data[i + 1] & 0xF) << 2)];
        }
        *p++ = '=';
    }

    return ret;
}
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
    DigiKeyboard.sendKeyStroke(KEY_ARROW_UP);
    DigiKeyboard.delay(1000);
    for (int i = 0; i < FINGERPRINT_SIZE; i++)
        DigiKeyboard.printf("%02x", (unsigned int)fingerPrint[i]);

    DigiKeyboard.print("\n");
}
void loop()
{
}
