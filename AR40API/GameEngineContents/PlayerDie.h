#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineImage;

class PlayerDie : public GameEngineActor
{
public:
	//����Ʈ ������
	PlayerDie();
	//����Ʈ �Ҹ���
	~PlayerDie();

public:
	void Start() override;
	void Render() override;
	void Update() override;

	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	PlayerDie(const PlayerDie& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	PlayerDie(PlayerDie&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	PlayerDie& operator=(const PlayerDie& _Other) = delete;
	PlayerDie& operator=(PlayerDie&& _Other) noexcept = delete;


protected:

private:
	float4 MoveDir;
	GameEngineRenderer* PlayerAnimationRender;
	float Time;

};

