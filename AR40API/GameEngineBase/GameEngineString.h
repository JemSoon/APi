#pragma once
#include <string>
#include <algorithm>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : String�� �����ִ� Ŭ���� ������ String�� ���õ� ���ڿ� ó���Լ��� ��
class GameEngineString
{
public:
	static void ToUpper(std::string& _Text)
	{
		for (size_t i = 0; i < _Text.size(); i++)
		{
			_Text[i] = std::toupper(_Text[i]);
		}

		//				�� ���� ���� ���ڵ��� �� �빮�ڷ� �ٲ��
		//std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;
		for (size_t i = 0; i < _Text.size(); i++)
		{
			NewText[i] = std::toupper(NewText[i]);
		}
		return NewText;
	}

protected:

private:
	//����Ʈ ������
	GameEngineString();
	//����Ʈ �Ҹ���
	~GameEngineString();




	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	GameEngineString(const GameEngineString& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

};

