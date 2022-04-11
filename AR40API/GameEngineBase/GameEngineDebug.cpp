#include "GameEngineDebug.h"

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

GameEngineDebug::GameEngineDebug()
{

}

GameEngineDebug::~GameEngineDebug()
{

}


//void GameEngineDebug::MsgBoxAssert(const std::string& _Text)
//{
//	MessageBeep(0);//뿝! 소리냄
//	MessageBoxA(nullptr, _Text.c_str(), "Error", MB_OK);
//	//자기자신 메시지 띄움
//	assert(false);
//}