#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{

}

GameEnginePath::~GameEnginePath()
{

}

void GameEnginePath::SetCurrentPath()//�����η� ����
{
	//���� ���� ��ġ
	Path_ = std::filesystem::current_path();
}

bool GameEnginePath::IsExits()//���� �ϴ��� �ϸ� �װɷ�
{
	return std::filesystem::exists(Path_);
}

std::string GameEnginePath::GetExtension()//Ȯ���� �ܿ��
{
	return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()//���� �̸� ��������
{
	return Path_.filename().string();
}