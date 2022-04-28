#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �Ӹ��� �ε����� �۸Դ� ����
class GameEngineImage;
class GameEngineCollision;
class Box : public GameEngineActor
{
public:
	//����Ʈ ������
	Box();
	//����Ʈ �Ҹ���
	~Box();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Box(const Box& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Box(Box&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Box& operator=(const Box& _Other) = delete;
	Box& operator=(Box&& _Other) noexcept = delete;


	void Start() override;
	void Render() override;
	void Update() override;


public:
	void FootCheck();
	void PlayerCheck();
protected:
	GameEngineRenderer* BoxAnimationRender;

private:
	GameEngineCollision* BoxCollision;
	GameEngineCollision* BoxBotCollision;
};

