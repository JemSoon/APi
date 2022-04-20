#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들



//설명 : 
class GameEngineImage;
class GameEngineCollision;
class Player : public GameEngineActor
{
public:
	//디폴트 생성자
	Player();
	//디폴트 소멸자
	~Player();


	static Player* MainPlayer;

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	Player(const Player& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Player(Player&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


	float4 CurDir()
	{
		return PlayerDir_;
	}

protected:
	GameEngineRenderer* PlayerAnimationRender;
	PlayerDir CurDir_;
	std::string AnimationName;

	void DirAnimationCheck();
	void PlayerStateUpdate();


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	static float4 NextLevelPosition;
	GameEngineRenderer* Render1;

	float Speed_;
	//float AccSpeed_;
	float Gravity_;
	float AccGravity_;
	float4 MoveDir_;
	float4 PlayerDir_;
	PlayerDir CheckDir_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision;

	//bool IsMoveKey();

	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();



};

