//Main.cpp

#include<graphics.h>
#include<Windows.h>
#include"class.h"
//using namespace std;


enum GameState
{
	Running,
	GameOver,
};


bool isGameRunning = true;
//ȫ�ַ�Χ���4������
Snake snake;
Wall wall;
Apple apple;
UI ui;

int state = Running;		// ��Ϸ����״̬

bool IsKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}

void Draw()
{
	BeginBatchDraw(); //��ʼ������ͼ����ֹ��˸
	cleardevice();//�ñ���ɫ�����Ļ

	snake.Draw();
	wall.Draw();
	apple.Draw();
	ui.Draw();
	EndBatchDraw();
}

void keyboardControl()
{
	if (IsKeyDown(VK_ESCAPE))
	{
		isGameRunning = false;
		return;
	}
	if (IsKeyDown(VK_LEFT))
	{
		snake.ChangeDirection(Direction::Left);
	}

	if (IsKeyDown(VK_RIGHT))
	{
		snake.ChangeDirection(Direction::Right);
	}

	if (IsKeyDown(VK_UP))
	{
		snake.ChangeDirection(Direction::Up);
	}

	if (IsKeyDown(VK_DOWN))
	{
		snake.ChangeDirection(Direction::Down);
	}

	if (IsKeyDown(VK_RETURN) && state == GameState::GameOver)
	{
		state = GameState::Running;
		snake.Reset();
	}
}

void HandleLogic()
{
	if (state == GameState::Running)
	{
		if (snake.Move())
		{
			if (snake.isDie())
			{
				state = GameState::GameOver;
			}

			snake.TryEat(apple);
		}
	}
}

int main()
{
	initgraph(640, 480);
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	cleardevice();

	while (isGameRunning)
	{
		keyboardControl();
		HandleLogic();
		Draw();
		Sleep(30);
	}

	closegraph();
	system("pause");
	return 0;
}
