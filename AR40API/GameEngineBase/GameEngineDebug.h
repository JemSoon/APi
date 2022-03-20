#pragma once
#include <crtdbg.h>
#include <string>
#include <assert.h>
#include <Windows.h>
//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 디버깅할때 문제가 생겼을때 알려주는 기능
class GameEngineDebug
{
public:
	//아예 객체를 안만들고 전역함수로=static멤버 함수로만
	static void LeakCheckOn();

	//static void MsgBoxAssert(const std::string& _Text);
	//const &를 쓰는 이유?
	//넘기는 인자를 아끼고 함수에 넘기는 인자의 비용을 아끼고
	//수정하지 않겠다(const)를 명시

protected:

private:
	//디폴트 생성자
	GameEngineDebug();
	//디폴트 소멸자
	~GameEngineDebug();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;
};

#define MsgBoxAssert(Text)	MessageBeep(0);\
MessageBoxA(nullptr, Text, "Error", MB_OK);\
assert(false);