#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �ȳ� ���� 100�� ������ ��� +1
class GameEngineImage;
class GameEngineCollision;
class Coin : public GameEngineActor
{
public:
	//����Ʈ ������
	Coin();
	//����Ʈ �Ҹ���
	~Coin();

	int GetCoin()
	{
		return CoinGet;
	}
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Coin(const Coin& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Coin(Coin&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Coin& operator=(const Coin& _Other) = delete;
	Coin& operator=(Coin&& _Other) noexcept = delete;

	void Start() override;
	void Render() override;
	void Update() override;

	void PlayerCheck();
protected:

private:
	GameEngineRenderer* CoinAnimationRender;
	GameEngineCollision* CoinCollision;
	int CoinGet;
};

