#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "BigPlayer.h"
#include "WhitePlayer.h"
#include "Monster.h"
#include "Turtle.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>

#include "GameEngine/GameEngineLevel.h"//내가추가
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Mushroom.h"
#include "Box.h"
#include "Block.h"
#include "FireFlower.h"
#include "Coin.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Loading()
{	
	{	//1스테이지의 배경 로드
		BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Actor->GetRenderer()->SetImage("Map1-1.bmp");

		{	//맵 이미지 첫화면에 맞게 맞추기
			float4 BackActor = {};
			BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
			BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);
			
			Actor->GetRenderer()->SetPivot(BackActor);

			//Actor->CreateCollision("Door",{100,100}, {800, 720});//문 콜리젼 임시생성

			Actor->CreateCollision("Wall", { 200,100 }, { 3712,576 });//파이프관
			Actor->CreateCollision("Die", { 128,5 }, { 4480,957 });//절벽
			Actor->CreateCollision("Die", { 192,5 }, { 5600,957 });//절벽
			Actor->CreateCollision("Die", { 128,5 }, { 9858,957 });//절벽
			Actor->CreateCollision("Flag", { 8,607 }, { 12704,460 });//깃발

		}

		{
			if (nullptr == Player::MainPlayer)
			{
			//스테이지의 플레이어 로드
			Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Player::MainPlayer -> SetPosition({ 320.0f, 740.0f }); //320.0f,740.0f

			//큰마리오
			BigPlayer::MainBigPlayer = CreateActor<BigPlayer>((int)ORDER::PLAYER);
			BigPlayer::MainBigPlayer->SetPosition({ 320.0f, 740.0f });

			//흰마리오
			WhitePlayer::MainWhitePlayer = CreateActor<WhitePlayer>((int)ORDER::PLAYER);
			WhitePlayer::MainWhitePlayer->SetPosition({ 320.0f, 740.0f });

			//스테이지의 UI 로드
			CreateActor<UI>((int)ORDER::UI);
			}
		}

		{
			//1스테이지의 몬스터 로드
			Monster* Gumba1 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba1->SetPosition({ 1408.0f,771.0f });
			
			Monster* Gumba2 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba2->SetPosition({ 2785.0f,771.0f });

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
			//거북이 테스트
			Turtle* Turtle1 = CreateActor<Turtle>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Turtle1->SetPosition({ 2100.0f,771.0f });
		}
		
		{	
			//박스 로드 체크
			Box* QBox = CreateActor<Box>((int)ORDER::BOX);
			QBox->SetPosition({ 120.0f,600.0f });

			//박스 로드 체크
			Box* QBox1 = CreateActor<Box>((int)ORDER::BOX);
			QBox1->SetPosition({ 184.0f,600.0f });

			Box* QBox2 = CreateActor<Box>((int)ORDER::BOX);
			QBox2->SetPosition({ 376.0f,600.0f });

			//박스 로드 체크
			Box* QBox3 = CreateActor<Box>((int)ORDER::BOX);
			QBox3->SetPosition({ 440.0f,600.0f });

			//블록 로드 체크
			Block* Block1 = CreateActor<Block>((int)ORDER::BOX);
			Block1->SetPosition({ 248.0f,600.0f });

			Block* Block2 = CreateActor<Block>((int)ORDER::BOX);
			Block2->SetPosition({ 312.0f,600.0f });
		}

		{
			//코인 테스트
			Coin* Coin1 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin1->SetPosition({ 400.0f,500.0f });
		
			Coin* Coin2 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin2->SetPosition({ 464.0f,500.0f });
	
			Coin* Coin3 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin3->SetPosition({ 518.0f,500.0f });
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

	//if (true == Player::MainPlayer->IsDeath())//조건문에서 터진다
	//{
	//	//리셋
	//	Reset();
	//	GameEngine::GetInst().ChangeLevel("Intro");
	//	int a = 0;
	//}
}	//잘못된 조건문 Death되서 null이 됬는데 쓰려고하면 당연 터진다

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "Title"|| _NextLevel->GetNameCopy() != "Intro")
	{	//타이틀과 인트로(목숨정보)화면으로 넘어갈땐 플레이어가 안넘어간다
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