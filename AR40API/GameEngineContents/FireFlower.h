#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �ҽ�� �Ǵ� ��
class GameEngineImage;
class GameEngineCollision;
class FireFlower : public GameEngineActor
{
public:
	//����Ʈ ������
	FireFlower();
	//����Ʈ �Ҹ���
	~FireFlower();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	FireFlower(const FireFlower& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	FireFlower(FireFlower&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	FireFlower& operator=(const FireFlower& _Other) = delete;
	FireFlower& operator=(FireFlower&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* FireFlowerAnimationRender;
	std::string AnimationName;
private:
	float4 CheckPos_;
	int Color_;

	GameEngineCollision* FireFlowerCollision;

	void Start() override;
	void Render() override;
	void Update() override;

public:
	void FootCheck();
};

