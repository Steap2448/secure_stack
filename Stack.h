#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define STACK_SIZE 6
#define STACK_NAME_SIZE 10

#ifdef _DEBUG
#define STACK_CANARY_SIZE 3
#endif

enum
{
	STACK_OK,
	STACK_OVERFLOW_ERR,
	STACK_UNDERFLOW_ERR,
	STACK_CORRUPTION_ERR,
	STACK_NULL_POINTER_ERR
};

/*!
*double Stack
*/
typedef struct _Stack_d
{
#ifdef _DEBUG
	char canary1[STACK_CANARY_SIZE];
	char hash1;
#endif

	//char name[STACK_NAME_SIZE];
	size_t size = STACK_SIZE;
	size_t position = 0;
	double data[STACK_SIZE];
	int errcode = 0;

#ifdef _DEBUG
	char hash2;
	char canary2[STACK_CANARY_SIZE];
#endif
}  elStack_d, * Stack_d;

/*!
*Construct Stack_d
*returns Stack_d
*/
Stack_d ConstructStack_d();
/*!
*Initialization of Stack_d at address stk
*returns error value
*/
int InitElStack_d(elStack_d* stk);
/*!
*Push value to Stack_d
*returns error value
*/
int PushStack_d(Stack_d stk, double value);
/*!
*Pops last element of Stack stk and puts it at destination address
*returns error value
*/
int PopStack_d(Stack_d stk, double* destination);
/*!
*Destroys Stack_d stk
*returns error value
*/
int DestroyStack_d(Stack_d stk);
/*!
*Checks Stack_d stk for corruption
*returns error value
*/
int CheckStack_d(Stack_d stk);
/*!
*Prints dump of stk
*returns error value
*/
int DumpStack_d(Stack_d stk);
/*!
*Calculates hashsum of Stack_d stk
*returns hashsum
*/
char HashStack_d(Stack_d stk);

#endif
