#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 커지는 버섯
class GameEngineImage;
class GameEngineCollision;
class UPMushroom : public GameEngineActor
{
public:
	//디폴트 생성자
	UPMushroom();
	//디폴트 소멸자
	~UPMushroom();




	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	UPMushroom(const UPMushroom& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	UPMushroom(UPMushroom&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	UPMushroom& operator=(const UPMushroom& _Other) = delete;
	UPMushroom& operator=(UPMushroom&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* UPMushroomAnimationRender;
	std::string AnimationName;

private:
	float Speed_;
	float AccSpeed_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* UPMushroomCollision;
	GameEngineCollision* UPMushroomBotCollision;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void WallCheck();
	void FootCheck();
	void LeftCheck();
	void RightCheck();
	void ColBotCheck();
	void ColBotCheck2();
};

