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
		//				�� ���� ���� ���ڵ��� �� �빮�ڷ� �ٲ��
		std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;
		//				�� ���� ���� ���ڵ��� �� �빮�ڷ� �ٲ��
		std::transform(NewText.begin(), NewText.end(), NewText.begin(), std::toupper);
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

