//GameEngineBase프로젝트의 모든 내용을 사용하겠다->참조추가
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/SuperMario.h>

SuperMario MyGame;

void GameInit()//텍스처 로딩 오브젝트 미리준비
{
	MyGame.GameInit();
}

void GameLoop()//게임 실행
{
	//이 안에서 게임을 만듦
	MyGame.GameLoop();
}

// hInstance == 이 프로그램의 주민번호를 가진 애

int __stdcall WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ char*		lpCmdLine,
	_In_ int		nCmdShow)
{
	GameEngineDebug::LeakCheckOn();//릭체크

	//GameEngineBase의 cpp까지 알 길이 없어 에러남
	GameEngineWindow::GetInst().CreateGameWindow(hInstance, "GameWindow");//이걸 통해 만들고
	GameEngineWindow::GetInst().ShowGameWindow();//이걸로 띄운다
	//게임 창은 한개니 한번만 띄워용(설명 할수 있자)
	GameEngineWindow::GetInst().MessageLoop(GameInit, GameLoop);

	GameEngineWindow::Destroy();

	MyGame.GameEnd();
}