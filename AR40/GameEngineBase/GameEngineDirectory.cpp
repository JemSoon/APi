#include "GameEngineDirectory.h"

GameEngineDirectory::GameEngineDirectory()
{
	SetCurrentPath();
}

GameEngineDirectory::~GameEngineDirectory()
{

}

void GameEngineDirectory::MoveParent()
{
	Path_ = Path_.parent_path();
}

bool GameEngineDirectory::IsRoot()
{
	return Path_ == Path_.root_directory();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)//� �̸��� ���� �ֱ��� �ö�
{
	while (false == IsRoot())
	{
	Path_ = Path_.parent_path();

		if (GetFileName() == _Name)//�̸��� �����ָ� �߰��ϸ� ������ �ö󰡴°� �����
		{
			break;
		}
	}
}
