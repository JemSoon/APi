#pragma once
#include "GameEnginePath.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ������ ���� �̿��ϱ� ���� ����
class GameEngineFile : public GameEnginePath
{
public:
	//����Ʈ ������
	GameEngineFile();
	//����Ʈ �Ҹ���
	~GameEngineFile();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineFile(const GameEngineFile& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;


protected:

private:

};

