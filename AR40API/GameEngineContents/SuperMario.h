#pragma once
#include <GameEngine/GameEngine.h>

//���� : Study Game
class SuperMario : public GameEngine
{
public:
	//����Ʈ ������
	SuperMario();
	//����Ʈ �Ҹ���
	~SuperMario();

	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	SuperMario(const SuperMario& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	SuperMario(SuperMario&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	SuperMario& operator=(const SuperMario& _Other) = delete;
	SuperMario& operator=(SuperMario&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

