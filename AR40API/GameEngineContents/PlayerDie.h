#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineImage;

class PlayerDie : public GameEngineActor
{
public:
	//디폴트 생성자
	PlayerDie();
	//디폴트 소멸자
	~PlayerDie();

public:
	void Start() override;
	void Render() override;
	void Update() override;

	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	PlayerDie(const PlayerDie& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	PlayerDie(PlayerDie&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	PlayerDie& operator=(const PlayerDie& _Other) = delete;
	PlayerDie& operator=(PlayerDie&& _Other) noexcept = delete;


protected:

private:
	float4 MoveDir;
	GameEngineRenderer* PlayerAnimationRender;
	float Time;

};

