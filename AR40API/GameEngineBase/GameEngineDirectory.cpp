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

void GameEngineDirectory::MoveParent(const std::string& _Name)//어떤 이름을 가진 애까지 올라감
{
	while (false == IsRoot())
	{
	Path_ = Path_.parent_path();

		if (GetFileName() == _Name)//이름이 같은애를 발견하면 상위로 올라가는걸 멈춘다
		{
			break;
		}
	}
}
