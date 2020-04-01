#pragma once
#include<iostream>
#include<vector>
#include"Plane.h"
#include<cstdlib>
#include<ctime>
static int ID;

#define N 999

//�ӵ�
class Cannon
{
public:
	Cannon(float _frequency = 0.0f):mFrequency(_frequency), mTimer(0) {}
	virtual bool Attack(float _dt, PlaneManager& manager) { return false; }

protected:
	inline bool Timer(float _dt)
	{
		mTimer += _dt;
		return mTimer > mFrequency;
	}

protected:
	float mFrequency;
	float mTimer;


};

class Bullet:public Cannon
{
public:
	Bullet(float _probility):Cannon(), mProbility(_probility)
	{
		mID = ++ID;
	}

	bool Attack(float _dt,PlaneManager& manager)
	{
		if (!Timer(_dt)) return false;

		float p = std::rand() % (N + 1) / (float)(N + 1);


		if (p > mProbility)
		{
			printf("�ӵ�%d�����ɹ�\n",mID);
			//���й���
			manager.BeAttack();
			return true;
		}

		printf("�ӵ�%d����ʧ��\n", mID);
		return true;
	}
protected:
	static int ID;
	int mID;
	float mProbility;
};

int Bullet::ID = 0;

class Boom:public Cannon
{
public:
	Boom(float _frequency) :Cannon(_frequency)
	{
		mID = ++ID;
	}

	virtual bool Attack(float _dt, PlaneManager& manager)
	{
		if (!Timer(_dt)) return false;
		printf("ը��%d�����ɹ�\n", mID);
		//���й���
		manager.AttackAll();
		return true;
		
	}


protected:
	int mID;
	static int ID;

};

int Boom::ID = 0;

class CannonManager
{
public:
	CannonManager()
	{
		
	}

	void Update(float dt, PlaneManager&planeManager)
	{
		
		for (int i = 0; i < mCannons.size(); i++)
		{
			if (mCannons[i]->Attack(dt, planeManager))
			{
				//������ڵ������Ƴ�
				auto p = mCannons[i];
				mCannons.erase(mCannons.begin()+i);
				delete p;
				i--;
			}
		}
		

	}
	void AddCannon(Cannon*_cannon)
	{
		mCannons.push_back(_cannon);
	}

	~CannonManager()
	{
		for (int i = 0; i < mCannons.size(); i++)
		{
			delete mCannons[i];
		}
	}

protected:

	std::vector<Cannon*> mCannons;
	

};


class CannonGenerator
{
public:
	CannonGenerator(float _frequency):mFrequency(_frequency) {
		timer = 0;
	}

	virtual void Update(float _dt,CannonManager& manager) {}
	
protected:
	inline bool Timer(float _dt)
	{
		timer += _dt;
		return timer > mFrequency;
	}

protected:
	float mFrequency;
	float timer;
};

class BulletGenerator :public CannonGenerator
{

public:
	BulletGenerator(float _frequency) :CannonGenerator(1/_frequency)
	{

	}
	void Update(float _dt, CannonManager& manager)
	{
		if (!Timer(_dt)) return;

		//��ʱ����������һ���ӵ�
		
		manager.AddCannon(new Bullet(0.5f));
		printf("������һ���ӵ�\n");
		timer = 0;
	}

};


class BoomGenerator :public CannonGenerator
{
public:
	BoomGenerator(float _frequency):CannonGenerator(1/_frequency)
	{

	}

	void Update(float _dt, CannonManager& manager)
	{
		if (!Timer(_dt)) return;

		//��ʱ����������һ��ը��

		manager.AddCannon(new Boom(1));
		printf("�����һ��ը��\n");
		timer = 0;
	}

};




