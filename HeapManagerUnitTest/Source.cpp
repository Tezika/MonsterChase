#include "stdafx.h"
#include "stdio.h"
#include "HeapManager.h"
#include "Engine-init.h"
#include <iostream> 

int main()
{
	Engine::Initialize();
	printf_s("Hello the world\n");
	system("pause");
    return 0;
}

