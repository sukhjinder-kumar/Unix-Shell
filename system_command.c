#include "headers.h"

int system_command_hub(struct tokens t) {
    // if like gedit & -> no waiting 
    // if like gedit   -> waiting
    // like emacs -> wait
    // like emacs & -> no waiting so print conclusion
    // that is & if we want to run in background by default app run in foreground
    int child_status;
    pid_t child_id = fork();

    if(child_id == 0) {
        char* command[t.size+1];
        for(int i = 0; i <= t.size; i++) {
            if(i==t.size-1 && !strcmp(t.string[i],"&")) {
                if(i<t.size-1) command[i] = t.string[i];
                else if(i == t.size-1) command[i] = NULL;
                else continue;
            } 
            else {
                if(i == t.size) command[t.size] = NULL;
                else command[i] = t.string[i];
            }
        }
        // int size = i+1;
        int a = execvp(command[0],command);
        if (a == -1)
        {
            // To exit the new child process created
            printf("command not found or didn't run\n");
            _exit(0);
        } // it runs if execvp fails
    }
    else {
        if(t.size > 1 && strcmp(t.string[t.size-1],"&")==0) ;
        else {
            pid_t tpid;
            do {
                tpid = wait(&child_status);
            } while(tpid != child_id);
        }
    }
    return 1;
}