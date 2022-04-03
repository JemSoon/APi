#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"

//�������� ������ �͵鵵 ���������� ĥ ���̴�
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

	
	
	
	//======�Ʒ��͵��� ���������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
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

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_; //���� bot
	RenderScaleMode ScaleMode_;
	float4 RenderPivot_;
	float4 RenderScale_;//ȭ�鿡 �׷����� ũ��
	float4 RenderImageScale_;//�̹������� �߶󳻴� ũ��
	float4 RenderImagePivot_;

	unsigned int TransColor_;//����� ���� �� ����
};
