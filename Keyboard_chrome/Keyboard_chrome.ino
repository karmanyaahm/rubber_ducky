#define LAYOUT_US_ENGLISH
#include "DigiKeyboard.h"

const bool vid = 0;
//const char vidlink[] = "https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/Oreo-Two-Cookies.png/1183px-Oreo-Two-Cookies.png";

#define KEY_ARROW_UP 0x52

void setup()
{
  pinMode(1, OUTPUT); // LED on Model B
  digitalWrite(1, HIGH);
  DigiKeyboard.delay(500);
  digitalWrite(1, LOW);


}

struct s
{
   byte mod;
   byte key;
  uint16_t d_t;
};

int done = 0;

s s1[] = {
  {0, KEY_ESC, 500},
  {0, KEY_ESC, 500},
  {0, KEY_ESC, 500},
  {0, KEY_ESC, 500},
  {MOD_CONTROL_LEFT,  KEY_T, 1000},
  {MOD_CONTROL_LEFT, KEY_L, 500},
};
const char link[] = "https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/Oreo-Two-Cookies.png/1183px-Oreo-Two-Cookies.png";
s s2[] = {
  {MOD_CONTROL_LEFT, KEY_S, 1000},
  {MOD_CONTROL_LEFT, KEY_W, 200},
  
  
  {MOD_ALT_LEFT | MOD_SHIFT_LEFT, KEY_M, 3000}, // file browser is open now

  {0, KEY_TAB, 900},
  {0, KEY_ARROW_UP, 75},
  {0, KEY_ARROW_UP, 75},
  {0, KEY_ARROW_UP, 75},
  {0, KEY_ARROW_UP, 75},
  {0, KEY_ARROW_UP, 75},
  {0, KEY_ARROW_UP, 75},
  {0, KEY_ENTER, 2000}, // opening recents

  {MOD_SHIFT_LEFT, KEY_TAB, 0},
  {MOD_SHIFT_LEFT, KEY_TAB, 0},
  {0, KEY_TAB, 1000}, // on file now
  {MOD_CONTROL_LEFT, KEY_SPACE, 700},
  {MOD_SHIFT_LEFT, KEY_TAB, 700},
  {MOD_SHIFT_LEFT, KEY_TAB, 300},
  {MOD_SHIFT_LEFT, KEY_TAB, 300},
  {MOD_SHIFT_LEFT, KEY_TAB, 300},
  {MOD_SHIFT_LEFT, KEY_TAB, 300},
// // 9250ms and 13 critical keypresses
  
  /*  //instead this
    {MOD_SHIFT_LEFT | MOD_ALT_LEFT, KEY_N, 500},
    {0, KEY_TAB, 100},
    {0, KEY_TAB, 100},
    {0, KEY_TAB, 100},
    {0, KEY_ENTER, 3000},
    {MOD_CONTROL_LEFT, KEY_SPACE, 700},
    {MOD_SHIFT_LEFT, KEY_TAB, 700},
    */
    //end this 5200 ms and 7 keypresses
    // but can be broken by file/drive syncing notifs or update(?) notifs
    //but theres few file manager loading issues in this version
    //pros and cons

    // dismiss lets make a shortcut banners in file manager affect both
  


  {0, KEY_ENTER, 600}, // open menu
  {0, KEY_ARROW_UP, 1000},
  {0, KEY_ENTER, 300}, // set

  {MOD_CONTROL_LEFT, KEY_W, 0}, // quit file manager
};

void loop()
{
  if (done >= 1)
  {
    digitalWrite(1, HIGH);
    return;
  }
  // don't need to set anything up to use DigiKeyboard
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  // char a[] = "AAAAAAAAA";



  for (unsigned int i = 0; i < sizeof(s1) / sizeof(s); i++)
  {
    //sprintf((char*)(&a), "%d", s1[i].d_t);
    //DigiKeyboard.println(a);
    DigiKeyboard.sendKeyStroke(s1[i].key, s1[i].mod);
    DigiKeyboard.delay(s1[i].d_t);
  }

  DigiKeyboard.println(link);
  DigiKeyboard.delay(2000); // to download the image

  for (unsigned int i = 0; i < sizeof(s2) / sizeof(s); i++)
  {

    DigiKeyboard.sendKeyStroke(s2[i].key, s2[i].mod);
    //sprintf((char*)(&a), "%d", s2[i].d_t);
    //DigiKeyboard.println(a);
    DigiKeyboard.delay(s2[i].d_t);
  }

  done++;
}
