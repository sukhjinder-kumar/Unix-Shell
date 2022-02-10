#ifndef _CD_H
#define _CD_H 

int cd_hub(struct tokens t); // this will call cd variation functions

// all variation functions
void cd();
void cd_path(char* path);
void cd_flag(char* path);
void cd_reverse();

#endif