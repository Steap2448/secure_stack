#include "Stack.h"

Stack_d ConstructStack_d()
{
	Stack_d stk = (Stack_d) calloc(1, sizeof(elStack_d));
	
	stk->position = 0;
	stk->errcode = 0;
	stk->size = STACK_SIZE;

	for (int i = 0; i < stk->size; ++i)
	{
		stk->data[i] = 0;
	}

#ifdef _DEBUG
	for (int i = 0; i < STACK_CANARY_SIZE; ++i)
	{
		stk->canary1[i] = i + 1;
		stk->canary2[i] = -(i + 1);
	}
	stk->hash1 = stk->hash2 = HashStack_d(stk);
#endif

	return stk;
}

int InitElStack_d(elStack_d* stk)
{

	stk->position = 0;
	stk->errcode = 0;
	stk->size = STACK_SIZE;

	for (int i = 0; i < stk->size; ++i)
	{
		stk->data[i] = 0;
	}

#ifdef _DEBUG
	for (int i = 0; i < STACK_CANARY_SIZE; ++i)
	{
		stk->canary1[i] = i + 1;
		stk->canary2[i] = -(i + 1);
	}
	stk->hash1 = stk->hash2 = HashStack_d(stk);
#endif

	return STACK_OK;
}

int PushStack_d(Stack_d stk, double value)
{
	if (stk == NULL)
	{
		return STACK_NULL_POINTER_ERR;
	}

#ifdef _DEBUG
	if (CheckStack_d(stk) != STACK_OK)
	{
		return STACK_CORRUPTION_ERR;
	}
#endif // _DEBUG

	if (stk->position >= stk->size)
	{
		return STACK_OVERFLOW_ERR;
	}

	stk->data[stk->position] = value;
	++stk->position;

#ifdef _DEBUG
	stk->hash1 = stk->hash2 = HashStack_d(stk);
	if (CheckStack_d(stk) != STACK_OK)
	{
		return STACK_CORRUPTION_ERR;
	}
#endif

	return STACK_OK;
}

int PopStack_d(Stack_d stk, double* destination)
{
	if (stk == NULL)
	{
		return STACK_NULL_POINTER_ERR;
	}

#ifdef _DEBUG
	if (CheckStack_d(stk) != STACK_OK)
	{
		return STACK_CORRUPTION_ERR;
	}
#endif // _DEBUG

	if (stk->position <= 0)
	{
		return STACK_UNDERFLOW_ERR;
	}
	stk->position--;
	*destination = stk->data[stk->position];

#ifdef _DEBUG
	stk->hash1 = stk->hash2 = HashStack_d(stk);
	if (CheckStack_d(stk) != STACK_OK)
	{
		return STACK_CORRUPTION_ERR;
	}
#endif

	return STACK_OK;
}

int DestroyStack_d(Stack_d stk)
{
	if (stk == NULL)
	{
		return STACK_NULL_POINTER_ERR;
	}

	free(stk);
	return STACK_OK;
}

int CheckStack_d(Stack_d stk)
{
	if (stk == NULL)
	{
		return STACK_NULL_POINTER_ERR;
	}

#ifdef _DEBUG
	for (int i = 0; i < STACK_CANARY_SIZE; ++i)
	{
		if ((stk->canary1[i] != i + 1) || (stk->canary2[i] != -(i + 1)))
		{
			printf("Corruption detected! Canaries are corrupted.\n");
			stk->errcode = STACK_CORRUPTION_ERR;
			DumpStack_d(stk);
			return STACK_CORRUPTION_ERR;
		}
	}

	int hash = HashStack_d(stk);
	if ((hash != stk->hash1) || (hash != stk->hash2))
	{
		printf("Corruption detected! Hashsums are corrupted.\n");
		stk->errcode = STACK_CORRUPTION_ERR;
		DumpStack_d(stk);
		return STACK_CORRUPTION_ERR;
	}
#endif

	if (stk->position > stk->size)
	{
		printf("Stack overflow!\n");
		stk->errcode = STACK_OVERFLOW_ERR;
		return STACK_OVERFLOW_ERR;
	}

	if (stk->position < 0)
	{
		printf("Stack underflow!\n");
		stk->errcode = STACK_UNDERFLOW_ERR;
		return STACK_UNDERFLOW_ERR;
	}

	return STACK_OK;
}

int DumpStack_d(Stack_d stk)
{
	if (stk == NULL)
	{
		printf("Null pointer!\n");
		return STACK_NULL_POINTER_ERR;
	}
	
	printf("Stack_d [%p] (%s)\n", stk, ((!stk->errcode) ? "ok" : "ERROR!"));

#ifdef _DEBUG
	printf("current hash = %d\n", HashStack_d(stk));
	printf("hash1 = %d\n", stk->hash1);
	printf("hash2 = %d\n", stk->hash2);

	char true_canary1[STACK_CANARY_SIZE];
	char true_canary2[STACK_CANARY_SIZE];
	for (int i = 0; i < STACK_CANARY_SIZE; ++i)
	{
		true_canary1[i] = i + 1;
		true_canary2[i] = -(i + 1);
	}

	printf("canary1 = ");
	for (int i = 0; i < STACK_CANARY_SIZE; ++i) printf("%d ", stk->canary1[i]);
	printf("( ");
	for (int i = 0; i < STACK_CANARY_SIZE; ++i) printf("%d ", true_canary1[i]);
	printf(")\n");
	
	printf("canary2 = ");
	for (int i = 0; i < STACK_CANARY_SIZE; ++i) printf("%d ", stk->canary2[i]);
	printf("( ");
	for (int i = 0; i < STACK_CANARY_SIZE; ++i) printf("%d ", true_canary2[i]);
	printf(")\n");
#endif

	printf("{\n errcode = %d\n size = %u\n", stk->errcode, stk->size);
	printf(" position = %u\n", stk->position);
	printf(" data[%u] = [%p]\n", 0, &stk->data[0]);
	printf(" data[%u] = [%p]\n", stk->size - 1, &stk->data[stk->size - 1]);

	for (int i = 0; i < stk->size; ++i)
	{
		printf(" ");
		if (i <= (((int)stk->position) - 1)) printf("*");
		printf("[%d] = %lf\n", i, stk->data[i]);
	}

	printf("}\n\n");

	return STACK_OK;
}

char HashStack_d(Stack_d stk)
{
	assert(stk);
	
	char res = 0;
	char* start = (char*) &(stk->size);
	char* finish = (char*) &(stk->errcode);

	while (start != finish)
	{
		res += *start;
		start++;
	}
	
	return res;
}