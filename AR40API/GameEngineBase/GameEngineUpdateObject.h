#pragma once
#include <string>
#include "GameEngineTime.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ���߻��
class GameEngineUpdateObject
{
public:
	//����Ʈ ������
	GameEngineUpdateObject();
	//����Ʈ �Ҹ���
	~GameEngineUpdateObject();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;

	inline void On()
	{
		IsUpdate_ = true;
	}

	inline void Off()
	{
		IsUpdate_ = false;
	}

	inline virtual bool IsUpdate()
	{
		return IsUpdate_ && false == IsDeath_;
	}

	inline virtual bool IsDeath()
	{
		return IsDeath_;
	}

	inline void Death()
	{
		IsDeath_ = true;
	}

	void ReleaseUpdate()
	{
		if (false == IsReleaseUpdate_)
		{
			return;
		}

		DeathTime_ -= GameEngineTime::GetDeltaTime();

		if (0.0f >= DeathTime_)
		{
			IsDeath_ = true;
		}
	}

	inline void Death(float _Time)
	{
		IsReleaseUpdate_ = true;
		DeathTime_ = _Time;
	}

	inline int GetOrder()
	{
		return Order_;
	}

	virtual inline void SetOrder(int _Order)
	{
		Order_ = _Order;
	}

protected:

private:
	int Order_;
	bool IsReleaseUpdate_;
	float DeathTime_;

	bool IsUpdate_;
	bool IsDeath_;
};

