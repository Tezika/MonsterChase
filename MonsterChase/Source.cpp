#include "game.h"

using namespace MonsterChase;

int main()
{ 
	// insert code here...
	Game::GetInstance().Initialize();
	while (!Game::GetInstance().ShouldEnd())
	{
		Game::GetInstance().Run();
	}
	Game::GetInstance().Stop();
	system("pause");
}