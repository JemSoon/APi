#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
{
public:
	friend GameEngineLevel;

	//디폴트 생성자
	GameEngineActor();
	//디폴트 소멸자
	virtual ~GameEngineActor();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineActor(const GameEngineActor& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	inline float4 GetPosition()
	{
		return Position_;
	}
	inline float4 GetScale()
	{
		return Scale_;
	}

	inline void SetMove(float4 _Value)
	{
		Position_ += _Value;
	}

	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}
	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}

protected:
	//start는 무조건 구현
	virtual void Start() = 0;//시작하면 뭔갈 하고싶은데 생성자에서는 절대로 못할 부분들을 처리한다
	
	virtual void Update() {}//스킬을 갖는다 레벨을 올린다 등등을 업데이트(지속적으로 겜이 실행될때 호출됨)

	virtual void Render() {}

	void DebugRectRender();
private:
	GameEngineLevel* Level_;

	float4 Position_;
	float4 Scale_;

	//나를 만들어준 레벨
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

public:
	//===================여기부터 Render관련 ==========================
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = {0, 0});
	
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _Scale, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0, 0 });

	void Renderering();
	
private:
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;

	std::list<GameEngineRenderer*> RenderList_;
};

