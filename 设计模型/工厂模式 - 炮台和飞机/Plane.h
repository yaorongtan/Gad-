#pragma once
#include<queue>
#include<ctime>
#include<cstdlib>

class PlaneManager;

class Plane
{
public:
	Plane(int _id, float _x, float _y) :mID(_id), next(nullptr), x(_x), y(_y) {

		
	}
	
	void UpdatePos(float _x, float _y)
	{
		x += _x;
		y += _y;
	}
public:
	Plane* next;
	int mID;
	float x, y;
};

class PlaneManager
{
public:
	PlaneManager(float time) :mUpdateTime(time), timer(0.0f), num(0)
	{
		head = tail = nullptr;
	}
	void Update(float dt)
	{
		timer += dt;

		if (timer < mUpdateTime)return;

		Plane* p = head;
		while (p != nullptr)
		{
			p->UpdatePos(0, 20);
			p = p->next;
		}
		timer = 0.0f;
	}
	void AddPlane(Plane* plane)
	{
		if (plane == nullptr) return;

		if (head == nullptr)
			head = tail = plane;
		else
		{
			tail->next = plane;
			tail = plane;
		}
		num++;
	}
	~PlaneManager()
	{
		while (head != nullptr)
		{
			auto p = head;
			head = head->next;
			delete p;
		}
		head = tail = nullptr;
		num = 0;
	}
	bool BeAttack()
	{
		if (empty()) return false;
		//�ɻ�������
		auto p = head;
		head = head->next;
		--num;
		if (head == nullptr) head = tail = nullptr;
		printf("		�ɻ�%d������\n", p->mID);
		delete p;
	}
	bool AttackAll()
	{
		//����ȫ���ķɻ�
		while (head != nullptr)
		{
			auto p = head;
			head = head->next;
			printf("		�ɻ�%d��ը������\n", p->mID);
			delete p;
		}
		head = tail = nullptr;
		num = 0;
		return true;
	}
	bool empty() { return num == 0; }
	float GetCloseDistance()
	{
		if (empty()) return 0.0f;
		return head->y;
	}
private:


protected:
	int num;
	float mUpdateTime;
	float timer;
	Plane *head;
	Plane *tail;

};

class PlaneGenerator
{
public:
	PlaneGenerator(float frequency,float _width,float _height) :mSwpanTime(1/frequency), timer(0.0f),mID(0),W(_width),H(_height) {}
	void Update(float dt, PlaneManager&manager)
	{
		timer += dt;

		if (timer >= mSwpanTime)
		{
			//����һ���ɻ�
			try
			{
				float x = std::rand() % (int)(W + 1);
				float y = 0;
				Plane* plane = new Plane(++mID, x, y);
				manager.AddPlane(plane);
				printf("		�����˷ɻ�\n");
				timer = 0.0f;
			}
			catch (const std::exception&)
			{
				throw "����ʧ��";

			}


		}

	}



protected:
	int mID;
	float mSwpanTime;
	float timer;
	float W, H;
};








