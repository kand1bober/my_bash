#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

#define CMD_MAX_LEN 255

static const char* WORK_DIR = "/home/vyacheslav/my_bash/";

char** make_argv(char* proc_line);
void execute_all(char*** proc_line_arr, int proc_num);

int main(int argc, char* argv[])
{
    char cmd_line[256];
    while (1)
    {
        fgets(cmd_line, CMD_MAX_LEN, stdin); //reads with '\n'
        if (cmd_line[0] == 'q')
            break;

        const char* proc_delim = "|\n";
        char* saveptr;
        char* proc_line = strtok_r(cmd_line, proc_delim, &saveptr); 

        char*** proc_line_arr = NULL;
        int proc_num = 0;
        while (proc_line)
        {
            proc_num++;
            proc_line_arr = (char***)realloc(proc_line_arr, sizeof(char**) * proc_num);
            proc_line_arr[proc_num - 1] = make_argv(proc_line);

            proc_line = strtok_r(NULL, proc_delim, &saveptr);
        }
        
        execute_all(proc_line_arr, proc_num);

        for (int i = 0; i < proc_num; i++) {free(proc_line_arr[i]);}     
        free(proc_line_arr);
    }

    return 0;
}


char** make_argv(char* proc_line)
{
    const char* arg_delim = " \n";
    char* saveptr;
    char* arg_str = strtok_r(proc_line, arg_delim, &saveptr);
    
    char** args_arr = NULL;
    int args_num = 0;
    while (arg_str)
    {  
        // printf("'%s'\n", arg_str);
        args_num++;
        args_arr = (char**)realloc(args_arr, sizeof(char*) * args_num); 
        args_arr[args_num - 1] = arg_str;

        arg_str = strtok_r(NULL, arg_delim, &saveptr);
    }
    
    args_arr = (char**)realloc(args_arr, sizeof(char*) * (args_num + 1));
    args_arr[args_num] = NULL; //add last argument in argv

    return args_arr;
}


void execute_all(char*** proc_line_arr, int proc_num)
{
    for (int i = 0; i < proc_num; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Error in fork");
            exit(1);
        }
        else if (pid == 0) //child
        {
            //MAKE_FILENAME()
            char filename[100];
            snprintf(filename, 100, "%s%s", WORK_DIR, proc_line_arr[i][0]);
            // printf("file: '%s'\n", filename);

            int status = execvp(filename, proc_line_arr[i] + 1);
            if (status == -1)
            {
                perror("error in execvp");
                exit(1);
            }
            exit(0);
        }
    }

    //parent  
    for (int i = 0; i < proc_num; i++)
        wait(NULL);
}
