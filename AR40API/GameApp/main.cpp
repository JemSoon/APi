//GameEngineBase프로젝트의 모든 내용을 사용하겠다->참조추가
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/SuperMario.h>


// hInstance == 이 프로그램의 주민번호를 가진 애

int __stdcall WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ char*		lpCmdLine,
	_In_ int		nCmdShow)
{

	//new int();//신뢰의 릭
	// 
	//내가 만들고 싶은게임의 클래스를 템플릿으로
	GameEngine::Start<SuperMario>();
}