#include "headers.h"

struct input getline_() {
    size_t max_size = input_length;
    // using int was showing error in getline, okay we use this 
    char* string = (char*)calloc(max_size,sizeof(char));
    if(string == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
    int size_string = getline(&string,&max_size,stdin);
    if(size_string == -1) {
        perror("input string");
        exit(EXIT_FAILURE);
    }
    // just note that size_string > max_size !!
    struct input i; i.size = size_string; i.string = string;
    return i;
}

struct tokens make_token(char* string){
    char** str = (char**)calloc(1,sizeof(char*));
    if(str == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
    int i = 0; // will be the number of str's (not including last null)
    str[0] = strtok(string, " ");
    while(str[i] != NULL && str[i][0] != '\n') {
        i++;
        str = realloc(str,(i+1)*sizeof(char*));
        if(str == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
        str[i] = strtok(NULL," ");
    }
    //------------------printf("i is %d\n", i);
    // to remove \0 of last token if it has.
    if(i > 0 && str[i-1][strlen(str[i-1])-1] == '\n') {
        int x = strlen(str[i-1])-1; 
        char* a = (char*)calloc(x+10,sizeof(char));
        // char a[x];
        if(a == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
        // b->a till size
        for(int j = 0; j < x; j++){
            a[j] = str[i-1][j];
            //-------------------------------printf("a[%d] is -> %c \n", j,a[j]);
        }
        //------------------------printf("x is %d but strlen(a) is %ld\n", x,strlen(a));
        str[i-1] = a;
        //---------------------for(int j = 0; j < i; j++) 
            //--------------------printf("%d -> %s \n", j , str[j]);
    }
    if(i==0){free(str); str = NULL;}

    struct tokens t; t.string = str; t.size = i;
    return t;
}

// why a[x] is wrong and calloc is correct

