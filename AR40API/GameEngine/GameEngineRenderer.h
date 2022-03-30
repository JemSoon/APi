#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	//����Ʈ ������
	GameEngineRenderer();
	//����Ʈ �Ҹ���
	~GameEngineRenderer();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
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
	RenderPivot PivotType; //���� bot
	float4 RenderPivot_;
};

