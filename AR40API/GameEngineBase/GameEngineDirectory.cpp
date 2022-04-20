#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory()
{
	SetCurrentPath();
}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
{
	Path_ = _Path;
	if (false == IsExits())
	{
		MsgBoxAssert("존재하지 않는 폴더로 디렉토리를 초기화하려고 했습니다.");
	}
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

void GameEngineDirectory::Move(const std::string& _Name)
{
	std::filesystem::path CheckPath = Path_;
	CheckPath.append(_Name);

	if (false==std::filesystem::exists(CheckPath))
	{
		MsgBoxAssertString(_Name + "경로가 존재하지 않습니다");
	}

	Path_ = CheckPath;

}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
	std::filesystem::directory_iterator DirIter(Path_);

	std::string Ext = _Ext;

	if (Ext!="")
	{
		GameEngineString::ToUpper(Ext);//무슨 글자를 써도 다 대문자로인식

		if (std::string::npos == Ext.find("."))//npos는 그냥 -1
		{
			Ext = "." + Ext;//.이 없으면 .을 추가한다
		}
	}
	std::vector<GameEngineFile> Return;

	//디렉토리까지 다 나오니까 File
	for (const std::filesystem::directory_entry& Entry : DirIter)//for문인데 좀 특이
	{
		if (true == Entry.is_directory())
		{
			continue;//디렉토리 경로가 맞다면 다시탈게 아니니 continue
			//이때 재귀 돌려야함=그러면 아래쪽 폴더까지 싹 다 긁어올 수 있다
		}

		if (Ext != "")
		{
			GameEnginePath NewPath = Entry.path();

			std::string OtherExt = NewPath.GetExtension();
			GameEngineString::ToUpper(OtherExt);

			if (OtherExt != Ext)
			{
				continue;
			}
		}

		Return.push_back(GameEngineFile(Entry.path()));
	}

	return Return;//여기서 이미지가 전부 들어온다
}