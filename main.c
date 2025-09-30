#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

static const char* WORK_DIR = "/home/vyacheslav/my_bash/";

#define CMD_MAX_LEN 255

int main(int argc, char* argv[])
{
    char cmd_line[256];
    const char* delim = " \n";
    while (1)
    {
        fgets(cmd_line, CMD_MAX_LEN, stdin); //reads with '\n'
        if (cmd_line[0] == 'q')
            break;

        char** args_arr = (char**)malloc(0); //array of strings

        int args_num = 0;
        char* saveptr;
        char* arg_str = strtok_r(cmd_line, delim, &saveptr);

        while (arg_str)
        {  
            // printf("'%s'\n", arg_str);
            args_num++;
            args_arr = (char**)realloc(args_arr, sizeof(char*) * args_num);
            args_arr[args_num - 1] = arg_str;

            arg_str = strtok_r(NULL, delim, &saveptr);
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Error in fork");
            exit(1);
        }
        else if (pid == 0) //child
        {
            char filename[100];
            snprintf(filename, 100, "%s%s", WORK_DIR, args_arr[0]);
            int status = execvp(filename, args_arr + 1);
            if (status == -1)
            {
                perror("error in execvp");
                exit(1);
            }
            exit(0);
        }
        else //parent  
        {
            wait(NULL);
        }  

        // for (int i = 0; i < ; i++)
        // {
            
        // }

        // for (int i = 0; i < args_num; i++)
        // {
        //     printf("'%s'\n", args_arr[i]);
        // }
        free(args_arr);
        exit(0);
    }

    return 0;
}
