#include "headers.h"

void prompt() {
    struct passwd* pwd; // for username
    uid_t uid;
    uid = getuid();
    pwd = getpwuid(uid);  
    // no error handling!! always successful acc. to man page

    struct utsname u_name; // for hostname
    int z = uname(&u_name);
    if(z == -1) { 
        perror("Program: ");
        _exit(1);
    }
    // int b = gethostname(host_name,50);  same as above
    // if (b == -1) {
    //     write(1,"error while handling hostname\n",strlen("error while handling 
    //     hostname\n"));
    //     _exit(1);
    // }

    char* Directory = (char*)calloc(directory_size,sizeof(char));
    if(Directory ==  NULL) {
        perror("RAM");
        _exit(1);
    }
    if(getcwd(Directory,directory_size) == NULL) {
        if(errno == ERANGE) 
            write(1,"max directory size exceeded\n",strlen("max directory size exceeded\n")); 
        else 
            perror("getcwd");
        
        // i could have just left perror("getcwd") however how would i tell
        // i know errno macros .... 
        _exit(EXIT_FAILURE);
    }

    char* terminal = (char*)calloc(100+directory_size,sizeof(char));
    if(terminal ==  NULL) {
        perror("RAM");
        _exit(1);
    }

    sprintf(terminal,"%s@%s:~%s$ ",pwd->pw_name,u_name.nodename,Directory);
    if(terminal[strlen(terminal)-2] != '$') {write(1,"name field too big for buffer\n",strlen("name field too big for buffer\n")); _exit(EXIT_FAILURE);}
    write(1,terminal,strlen(terminal));

    free(Directory);
    free(terminal);
}