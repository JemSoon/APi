#pragma once
#include <Windows.h>
#include <map>
#include <string>


//���� : ��ư�Է�(getch_�� ��������� �̰� ����������� �������� ��� ������)
//����2: Ű �Է��̶�� ���Ǵ� �Ѱ��� �Ǳ⿡ �̱���
class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; //���� Ű�� ��������
		bool Press_; //�� ���ķ� ���������� ������ ������
		bool Up_; //�����ٰ� ������
		bool Free_;//�ȴ����� ������

		int Key_;//�� Ű�� ���ȴٸ�
		//'A'

		bool KeyCheck()
		{
			//��(��ȣ��) Ű�� üũ�ؼ� ���ϰ��� 0�� �ƴ϶�� �� Ű�� ���ȴ� 
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update();

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}

		//GameEngineKey(int _Key)
		//	:Key_(_Key)
		//	,Down_(false)
		//	,Press_(false)
		//	,Up_(false)
		//	,Free_(true)
		//{

		//}
	};


private:
	static GameEngineInput* Inst_;

public:
	static GameEngineInput* GetInst()
	{
		return Inst_;
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
	void Update();

	//(����)CreateKey(����,'A') == ������ AŰ�� 
	void CreateKey(const std::string& _Name, int _Key);

	bool IsDown(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);//�ٸ����� �ߺ��������� �ʰڱ� �ִ��� ������ üũ��

protected:

private:
	//�÷��̾� ����Ű�� ���Ⱦ�?
	std::map<std::string, GameEngineKey> AllInputKey_;

	//����Ʈ ������
	GameEngineInput();
	//����Ʈ �Ҹ���
	~GameEngineInput();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineInput(const GameEngineInput& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

};

