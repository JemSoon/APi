#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;
class GameEngineCollision;
class EmptyBox : public GameEngineActor
{
public:
	//����Ʈ ������
	EmptyBox();
	//����Ʈ �Ҹ���
	~EmptyBox();

	

	void Start() override;
	void Render() override;
	void Update() override;
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	EmptyBox(const EmptyBox& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	EmptyBox(EmptyBox&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	EmptyBox& operator=(const EmptyBox& _Other) = delete;
	EmptyBox& operator=(EmptyBox&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* EmptyBoxAnimationRender;

private:
	GameEngineCollision* EmptyBoxCollision;
	GameEngineCollision* EmptyBoxTopCollision;
	GameEngineCollision* EmptyBoxBotCollision;
	GameEngineCollision* EmptyBoxLeftCollision;
	GameEngineCollision* EmptyBoxRightCollision;


};

