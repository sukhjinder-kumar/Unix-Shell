#ifndef _LS_H
#define _LS_H

void ls_hub(struct tokens t);

// variations
void print_long_format(struct stat* S, char** name, char* file_type, int size);
void print_time(struct tm* times);

#endif