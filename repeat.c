#include "headers.h"

int repeat_hub(struct tokens t) {
    int repeat;
    sscanf(t.string[1],"%d",&repeat);

    struct tokens t_;
    t_.size = t.size - 2;

    char** str = (char**)calloc(1,sizeof(char*));
    if(str == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
    for(int i = 0; i < t_.size; i++) {
        str[i] = t.string[i+2];
        if(i==t_.size-1) continue;
        str = realloc(str,(i+2)*sizeof(char*));
        if(str == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
    }
    t_.string = str;
    
    int checker;
    for(int i = 0; i < repeat; i++) {
        if(!strcmp(t_.string[t_.size-1],"exit")) checker=-1;
        else if(!strcmp(t_.string[0],"repeat")){repeat_hub(t_);checker=1;} 
        else if(!strcmp(t_.string[0],"cd")){cd_hub(t_);checker=1;} 
        else if(!strcmp(t_.string[0],"pwd")){pwd(t_);checker=1;}
        else if(!strcmp(t_.string[0],"echo")){echo(t_);checker=1;}
        else if(!strcmp(t_.string[0],"clear")){clear_terminal();checker=1;} 
        else if(!strcmp(t_.string[0],"ls")){ls_hub(t_);checker=1;}  
        else if(!strcmp(t_.string[0],"pinfo")){pinfo_hub(t_);checker=1;}  
        else checker = system_command_hub(t_);
    }

    return checker;
}