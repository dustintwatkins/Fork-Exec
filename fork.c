#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
	int pid;

	printf("Starting program; process has pid %d\n", getpid());

	FILE *fp;
	fp = fopen("fork-output.txt", "w");
	fprintf(fp, "BEFORE FORK\n");
	
	if ((pid = fork()) < 0) {
		fprintf(stderr, "Could not fork()");
		exit(1);
	}

	/* BEGIN SECTION A */
	fprintf(fp, "SECTION A \n");
	printf("Section A;  pid %d\n", getpid());
//	sleep(30);

	/* END SECTION A */
	if (pid == 0) {
		/* BEGIN SECTION B */
		fprintf(fp, "SECTION B\n");
		printf("Section B\n");
//		sleep(30);
//		sleep(30);
		printf("Section B done sleeping\n");

		exit(0);

		/* END SECTION B */
	} else {
		/* BEGIN SECTION C */
		fprintf(fp, "SECTION C\n");
		printf("Section C\n");
//		sleep(30);
		wait(0);
		//sleep(30);
		printf("Section C done sleeping\n");
	//	fclose(fp);
		exit(0);

		/* END SECTION C */
	}
	/* BEGIN SECTION D */
	fprintf(fp, "SECTION D\n");
	printf("Section D\n");
	sleep(30);

	/* END SECTION D */
}
