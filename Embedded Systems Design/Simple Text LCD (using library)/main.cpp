 #include "mbed.h"
 #include "TextLCD.h"
 
 TextLCD lcd(p24, p25, p27, p28, p29, p30); // rs, e, d4-d7
 
 int main() {
     while(1)
     {
        lcd.printf("\nTravis\nCrumley");
        wait(0.3);
        lcd.printf("         \n        ");
        wait(0.3);
     }
 }