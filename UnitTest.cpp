#include "UnitTest.h"

TortureRoom TortureRoomConstruct()
{
	TortureRoom tr = (TortureRoom) calloc(1, sizeof(elTortureRoom));
	InitElStack_d(&(tr->stk));

	return tr;
}

char TortureRoomPeekLeft(TortureRoom tr, unsigned shift)
{
	if (shift >= sizeof(tr->stk))
	{
		return UNIT_TEST_SHIFT_ERR;
	}
	
	char* tmp = &(tr->left);
	tmp += shift;
	return *tmp;
}

char TortureRoomPeekRight(TortureRoom tr, unsigned shift)
{
	if (shift >= sizeof(tr->stk))
	{
		return UNIT_TEST_SHIFT_ERR;
	}

	char* tmp = &(tr->right);
	tmp -= shift;
	return *tmp;
}

int TortureRoomModifyLeft(TortureRoom tr, unsigned shift, char value)
{
	if (shift >= sizeof(tr->stk))
	{
		return UNIT_TEST_SHIFT_ERR;
	}

	char* tmp = &(tr->left);
	tmp += shift;
	(*tmp) = value;
	return UNIT_TEST_OK;
}

int TortureRoomModifyRight(TortureRoom tr, unsigned shift, char value)
{
	if (shift >= sizeof(tr->stk))
	{
		return UNIT_TEST_SHIFT_ERR;
	}

	char* tmp = &(tr->right);
	tmp -= shift;
	(*tmp) = value;
	return UNIT_TEST_OK;
}

int UnitTest()
{
	printf("Conducting UnitTest.\n\n");
	TortureRoom tr = TortureRoomConstruct();
	double buf;
	Stack_d stk = &(tr->stk);

	assert(PushStack_d(stk, 10) == STACK_OK);
	assert(PushStack_d(stk, 15) == STACK_OK);
	assert(PushStack_d(stk, 13) == STACK_OK);
	assert(PushStack_d(stk, 16) == STACK_OK);
	assert(TortureRoomModifyLeft(tr, 10, 54) == UNIT_TEST_OK);
	assert(PopStack_d(stk, &buf) == STACK_CORRUPTION_ERR);

	assert(InitElStack_d(stk) == STACK_OK);
	assert(PushStack_d(stk, 10) == STACK_OK);
	assert(PopStack_d(stk, &buf) == STACK_OK);

	assert(InitElStack_d(stk) == STACK_OK);
	assert(PushStack_d(stk, 10) == STACK_OK);
	assert(PushStack_d(stk, 15) == STACK_OK);
	assert(PushStack_d(stk, 13) == STACK_OK);
	assert(PushStack_d(stk, 16) == STACK_OK);
	assert(TortureRoomModifyLeft(tr, 54, 54) == UNIT_TEST_OK);
	assert(PopStack_d(stk, &buf) == STACK_CORRUPTION_ERR);

	assert(InitElStack_d(stk) == STACK_OK);
	for (int i = 0; i < STACK_SIZE; ++i)
	{
		assert(PushStack_d(stk, i) == STACK_OK);
	}
	assert(PushStack_d(stk, 42) == STACK_OVERFLOW_ERR);
	assert(TortureRoomModifyLeft(tr, 54, 54) == UNIT_TEST_OK);
	assert(PopStack_d(stk, &buf) == STACK_CORRUPTION_ERR);

	assert(InitElStack_d(stk) == STACK_OK);
	for (int i = 0; i < STACK_SIZE; ++i)
	{
		assert(PushStack_d(stk, i) == STACK_OK);
	}
	assert(PushStack_d(stk, 42) == STACK_OVERFLOW_ERR);
	stk->size = 42;
	assert(PopStack_d(stk, &buf) == STACK_CORRUPTION_ERR);

	assert(InitElStack_d(stk) == STACK_OK);
	for (int i = 0; i < STACK_SIZE; ++i)
	{
		assert(PushStack_d(stk, i) == STACK_OK);
	}
	assert(PushStack_d(stk, 42) == STACK_OVERFLOW_ERR);
	stk->position = 42;
	assert(PopStack_d(stk, &buf) == STACK_CORRUPTION_ERR);

	assert(InitElStack_d(stk) == STACK_OK);
	assert(PopStack_d(stk, &buf) == STACK_UNDERFLOW_ERR);

	printf("UnitTest completed. Everything seems to be normal.\n");
	return UNIT_TEST_OK;
}
