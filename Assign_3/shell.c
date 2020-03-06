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
int main(int argc, char* agrv[]){
char *userInput; 
while (1){
    char **command_list;
    char *userInput[100], *file_path;
    file_path = NULL;
    printf("%s","Lin's shell>>");
    scanf("%s", userInput);
    printf("User input in main %s\n",userInput);
    command_list = get_input(userInput);
    if (get_command(command_list[0])==NULL)
        printf("%s\n", "Command not found");
    else{
        command_list[0] = get_command(command_list[0]);
        printf("%s\n", command_list[0]);
        run_command(command_list[0], command_list);
    }


}
    
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
    //printf("exist %d\n", exist);
    if(exist == 0){
        return 1;
    }
    else 
        return 0;
}

char *string_concat(char* path, char* command){
    char *original_path = (char *) malloc(100);
    strcpy(original_path,path);
    strcat(original_path,"/");
    strcat(original_path, command);
    return *original_path;
}

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;
    parsed = strtok(input, separator);
    while (parsed != NULL) {
        printf("Parsed %s\n", parsed);
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    printf("input 1 from get_input %s\n", command[1]);
    command[index] = NULL;
    return command;
}

void run_command(char* command, char** command_list){
    //printf("exist %s\n", command[1]);
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

