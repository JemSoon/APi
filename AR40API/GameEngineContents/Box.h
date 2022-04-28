#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 머리로 부딪혀서 템먹는 상자
class GameEngineImage;
class GameEngineCollision;
class Box : public GameEngineActor
{
public:
	//디폴트 생성자
	Box();
	//디폴트 소멸자
	~Box();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Box(const Box& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Box(Box&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Box& operator=(const Box& _Other) = delete;
	Box& operator=(Box&& _Other) noexcept = delete;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void FootCheck();
	void PlayerCheck();
protected:
	GameEngineRenderer* BoxAnimationRender;

private:
	GameEngineCollision* BoxCollision;
	GameEngineCollision* BoxBotCollision;
};

