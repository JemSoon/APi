#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 

class GameEngineImage;
class GameEngineCollision;
class Block : public GameEngineActor
{
public:
	//����Ʈ ������
	Block();
	//����Ʈ �Ҹ���
	~Block();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Block(const Block& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Block(Block&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void PlayerCheck();
protected:
	GameEngineRenderer* BlockAnimationRender;

private:
	GameEngineCollision* BlockCollision;
	GameEngineCollision* BlockBotCollision;
	GameEngineCollision* BlockTopCollision;
	GameEngineCollision* BlockLeftCollision;
	GameEngineCollision* BlockRightCollision;

};

