//exe가 만들어질 필요가 없는 "라이브러리 프로젝트"
#pragma once
#include <Windows.h>
#include <string>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 싱글톤
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
	void CreateGameWindow(HINSTANCE _hInst, const std::string& _Title);//만들기
	void ShowGameWindow();//띄우기
	void MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)());//메세지를 기다리며 윈도우 잘 돌아가나 계속 감시

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

	//디폴트 생성자
	GameEngineWindow();
	//디폴트 소멸자
	~GameEngineWindow();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;


};

