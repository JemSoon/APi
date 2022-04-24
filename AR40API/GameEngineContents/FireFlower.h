#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 불쏘게 되는 꽃
class GameEngineImage;
class GameEngineCollision;
class FireFlower : public GameEngineActor
{
public:
	//디폴트 생성자
	FireFlower();
	//디폴트 소멸자
	~FireFlower();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	FireFlower(const FireFlower& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	FireFlower(FireFlower&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	FireFlower& operator=(const FireFlower& _Other) = delete;
	FireFlower& operator=(FireFlower&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* FireFlowerAnimationRender;
	std::string AnimationName;
private:
	float4 CheckPos_;
	int Color_;

	GameEngineCollision* FireFlowerCollision;

	void Start() override;
	void Render() override;
	void Update() override;

public:
	void FootCheck();
};

