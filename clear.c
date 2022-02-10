#include "headers.h"

void clear_terminal() {
   // printf("\e[1;1H\e[2J"); faster but seems buggy to me, like prompt not work, 
   // clears next instruction too....
   system("clear");
}