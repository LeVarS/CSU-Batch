/*
 *
 * Compilation Instruction:
 * gcc commandline_parser.c -o commandline_parser
 * ./commandline_parser
 *
 */

#include <sys/types.h>	// time_t used for time in seconds (__darwin_time_t) - u_int32_t is an unsigned int
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "scheduling.h"	// scheduling policy
#include "queue.h"	// queue structs and queue funcions
#include "global.h" // global variables
#include "parser.h"

/* Error Code */
#define EINVAL       1
#define E2BIG        2

#define MAXMENUARGS  4 		/* maximum amount of arguments that the parser can accept */
#define MAXCMDLINE   64 	/* */

void menu_execute(char *line, int isargs); 
int cmd_run(int nargs, char **args); 		// Prototype for cmd_run which is later defined
int cmd_quit(int nargs, char **args);  		// Prototype for cmd_quit which is later defined
void showmenu(const char *x[]);		// Prototype for showmenu which is later defined
int cmd_helpmenu(int nargs, char **args);		// Prototype for cmd_helpmenu which is later defined
int cmd_dispatch(char *cmd);		// Prototype for cmd_dispatch which is later defined
int cmd_fcfs(int nargs);
int cmd_sjf(int nargs);
int cmd_priority(int nargs);
int cmd_list(int nargs);
int cmd_test(int nargs);

/*
 * The run command - submit a job.
 */
int cmd_run(int nargs, char **args) // "**" = pointer to pointer
{ 

	if (nargs != 4 && nargs != 3) {
		printf("Usage: \"run <job> <time> <priority>\" to specify the time and priority.\n");
		printf("Usage: \"run <job> <time>\" to specify the time. Priority will be set to 1.\n");
		return EINVAL;
	}
        
	Node *newNode = (Node*) malloc(sizeof(Node));
	printf("Job %s was submitted.\n", args[1]);
		
	// TODO: Print expected wait time
	print_policy();
	newNode->name = (char*) malloc(strlen(args[1]) + 1);
	strcpy(newNode->name, args[1]);
	newNode->jobTime = (int) atoi(args[2]);

	if (nargs == 3) 
	{
		newNode->jobPriority = 1;
	}
	else 
	{
		newNode->jobPriority = (int) atoi(args[3]);
	}

	enQueue(newNode);
	print_num_jobs();
	/* Use execv to run the submitted job in csubatch */
  	return 0; /* if succeed */
}

/* 
 * FCFS command - changes the policy to First Come First Served
 */
int cmd_fcfs(int nargs)
{
	if (nargs != 1)
	{
		printf("The \"FCFS\" command doesn't accept any flags.\n");
		return EINVAL;
	}
	return orderFCFS();
}

/* 
 * SJF command - changes the policy to Shortest Job First
 */
int cmd_sjf(int nargs)
{
	if (nargs != 1)
	{
		printf("The \"SJF\" command doesn't accept any flags.\n");
		return EINVAL;
	}
	return orderSJF();
}

/* 
 * Priority command - changes the policy to the 
 */
int cmd_priority(int nargs)
{
	if (nargs != 1)
	{
		printf("The \"Priority\" command doesn't accept any flags.\n");
		return EINVAL;
	}
	return orderPriority();
}

/*
 * List command - displays the jobs in the queue that are running and pending
 */
int cmd_list(int nargs)
{
	if (nargs != 1)
	{
		printf("The \"list\" command doesn't accept any flags.\n");
		return EINVAL;
	}
	print_num_jobs();
	print_policy();
	printQueue();
	return 0;
}

int cmd_test(int nargs)
{
	if (nargs != 4)
	{
		printf("Usage: run <job> <time> <priority>\n");
		return EINVAL;
	}
	// TODO: complete this command
	return 0;
}

/*
 * The quit command.
 */
int cmd_quit(int nargs, char **args) 
{
	if (nargs != 1)
	{
		printf("The \"quit\" command doesn't accept any flags.\n");
		return EINVAL;
	}
	printf("Please display performance information before exiting csubatch!\n");
        exit(0);
}

/*
 * Display menu information
 */
void showmenu(const char *x[])	// Name is a descriptive title for the menu that will be printed, and x[] is the array holding the contents of the menu
{
	int ct, half, i;

	printf("\n");
	//printf("%s\n", name);
	
	for (i=ct=0; x[i]; i++) {
		ct++;
	}

	for (i=0; i<ct; i++) {
		printf("  %-36s\n", x[i]);	// Prints the element at index "i" in 36 spaces. If element doesn't fill the entire 36 spaces, then fill the rest with empty spaces
		// if (i+half < ct) {
		// 	printf("%s", x[i+half]);
		// }
		printf("\n");
	}

	printf("\n");
}

static const char *helpmenu[] =
	{

		"NAME                         USAGE                            DESCRIPTION                  ",
		"fcfs                       cfs, FCFS           Changes policy to FCFS and reorders queue   ",
		"help                   help, h, ?, <flag>                   Print help menu                ",
		"list                         list               Prints jobs running and pending in queue   ",
		"priority                  priority, p         Changes policy to priority and reorders queue",
		"quit                        quit, q                          Exit csubatch                 ",
		"run                run <job> <time> <priority>          Adds a job to the queue            ",
		"sjf                         sjf, SJF            Changes policy to SJF and reorders queue   ",
		"test               test <benchmark> <policy>    Benchmark a policy with given information\n\t\t  <num_of_jobs> <priority_levels>\n\t\t   <min_CPU_time> <max_CPU_time>",

		NULL};

int cmd_helpmenu(int n, char **a)
{
	(void)n;
	(void)a;
	if (n == 1)
	{
		showmenu(helpmenu);	
	}
	else if (n > 2) {
		printf("Can only accept one flag at a time\n");
		printf("Acceptable flags:\"-fcfs\", \"-help\", \"-list\", \"-priority\", \"-quit\", \"-run\", \"-sjf\", \"-test\"\n");
	}
	else
	{
		if (a[1][0] == '-')
		{
			showmenu(helpmenu);
		}
		else
		{
			printf("\"%s\" is not a valid flag. All flag starts with a hyphen ('-').\n", a[1]);
		}
	}
	

	return 0;
}

/*
 *  Command table.
 *  Creating an unnamed struct and then creating an array that holds these structs
 * 	cmdtable is an array of these structs
 */
static struct {
	const char *name;
	int (*func)(int nargs, char **args);
} cmdtable[] = {
	/* commands: single command must end with \n */
	{ "?",	    cmd_helpmenu },
	{ "h",	    cmd_helpmenu },
	{ "help",	cmd_helpmenu },
	{ "r",		cmd_run },
	{ "run",	cmd_run },
	{ "q",	    cmd_quit },
	{ "quit",	cmd_quit },
	{ "list",   cmd_list },
	{ "test",   cmd_test },
	{ "fcfs",   cmd_fcfs },
	{ "FCFS",   cmd_fcfs },
	{ "sjf",    cmd_sjf },
	{ "SJF",    cmd_sjf },	
	{ "p",      cmd_priority },
	{ "priority", cmd_priority },
        /* Please add more operations below. */
        {NULL, NULL}
};

/*
 * Process a single command.
 */
int cmd_dispatch(char *cmd)
{
	// time_t beforesecs, aftersecs, secs;
	// u_int32_t beforensecs, afternsecs, nsecs;
	char *args[MAXMENUARGS];
	int nargs=0;
	char *word;
	char *context;
 	int i, result;

	for (word = strtok_r(cmd, " ", &context);  // sets "word" to be the first word in the string "cmd" that was passed
		 word != NULL;						   // "word" will be NULL once it reaches the end of the string
		 word = strtok_r(NULL, " ", &context)) // Walks through the string "cmd" and uses spaces as a delimeter. Whatever word it finds up to a space is stored in "word"
	{

		if (nargs > MAXMENUARGS) {
			printf("Command line has too many words\n");
			return E2BIG;
		}
		if (strcmp(word, " ") != 0 && strcmp(word, "\n") != 0)
		{
			args[nargs++] = word;
		}
	}

	if (nargs == 0) // if nothing was entered as a command
	{	
		return 0;
	}
	for (i = 0; i < nargs; i++)
	{
		args[i] = strtok(args[i], "\n");
	}

	// Iterates through the command table to see if the "cmd" entered is a valid command. If it is, then it will execute it and store the result in "result" and return it
	for (i=0; cmdtable[i].name; i++) {
		if (*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
			assert(cmdtable[i].func!=NULL);
            
            /* Call function through the cmd_table */
			result = cmdtable[i].func(nargs, args);
			return result;
		}
	}

	// If the command was not found in the for loop above 
	printf("%s: Command not found\n", args[0]);
	return EINVAL;
}

/*
 * Command line main loop.
 */
int parse()
{
	job_queue = initializeQueue();
	policy = FCFS;

	char *buffer;
    size_t bufsize = 64;
        
    buffer = (char*) malloc(bufsize * sizeof(char));
    if (buffer == NULL) 
	{
 		perror("Unable to malloc buffer\n");
 		exit(1);
	}
	
	printf("Welcom to LeVar's and Aaron's batch job scheduler Version 0.5\nType 'help' or '?' to find more about CSUbatch commands.\n");

    while (1) 
	{
		printf("> ");
		getline(&buffer, &bufsize, stdin);
		cmd_dispatch(buffer);
		printf("\n");
	}
        return 0;
}
