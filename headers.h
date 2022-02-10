#ifndef _HEADERS_H
#define _HEADERS_H

#include<stdio.h> 
#include<fcntl.h>

// for calloc 
#include <stdlib.h>

// for strings
#include <string.h>

// these two for making mkdir() (first 2) and for lseek() (last 2)
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> 

// for system information
#include <sys/utsname.h>

// for username 
#include <pwd.h>

// for error handling
#include<errno.h> 
extern int errno; 

// for directory information
#include <dirent.h>

// for time display
#include <time.h>

// for wait function
#include <sys/wait.h>

// global variables
struct input {
    char* string;
    int size;
};
struct tokens {
    char** string;
    int size;
};
typedef struct current_state_information{
    struct current_state_information* prev;
    struct passwd* pwd_present;
    struct tokens present_token;
    char* directory;
} current_state;

extern current_state* CS;
extern current_state* CS_prev;
#define directory_size 200
#define input_length 200

// newly created
#include "prompt.h" // for printing info of shell....sort of 
#include "getline_.h" // for taking input of user
#include "function_matcher.h" // matches command to there headers
#include "always_run.h" // always run to store information of prev execution.
#include "cd.h" // for cd command
#include "pwd.h" // for pwd command
#include "echo.h" // for echo command
#include "clear.h" // for clear command
#include "ls.h" // for ls command
#include "system_command.h" // for system commands like vi,gedit etc
#include "pinfo.h" // for our command pinfo
#include "repeat.h" // for repeat command
#endif