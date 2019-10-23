#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

enum
{
	UNIT_TEST_OK,
	UNIT_TEST_INIT_ERR,
	UNIT_TEST_SHIFT_ERR,
};

typedef struct _TortureRoom
{
	char left = 42;
	elStack_d stk;
	char right = 42;
} *TortureRoom, elTortureRoom;

TortureRoom TortureRoomConstruct();
char TortureRoomPeekLeft(TortureRoom tr, unsigned shift);
char TortureRoomPeekRight(TortureRoom tr, unsigned shift);
int TortureRoomModifyLeft(TortureRoom tr, unsigned shift, char value);
int TortureRoomModifyRight(TortureRoom tr, unsigned shift, char value);
int UnitTest();

#endif
