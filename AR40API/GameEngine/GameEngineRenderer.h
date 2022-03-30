#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	//디폴트 생성자
	GameEngineRenderer();
	//디폴트 소멸자
	~GameEngineRenderer();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType = _Type;
	}
	void SetImage(const std::string& _Name);

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType; //센터 bot
	float4 RenderPivot_;
};

