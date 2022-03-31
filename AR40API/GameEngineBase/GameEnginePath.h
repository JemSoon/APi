#pragma once
#include <filesystem>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEnginePath
{

public:
	//����Ʈ ������
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _Path);
	//����Ʈ �Ҹ���
	~GameEnginePath();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEnginePath(const GameEnginePath& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;
	
	void SetCurrentPath();

	bool IsExits();

	std::string GetExtension();

	std::string GetFileName();

	std::string GetFullPath();

protected:
	std::filesystem::path Path_;

private:

};

