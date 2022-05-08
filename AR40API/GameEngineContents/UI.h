#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 인게임 화면에 출력될 UI
class GameEngineRenderer;
class UI : public GameEngineActor
{
public:
	static UI* MainUI;

	//디폴트 생성자
	UI();
	//디폴트 소멸자
	~UI();

	int GetCoinCount()
	{
		return CoinCount_;
	}
	
	static int CoinCount_;
	int TimeCount_;
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	UI(const UI& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	UI(UI&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;


protected:

	void Start() override;
	void Update() override;
	//void Render() override;
private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	GameEngineRenderer* One;
	GameEngineRenderer* Ten;

	GameEngineRenderer* TOne;
	GameEngineRenderer* TTen;
	GameEngineRenderer* TH;
};

