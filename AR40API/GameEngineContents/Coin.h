#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 냠냠 코인 100개 모으면 목숨 +1
class GameEngineImage;
class GameEngineCollision;
class Coin : public GameEngineActor
{
public:
	//디폴트 생성자
	Coin();
	//디폴트 소멸자
	~Coin();

	int GetCoin()
	{
		return CoinGet;
	}
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Coin(const Coin& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Coin(Coin&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Coin& operator=(const Coin& _Other) = delete;
	Coin& operator=(Coin&& _Other) noexcept = delete;

	void Start() override;
	void Render() override;
	void Update() override;

	void PlayerCheck();
protected:

private:
	GameEngineRenderer* CoinAnimationRender;
	GameEngineCollision* CoinCollision;
	int CoinGet;
};

