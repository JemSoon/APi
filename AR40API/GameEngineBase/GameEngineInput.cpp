#include "GameEngineInput.h"
#include "GameEngineDebug.h"

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

/*===========================================*/
void GameEngineInput::GameEngineKey::Update()
{
	if (true == KeyCheck())
	{	//KeyCheck�� true�� ���ȴ�

		if (true == Free_)
		{	//�������� Free�� true���ٸ� ��� ó�� �����ٴ°�
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		else if (true == Press_)
		{	//�̹� ������ ��� ������ �ִ� ����
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
	}
	else
	{
		if (true == Press_)
		{
			//�� ���߿� Press�� true���ٸ� ��� ���ٴ°�
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}
	
		else if (true == Up_)
		{
			//�� ���߿� Up�� true���ٸ� ���� ���¶�� ��
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}


/*===========================================*/
GameEngineInput::GameEngineInput()
{

}

GameEngineInput::~GameEngineInput()
{

}

bool GameEngineInput::IsKey(std::string _Name)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))//end�� fine�� ���������� �߰��� �̹� �����Ѵٴ°�
	{
		
		return true;
	}
	return false;
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	//�̹� Ű�� ������ ����� �ȵ�
	if (AllInputKey_.end() != AllInputKey_.find(_Name))//end�� fine�� ���������� �߰��� �̹� �����Ѵٴ°�
	{
		MsgBoxAssert("�̹� �����ϴ� Ű�� �� ������� ��");
		return;
	}

	//�ҹ��ڷ� Ű�Է� �־������� ������ġ
	if ('a' <= _Key && 'z' >= _Key)//�ƽ�Ű �ڵ�� a~z�� A~Z���� ���� ���ڴ�
	{
		_Key = std::toupper(_Key);//�빮�ڷ� �ٲ��ش�
	}
	AllInputKey_.insert(std::make_pair(_Name, GameEngineKey()));
	AllInputKey_[_Name].Key_ = _Key;
	AllInputKey_[_Name].Reset();
}

void GameEngineInput::Update()
{
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		//second�� �����̶� ���� �� ����

		//KeyUpdateStart�� ���� ��ƴٸ�
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update();

	}
}

bool GameEngineInput::IsDown(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))//end�� fine�� ���������� �߰��� �̹� �����Ѵٴ°�
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");
		return false;
	}

	return AllInputKey_[_Name].Down_;
}
bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");
		return false;
	}

	return AllInputKey_[_Name].Up_;
}

bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");

		return false;
	}

	return AllInputKey_[_Name].Press_;
}
bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");

		return false;
	}

	return AllInputKey_[_Name].Free_;
}