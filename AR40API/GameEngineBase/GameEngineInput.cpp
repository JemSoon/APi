#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"


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

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();


GameEngineInput::GameEngineInput()
{

}

GameEngineInput::~GameEngineInput()
{

}

bool GameEngineInput::IsKey(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(_Name))//end�� fine�� ���������� �߰��� �̹� �����Ѵٴ°�
	{
		return true;
	}
	return false;
}

void GameEngineInput::CreateKey(const std::string& _Name, int _Key)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	//�̹� Ű�� ������ ����� �ȵ�
	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))//end�� fine�� ���������� �߰��� �̹� �����Ѵٴ°�
	{
		MsgBoxAssert("�̹� �����ϴ� Ű�� �� ������� ��");
		return;
	}

	//�ҹ��ڷ� Ű�Է� �־������� ������ġ
	if ('a' <= _Key && 'z' >= _Key)//�ƽ�Ű �ڵ�� a~z�� A~Z���� ���� ���ڴ�
	{
		_Key = std::toupper(_Key);//�빮�ڷ� �ٲ��ش�
	}
	AllInputKey_.insert(std::make_pair(UpperKey, GameEngineKey()));
	AllInputKey_[UpperKey].Key_ = _Key;
	AllInputKey_[UpperKey].Reset();
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

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))//end�� fine�� ���������� �߰��� �̹� �����Ѵٴ°�
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");
		return false;
	}

	return AllInputKey_[UpperKey].Down_;
}
bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");
		return false;
	}

	return AllInputKey_[UpperKey].Up_;
}

bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");

		return false;
	}

	return AllInputKey_[UpperKey].Press_;
}
bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�̹� �����ϴ� Ű �Դϴ�");

		return false;
	}

	return AllInputKey_[UpperKey].Free_;
}