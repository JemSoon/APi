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


	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}
	
	void SetImageScale();

	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	void SetImage(const std::string& _Name);
	void SetIndex(size_t _Index);
	void SetIndexToScale(size_t _Index, float4 _Scale = {-1.0f, -1.0f});

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_; //센터 bot
	RenderScaleMode ScaleMode_;
	float4 RenderPivot_;
	float4 RenderScale_;//화면에 그려지는 크기
	float4 RenderImageScale_;//이미지에서 잘라내는 크기
	float4 RenderImagePivot_;

	unsigned int TransColor_;//지우고 싶은 색 설정
};

