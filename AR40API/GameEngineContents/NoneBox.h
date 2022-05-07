#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineSound.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �Ӹ��� �ε����� �۸Դ� ����
class GameEngineImage;
class GameEngineCollision;
class NoneBox : public GameEngineActor
{
public:
	//����Ʈ ������
	NoneBox();
	//����Ʈ �Ҹ���
	~NoneBox();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	NoneBox(const NoneBox& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	NoneBox(NoneBox&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	NoneBox& operator=(const NoneBox& _Other) = delete;
	NoneBox& operator=(NoneBox&& _Other) noexcept = delete;



	void Start() override;
	void Render() override;
	void Update() override;


public:
	void PlayerCheck();
protected:
	GameEngineRenderer* BoxAnimationRender;

private:
	GameEngineCollision* BoxCollision;
	GameEngineCollision* BoxBotCollision;
	GameEngineCollision* BoxTopCollision;
	GameEngineCollision* BoxLeftCollision;
	GameEngineCollision* BoxRightCollision;

};

