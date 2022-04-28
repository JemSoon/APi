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

#include "GameEngine/GameEngineLevel.h"//내가추가
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
	{	//1스테이지의 배경 로드
		BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Actor->GetRenderer()->SetImage("Map1-1.bmp");

		{	//맵 이미지 첫화면에 맞게 맞추기
			float4 BackActor = {};
			BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
			BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);
			
			Actor->GetRenderer()->SetPivot(BackActor);

			//Actor->CreateCollision("Door",{100,100}, {800, 720});//문 콜리젼 임시생성

			Actor->CreateCollision("Wall", { 100,100 }, { 600, 720 });

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
			Monster* Gumba = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba->SetPosition({ 320.0f,740.0f });

			//카메라 인식 테스트용
			Monster* Gumba1 = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba1->SetPosition({ 4830.0f,810.0f });
		}

		{
			//아이템 로드 체크
			Mushroom* Item = CreateActor<Mushroom>((int)ORDER::ITEM);
			Item->SetPosition({ 500.0f, 740.0f });
		}

		{
			//아이템 로드 체크
			//FireFlower* Item = CreateActor<FireFlower>((int)ORDER::ITEM);
			//Item->SetPosition({ 628.0f, 740.0f });
		}

		{
			//박스 로드 체크
			Box* QBox = CreateActor<Box>((int)ORDER::BOX);
			QBox->SetPosition({ 120.0f,600.0f });

			//박스 로드 체크
			Box* QBox1 = CreateActor<Box>((int)ORDER::BOX);
			QBox1->SetPosition({ 184.0f,600.0f });
		}

	}
 }

void PlayLevel::Update()
{
	//{	//맵과 캐릭터의 충돌설정용
	//	//(참고)실제 BG랑 좌표가 안맞음 현재
	//	MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


	//	if (nullptr == MapColImage_)
	//	{
	//		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
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