#include "BonusLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "Monster.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>

BonusLevel::BonusLevel()
{

}

BonusLevel::~BonusLevel()
{

}

void BonusLevel::Loading()
{
	BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Actor->GetRenderer()->SetImage("Pipe1-1.bmp");

	{	//�� �̹��� ùȭ�鿡 �°� ���߱�
		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x) - (GameEngineWindow::GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y) - (GameEngineWindow::GetScale().Half().y) /*- 240*/;

		Actor->GetRenderer()->SetPivot(BackActor);
	}
	{
		//���������� �÷��̾� �ε�
		Player* Mario = CreateActor<Player>((int)ORDER::PLAYER);
		//Player->SetPosition(GameEngineWindow::GetScale().Half());
		Mario->SetPosition({ 300.0f,300.0f });
	}
	{
		//���������� UI �ε�
		CreateActor<UI>((int)ORDER::UI);
	}
}

void BonusLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GetInst().ChangeLevel("Intro");
	}
}

void BonusLevel::LevelChangeStart()
{
}
