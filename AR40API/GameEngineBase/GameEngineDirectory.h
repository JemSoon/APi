#pragma once
#include "GameEnginePath.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

class GameEngineFile;
//���� : ���丮�� ���� ����ϱ� ���� ���� (���� ����)
class GameEngineDirectory : public GameEnginePath
{
public:
	//����Ʈ ������
	GameEngineDirectory();
	//����Ʈ �Ҹ���
	~GameEngineDirectory();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	void MoveParent();

	void MoveParent(const std::string& _Name);

	bool IsRoot();

	void Move(const std::string& _Name);

	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

protected:

private:

};

