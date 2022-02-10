#include "headers.h"

// here can be path or name of file!!!

void ls_path(char* path) {
    DIR* current_directory;
    struct dirent* file_ptr; // it's not like a whole
    // something like one at a time, readdir tells that in current_dir, next item ptr is 
    // this

    current_directory = opendir(path); // "." will also work
    if(current_directory) { // -> current_directory != NULL
        while((file_ptr = readdir(current_directory)) != NULL) {
            char* name = file_ptr->d_name;
            // if(file_ptr->d_type == DT_REG && name[0]!='.') // DT_RED is value for file returned of d_type
            //     printf("%s  ",name);
            // else if(file_ptr->d_type == DT_DIR && strcmp(name,".")!=0 && strcmp(name,"..")!=0 && name[0]!='.') printf("%s  ",name);
            if(name[0]!='.' && strcmp(name,".")!=0 && strcmp(name,"..")!=0)
                printf("%s  ",name);
        }
        printf("\n"); // removing it shows undefined behavious calling prompt first!
        closedir(current_directory);
    }
}

void ls_minus_a_l(struct tokens t) {
    char* path_ = (char*)calloc(directory_size,sizeof(char));
    if(path_==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    if(t.size == 3) path_ = CS->directory;
    else 
        for(int i = 3; i < t.size;i++){
            sprintf(path_,"%s%s",path_,t.string[i]); // at first iretration path is empty!
            if(i!=t.size-1)sprintf(path_,"%s ",path_);
        }
    // DIR* current_directory;
    // struct dirent* file_ptr;
    // current_directory = opendir(path); // "." will also work

    // struct stat* S = (struct stat*)calloc(1,sizeof(struct stat));
    // if(S==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    // char** name = (char**)calloc(1,sizeof(char*));
    // if(name==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    // char* file_type = (char*)calloc(1,sizeof(char));
    // if(file_type==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    // int i = 1; // will come out as size.

    // if(current_directory) { // -> current_directory != NULL
    //     while((file_ptr = readdir(current_directory)) != NULL) {
    //             name[i-1] = file_ptr->d_name;
    //             file_type[i-1] = file_ptr->d_type;
    //             stat(name[i-1],&S[i-1]); // will return 0 for sur
    //             i++;
    //             name = realloc(name,i*sizeof(char*));
    //             S = realloc(S,i*sizeof(struct stat));
    //         }
    //     i--;
    //     print_long_format(S,name,file_type,i);
    //     printf("\n"); // removing it shows undefined behavious calling prompt first!
    //     closedir(current_directory);
    // }
    char* path = realpath(path_, NULL);
    if(path == NULL){
        printf("cannot find file with name[%s]\n", path_);
    } 
    else{
    DIR* current_directory;
    struct dirent* file_ptr;
    current_directory = opendir(path_); // "." will also work

    struct stat* S = (struct stat*)calloc(1,sizeof(struct stat));
    if(S==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    char** name = (char**)calloc(1,sizeof(char*));
    if(name==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    char* file_type = (char*)calloc(10,sizeof(char));
    if(file_type==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    int i = 1; // will come out as size.

    if(current_directory) { // -> current_directory != NULL
        while((file_ptr = readdir(current_directory)) != NULL) {
                name[i-1] = file_ptr->d_name;
                file_type[i-1] = file_ptr->d_type;
                char* path_name = (char*)calloc(1000,sizeof(char));
                sprintf(path_name,"%s/%s",path,name[i-1]);
                stat(path_name,&S[i-1]); // will return 0 for sur
                i++;
                name = realloc(name,i*sizeof(char*));
                S = realloc(S,i*sizeof(struct stat)); 
                file_type =  realloc(file_type,i*sizeof(char));
                if(file_type== NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
                if(name == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
                if(S == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);} 

            }
        i--; // to make it size
        print_long_format(S,name,file_type,i);
        printf("\n"); // removing it shows undefined behavious calling prompt first!
        closedir(current_directory);
    }
    free(S);
    free(file_type);
    free(name);
    }
}

void ls_minus_a(struct tokens t) {
    char* path = (char*)calloc(directory_size,sizeof(char));
    if(path==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    if(t.size == 2) path = CS->directory;
    else 
        for(int i = 2; i < t.size;i++){
            sprintf(path,"%s%s",path,t.string[i]); // at first iretration path is empty!
            if(i!=t.size-1)sprintf(path,"%s ",path);
        }
    if(t.size >=3 && !strcmp(t.string[2],"-l")) ls_minus_a_l(t);
    else {
        DIR* current_directory;
        struct dirent* file_ptr;
        current_directory = opendir(path); // "." will also work
        if(current_directory) { // -> current_directory != NULL
            while((file_ptr = readdir(current_directory)) != NULL) {
                char* name = file_ptr->d_name;
                printf("%s  ",name);
            }
            printf("\n"); // removing it shows undefined behavious calling prompt first!
            closedir(current_directory);
        }
    }
}

//void print_time(struct tm* times) {
//         // struct tm {
//         //        int tm_sec;    /* Seconds (0-60) */
//         //        int tm_min;    /* Minutes (0-59) */
//         //        int tm_hour;   /* Hours (0-23) */
//         //        int tm_mday;   /* Day of the month (1-31) */
//         //        int tm_mon;    /* Month (0-11) */
//         //        int tm_year;   /* Year - 1900 */
//         //        int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
//         //        int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
//         //        int tm_isdst;  /* Daylight saving time */
//         //    };
//     // 1. print month
//     if(times->tm_mon == 0) printf("Jan");
//     else if(times->tm_mon == 1) printf("Feb");
//     else if(times->tm_mon == 2) printf("Mar");
//     else if(times->tm_mon == 3) printf("Apr");
//     else if(times->tm_mon == 4) printf("May");
//     else if(times->tm_mon == 5) printf("Jun");
//     else if(times->tm_mon == 6) printf("July");
//     else if(times->tm_mon == 7) printf("Aug");
//     else if(times->tm_mon == 8) printf("Sep");
//     else if(times->tm_mon == 9) printf("Oct");
//     else if(times->tm_mon == 10) printf("Nov");
//     else printf("Dec");
//     // 2. print date of month
//     printf(" %d", times->tm_mday);
//}

// pending time correction and /n formatting
void print_long_format(struct stat* S, char** name, char* file_type, int size) {
    // print total
    int total = 0;
    for(int i = 0; i < size; i++) total += S[i].st_blocks;
    printf("total %d\n", total/2);

    // print information of files in a line
    for(int i = 0; i < size; i++) {
        // 1. first print file type
        if(file_type[i] == DT_REG) printf("-");
        else if(file_type[i] == DT_DIR) printf("d");

        // 2. modes
        char *modes = (char *)calloc(10, sizeof(char));
        if(modes==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
        mode_t perm = S[i].st_mode; // stat.st_mode -> returns modes of our file
        modes[0] = (perm & S_IRUSR) ? 'r' : '-';
        modes[1] = (perm & S_IWUSR) ? 'w' : '-';
        modes[2] = (perm & S_IXUSR) ? 'x' : '-';
        modes[3] = (perm & S_IRGRP) ? 'r' : '-';
        modes[4] = (perm & S_IWGRP) ? 'w' : '-';
        modes[5] = (perm & S_IXGRP) ? 'x' : '-';
        modes[6] = (perm & S_IROTH) ? 'r' : '-';
        modes[7] = (perm & S_IWOTH) ? 'w' : '-';
        modes[8] = (perm & S_IXOTH) ? 'x' : '-';
        modes[9] = '\0';
        for(int i = 0; i < 9; i++) printf("%c", modes[i]);
        
        // 3. number of links
        printf(" %ld",S[i].st_nlink);

        // 4. owner who created the file
        uid_t owner = S[i].st_uid;
        struct passwd* owner_info = getpwuid(owner);
        printf(" %s", owner_info->pw_name);

        // 5. name of the group who owns the file
        uid_t owner_ = S[i].st_gid;
        struct passwd* owner_info_ = getpwuid(owner_);
        printf(" %s", owner_info_->pw_name);

        // 6. size of file
        printf(" %ld ", S[i].st_size);

        // 7. date and time
        // if(file_type[i] == DT_REG) print_time(&S[i].st_mtim);
        // if(file_type[i] == DT_DIR) print_time(&S[i].st_ctim);
        printf("%s", ctime(&S[i].st_mtime));

        // 8. file name
        printf(" %s ", name[i]);

        printf("\n");
    }
}

void ls_minus_l(struct tokens t) {
    char* path_ = (char*)calloc(directory_size,sizeof(char));
    if(path_==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    if(t.size == 2) path_ = CS->directory;
    else 
        for(int i = 2; i < t.size;i++){
            sprintf(path_,"%s%s",path_,t.string[i]); // at first iretration path is empty!
            if(i!=t.size-1)sprintf(path_,"%s ",path_);
        }
    if(t.size >=3 && !strcmp(t.string[2],"-a")) ls_minus_a_l(t);
    else {
    char* path = realpath(path_, NULL);
    if(path == NULL){
        printf("cannot find file with name[%s]\n", path_);
    } 
    else{
    DIR* current_directory;
    struct dirent* file_ptr;
    current_directory = opendir(path_); // "." will also work

    struct stat* S = (struct stat*)calloc(1,sizeof(struct stat));
    if(S==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    char** name = (char**)calloc(1,sizeof(char*));
    if(name==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    char* file_type = (char*)calloc(10,sizeof(char));
    if(file_type==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    int i = 1; // will come out as size.

    if(current_directory) { // -> current_directory != NULL
        while((file_ptr = readdir(current_directory)) != NULL) 
            if(file_ptr->d_name[0]!='.' && strcmp(file_ptr->d_name,".")!=0 && strcmp(file_ptr->d_name,"..")!=0) {
                name[i-1] = file_ptr->d_name;
                file_type[i-1] = file_ptr->d_type;
                char* path_name = (char*)calloc(1000,sizeof(char));
                sprintf(path_name,"%s/%s",path,name[i-1]);
                stat(path_name,&S[i-1]); // will return 0 for sur
                i++;

                char* file_type_ = (char*)calloc(10,sizeof(char));
                if(file_type_==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
                struct stat* S_ = (struct stat*)calloc(1,sizeof(struct stat));
                if(S_==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
                char** name_ = (char**)calloc(1,sizeof(char*));
                if(name_==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
                name_ = realloc(name,i*sizeof(char*));
                S_ = realloc(S,i*sizeof(struct stat)); 
                file_type_ = realloc(file_type,(i+10)*sizeof(char));
                if(file_type_== NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
                if(name_ == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
                if(S_ == NULL) {perror("string not allocated");_exit(EXIT_FAILURE);} 
                name = name_;
                S = S_;
                file_type = file_type_;
            }
        i--; // to make it size
        print_long_format(S,name,file_type,i);
        printf("\n"); // removing it shows undefined behavious calling prompt first!
        closedir(current_directory);
    }
     free(S);
     free(name);
    free(file_type);
    }
    }
}

void ls_tilda() {
    ls_path("/");
}

void ls_dot_dot(struct tokens t) {
    ls_path("..");
}

void ls_dot(struct tokens t) {
    ls_path(".");
}

void ls_la_ls_minus_al(struct tokens t) {
    char* path_ = (char*)calloc(directory_size,sizeof(char));
    if(path_==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    if(t.size == 2) path_ = CS->directory;
    else 
        for(int i = 2; i < t.size;i++){
            sprintf(path_,"%s%s",path_,t.string[i]); // at first iretration path is empty!
            if(i!=t.size-1)sprintf(path_,"%s ",path_);
        }
    char* path = realpath(path_, NULL);
    if(path == NULL){
        printf("cannot find file with name[%s]\n", path_);
    } 
    else{
    DIR* current_directory;
    struct dirent* file_ptr;
    current_directory = opendir(path_); // "." will also work

    struct stat* S = (struct stat*)calloc(1,sizeof(struct stat));
    if(S==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    char** name = (char**)calloc(1,sizeof(char*));
    if(name==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    char* file_type = (char*)calloc(1,sizeof(char));
    if(file_type==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    int i = 1; // will come out as size.

    if(current_directory) { // -> current_directory != NULL
        while((file_ptr = readdir(current_directory)) != NULL) {
                name[i-1] = file_ptr->d_name;
                file_type[i-1] = file_ptr->d_type;
                char* path_name = (char*)calloc(1000,sizeof(char));
                sprintf(path_name,"%s/%s",path,name[i-1]);
                stat(path_name,&S[i-1]); // will return 0 for sur
                i++;
                name = realloc(name,i*sizeof(char*));
                S = realloc(S,i*sizeof(struct stat));  
                file_type = realloc(file_type,(i+10)*sizeof(char));
                if(file_type== NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
                if(S== NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
                if(name== NULL) {perror("string not allocated");_exit(EXIT_FAILURE);}
            }
        i--; // to make it size
        print_long_format(S,name,file_type,i);
        printf("\n"); // removing it shows undefined behavious calling prompt first!
        closedir(current_directory);
    }
    }
}

void ls_selector(struct tokens t) {
    char* path = (char*)calloc(directory_size,sizeof(char));
    if(path==NULL){perror("memory allocation"),_exit(EXIT_FAILURE);}
    for(int i = 1; i < t.size;i++){
        sprintf(path,"%s%s",path,t.string[i]); // at first iretration path is empty!
        if(i!=t.size-1)sprintf(path,"%s ",path);
    }

    if(!strcmp(path,"~")) ls_tilda();
    else if(!strcmp(path,"..")) ls_dot_dot(t); 
    else if(!strcmp(path,".")) ls_dot(t); 

    else if(!strcmp(t.string[1],"-a")) ls_minus_a(t); 
    else if(!strcmp(t.string[1],"-l")) ls_minus_l(t); 
    // else if(!strcmp(path,"-a -l")) ls_minus_a_l(t);  
    else if(!strcmp(t.string[1],"-la")) ls_la_ls_minus_al(t);
    else if(!strcmp(t.string[1],"-al")) ls_la_ls_minus_al(t); 
    else ls_path(path); 
    // in flags keep in mind there can be path ahead at t.string[2]
}

void ls() {
    ls_path(".");
}

void ls_hub(struct tokens t) {
    if(t.size == 1) ls();
    if(t.size > 1) ls_selector(t);
}