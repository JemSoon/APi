#pragma once
#include "GameEngine/GameEngineLevel.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class PlayLevel3 : public GameEngineLevel
{
public:
	//����Ʈ ������
	PlayLevel3();
	//����Ʈ �Ҹ���
	~PlayLevel3();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	PlayLevel3(const PlayLevel3& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	PlayLevel3(PlayLevel3&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	PlayLevel3& operator=(const PlayLevel3& _Other) = delete;
	PlayLevel3& operator=(PlayLevel3&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:

};

