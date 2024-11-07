Parent and Child Processes:
This program in C performs the following tasks:
1. The parent process will create a child process (i.e., child_1)
2. Parent process will wait for child_1 to complete before creating child_2
3. child_1 will call an external program “external_program.out” (hint: excel()) and pass its PID concatenated with
string “ for child_1”. As a result of this external program call, child_1 will be replaced by external_program.out.
4. Parent process will create child_2 and then child_2 will create child_2.1
5. Inside child_2.1, a call to an external program “external_program.out” will be made (hint: excel()). child_2.1
must pass its PID to “external_program.out” concatenated with string “ for child_2.1”. As a result of this external
program call, child_2.1 will be replaced by external_program.out.
6. Parent process will wait for child_1 and child_2 to be completed before it terminates.

Functions used: fork(), wait(), getpid(), getppid(), execl(), strcat()


The expected output look like the following:
parent (PID 333275) created child_1 (PID 333276)
parent (PID 333275) is waiting for child_1 (PID 333276) to complete before creating child_2
child_1 (PID 333276) is calling an external program external_program.out and leaving parent
From the external program: The PID was 333276 for child_1
parent (PID 333275) created child_2 (PID 333277)
child_2 (PID 333277) created child_2.1 (PID 333278)
child_2.1 (PID 333278) is calling an external program external_program.out and leaving child_2
From the external program: The PID was 333278 for child_2.1
child_1 and child_2 are completed and parent process is terminating...
