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
#include <GameEngineBase/GameEngineTime.h>

#include "GameEngine/GameEngineLevel.h"//내가추가
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Mushroom.h"
#include "Box.h"
#include "NoneBox.h"
#include "CoinBox.h"
#include "Block.h"
#include "FireFlower.h"
#include "Coin.h"

bool PlayLevel::first = true;

PlayLevel::PlayLevel():
	Time(1.0f)
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Loading()
{	

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

	//Time -= GameEngineTime::GetDeltaTime();
	//if (0 >= Time)
	//{	//5초뒤 브금 끔
	//	BgmPlayer.Stop();
	//}

	if (Player::MainPlayer == nullptr&&
		BigPlayer::MainBigPlayer == nullptr&&
		WhitePlayer::MainWhitePlayer==nullptr)
	{
		BgmPlayer.Stop();
	}
	ClearSongCheck();
}	

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BgmPlayer.Stop();

	if ((_NextLevel->GetNameCopy() != "Title"|| _NextLevel->GetNameCopy() != "Intro")&&Player::ChangeLevel_==true)
	{	//타이틀과 인트로(목숨정보)화면으로 넘어갈땐 플레이어가 안넘어간다
		Player::MainPlayer->NextLevelOn();
		BigPlayer::MainBigPlayer->NextLevelOn();
		WhitePlayer::MainWhitePlayer->NextLevelOn();
		UI::MainUI->NextLevelOn();
	}
		Player::ChangeLevel_ = false;//다시꺼줘야 함
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

		BgmPlayer = GameEngineSound::SoundPlayControl("01 - Ground Stage.wav");
		BgmPlayer.Volume(0.1f);
		Time = 5.0f;
	if (first == true)
	{
		{	//1스테이지의 배경 로드
			BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
			Actor->GetRenderer()->SetImage("Map1-1.bmp");

			{	//맵 이미지 첫화면에 맞게 맞추기
				float4 BackActor = {};
				BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
				BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

				Actor->GetRenderer()->SetPivot(BackActor);

				Actor->CreateCollision("Door",{64,1128}, {13120.0f, 720});//문 콜리젼 임시생성

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
				}

				if (nullptr == BigPlayer::MainBigPlayer)
				{
					//큰마리오
					BigPlayer::MainBigPlayer = CreateActor<BigPlayer>((int)ORDER::PLAYER);
				}

				if (nullptr == WhitePlayer::MainWhitePlayer)
				{
					//흰마리오
					WhitePlayer::MainWhitePlayer = CreateActor<WhitePlayer>((int)ORDER::PLAYER);

					//스테이지의 UI 로드
					CreateActor<UI>((int)ORDER::UI);
				}

				//이전레벨이 파이프1이라면 
				//if (MainPlayer->GetLevel()->GetNameCopy() == "Pipe1")
				//{	//파이프레벨에서 넘어왔으면
				//	Player::MainPlayer->SetPosition({ 14070.0f, 576.0f }); //320.0f,740.0f
				//	BigPlayer::MainBigPlayer->SetPosition({ 14070.0f, 576.0f });
				//	WhitePlayer::MainWhitePlayer->SetPosition({ 14070.0f, 576.0f });
				//}


				Player::MainPlayer->SetPosition({ 320.0f, 740.0f }); //320.0f,740.0f
				BigPlayer::MainBigPlayer->SetPosition({ 320.0f, 740.0f });
				WhitePlayer::MainWhitePlayer->SetPosition({ 320.0f, 740.0f });

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

			Monster* Gumba16 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba16->SetPosition({ 2200.0f,771.0f });
		}

		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 1058.0f,608.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 1314.0f,608.0f });
		}
		{
			Box* a = CreateActor<Box>((int)ORDER::BOX);
			a->SetPosition({ 1378.0f,608.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 1442.0f,608.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 1506.0f,608.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 1570.0f,608.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 1442.0f,358.0f });
		}
		{
			NoneBox* a = CreateActor<NoneBox>((int)ORDER::BOX);
			a->SetPosition({ 4130.0f,544.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 4962.0f,608.0f });
		}
		{
			Box* a = CreateActor<Box>((int)ORDER::BOX);
			a->SetPosition({ 5026.0f,608.0f });
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5154.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5218.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5282.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5346.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5410.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5474.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5538.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5602.0f,358.0f });
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5836.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5900.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 5964.0f,358.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 6028.0f,358.0f });
		}

		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 6028.0f,608.0f });
			//이거 10번 쳐야되는데..
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 6434.0f,608.0f });
			//이거 옆에 별나오는 블록(아직 안만듦
		}

		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 6818.0f,608.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 7010.0f,608.0f });
		}
		{
			Box* a = CreateActor<Box>((int)ORDER::BOX);
			a->SetPosition({ 7010.0f,358.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 7202.0f,608.0f });
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 7586.0f,608.0f });
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 7777.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 7841.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 7905.0f,358.0f });
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 8226.0f,358.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 8290.0f,358.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 8354.0f,358.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 8418.0f,358.0f });
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 8290.0f,608.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 8354.0f,608.0f });
		}

		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 10786.0f,608.0f });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 10850.0f,608.0f });
		}
		{
			CoinBox* a = CreateActor<CoinBox>((int)ORDER::BOX);
			a->SetPosition({ 10914.0f,608.0 });
		}
		{
			Block* a = CreateActor<Block>((int)ORDER::BOX);
			a->SetPosition({ 10978.0f,608.0f });
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

		{
			//코인 테스트
			Coin* Coin1 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin1->SetPosition({ 582.0f,500.0f });

			Coin* Coin2 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin2->SetPosition({ 646.0f,500.0f });

			Coin* Coin3 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin3->SetPosition({ 710.0f,500.0f });
		}

		{
			//코인 테스트
			Coin* Coin1 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin1->SetPosition({ 774.0f,500.0f });

			Coin* Coin2 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin2->SetPosition({ 838.0f,500.0f });

			Coin* Coin3 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin3->SetPosition({ 902.0f,500.0f });
		}

		{
			//코인 테스트
			Coin* Coin1 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin1->SetPosition({ 966.0f,436.0f });

			Coin* Coin2 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin2->SetPosition({ 464.0f,372.0f });

			Coin* Coin3 = CreateActor<Coin>((int)ORDER::ITEM);
			Coin3->SetPosition({ 518.0f,308.0f });
		}
	}
	
	else if (first == false)
	{
		Player::MainPlayer->SetPosition({ 10475.0f, 630.0f }); //320.0f,740.0f
		BigPlayer::MainBigPlayer->SetPosition({ 10475.0f, 630.0f });
		WhitePlayer::MainWhitePlayer->SetPosition({ 10475.0f, 630.0f });
	}
	first = false;
}

void PlayLevel::ClearSongCheck()
{
	if (Player::ClearSongOn_ == true)
	{
		BgmPlayer.Stop();
		Time = Time-GameEngineTime::GetDeltaTime();

		
		GameEngineSound::SoundPlayOneShot("smb_stage_clear.wav", 0, 0.03f);
		
		
	}
}

