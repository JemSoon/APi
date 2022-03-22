//GameEngineBase������Ʈ�� ��� ������ ����ϰڴ�->�����߰�
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/SuperMario.h>

SuperMario MyGame;

void GameInit()//�ؽ�ó �ε� ������Ʈ �̸��غ�
{
	MyGame.GameInit();
}

void GameLoop()//���� ����
{
	//�� �ȿ��� ������ ����
	MyGame.GameLoop();
}

// hInstance == �� ���α׷��� �ֹι�ȣ�� ���� ��

int __stdcall WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ char*		lpCmdLine,
	_In_ int		nCmdShow)
{
	GameEngineDebug::LeakCheckOn();//��üũ

	GameEngineWindow::Destroy();

	MyGame.GameEnd();

	//���� ����� ���������� Ŭ������ ���ø�����
	GameEngine::Start<SuperMario>();
}