#pragma once
#include "GameEngine/GameEngineLevel.h"
#include <GameEngineBase/GameEngineSound.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Player;
class GameEngineImage;
class PlayLevel : public GameEngineLevel 
{
public:
	//����Ʈ ������
	PlayLevel();
	//����Ʈ �Ҹ���
	~PlayLevel();

	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	PlayLevel(const PlayLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;


	float Time;

	static bool first;

	Player* MainPlayer;
	GameEngineSoundPlayer BgmPlayer;


protected:
	void Loading() override;
	void Update() override;
	
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;

private:
	void ClearSongCheck();
	bool OneCheck;
};

