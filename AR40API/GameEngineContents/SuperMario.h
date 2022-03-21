#pragma once
#include <GameEngine/GameEngine.h>

//설명 : Study Game
class SuperMario : public GameEngine
{
public:
	//디폴트 생성자
	SuperMario();
	//디폴트 소멸자
	~SuperMario();

	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	SuperMario(const SuperMario& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	SuperMario(SuperMario&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	SuperMario& operator=(const SuperMario& _Other) = delete;
	SuperMario& operator=(SuperMario&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

