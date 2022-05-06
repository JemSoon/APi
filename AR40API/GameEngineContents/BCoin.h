#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;
class GameEngineCollision;
class BCoin : public GameEngineActor
{
public:
	//����Ʈ ������
	BCoin();
	//����Ʈ �Ҹ���
	~BCoin();

	int GetCoin()
	{
		return CoinGet;
	}
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	BCoin(const BCoin& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BCoin(BCoin&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BCoin& operator=(const BCoin& _Other) = delete;
	BCoin& operator=(BCoin&& _Other) noexcept = delete;


	void Start() override;
	void Render() override;
	void Update() override;

protected:

private:
	GameEngineRenderer* BCoinAnimationRender;
	GameEngineCollision* BCoinCollision;
	int CoinGet;
	float4 MoveDir_;
	float Time_;
};

