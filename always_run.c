#include "headers.h"

int check_deadprocess() {
    pid_t tpid;
    int child_status;
    tpid = waitpid(-1,&child_status,WNOHANG);
    if(tpid != -1 && tpid != 0){printf("\nprocess with pid = %d has just ended\n", tpid);return 1;}
    return 0;

}

void transfer(){
    if(CS != NULL) {
        if(CS_prev == NULL) {
            CS_prev = (current_state*)calloc(1,sizeof(current_state));
            if(CS_prev == NULL){perror("memory allocation");_exit(EXIT_FAILURE);}
        }
        CS_prev->directory = CS->directory;
        CS_prev->present_token = CS->present_token;
        CS_prev->prev = NULL; // otherwise loop of itself!
        CS_prev->pwd_present = CS->pwd_present;
    }
}

void always_run(struct tokens t) {
    if(CS == NULL) {
        CS = (current_state*)calloc(1,sizeof(current_state));
        if(CS == NULL){perror("memory allocation");_exit(EXIT_FAILURE);}
    }
    CS->pwd_present = getpwuid(getuid());
    CS->present_token = t;
    CS->prev = CS_prev;
    char* dir = (char*)calloc(directory_size,sizeof(char));
    if(dir == NULL){perror("memory allocation");_exit(EXIT_FAILURE);}
    if(getcwd(dir,directory_size) == NULL) {perror("getcwd");_exit(EXIT_FAILURE);}
    CS->directory = dir;
}
