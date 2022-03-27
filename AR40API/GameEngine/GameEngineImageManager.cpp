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

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	//���� ������ ���� �ʾҴ�=�̹� �ִ�
	if (AllRes.end() != AllRes.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� ");
		return nullptr;
	}

	//������ �����Ҵ����� �ϳ� ����
	GameEngineImage* NewImage = new GameEngineImage();

	NewImage->SetName(_Name);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "�̹����� �����ϴµ� ����").c_str());
		return nullptr;
	}

	//�̹����� ��������� ��Ƴ��� �����Ѵ�
	AllRes.insert(std::make_pair(_Name, NewImage));

	return NewImage;
}


GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, float4 _Scale)
{
	//���� ������ ���� �ʾҴ�=�̹� �ִ�
	if (AllRes.end()!=AllRes.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� ");
		return nullptr;
	}
	
	//������ �����Ҵ����� �ϳ� ����
	GameEngineImage* NewImage = new GameEngineImage();
	
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name+"�̹����� �����ϴµ� ����").c_str());
		return nullptr;
	}

	//�̹����� ��������� ��Ƴ��� �����Ѵ�
	AllRes.insert(std::make_pair(_Name, NewImage));
	
	return NewImage;
}