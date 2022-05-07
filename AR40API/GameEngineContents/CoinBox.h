#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineSound.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;
class GameEngineCollision;
class CoinBox : public GameEngineActor
{
public:
	//����Ʈ ������
	CoinBox();
	//����Ʈ �Ҹ���
	~CoinBox();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	CoinBox(const CoinBox& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	CoinBox(CoinBox&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	CoinBox& operator=(const CoinBox& _Other) = delete;
	CoinBox& operator=(CoinBox&& _Other) noexcept = delete;

	void Start() override;
	void Render() override;
	void Update() override;


public:
	void PlayerCheck();
	int HP;
protected:
	GameEngineRenderer* BoxAnimationRender;

private:
	GameEngineCollision* BoxCollision;
	GameEngineCollision* BoxBotCollision;
	GameEngineCollision* BoxTopCollision;
	GameEngineCollision* BoxLeftCollision;
	GameEngineCollision* BoxRightCollision;

	bool HitFlg;
};

