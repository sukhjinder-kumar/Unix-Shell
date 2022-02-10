#include "headers.h"

void cd() {
    /*
    struct passwd* pwd;
    uid_t uid;
    uid = getuid();
    pwd = getpwuid(uid);
    chdir(pwd->pw_dir);
    */
    /*
    char *homedir = getenv("HOME");
    if(homedir==NULL){perror("HOME_DIRECTORY");_exit(EXIT_FAILURE);}
    chdir(homedir);
    */

    // combination of above 2 mehtods as internet is quite split on some issues
    char *homedir;
    if ((homedir = getenv("HOME")) == NULL) homedir = getpwuid(getuid())->pw_dir;
    chdir(homedir);
}

void cd_reverse(char* path) {
    if(CS != NULL && CS->prev != NULL) {
        path = CS->prev->directory;
        cd_path(path);
    }
    else printf("write something first!\n");
}

void cd_flag(char* path) {
    if(!strcmp(path,"~")) cd();
    else if(!strcmp(path,"-")) cd_reverse(path);
    else if(!strcmp(path,"..")) cd_path(path); // it works!
    else if(!strcmp(path,".")) cd_path(path); // it works!
    else cd_path(path);
}

void cd_path(char* path) {
    int a = chdir(path);
    if(a==-1) printf("directory not found!\n");
}

int cd_hub(struct tokens t) {
    if(t.size == 1) {cd(); return 1;}

    // NOTE - USER CAN SPECIFY ANY KIND OF PATH, ABSOLUTE OR RELATIVE BOTH WORKS 
    // BY CHDIR()!!, i.e name of directory or address
    // ALSO CD / WORKS AS / IS PATH OF ROOT DIRECTORY
    char* path = (char*)calloc(directory_size,sizeof(char));
    if(path==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    for(int i = 1; i < t.size;i++){
        sprintf(path,"%s%s",path,t.string[i]); // at first iretration path is empty!
        if(i!=t.size-1)sprintf(path,"%s ",path);
    }

    cd_flag(path); // if it is not a flag it will redirect to cd_path

    free(path);
    
    return 1;
}