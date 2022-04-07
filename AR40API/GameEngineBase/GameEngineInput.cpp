#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"
//#include "GameEngineTime.h"


/*===========================================*/
void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{	//KeyCheck가 true면 눌렸다

		if (true == Free_)
		{	//그직전에 Free가 true였다면 방금 처음 눌렀다는것
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ = 0.0f;
			Time_ += _DeltaTime;

		}
		else if (true == Press_)
		{	//이미 눌렀고 계속 누르고 있는 상태
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ += _DeltaTime;
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
			Time_ = 0.0f;
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

	if (AllInputKey_.end() != AllInputKey_.find(_Name))//end랑 fine가 같지않으면 중간에 이미 존재한다는것
	{
		return true;
	}
	return false;
}

void GameEngineInput::CreateKey(const std::string& _Name, int _Key)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	//이미 키가 있으면 만들면 안됨
	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))//end랑 fine가 같지않으면 중간에 이미 존재한다는것
	{
		MsgBoxAssert("이미 존재하는 키를 또 만들려고 함");
		return;
	}

	//소문자로 키입력 넣었을때의 안전장치
	if ('a' <= _Key && 'z' >= _Key)//아스키 코드로 a~z는 A~Z보다 작은 숫자다
	{
		_Key = std::toupper(_Key);//대문자로 바꿔준다
	}
	AllInputKey_.insert(std::make_pair(UpperKey, GameEngineKey()));
	AllInputKey_[UpperKey].Key_ = _Key;
	AllInputKey_[UpperKey].Reset();
}

void GameEngineInput::Update(float _DeltaTime)
{
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		//second가 값형이라 널일 수 없다

		//KeyUpdateStart가 보기 어렵다면
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update(_DeltaTime);

	}
}

float GameEngineInput::GetTime(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))//end랑 fine가 같지않으면 중간에 이미 존재한다는것
	{
		MsgBoxAssert("이미 존재하는 키 입니다");
		return false;
	}

	return AllInputKey_[UpperKey].Time_;
}

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))//end랑 fine가 같지않으면 중간에 이미 존재한다는것
	{
		MsgBoxAssert("이미 존재하는 키 입니다");
		return false;
	}

	return AllInputKey_[UpperKey].Down_;
}
bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("이미 존재하는 키 입니다");
		return false;
	}

	return AllInputKey_[UpperKey].Up_;
}

bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("이미 존재하는 키 입니다");

		return false;
	}

	return AllInputKey_[UpperKey].Press_;
}
bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("이미 존재하는 키 입니다");

		return false;
	}

	return AllInputKey_[UpperKey].Free_;
}