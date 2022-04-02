#include "GameEngineInput.h"
#include "GameEngineDebug.h"

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

/*===========================================*/
void GameEngineInput::GameEngineKey::Update()
{
	if (true == KeyCheck())
	{	//KeyCheck가 true면 눌렸다

		if (true == Free_)
		{	//그직전에 Free가 true였다면 방금 처음 눌렀다는것
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		else if (true == Press_)
		{	//이미 눌렀고 계속 누르고 있는 상태
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
			//그 외중에 Press가 true였다면 방금 땠다는것
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}
	
		else if (true == Up_)
		{
			//그 외중에 Up가 true였다면 때진 상태라는 것
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
	if (AllInputKey_.end() != AllInputKey_.find(_Name))//end랑 fine가 같지않으면 중간에 이미 존재한다는것
	{
		
		return true;
	}
	return false;
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	//이미 키가 있으면 만들면 안됨
	if (AllInputKey_.end() != AllInputKey_.find(_Name))//end랑 fine가 같지않으면 중간에 이미 존재한다는것
	{
		MsgBoxAssert("이미 존재하는 키를 또 만들려고 함");
		return;
	}

	//소문자로 키입력 넣었을때의 안전장치
	if ('a' <= _Key && 'z' >= _Key)//아스키 코드로 a~z는 A~Z보다 작은 숫자다
	{
		_Key = std::toupper(_Key);//대문자로 바꿔준다
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
		//second가 값형이라 널일 수 없다

		//KeyUpdateStart가 보기 어렵다면
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update();

	}
}

bool GameEngineInput::IsDown(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))//end랑 fine가 같지않으면 중간에 이미 존재한다는것
	{
		MsgBoxAssert("이미 존재하는 키 입니다");
		return false;
	}

	return AllInputKey_[_Name].Down_;
}
bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 키 입니다");
		return false;
	}

	return AllInputKey_[_Name].Up_;
}

bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 키 입니다");

		return false;
	}

	return AllInputKey_[_Name].Press_;
}
bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 키 입니다");

		return false;
	}

	return AllInputKey_[_Name].Free_;
}