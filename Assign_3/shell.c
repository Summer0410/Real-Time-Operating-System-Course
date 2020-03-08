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
#define DATA_SIZE 100
int main(int argc, char* agrv[]){ 
    while (1){
        char **command_list;
        char *userInput[100], *file_path;
        file_path = NULL;
        printf("%s","Lin's shell>>");
        gets(userInput);//Get user input from the command line

        if(strcmp(userInput, "history")==0){
            printf("%s", "Came to history");
            //history();
        }     
        else if(strcmp(userInput, "control_c")==0)
            control_c();
        else if(strcmp(userInput, "control_z")==0)
            control_z();
        else{
            command_list = get_input(userInput);
            if (get_command(command_list[0])==NULL)
                printf("%s\n", "Command not found");
            else{
                store_history(userInput);
                command_list[0] = get_command(command_list[0]);
                run_command(command_list[0], command_list);
                }
        }    
    }
remove("./history.txt");
return 0;
}

char *get_command(char* command){
    char *string,*found;
    string = getenv("PATH");
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
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;
    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;
    return command;
}

void run_command(char* command, char** command_list){
    pid_t pid, wpid;
    int status;
    pid = fork();
    if(pid==0){
        execvp(command, command_list);
    }
    else{
        wpid = waitpid(pid, &status, WUNTRACED);
        }   
    } 

void history(char* history){
     printf("%s\n", "History");
}

void control_c(){
    printf("%s\n", "control_c");
}

void redirect(){
    printf("%s\n", "redirect");
}

void control_z(){
    printf("%s\n", "control_z");
}
void store_history(char* user_command){
    char data[DATA_SIZE];/* Variable to store user command*/
    FILE * fPtr; /* File pointer to hold reference to our file */
    fPtr = fopen("./history.txt", "a");
    if(fPtr == NULL)
    {
        printf("Unable to history.txt.\n");/* File not created hence exit */
    }
    printf("User Command: %s", user_command);
    fputs("\n",fPtr);
    fputs (user_command,fPtr);
    fclose(fPtr);
}



