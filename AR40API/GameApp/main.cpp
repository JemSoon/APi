//GameEngineBase������Ʈ�� ��� ������ ����ϰڴ�->�����߰�
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/SuperMario.h>


// hInstance == �� ���α׷��� �ֹι�ȣ�� ���� ��

int __stdcall WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ char*		lpCmdLine,
	_In_ int		nCmdShow)
{

	//new int();//�ŷ��� ��
	// 
	//���� ����� ���������� Ŭ������ ���ø�����
	GameEngine::Start<SuperMario>();
}