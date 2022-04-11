#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Loading()
{	
	{	//1���������� ��� �ε�
		BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Actor->GetRenderer()->SetImage("Map1-1All.bmp");

		{	//�� �̹��� ùȭ�鿡 �°� ���߱�
			float4 BackActor = {};
			BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x) - (GameEngineWindow::GetScale().Half().x);
			BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y) - (GameEngineWindow::GetScale().Half().y) /*- 240*/;
			
			Actor->GetRenderer()->SetPivot(BackActor);

			Actor->CreateCollision("Door",{100,100}, {100, 100});//�� �ݸ��� �ӽû���
		}

		{
			//1���������� �÷��̾� �ε�
			Player* Mario = CreateActor<Player>((int)ORDER::PLAYER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Mario->SetPosition({ 320.0f,740.0f });
		}

		{	
			//1���������� UI �ε�
			CreateActor<UI>((int)ORDER::UI);
		}
	}

 }

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Intro");
	}

}

void PlayLevel::LevelChangeStart()
{
	//CreateActor<Player>((int)ORDER::PLAYER);
	//CreateActor<UI>((int)ORDER::UI);

}