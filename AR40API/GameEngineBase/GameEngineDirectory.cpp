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
		MsgBoxAssert("�������� �ʴ� ������ ���丮�� �ʱ�ȭ�Ϸ��� �߽��ϴ�.");
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

void GameEngineDirectory::Move(const std::string& _Name)
{
	std::filesystem::path CheckPath = Path_;
	CheckPath.append(_Name);

	if (false==std::filesystem::exists(CheckPath))
	{
		MsgBoxAssertString(_Name + "��ΰ� �������� �ʽ��ϴ�");
	}

	Path_ = CheckPath;

}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _Ext)
{
	std::filesystem::directory_iterator DirIter(Path_);

	std::string Ext = _Ext;

	if (Ext!="")
	{
		GameEngineString::ToUpper(Ext);//���� ���ڸ� �ᵵ �� �빮�ڷ��ν�

		if (std::string::npos == Ext.find("."))//npos�� �׳� -1
		{
			Ext = "." + Ext;//.�� ������ .�� �߰��Ѵ�
		}
	}
	std::vector<GameEngineFile> Return;

	//���丮���� �� �����ϱ� File
	for (const std::filesystem::directory_entry& Entry : DirIter)//for���ε� �� Ư��
	{
		if (true == Entry.is_directory())
		{
			continue;//���丮 ��ΰ� �´ٸ� �ٽ�Ż�� �ƴϴ� continue
			//�̶� ��� ��������=�׷��� �Ʒ��� �������� �� �� �ܾ�� �� �ִ�
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

	return Return;//���⼭ �̹����� ���� ���´�
}