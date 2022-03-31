#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>

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

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)//�̹��� ã�� �Լ�
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);//�̸� �빮�ڷ�

	std::map<std::string, GameEngineImage*>::iterator FindIter = AllRes.find(EngineName);

	if (AllRes.end() == FindIter)
	{
		//��ã�Ҵ�
		return nullptr;
	}

	//ã�Ҵ�
	return FindIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);//�̸� �빮�ڷ�

	//���� ������ ���� �ʾҴ�=�̹� �ִ�
	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� ");
		return nullptr;
	}

	//������ �����Ҵ����� �ϳ� ����
	GameEngineImage* NewImage = new GameEngineImage();

	NewImage->SetName(EngineName);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		MsgBoxAssert((EngineName + "�̹����� �����ϴµ� ����").c_str());
		return nullptr;
	}

	//�̹����� ��������� ��Ƴ��� �����Ѵ�
	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}


GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4& _Scale)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);//�̸� �빮�ڷ�

	//���� ������ ���� �ʾҴ�=�̹� �ִ�
	if (AllRes.end()!=AllRes.find(EngineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� ");
		return nullptr;
	}
	
	//������ �����Ҵ����� �ϳ� ����
	GameEngineImage* NewImage = new GameEngineImage();
	
	NewImage->SetName(EngineName);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((EngineName +"�̹����� �����ϴµ� ����").c_str());
		return nullptr;
	}

	//�̹����� ��������� ��Ƴ��� �����Ѵ�
	AllRes.insert(std::make_pair(EngineName, NewImage));
	
	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	//���ϸ��� �� Ű
	return Load(_Path, NewPath.GetFileName());
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path, const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);//�̸� �빮�ڷ�

	//���� ������ ���� �ʾҴ�=�̹� �ִ�
	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �̹����� �� ������� ");
		return nullptr;
	}

	//������ �����Ҵ����� �ϳ� ����
	GameEngineImage* NewImage = new GameEngineImage();

	NewImage->SetName(EngineName);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((_Name + "�̹����� �����ϴµ� ����").c_str());
		return nullptr;
	}

	//�̹����� ��������� ��Ƴ��� �����Ѵ�
	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}