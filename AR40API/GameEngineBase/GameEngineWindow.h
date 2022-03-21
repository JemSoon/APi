//exe�� ������� �ʿ䰡 ���� "���̺귯�� ������Ʈ"
#pragma once
#include <Windows.h>
#include <string>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �̱���
class GameEngineWindow
{
private:
	static GameEngineWindow* Inst_;

public:
	inline static GameEngineWindow& GetInst()
	{
		return *Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}
	
public:
	void RegClass(HINSTANCE _hInst);
	void CreateGameWindow(HINSTANCE _hInst, const std::string& _Title);//�����
	void ShowGameWindow();//����
	void MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)());//�޼����� ��ٸ��� ������ �� ���ư��� ��� ����

	void Off();

	static inline HDC GETDC()
	{
		return Inst_->HDC_;
	}

protected:

private:
	std::string Title_;
	bool WindowOn_;

	HINSTANCE hInst_;
	HWND hWnd_;

	HDC HDC_;

	//����Ʈ ������
	GameEngineWindow();
	//����Ʈ �Ҹ���
	~GameEngineWindow();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;


};

