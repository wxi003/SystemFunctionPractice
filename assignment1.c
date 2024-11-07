#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*
This program forks a process.  The child and parent processes print to terminal to identify themselves, and also the child process prints its parent's ID.
*/

int main(int argc, char *argv[])
{
	pid_t parent, child_1, child_1_1, child_1_2, child_2;
	size_t size;

	parent = getpid();
	child_1 = fork();

	if (child_1 > 0) // parent process
	{
		printf("\nparent (PID %d): process started\n", parent);
		printf("\nparent (PID %d): forking child_1", parent);
		printf("\nparent (PID %d): fork successful for child_1 (PID %d)", parent, child_1);
		printf("\nparent (PID %d): waiting for child_1 (PID %d) to complete", parent, child_1);
		printf("\n");

		wait(NULL); // wait until child_1 is completed

		child_2 = fork();

		if (child_2 > 0)
		{ // still parent process
			printf("\n\nparent (PID %d): forking child_2", parent);
			printf("\nparent (PID %d): fork successful for child_2 (PID %d)", parent, child_2);
			printf("\n");

			wait(NULL); // wait until child_2 is completed

			printf("parent (PID %d): completed parent\n", parent);
		}
		else if (child_2 == 0)
		{ // child_2 process
			printf("child_2 (PID %d): process started from parent (PID %d)", getpid(), parent);
			printf("\nchild_2 (PID %d): calling an external program [./external_program2.out]\n", getpid());
			execl(argv[2], argv[5], NULL); // pass the third input variable(argv[3]) to external program 1
		}
		else
		{
			exit(1); // fork unsuccessful
		}
	}
	else if (child_1 == 0)
	{ // child_1 process
		child_1_1 = fork();

		if (child_1_1 > 0)
		{ // still child_1 process
			printf("child_1 (PID %d): process started from parent (PID %d)\n", getpid(), parent);
			printf("\nchild_1 (PID %d): forking child_1.1", getpid());
			printf("\n");
			wait(NULL);

			child_1_2 = fork();

			if (child_1_2 > 0)
			{ // still child_1 process
				printf("child_1 (PID %d): completed child_1.1\n", getpid());
				printf("\nchild_1 (PID %d):forking child_1.2", getpid());
				printf("\n");

				wait(NULL);
				printf("child_1 (PID %d): completed child_1.2", getpid());
			}
			else if (child_1_2 == 0)
			{ // child_1.2 process
				printf("child_1.2 (PID %d): process started from child_1 (PID %d)", getpid(), getppid());
				printf("\nchild_1.2 (PID %d): calling an external program [./external_program1.out]", getpid());
				printf("\n");
				execl(argv[1], argv[4], NULL); // pass the second input variable(argv[2]) to external program 1
			}
			else
			{
				exit(1); // fork unsuccessful
			}
		}
		else if (child_1_1 == 0)
		{ // child_1.1 process
			printf("child_1.1 (PID %d): process started from child_1 (PID %d)", getpid(), getppid());
			printf("\nchild_1.1 (PID %d): calling an external program [./external_program1.out]", getpid());
			printf("\n");
			execl(argv[1], argv[3], NULL); // pass the first input variable(argv[1]) to external program 1
		}
		else
		{
			exit(1); // fork unsuccessful
		}
	}
	else
	{
		exit(1); // fork unsuccessful
	}

	return 0;
}
