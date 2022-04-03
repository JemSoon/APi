#pragma once
#include <Windows.h>
#include <map>
#include <string>


//설명 : 버튼입력(getch_는 대기하지만 이건 대기하지않음 눌렸을때 잠깐 리턴함)
//설명2: 키 입력이라는 정의는 한개면 되기에 싱글톤
class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; //최초 키를 눌렀을때
		bool Press_; //그 이후로 지속적으로 누르고 있을때
		bool Up_; //누르다가 땠을때
		bool Free_;//안누르고 있을때

		int Key_;//이 키가 눌렸다면
		//'A'

		bool KeyCheck()
		{
			//이(괄호안) 키를 체크해서 리턴값이 0이 아니라면 이 키가 눌렸다 
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

	//(예시)CreateKey(점프,'A') == 점프를 A키로 
	void CreateKey(const std::string& _Name, int _Key);

	bool IsDown(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);//다른씬에 중복생성하지 않겠금 있는지 없는지 체크용

protected:

private:
	//플레이어 점프키가 눌렸어?
	std::map<std::string, GameEngineKey> AllInputKey_;

	//디폴트 생성자
	GameEngineInput();
	//디폴트 소멸자
	~GameEngineInput();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineInput(const GameEngineInput& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

};

