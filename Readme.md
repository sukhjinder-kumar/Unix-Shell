
# SHELL


---

To run the code , use command `make` and then `./shell` and use `exit` to quit the program

In my shell, control starts at main, and here it first calls clear function( to make it nicer experince) and than a loop occurs (a standard for calling prompt multiple times till user exits). Here -
1. prompt() - this prints shell information as appear in bourne shell
2. taking input - to take input i have made getline and make_token function, which read input of shell and tokenise respectively. What i did is made a struct token cantaining parsed strings and a size attribute.
3. function matcher - i call this function and it decides which command is asked and sends control to that unit.
4. some checking and loop is continued. 

Okay now to main stuff , the function matcher, i have made all the essential by rather plain and standard function name. it uses if and else statement to match input with function name. cd, ls , pwd, pinfo, repeat are made and do assigned task (flags are also taken care of). system command , is a function which is kinda abstraction layer for system commands like gedit. (all function called in function matcher are kinda abstraction in case underlying function are not unique like cd requires flag and so in cd.c a function matcher for itself is made.) Foreground and background process are also implemented. 

Along with above there are some personal commands like repeat \<count\> \<command\> , excupted that command count number of times. pinfo \<process id\> , tells information about that process id \(if process id is set to null , it prints info of our shell program\) like pid , memory , path etc , clear (i find addicting to type clear after every other minute so i implemented in the very start of my shell and kept it still now for i love clear for some unknown reason and just a desclaimer it has "system" function used, but as its anyways was going to be called execvp i don't think there is any error done by me, it's printf version was glitchy...) , there is also a always_run feature which stores current information used in cd - and others. 