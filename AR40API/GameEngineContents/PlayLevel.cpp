#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "BigPlayer.h"
#include "WhitePlayer.h"
#include "Monster.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>

#include "GameEngine/GameEngineLevel.h"//�����߰�
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Mushroom.h"
#include "Box.h"
#include "Block.h"
#include "FireFlower.h"

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
		Actor->GetRenderer()->SetImage("Map1-1.bmp");

		{	//�� �̹��� ùȭ�鿡 �°� ���߱�
			float4 BackActor = {};
			BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
			BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);
			
			Actor->GetRenderer()->SetPivot(BackActor);

			//Actor->CreateCollision("Door",{100,100}, {800, 720});//�� �ݸ��� �ӽû���

			Actor->CreateCollision("Wall", { 100,100 }, { 600, 720 });

		}

		{
			if (nullptr == Player::MainPlayer)
			{
			//���������� �÷��̾� �ε�
			Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Player::MainPlayer -> SetPosition({ 320.0f, 740.0f }); //320.0f,740.0f

			//ū������
			BigPlayer::MainBigPlayer = CreateActor<BigPlayer>((int)ORDER::PLAYER);
			BigPlayer::MainBigPlayer->SetPosition({ 320.0f, 740.0f });

			//�򸶸���
			WhitePlayer::MainWhitePlayer = CreateActor<WhitePlayer>((int)ORDER::PLAYER);
			WhitePlayer::MainWhitePlayer->SetPosition({ 320.0f, 740.0f });

			//���������� UI �ε�
			CreateActor<UI>((int)ORDER::UI);
			}
		}

		{
			//1���������� ���� �ε�
			Monster* Gumba1 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba1->SetPosition({ 1408.0f,771.0f });
			
			Monster* Gumba2 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba2->SetPosition({ 2585.0f,771.0f });

			Monster* Gumba3 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba3->SetPosition({ 3264.0f,771.0f });

			Monster* Gumba4 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba4->SetPosition({ 3360.0f,771.0f });

			Monster* Gumba5 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba5->SetPosition({ 5120.0f,258.0f });

			Monster* Gumba6 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba6->SetPosition({ 5248.0f,258.0f });

			Monster* Gumba7 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba7->SetPosition({ 6206.0f,771.0f });

			Monster* Gumba8 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba8->SetPosition({ 6304.0f,771.0f });

			Monster* Gumba9 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba9->SetPosition({ 7296.0f,771.0f });

			Monster* Gumba10 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba10->SetPosition({ 7392.0f,771.0f });

			Monster* Gumba11 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba11->SetPosition({ 7935.0f,771.0f });

			Monster* Gumba12 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba12->SetPosition({ 8030.0f,771.0f });

			Monster* Gumba13 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba13->SetPosition({ 8192.0f,771.0f });

			Monster* Gumba14 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba14->SetPosition({ 8290.0f,771.0f });

			Monster* Gumba15 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba15->SetPosition({ 11136.0f,771.0f });

			Monster* Gumba16 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba16->SetPosition({ 11232.0f,771.0f });


		}

		{
			//�ڽ� �ε� üũ
			Box* QBox = CreateActor<Box>((int)ORDER::BOX);
			QBox->SetPosition({ 120.0f,600.0f });

			//�ڽ� �ε� üũ
			Box* QBox1 = CreateActor<Box>((int)ORDER::BOX);
			QBox1->SetPosition({ 184.0f,600.0f });

			//��� �ε� üũ
			Block* Block1 = CreateActor<Block>((int)ORDER::BOX);
			Block1->SetPosition({ 248.0f,600.0f });

			Block* Block2 = CreateActor<Block>((int)ORDER::BOX);
			Block2->SetPosition({ 312.0f,600.0f });
		}

	}
 }

void PlayLevel::Update()
{

	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GetInst().ChangeLevel("Intro");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Pipe1"))
	{
		GameEngine::GetInst().ChangeLevel("Pipe1");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}

	//if (true == Player::MainPlayer->IsDeath())
	//{
	//	//����
	//	Reset();
	//}
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "Title"|| _NextLevel->GetNameCopy() != "Intro")
	{	//Ÿ��Ʋ�� ��Ʈ��(�������)ȭ������ �Ѿ�� �÷��̾ �ȳѾ��
		Player::MainPlayer->NextLevelOn();
		BigPlayer::MainBigPlayer->NextLevelOn();
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// Player->SetPosition();

	// BgmPlayer = GameEngineSound::SoundPlayControl("BGM.MP3");

	/*GameEngineSound::SoundPlayOneShot("vo_shk.mp3");
	Time = 5.0f;*/

}