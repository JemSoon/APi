#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineImageManager* GameEngineImageManager::Inst_= new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager()
{

}

GameEngineImageManager::~GameEngineImageManager()
{
	std::map<std::string, GameEngineImage*>::iterator StartIter= AllRes.begin();
	std::map<std::string, GameEngineImage*>::iterator EndIter = AllRes.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

}

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)//이미지 찾는 함수
{
	std::map<std::string, GameEngineImage*>::iterator FindIter = AllRes.find(_Name);

	if (AllRes.end() == FindIter)
	{
		//못찾았다
		return nullptr;
	}

	//찾았다
	return FindIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	//맵이 끝까지 돌지 않았다=이미 있다
	if (AllRes.end() != AllRes.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려함 ");
		return nullptr;
	}

	//없으면 동적할당으로 하나 생성
	GameEngineImage* NewImage = new GameEngineImage();

	NewImage->SetName(_Name);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패").c_str());
		return nullptr;
	}

	//이미지를 만들었으면 모아놓고 관리한다
	AllRes.insert(std::make_pair(_Name, NewImage));

	return NewImage;
}


GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4& _Scale)
{
	//맵이 끝까지 돌지 않았다=이미 있다
	if (AllRes.end()!=AllRes.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려함 ");
		return nullptr;
	}
	
	//없으면 동적할당으로 하나 생성
	GameEngineImage* NewImage = new GameEngineImage();
	
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name+"이미지를 생성하는데 실패").c_str());
		return nullptr;
	}

	//이미지를 만들었으면 모아놓고 관리한다
	AllRes.insert(std::make_pair(_Name, NewImage));
	
	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path)
{
	//무시(일단 나중에 만듦)
	//Create();

	return nullptr;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path, const std::string& _Name)
{
	//맵이 끝까지 돌지 않았다=이미 있다
	if (AllRes.end() != AllRes.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려함 ");
		return nullptr;
	}

	//없으면 동적할당으로 하나 생성
	GameEngineImage* NewImage = new GameEngineImage();

	NewImage->SetName(_Name);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "이미지를 생성하는데 실패").c_str());
		return nullptr;
	}

	//이미지를 만들었으면 모아놓고 관리한다
	AllRes.insert(std::make_pair(_Name, NewImage));

	return NewImage;
}