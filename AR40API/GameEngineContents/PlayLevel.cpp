#include "PlayLevel.h"
#include "Player.h"
#include "UI.h"

enum class ORDER //이미지 올라갈 순서 설정
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	UI
};

PlayLevel::PlayLevel()
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

}

void PlayLevel::LevelChangeStart()
{
	CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<UI>((int)ORDER::UI);

}