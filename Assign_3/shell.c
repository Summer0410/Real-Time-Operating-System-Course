/*
Imemented core function
control c
control z
history
redirect --  does not really work
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "shell.h"
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

pid_t pid;

int main(int argc, char* agrv[]){ 
    remove("./history.txt");
    while (1){
        char **command_list;
        char *userInput[100];
        char *file_path = NULL;
        printf("%s","Lin's shell>>");
        gets(userInput);//Get user input from the command line
        char *input_string = malloc(100);
        strcpy(input_string,userInput);
        command_list = get_input(userInput);
        if(strcmp(userInput, "history")==0){//handile histroy input
            store_history(userInput);
            history();
        }  
       
        else{
            if (get_command(command_list[0])==NULL)
                printf("%s\n", "Command not found");
            else{
                command_list[0] = get_command(command_list[0]);
                
                run_command(command_list[0], command_list);
                }
            } 
        store_history(input_string);  
        }
    return 0;
}

char *get_command(char* command){
    char *found;
    char *string = getenv("PATH");
    char *path = malloc(strlen(string));
    strcpy(path, string);
    char *final_command = NULL;
    while((found = strsep(&path,":")) != NULL ){
        char *original_path = (char *) malloc(100);
        strcpy(original_path,found);
        strcat(original_path,"/");
        strcat(original_path, command);
        bool check_result =file_exist(original_path);
        if(check_result == 1){
            final_command = original_path;
            break;
        }  
        found = NULL;
    }
    return final_command;
}

bool file_exist(char *file_path){
    struct stat buffer;
    int exist = stat(file_path,&buffer);
    if(exist == 0){
        return 1;
    }
    else 
        return 0;
}

char **get_input(char *input) {
    char **command_list = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;
    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command_list[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command_list[index] = NULL;
    return command_list;
}

pid_t run_command(char* command, char** command_list){
    pid_t wpid;
    int status;
    pid = fork();
    if(pid==0){
        if(is_redirect(command_list)){
            printf("Implement ment redirect\n");
            }
        execvp(command_list[0], command_list);
    }
    else{
        wpid = waitpid(pid, &status, WUNTRACED);
        pid = 0;
        signal(SIGINT, control_c_handler);
        signal(SIGTSTP, control_z_handler);
        }   
        return pid;
    } 
    

void history( ){
      FILE *fp = fopen("history.txt", "r");
      if(fp == NULL) {
          perror("Unable to open file!");
          exit(1);
      }
      char chunk[128];
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
         fputs(chunk, stdout); // marker string used to show where the content of the chunk array has ended
     }
     fclose(fp);
}

bool is_redirect(char** command_list){
    bool found = false;
    char *redirect_indicator;
    int index = 0;
    char* command  = command_list[index];
    while(command != NULL){
        redirect_indicator =strchr(command, '>');
        if (redirect_indicator!=NULL){
            found = true;
        } 
        index++;
        command  = command_list[index];
    }
    return found;  
}

void control_c_handler(int dummy){
    kill(pid, SIGTERM);
}

void control_z_handler(int dummy){
    kill(pid, SIGTSTP);
}

void store_history(char* user_command){
    FILE * fPtr; /* File pointer to hold reference to our file */
    fPtr = fopen("./history.txt", "a");
    if(fPtr == NULL)
    {
        printf("Unable to history.txt.\n");/* File not created hence exit */
    }
    fprintf (fPtr, "%s", user_command);
    fprintf(fPtr, "\n");
    fclose(fPtr);
}



