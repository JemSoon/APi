#pragma once
#include "GameEngine/GameEngineLevel.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class PlayLevel2 : public GameEngineLevel
{
public:
	//����Ʈ ������
	PlayLevel2();
	//����Ʈ �Ҹ���
	~PlayLevel2();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	PlayLevel2(const PlayLevel2& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	PlayLevel2(PlayLevel2&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	PlayLevel2& operator=(const PlayLevel2& _Other) = delete;
	PlayLevel2& operator=(PlayLevel2&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update() override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
private:

};

