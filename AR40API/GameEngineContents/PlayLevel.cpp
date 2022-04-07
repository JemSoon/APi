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
	{	//배경 로드
		BackGround* Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Back->GetRenderer()->SetImage("Map1-1All.bmp");

		{	//맵 이미지 첫화면에 맞게 맞추기
			float4 BackActor = {};
			BackActor.x = (Back->GetRenderer()->GetImage()->GetScale().Half().x) - (GameEngineWindow::GetScale().Half().x);
			BackActor.y = (Back->GetRenderer()->GetImage()->GetScale().Half().y) - (GameEngineWindow::GetScale().Half().y) - 240;

			Back->GetRenderer()->SetPivot(BackActor);
		}
	}

	{	//플레이어 로드
		CreateActor<Player>((int)ORDER::PLAYER);
	}

	{	//UI로드
		CreateActor<UI>((int)ORDER::UI);
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