#include "headers.h"

int echo(struct tokens t) {
    // char* message = (char*)calloc(directory_size,sizeof(char));
    // // bug -> size
    // if(message == NULL){perror("memory allocation"); return 1;}
    // for(int i = 1; i < t.size;i++){
    //     sprintf(message,"%s%s",message,t.string[i]); // at first iretration path is empty!
    //     if(i!=t.size-1)sprintf(message,"%s ",message);
    // }
    for(int i = 1; i < t.size; i++)
        printf("%s",t.string[i]);
    printf("\n");
    return 0;
}