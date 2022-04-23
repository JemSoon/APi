#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 커지는 버섯
class GameEngineImage;
class GameEngineCollision;
class Mushroom : public GameEngineActor
{
public:
	//디폴트 생성자
	Mushroom();
	//디폴트 소멸자
	~Mushroom();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Mushroom(const Mushroom& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Mushroom(Mushroom&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Mushroom& operator=(const Mushroom& _Other) = delete;
	Mushroom& operator=(Mushroom&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* MushroomAnimationRender;
	PlayerDir CurDir_;
	std::string AnimationName;

private:
	float Speed_;
	float AccSpeed_;

	float4 NextPos_;
	float4 CheckPos_;
	float4 MoveDir_;
	int Color_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* MushroomCollision;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void WallCheck();
	void FootCheck();
	void LeftCheck();
	void RightCheck();
};

