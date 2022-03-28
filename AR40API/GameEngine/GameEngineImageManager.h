#pragma once
#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

//�⺻������ ���ҽ��� �׳� �� ���� ������
//�����Ǵ� ���ҽ����� ���� �� �̸��� �ִٰ� ���� ����

//���� : �̹����� ���� ���ִ� ����
class GameEngineImageManager
{
private:
	static GameEngineImageManager* Inst_;//�̱���

public:
	static GameEngineImageManager* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}
		delete Inst_;
		Inst_ = nullptr;
	}

	
	GameEngineImage* Create(const std::string& _Name, float4 _Scale);//�̹����� ����� �ִ� �Լ�

	GameEngineImage* Create(const std::string& _Name, HDC _DC);//�̹����� ����� �ִ� �Լ�


private://�̱���(�ϳ��� �����)
	//����Ʈ ������
	GameEngineImageManager();
	//����Ʈ �Ҹ���
	~GameEngineImageManager();

	
	
	
	//======�Ʒ��͵��� ���������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;


protected:

private:
	std::map<std::string, GameEngineImage*> AllRes;
};
