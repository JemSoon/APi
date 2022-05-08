#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �ΰ��� ȭ�鿡 ��µ� UI
class GameEngineRenderer;
class UI : public GameEngineActor
{
public:
	static UI* MainUI;

	//����Ʈ ������
	UI();
	//����Ʈ �Ҹ���
	~UI();

	int GetCoinCount()
	{
		return CoinCount_;
	}
	
	static int CoinCount_;
	int TimeCount_;
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	UI(const UI& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	UI(UI&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;


protected:

	void Start() override;
	void Update() override;
	//void Render() override;
private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	GameEngineRenderer* One;
	GameEngineRenderer* Ten;

	GameEngineRenderer* TOne;
	GameEngineRenderer* TTen;
	GameEngineRenderer* TH;
};

