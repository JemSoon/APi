#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{

}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
	:Path_(_Path)
{

}

GameEnginePath::~GameEnginePath()
{

}

void GameEnginePath::SetCurrentPath()//현재경로로 셋팅
{
	//현재 폴더 위치
	Path_ = std::filesystem::current_path();
}

bool GameEnginePath::IsExits()//존재 하느냐 하면 그걸로
{
	return std::filesystem::exists(Path_);
}

std::string GameEnginePath::GetExtension()//확장자 외우기
{
	return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()//파일 이름 가져오기
{
	return Path_.filename().string();
}

std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}