#pragma once
#include <GameEngine/GameEngineLevel.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class BonusLevel : public GameEngineLevel
{
public:
	//����Ʈ ������
	BonusLevel();
	//����Ʈ �Ҹ���
	~BonusLevel();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	BonusLevel(const BonusLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BonusLevel(BonusLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BonusLevel& operator=(const BonusLevel& _Other) = delete;
	BonusLevel& operator=(BonusLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:

};

