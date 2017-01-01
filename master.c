/****************************************************************************/
/*      sharedMem.c                                                         */
/****************************************************************************/
/* Author: Carlos L Sanchez Vila                                            */
/****************************************************************************/
/*                      Disclaimer:                                         */
/* I hereby certify that this collective work is my own and none of it is   */
/* the work of any other person or entity.                                  */
/****************************************************************************/
#include "master.h"

/**
 * createSharedMemmoryForIntArray: The following function creates a shared 
 * memory to allocate integer numbers of size N where N is given by the 
 * parameter length, and returns a shared memory ID as an integer. If the 
 * function is unable to create a shared memory the program will end and an 
 * error message will be shown.
 * @param  length: This parameter is the length of the memory to be alocated.
 * @return: This function returns an integer number representing the ID of 
 * the shared memory.
 */
int createSharedMemmoryForIntArray(int length){
  key_t sharedMemID = shmget(IPC_PRIVATE, 
      length * sizeof(int), IPC_CREAT | SHMGET_FLAG);

    if (sharedMemID < 0) {
    	printf("%s\n", SHMGET_ERROR);
      	exit(1);
    } else {
      	printf("%s\n", SHMGET_SUCCESS);
    }

    return sharedMemID;
}



/**
 * atachSharedMemory: The following function ataches a shared memory to the 
 * callers adress space. The function uses the shared memory ID entered as a
 * parameter and returns a pointer that directs to the shared memory adress.
 * @param  sharedMemID: This parameter represents the shared memory ID of the
 * shared memory that will be attached. If the funciton is unable to atach the 
 * shared memory the program will end. Notice that this function gnerates a 
 * warning during compilation time, as the result of shmat() is a void pointer.
 * This is perfectly normal.
 * @return: This function returns a pointer to the atached memory. 
 */
int * atachSharedMemory(key_t sharedMemID){

	int *sharedMemoryPtr = (int *) shmat(sharedMemID, NULL, 0);

	if ((int) sharedMemoryPtr == -1) { 
	  printf("%s\n", SHMAT_ERROR);
		exit(1);
	} else{
		printf("%s\n", SHMAT_SUCCESS);
	}
	return sharedMemoryPtr;
}


/**
 * forkNChildren description: The following function takes a shared memory 
 * pointer and an integer number and forks the program N times where N is the 
 * parameter lenght and does some work for each child. The function then waits
 * for all childs to complete before finishing. If the function is unable to 
 * execute a fork the program will terminate and an error message will be shown.
 * @param length: This parameter contains the length of the shared memory and 
 * also the number of children processes that will be created(forked), and also
 * the number of children that the function will wait for before closing.
 * @param sharedMemoryPtr: This parameter represents the pointer to the 
 * allocated shared memory.
 */
void forkNChildren(int length, int *sharedMemoryPtr){

	pid_t forkID;
	int status;
	int i;
	for(i = 0; i < length; i++){
		forkID = fork();
      	if(forkID < 0){
      		printf("%s\n",FORK_ATTEMPT_ERROR);
        	exit(1);
     	 } else if(forkID == 0){
     	 	childTasks(i, sharedMemoryPtr, length);
        	exit(0);
      	}
    }

     /* Wait for all children*/
    for(i = 0; i < length; i++){
    	wait(&status);
    }
    printf("%s %d %s\n","Waited for all ", i,
     " children process/es to finish.");
}


/**
 * printSharedMemmory: The following function takes a pointer to int saved in 
 * and an the shared memory and an integer which represents the size of the 
 * shared memory and prints its contents onto the screen.
 * @param sharedMemoryPtr: This is the pointer to the int array contained in
 * the shared memory.
 * @param lenght: This parameter represents the length of the integer array 
 * that will be print onto the screen.
 */
void printSharedMemmory(int * sharedMemoryPtr, int lenght){
  char line[LINE_BUFFER];

  fflush(stdout);
	int i;
	printf("%s %d","[", sharedMemoryPtr[0]);
	for(i =1; i < lenght; i++){
		printf("%s %d", ", ", sharedMemoryPtr[i]);
	}
	printf("%s\n"," ]" );
  fflush(stdout);
}



/**
 * fillSharedMemmory: The following function takes a constant char array, a 
 * pointer to an int array in shared memory, and also an int representing the 
 * size of both arrays.
 * @param argv: This array contains the data that will be stored into the 
 * integer array contained in the shared memory.
 * @param sharedMemoryPtr: This parameter represents the pointer to the int 
 * array contained in shared memory whose contents will be filled with the data
 * contained in the array argv.
 * @param length: This parameter represents the length of the array on the 
 * shared memory that will be filled with the data contained in the array argv.           
 */
void fillSharedMemmory(const char *argv[], int *sharedMemoryPtr, int length){
    int i;
	for(i = 0; i < length; i++){
      sharedMemoryPtr[i] = atoi(argv[i + 1]);
    }
}


/**
 * childTasks: The following function contains a certain number of tasks that 
 * that monitor each child process actions and bhaviours, for the requesting 
 * child the function will print its unique index which is a number from 
 * one to seven, its parent's process ID, and its own process ID.
 * @param index: This is the current children number according to the caller
 * @param sharedMemoryPtr: This parameter represents a pointer to the array 
 * contained in the shared memory.
 * @param length: This parameter represents the length of the array contained 
 * in the shared memory.
 */
void childTasks(int index, int *sharedMemoryPtr, int length){
  int childIndex = index;
  char line [LINE_BUFFER];

  sharedMemoryPtr[index] *= (childIndex + 1);
  childIndex = index + 1;

  /* Prepare a child response and save it to line */
  sprintf(line, "%s \n%s%29s \n%s%5d%24s \n%s%8d%21s \n%s%8d%21s \n%s\n %15s",
      "+-----------------------------------------------------+",
      "| Fork successful:        ","|",
      "| Unique childIndex:      ", childIndex, "|",
      "| Parent process ID:      ", getppid(),"|",
      "| This child Process ID:  ", getpid(),"|",
      "+-----------------------------------------------------+",
      "Shared Memory ->  ");

  /* Print the line created */
  fflush(stdout);
  printf("%s", line);
  fflush(stdout);
  printSharedMemmory(sharedMemoryPtr, length);
  
}
