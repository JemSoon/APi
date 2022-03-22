#include "SuperMario.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"

SuperMario::SuperMario()
{

}

SuperMario::~SuperMario()
{

}

void SuperMario::GameInit()
{
	CreateLevel<PlayLevel>("Play");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");
}

void SuperMario::GameLoop()
{
}

void SuperMario::GameEnd()
{
}
