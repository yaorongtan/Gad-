
#include"MyTimer.h"
#include"Cannon.h"
#include"Plane.h"
#include<queue>
using namespace std;

int Width = 100;
int Height = 100;

bool isGameOver(PlaneManager& manager)
{

	if (manager.empty()) return false;

	return manager.GetCloseDistance() >= Height;

}

int main()
{
	MyTimer timer;
	queue<Plane*> planes;



	if (!timer.Start())
	{
		cout << "�������֧��Ӳ����ʱ��\n";

	}
	else
	{

		
		std::srand(time(nullptr));

		PlaneGenerator generator(2,Width,Height);
		PlaneManager manager(1);
		CannonManager cannonManager;
		BulletGenerator bulletGenerator(1);
		BoomGenerator boomGenerator(0.5f);

		
		//����ǰ��Ϸʱ��С��30��
		while (!isGameOver(manager)&&timer.TotalTime()<=30.0f)
		{
			timer.Tick();

			bulletGenerator.Update(timer.DeltaTime(), cannonManager);
			boomGenerator.Update(timer.DeltaTime(),cannonManager);
			generator.Update(timer.DeltaTime(),manager);

			manager.Update(timer.DeltaTime());
			cannonManager.Update(timer.DeltaTime(),manager);

		}
		
		if (timer.TotalTime() <= 30.0f)
		{
			cout << "�ɻ�ʤ��\n";
		}
		else
		{
			cout << "��̨ʤ��\n";
		}


	}

	getchar();
	return 0;
}



