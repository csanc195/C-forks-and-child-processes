# C-forks-and-child-processes

<h3>The following program is a proof of concept of the functionalities provided by C Forks which allow the creation of child processes.</h3>

The following program accepts a number of arguments from the command-line, (between 1 and 7), inclusive – each a unique integer between 0-9. The program (parent process) requests shared memory for these integers, attaches the shared memory to its own address space and fills the space (using an array) with the integers from the command-line. 
The parent displays the initial state of the shared memory and then spawns a number of child processes equal to the number of command-line arguments, and waits for each child to complete its tasks. Upon completion of all children, the parent acknowledges said completion by storing and displaying each of their respective exit codes, then displays the final state of the shared memory, detaches the shared memory, removes the shared memory, and then terminates. Each child process receives a unique ID upon initiation – an integer between 1 and the number of command-line arguments (maximum 7).

Each child displays the initial state of the shared memory and their private memory - their unique ID. Next each child locates the array element (index) associated with their unique ID and then multiplies that array element by their unique ID, storing the result in the same array element. Each child then displays the current state of the shared memory, provide their exit status/code, and exit.
