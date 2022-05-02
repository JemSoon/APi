#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineImage;
class GameEngineCollision;
class Turtle : public GameEngineActor
{
public:
	//디폴트 생성자
	Turtle();
	//디폴트 소멸자
	~Turtle();

	void DirCheck();


	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	Turtle(const Turtle& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Turtle(Turtle&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Turtle& operator=(const Turtle& _Other) = delete;
	Turtle& operator=(Turtle&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* TurtleAnimationRender;
	std::string AnimationName;


private:
	float Speed_;
	float AccSpeed_;

	std::string DirString_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* TurtleCollision;
	GameEngineCollision* TurtleTopCollision;
	GameEngineCollision* TurtleLeftCollision;
	GameEngineCollision* TurtleRightCollision;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void WallCheck();
	void FootCheck();
	void LeftCheck();
	void RightCheck();

	void AnotherTurtleCheck();
};

