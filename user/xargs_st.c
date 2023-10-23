#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include <stddef.h>
 
 
 
//Initializes a params array to store 
 
/*
int pid = fork();
//Child Process
if (pid == 0){
 
}else{
//Parent Process
 
}*/
 
 
void pidProcess(int argc, char *argv[]){
 
	char *store[MAXARG];
	int count = 0;
	int numberofCharacters = 0;
 
        char currentArgument[100];
        //arguments = malloc((argc*100)*sizeof(char));
        //read in how many bytes are read in command argument
 
 
 
 
		//reads into standard input and saves all the chars recorded to currentArgument
		int byteRead = read(0,&currentArgument[numberofCharacters],sizeof(char));
		numberofCharacters++;
		while(byteRead > 0){
			byteRead = read(0,&currentArgument[numberofCharacters],sizeof(char));
			//numberofCharacters represent every character being read
			numberofCharacters++;
			//when reached end of file, byteRead willl return 0, and the program should exit while loop
			if(byteRead == 0){
				break;
			}
		}
		//currentArgument by default is a pointer that points to the start of the currentArgument[] array
		//set up startofNewString to be a pointer to the start of currentArgument
		char *startofNewString = currentArgument;
		//loop through every character in the array
		for(int i = 0; i<numberofCharacters; i++){
			//if reached a space character, replace space with endoffile character
			if(currentArgument[i] == ' ' || currentArgument[i] == '\0'){
				currentArgument[i] = '\0';
				//place the pointer representing a word of stdin into store[] array
				store[count] = startofNewString;
				//places pointer at start of the next word
				startofNewString = currentArgument + i + 1;
				printf("string: %s\n",store[count]);
				count++;
			}
		}
 
		char *allArguments[argc+count+1];
		int countArguments = 0;
		for(int i = 0; i<(argc-1); i++){
			allArguments[i] = argv[i+1];
			printf("allArguments[%d] = %s\n", i, allArguments[i]);
			countArguments++;
		}
		for(int i = 0; i < count; i++){
			allArguments[countArguments + i] = store[i];
			//exec("./echo", allArguments[countArguments + i]);
 
			printf("allArguments[%d] = %s\n", countArguments + i, allArguments[countArguments + i]);
		}
 
		//printf("countArguments = %d\n", countArguments);
		//printf("count = %d", count);
		/*for(int i = 0; i<count; i++){
			printf("store[%d] = %s", i, store[i]);
		}*/
		int pid = 0;
 
		pid = fork();
 
			if (pid > 0){
        	//parent process
			wait((int *)10);
 
    		}else{
    		//Child Process
			printf("store[0] = %s\n", store[0]);
			printf("store[1] = %s\n", store[1]);
			printf("store[2] = %s\n", store[2]);
        	exec(allArguments[0],store);
		}
 
		/*for(int i = 0; i<count; i++){
			//printf("Forked");
			pid = fork();
 
			if (pid > 0){
        	//parent process
			printf("in parent process\n");
			wait((int *)10);
			printf("parent died\n");
 
    		}else{
    		//Child Process
			printf("in child process\n");
			exit(0);
        	//exec(allArguments[0],&store[i]);
		}
	}*/
}
 
/*
for each argument in store
    fork a new process
    if (child process)
        execute the command with the argument
        exit the child process
 
// Wait for all child processes to finish
for each child process
    wait for the process to finish
*/
 
 
 
 
/*
//checks if chr is equal to space or tab character
#define is_blank(chr) (chr == ' ' || chr == '\t') 
 
int
main(int argc, char *argv[])
{
	char buf[2048], ch;
	char *p = buf;
	char *v[MAXARG];
	int c;
	int blanks = 0;
	int offset = 0;
 
	if(argc <= 1){
		fprintf(2, "usage: xargs <command> [argv...]\n");
		exit(1);
	}
    //
	for (c = 1; c < argc; c++) {
		v[c-1] = argv[c];
        //printf("v[%d] = %s\n", c-1, v[c-1]);
	}
	--c;
    //printf("c = %d\n", c);
 
    //0 in read represents reading from standard input (cmd)
    //stores what is read into ch
    //1 means it read 1 byte
	while (read(0, &ch, 1) > 0) {
        //checks if there is space or tab character. If so, increment blank
		if (is_blank(ch)) {
			blanks++;
			continue;
		}
        //if there are blank spaces, do below
		if (blanks) {  
			buf[offset++] = 0;
			//place 
			v[c++] = p;
			p = buf + offset;
 
			blanks = 0;
		}
 
		if (ch != '\n') {
			buf[offset++] = ch;
		} else {
			v[c++] = p;
			p = buf + offset;
 
			if (!fork()) {
				exit(exec(v[0], v));
			}
			wait(0);
 
			c = argc - 1;
		}
	}
	printf("succeeded");
 
	exit(0);
}*/
 
 
 
int main(int argc, char *argv[])
{
    //Declares params array that takes in Maxarg amount of elements
    //Will be used for taking in commands (represented in chars)
    //const char* params[MAXARG];
 
    pidProcess(argc,argv);
    exit(0);
}