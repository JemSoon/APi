#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 

class GameEngineImage;
class GameEngineCollision;
class Block : public GameEngineActor
{
public:
	//디폴트 생성자
	Block();
	//디폴트 소멸자
	~Block();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Block(const Block& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Block(Block&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void PlayerCheck();
protected:
	GameEngineRenderer* BlockAnimationRender;

private:
	GameEngineCollision* BlockCollision;
	GameEngineCollision* BlockBotCollision;
	GameEngineCollision* BlockTopCollision;
	GameEngineCollision* BlockLeftCollision;
	GameEngineCollision* BlockRightCollision;

};

