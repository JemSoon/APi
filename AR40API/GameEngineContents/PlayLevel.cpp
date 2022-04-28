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
			Monster* Gumba = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba->SetPosition({ 320.0f,740.0f });

			//ī�޶� �ν� �׽�Ʈ��
			Monster* Gumba1 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba1->SetPosition({ 4830.0f,810.0f });
		}

		{
			//������ �ε� üũ
			Mushroom* Item = CreateActor<Mushroom>((int)ORDER::ITEM);
			Item->SetPosition({ 500.0f, 740.0f });
		}

		{
			//������ �ε� üũ
			//FireFlower* Item = CreateActor<FireFlower>((int)ORDER::ITEM);
			//Item->SetPosition({ 628.0f, 740.0f });
		}

		{
			//�ڽ� �ε� üũ
			Box* QBox = CreateActor<Box>((int)ORDER::BOX);
			QBox->SetPosition({ 120.0f,600.0f });

			//�ڽ� �ε� üũ
			Box* QBox1 = CreateActor<Box>((int)ORDER::BOX);
			QBox1->SetPosition({ 184.0f,600.0f });
		}

	}
 }

void PlayLevel::Update()
{
	//{	//�ʰ� ĳ������ �浹������
	//	//(����)���� BG�� ��ǥ�� �ȸ��� ����
	//	MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


	//	if (nullptr == MapColImage_)
	//	{
	//		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
	//	}
	//}


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