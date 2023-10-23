#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../kernel/fcntl.h"
#include "../kernel/fs.h"
#include "../kernel/param.h"
#include "user.h"


int main(int argc, char *argv[]) {

  while(1){
    fprintf(1, ">>>");

    
    char formatedBuffer[512];
    char inputBuffer[500];
    char *argumentBuffer[MAXARG];
    int argCount = 0;
    int opCount = 0;

    int inputSize = read(0, inputBuffer, sizeof(inputBuffer));

    //format inputBuffer
    int semicolonCount = 0;
    for(int i = 0; i < inputSize; i++){
      if(inputBuffer[i] == ';'){
        formatedBuffer[i] = ' ';
        semicolonCount++;
      }
      formatedBuffer[i+semicolonCount] = inputBuffer[i];
    }


    //char *operatorQueue[4];
    int subArgLength[4];
    subArgLength[0] = 0;
    subArgLength[1] = 0;
    subArgLength[2] = 0;
    subArgLength[3] = 0;
    char **commands[4];

    //flag for checking if iterating through a word. 0 = false, 1 = true
    int wordFound = 0;



    for(int i = 0; i < inputSize; i++){

      if(formatedBuffer[i] != ' ' && wordFound == 0){
        argumentBuffer[argCount++] = &formatedBuffer[i];

        // if(inputBuffer[i] == '|' || inputBuffer[i] == '>' || inputBuffer[i] == '<' || inputBuffer[i] == ';'){
        //   opCount++;
        // }
        wordFound = 1;

      }
      else if ((formatedBuffer[i] == ' ' || formatedBuffer[i] == '\n') && wordFound == 1)
      {
        formatedBuffer[i] = '\0';
        wordFound = 0;
      }
    }

    
    for(int i = 0; i < argCount; i++){
      if(*argumentBuffer[i] == '|' || *argumentBuffer[i] == '>' || *argumentBuffer[i] == '<' || *argumentBuffer[i] == ';'){
        //operatorQueue[opCount] = argumentBuffer[i];
        commands[opCount] = malloc(sizeof(char*) * subArgLength[opCount]);
        for(int subArg=0; subArg < subArgLength[opCount]; subArg++){
          commands[opCount][subArg] = argumentBuffer[i-subArgLength[opCount]+subArg];
        }

        opCount++;
      }else{
        subArgLength[opCount]++;
      }
    }
    commands[opCount] = malloc(sizeof(char*) * subArgLength[opCount]);
    for(int subArg=0; subArg < subArgLength[opCount]; subArg++){
      commands[opCount][subArg] = argumentBuffer[argCount-subArgLength[opCount]+subArg];
    }
    
    printf("opCount: %d\n", opCount);

    for(int i = 0; i < (opCount + 1); i++){
      int pid = fork();
      if (pid > 0){ // Parent
        wait(0);
        
      } else if (pid == 0) { // Child
        exec(commands[i][0], commands[i]);
        exit(0);
      }
    }




    // if(strcmp(argumentBuffer[0], "cd") == 0){

    //   chdir(argumentBuffer[1]);

    // }else{

    //   int pid = fork();
    //   if (pid > 0){ // Parent
    //     wait(0);
    //   } else if (pid == 0) { // Child
    //     exec(argumentBuffer[0], argumentBuffer);
    //     exit(0);
    //   }

    // }

    // Clear the argument buffer
    for (int i = 0; i < argCount; i++)
    {
      argumentBuffer[i] = 0;
    }
    // for (int i =0; i < 4; i++){
    //   printf("%s", operatorQueue[i]);
    // }

    // else {
    //   fprintf(1, "fork() failed\n");
    // }
  }
  return 0;
}