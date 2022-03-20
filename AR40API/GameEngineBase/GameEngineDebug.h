#pragma once
#include <crtdbg.h>
#include <string>
#include <assert.h>
#include <Windows.h>
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ������Ҷ� ������ �������� �˷��ִ� ���
class GameEngineDebug
{
public:
	//�ƿ� ��ü�� �ȸ���� �����Լ���=static��� �Լ��θ�
	static void LeakCheckOn();

	//static void MsgBoxAssert(const std::string& _Text);
	//const &�� ���� ����?
	//�ѱ�� ���ڸ� �Ƴ��� �Լ��� �ѱ�� ������ ����� �Ƴ���
	//�������� �ʰڴ�(const)�� ���

protected:

private:
	//����Ʈ ������
	GameEngineDebug();
	//����Ʈ �Ҹ���
	~GameEngineDebug();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;
};

#define MsgBoxAssert(Text)	MessageBeep(0);\
MessageBoxA(nullptr, Text, "Error", MB_OK);\
assert(false);