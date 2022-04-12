#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

//�� ���ڰ� ������ ���͸� �ִ� �״�� ����
//#define RENDERORDERMAX 2147483647

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineRenderer;
class GameEngineLevel;
class GameEngineCollision;
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
{
public:
	friend GameEngineLevel;

	//����Ʈ ������
	GameEngineActor();
	//����Ʈ �Ҹ���
	virtual ~GameEngineActor();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	GameEngineActor(const GameEngineActor& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	inline float4 GetCameraEffectPosition()
	{
		return Position_ - GetLevel()->GetCameraPos();
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
	//start�� ������ ����
	virtual void Start() = 0;//�����ϸ� ���� �ϰ������ �����ڿ����� ����� ���� �κе��� ó���Ѵ�

	virtual void Update() {}//��ų�� ���´� ������ �ø��� ����� ������Ʈ(���������� ���� ����ɶ� ȣ���)

	virtual void Render() {}

	void Release();

	void DebugRectRender();
private:
	GameEngineLevel* Level_;

	float4 Position_;
	float4 Scale_;

	//���� ������� ����
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

public:
	//===================������� Render���� ==========================
	GameEngineRenderer* CreateRenderer(int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });

	GameEngineRenderer* CreateRenderer(const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });

	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _Scale, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });


private:
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;

	std::list<GameEngineRenderer*> RenderList_;






public:
	/*=================���⼭ ���� �浹====================*/
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = { 0,0 });
	//�÷��̾�׷�,���ͱ׷�,�÷��̾� ���ñ׷�, ���� ���ñ׷� ��//�浹 �ڽ� ������//�浹 �ڽ� ������ (��ġ)


private:
	std::list<GameEngineCollision*> CollisionList_;

};

