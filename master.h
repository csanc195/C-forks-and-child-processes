/****************************************************************************/
/*      master.h                                                            */
/****************************************************************************/
/* Author: Carlos L Sanchez Vila                                            */
/****************************************************************************/
/*                      Disclaimer:                                         */
/* I hereby certify that this collective work is my own and none of it is   */
/* the work of any other person or entity.                                  */
/****************************************************************************/
/* The following file contains all of the function prototypes, constants and*/
/* libraries needed for the program ./memChildShare.out to execute.			    */
/****************************************************************************/

#include <stdio.h>
#include <stdlib.h> 	/* Included to make use functions exit() and atoi() */
#include <unistd.h>		/* Included to make use of fork, getpid(), getppid()*/
#include <sys/types.h>	/* Included to make use of fork, getpid(), getppid()*/
#include <sys/ipc.h>	/* Needed by shared memory, messages and semaphores */
#include <sys/shm.h>	/* Inclued to make use of shmget() and shmat() 		*/

#define NO_PROGRAM_ERRORS 0 /* Signals a correct program execution			*/
#define PROGRAMM_ERRORS 1	/* Signals an incorrect program execution		*/
#define SHMGET_FLAG 0666	/* Flag/control signal used by  SHMGET 			*/
#define LINE_BUFFER 512		/* Buffer size for the sprintf function 		*/
#define SMALLEST_DIGIT_ALLOWED 0	/* Smallest available imput digit 		*/
#define LARGEST_DIGIT_ALLOWED 9		/* Largest available imput digit 		*/
#define MIN_NUM_PARAMS 1			/* Minimun number of params required	*/
#define MAX_NUM_PARAMS 7			/* Maximun number of params required	*/

/*The following are mysc, alerts and error messages used throught the program:*/
#define SHMGET_ERROR	"shmget error, Could not create shared memory!"
#define SHMGET_SUCCESS	"smget success, Shared memory successfully created!"
#define SHMAT_ERROR		"shmat error, Could not attach shared memory to server!"
#define SHMAT_SUCCESS	"shmat success, The memory was sucessfully atached!"
#define FORK_ATTEMPT_SUCCESS	"fork created for child: "
#define FORK_ATTEMPT_ERROR		"fork could not be created for child: "
#define WAIT_WITH_SUCCESS		"This child finished successfully, id: "
#define WAIT_WITH_ERROR			"This child finished with errors, id: "
#define FILL_MEM_NOTIF   		"...\nFilling the shared memory...\n..."
#define SHARED_MEM_STATE_INIT	"Initial state of the shared memory"
#define SHARED_MEM_STATE_FINAL	"Final state of the shared memory"
#define SHMDT_NOTIFICATION 		"Detaching shared memory..."
#define SHMCTL_NOTIFICATION 	"Deleting shared memory..."
#define PROGRAM_END_NOTIF		"Program terminated. >_<"

typedef enum {FALSE, TRUE} bool;		/* Allow the use of boolean types */

/* Function prototypes used by the program */

/* sharedMem.c function prototypes */
bool isDigit(char const[]);
bool validateImput(int , char const *[]);

/* master.c function prototypes */
void fillSharedMemmory(const char *[], int* , int);
void printSharedMemmory(int *, int);
void childTasks(int, int *, int);
int createSharedMemmoryForIntArray(int);
int * atachSharedMemory(key_t);
void forkNChildren(int, int *);


