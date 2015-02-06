#include <stdio.h>

enum Color { RED=1, GREEN=2, BLUE=4 };    // Create a enumeration that can only

                                           // hold the values of RED, GREEN, and BLUE

int main(void)

{   enum Color hat;   // declare hat variable to hold only RED,GREEN, or BLUE

enum Color fish;  // declare fish variable of type enum Color

hat = RED;

fish = GREEN;

 

if (hat == RED)   // check if hat is blue

{   printf ("Your hat  is RED!");  }

if(hat==fish)

{  printf(" Your fish and hat are the same color\n");  }

return 0;

}