#include "stdafx.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>

#else
#include <stdlib.h>
#endif // _DEBUG
#include "conio.h"


char* MakeSentence(const char** strings)
{
	return nullptr;
}

int main(int i_argc, char ** i_argl)
{
	const char * strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};

	char * pSentence = MakeSentence(strings);

	printf("The Sentence is: %s", pSentence);

	free(pSentence);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	_getch();
	return 0;
}