#include "headers.h"

int main() 
{
    clear_terminal(); // cool layer 1

    while(1) {
        prompt();
        int a = check_deadprocess();
        if(a==1) continue;
        fflush(stdout);

        struct input i = getline_();

        struct tokens t = make_token(i.string);

        if(t.size <= 0) continue;

        int z = function_matcher(t); 
        if(z == 0) printf("Command not found\n");

        //free(i.string);
        if(z == -1) break;
    }

    clear_terminal(); // cool layer 2

    return 0;
}

// memory leaks
// abnormality with "exit"