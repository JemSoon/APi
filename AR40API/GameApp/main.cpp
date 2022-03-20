//GameEngineBase������Ʈ�� ��� ������ ����ϰڴ�->�����߰�
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

void GameLoop()
{
	//�� �ȿ��� ������ ����
	Rectangle(GameEngineWindow::GETDC(), 100, 100, 200, 200);
}

// hInstance == �� ���α׷��� �ֹι�ȣ�� ���� ��

int __stdcall WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ char*		lpCmdLine,
	_In_ int		nCmdShow)
{
	GameEngineDebug::LeakCheckOn();//��üũ

	//GameEngineBase�� cpp���� �� ���� ���� ������
	GameEngineWindow::GetInst().CreateGameWindow(hInstance, "GameWindow");//�̰� ���� �����
	GameEngineWindow::GetInst().ShowGameWindow();//�̰ɷ� ����
	//���� â�� �Ѱ��� �ѹ��� �����(���� �Ҽ� ����)
	GameEngineWindow::GetInst().MessageLoop(GameLoop);

	GameEngineWindow::Destroy();
}