#include "headers.h"

int function_matcher(struct tokens t) {
    transfer();
    always_run(t); // updates CS
    
    int checker = 0;
    
    if(!strcmp(t.string[t.size-1],"exit")) checker=-1;
    else if(!strcmp(t.string[0],"repeat")){checker = repeat_hub(t);} 
    else if(!strcmp(t.string[0],"cd")){cd_hub(t);checker=1;} 
    else if(!strcmp(t.string[0],"pwd")){pwd(t);checker=1;}
    else if(!strcmp(t.string[0],"echo")){echo(t);checker=1;}
    else if(!strcmp(t.string[0],"clear")){clear_terminal();checker=1;} 
    else if(!strcmp(t.string[0],"ls")){ls_hub(t);checker=1;}  
    else if(!strcmp(t.string[0],"pinfo")){pinfo_hub(t);checker=1;}  
    else checker = system_command_hub(t);

    return checker;
}