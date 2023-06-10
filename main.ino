#include "Keyboard.h"
const byte pinBut = 2;
byte butLst;

enum { None, SingleClick, DoubleClick };

// -----------------------------------------------------------------------------
int
chkButton (void)
{
    const  unsigned long ButTimeout  = 500;
    static unsigned long msecLst;
           unsigned long msec = millis ();

    if (msecLst && (msec - msecLst) > ButTimeout)  {
        msecLst = 0;
        return SingleClick;
    }

    byte but = digitalRead (pinBut);
    if (butLst != but)  {
        butLst = but;
        delay (10);           // ** debounce

        if (LOW == but)  {   // press
            if (msecLst)  { // 2nd press
                msecLst = 0;
                return DoubleClick;
            }
            else
                msecLst = 0 == msec ? 1 : msec;
        }
    }

    return None;
}

// -----------------------------------------------------------------------------
void
loop ()
{
    switch (chkButton ())  {
    case SingleClick:
         Keyboard.press(KEY_DOWN_ARROW);
         Serial.println("DOWN_ARROW");
        Keyboard.releaseAll();
        break;

    case DoubleClick:
         Keyboard.press(KEY_UP_ARROW);
         Serial.println("UP_ARROW");

        Keyboard.releaseAll();
        break;
    }
}

// -----------------------------------------------------------------------------
void
setup ()
{
    
    pinMode (pinBut, INPUT_PULLUP);
    butLst = digitalRead (pinBut);
    Keyboard.begin();
}