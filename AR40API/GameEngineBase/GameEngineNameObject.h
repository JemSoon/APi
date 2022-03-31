#pragma once
#include <string>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : � �ְ� �̸��� ������ ���� ���
class GameEngineNameObject
{
public:
	//����Ʈ ������
	GameEngineNameObject();
	//����Ʈ �Ҹ���
	virtual ~GameEngineNameObject();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	//�׳� std::string���� �ϸ� ���� ���簡 �Ǹ鼭 ������ ������
	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}

	std::string GetNameCopy()
	{
		return Name_;
	}

	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}

protected:
private:
	std::string Name_;
};

