/****************************************************************************/
/*      sharedMem.c                                                         */
/****************************************************************************/
/* Author: Carlos L Sanchez Vila                                            */
/****************************************************************************/
/*                      Disclaimer:                                         */
/* I hereby certify that this collective work is my own and none of it is   */
/* the work of any other person or entity.                                  */
/****************************************************************************/
/*                      Program Description:                                */
/* The following program creates a shared memory and ataches it to the      */
/* current process, it then fills it with the data enterer through the      */
/* command line. The shared memory is then manipulated by child processes   */
/* that change each one corresponding value inside the shared memory and    */
/* each prints the state of the shared memory after their operations have   */
/* taken place. The parent process waits until all child processes are done */
/* to detach and delete the shared memory, it then terminates.              */
/****************************************************************************/
/*            			Instructions/How to use:                    */
/* First download the files sharedMem.c, master.c, master.h and the 	    */
/* makefile to the same directory and follow the following steps:	    */
/* 	        							    */
/* 1-)	To Build:	 						    */
/* 		To compile and build this specific program just enter in    */
/*		the terminal:		  			   	    */
/*    		make build                                                  */
/* 									    */
/* 		or enter:						    */
/* 		     gcc -Wall -w sharedMem.c master.c -o memChildShare.out */
/* 									    */
/* 2-)	To execute: 							    */
/* 		After building with make, enter the following in 	    */
/* 		the terminal: 						    */
/* 		./memChildShare.out x1 x2 x3 ... xN		      	    */
/* 									    */
/* 		Notice N is a number from 1 to 7 inclusive and x is an integer*/
/* 		from 0 to 9			                            */
/****************************************************************************/
/*                      References:                                         */
/* The program uses the POSIX standars, Portable Operating System Interface */
/* Some of the functions contained in the POSIX standars are for example    */
/* functions that controll forks, the creation and manipulation of shared   */
/* memory, functions that allow to verify and assert process ids, and       */
/* functions that allow to wait for forked processes to finish.             */
/* Some of the functions used in this program: 				    */
/* For functions such as fflush(), getpid(), getppid(), fork(), wait(),	    */
/* create, atach, detach and delete shared memories the following soruce    */
/* was used as reference: 			   			    */
/* "Unix Multiprocess Programming"					    */ 														
/* http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/process.html          */
/****************************************************************************/
#include "master.h"


/**
 * main: The following program takes an array of numbers as imput, creates a 
 * shared memory large enough to save the data entered, the shared memory is 
 * created, atached and filled with the given data, if said data is within
 * valid parameters. After this is all done, the program then forks for N times
 * where N is the size of the command line imput array without the program name.
 * Notice that a valid program imput will be an array of 1 to 7 numbers where 
 * each number ranges from 0 to 9. Other imputs will be ignored and the program 
 * will just terminates. In the event of any errors the program will produce a 
 * error message and terminate.
 * 
 * @param  argc This parameter is the length of the array argv which contains 
 * the command line imput.
 * @param  argv: This parameter is an array containing the command line imputs.
 * @return      The program returns 0 if there are no program errors, or 1 if 
 * any critical error has occured. (ex: OS could not allocate shared memory)
 */

int main(int argc, char const *argv[])
{
	if(validateImput(argc, argv)){

		int length = argc - 1;
		key_t sharedMemID;
		int *sharedMemoryPtr;
		pid_t forkID;

		/* Create shared memory */
		sharedMemID = createSharedMemmoryForIntArray(length);

		printf("%s\n","...");

		/* Attach shared memory */
		sharedMemoryPtr = atachSharedMemory(sharedMemID);
		printf("%s\n", FILL_MEM_NOTIF);

		/* Fill atached shared memory with integers from argvs*/
		fillSharedMemmory(argv, sharedMemoryPtr, length);

		/* Print state of the shared memory*/
		printf("%s\n",SHARED_MEM_STATE_INIT);
		printSharedMemmory(sharedMemoryPtr, length);
		printf("%s\n","...");

		/* Fork N times, N is size of param array*/
		printf("%s %d %s\n","Getting ready to fork ", length, " time/s: ");
		forkNChildren(length, sharedMemoryPtr);

		/* Print state of the shared memory AGAIN*/
		printf("\n%s\n",SHARED_MEM_STATE_FINAL);
		printSharedMemmory(sharedMemoryPtr, length);
		printf("%s\n","...");

		/* Detach shared memory*/
		printf("%s\n", SHMDT_NOTIFICATION);
		shmdt(sharedMemoryPtr);

		/* Delete shared memory*/
		printf("%s\n", SHMCTL_NOTIFICATION);
		shmctl(sharedMemID, IPC_RMID, NULL);

		/* Notify end of the program */
		printf("%s\n", PROGRAM_END_NOTIF);
	} 

  return NO_PROGRAM_ERRORS;
}







/**
 * validateImput: The following function validates the command line imputs
 * received and verifies that the number of entries ranges from 1 to 7 
 * inclusive and that each entry corresponds to any number ranging from 
 * zero to 9.
 * @param  argc:  The number of parameters entered through the command line 
 * including the program name.
 * @param  argv:  The array containing the command line entries.
 * @return:       Returns TRUE if the imput is valid, FALSE if it is not.
 */
bool validateImput(int argc, char const *argv[]){
  bool answer = TRUE;
  int params = argc - 1;

	if((params < MIN_NUM_PARAMS) || (params > MAX_NUM_PARAMS)){
    	answer = FALSE;
  	}else {
    	int count = 0;
    	while((count < params) && (answer)){
    		if(!isDigit(argv[count + 1])){
        		answer = FALSE;
      		}	
      		count++;
    	}
  	}
  return answer;
}

/**
 * isDigit description: The following program determines if a string entered
 * through the method signature is a number and is a digit from 0 to 9.
 * @param  param: This is the string that will be evaluated.
 * @return: Returns TRUE if the string entered corresponds, or can be converted 
 * to a number ranging from 0 to 9, FALSE if its not.      
 */
bool isDigit(char const param[]){
	bool answer = FALSE;

 	if((atoi(param) >= SMALLEST_DIGIT_ALLOWED) 
 		&& (atoi(param) <= LARGEST_DIGIT_ALLOWED)){
  		answer = TRUE;
  	}

	return answer;
}


















