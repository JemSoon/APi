#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineSound.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineImage;
class GameEngineCollision;
class TurtleBack : public GameEngineActor
{
public:
	//디폴트 생성자
	TurtleBack();
	//디폴트 소멸자
	~TurtleBack();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	TurtleBack(const TurtleBack& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	TurtleBack(TurtleBack&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	TurtleBack& operator=(const TurtleBack& _Other) = delete;
	TurtleBack& operator=(TurtleBack&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* TBAnimationRender;
	std::string AnimationName;

private:
	float Speed_;
	float AccSpeed_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	void Start() override;
	void Render() override;
	void Update() override;

	GameEngineImage* MapColImage_;
	GameEngineCollision* TBCollision;
	GameEngineCollision* TBTopCollision;
	GameEngineCollision* TBTopLeftCollision;
	GameEngineCollision* TBTopRightCollision;
	GameEngineCollision* TBLeftCollision;
	GameEngineCollision* TBRightCollision;

public:
	void FootCheck();
	void LeftCheck();
	void RightCheck();
	void PlayerAttack();
	void Kill();

	void FallDead();
};

