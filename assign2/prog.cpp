
/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Andrew M
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */

 //parent. process receives user input and then, the command gets executed in a seperate process (child)
 //parent should wait until the child finishes, then the parent can exit. parent must use wait(nULL); i believe.
 //if a & is used after the command, the parent and child process will run concurrently
 //fin and fout files, i think i need a library
 //sys/wait, impies process waiting library. i assume for the the parent to wait for the child


int parse_command(char command[], char *args[])
{
    //check for an empty command, invalid command, the spaces between words, and when the user clicks enter (, strok, c string lib.


    char *aCertainToken = strtok(command, " \t\n"); //make one argument go into just one parsed token, to categorize this even more. 

    int i = 0; //serve as the index iterating through the amt of argus. in the command, 

    while (aCertainToken != NULL)  
    {
        args[i] = aCertainToken;
        i++;
        aCertainToken = strtok(NULL, " \t\n");
    }
    args[i] = NULL; //the last index of a char. array implies the end of the char. array.

    return i; //returns the amt of args. in the command, 
}

// TODO: Add additional functions if you need

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */


    // TODO: Add additional variables for the implementation.
    while (should_run)
    {
        printf("osh>");
        fflush(stdout); // fflush displays instantly, instead of waiting
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        // Parse the input command
        int num_args = parse_command(command, args);
        //cout << num_args << endl;
        //* After reading user input, the steps are:., //done

        



        char *parentDoesntWait = "&"; //ampersand for strcmp check
        bool runInBack = false; //if true, parent not waiting

          if (num_args > 0 && strcmp(args[num_args-1],parentDoesntWait) == 0) //if there a & at end, parent does wait. child doesnt have control, propmp backs up
          //the child running command in background
            {
                args[num_args - 1] = NULL;
                num_args--;
                runInBack = true;
            }

        //* (1) fork a child process using fork()
        pid_t pid; //pid_t data type needed., it's. a signed integer and no assumptions are made by dev. about the size od pid
        pid = fork();
        //* (2) the child process will invoke execvp()
        if (pid == 0)        //if fork returns -1, failed
        {
            int resultExec;
            resultExec = execvp(args[0],args); //be sure to check to see where ther user put &, means unix shell has child run in the background

            if (resultExec == -1) //a failure happended, 
            {
                perror("EXECVP returned -1");
                exit(1); //leave, 
            }
                  //if execcvp returns -1,  it failed
        }
        else if (pid > 0)            
        {
            if (runInBack == false) //
            {
                //waitpid, more specific than wait()
                //wwaitpid will wait for your child instead of any child process. reducing ambuiguity and better practice.
                //the 0 exercsies the blocking call, not letting the client type another command until the recent command finishes
                waitpid(pid,NULL,0); //parent must wait for child to fininsh, child has control. can't type another command until process finished.
            }

        }
        // * (3) parent will invoke wait() unless command included &

    }
    return 0;
}
