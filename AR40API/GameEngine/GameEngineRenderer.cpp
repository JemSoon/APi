#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("idle-R.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 랜더러에 세팅함");
		return;
	}

	Image_ = FindImage;
}

void GameEngineRenderer::Render()
{
	GameEngine::BackBufferImage()->BitCopyBot(Image_, GetPosition());
}