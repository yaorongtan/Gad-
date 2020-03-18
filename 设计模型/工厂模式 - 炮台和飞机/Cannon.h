#pragma once
#include<iostream>
#include<vector>
#include"Plane.h"
#include<cstdlib>
#include<ctime>
static int ID;

#define N 999

//子弹
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
			printf("子弹%d攻击成功\n",mID);
			//进行攻击
			manager.BeAttack();
			return true;
		}

		printf("子弹%d攻击失败\n", mID);
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
		printf("炸弹%d攻击成功\n", mID);
		//进行攻击
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
				//将这个炮弹进行移除
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

		//计时器到达生成一个子弹
		
		manager.AddCannon(new Bullet(0.5f));
		printf("生成了一个子弹\n");
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

		//计时器到达生成一个炸弹

		manager.AddCannon(new Boom(1));
		printf("添加了一个炸弹\n");
		timer = 0;
	}

};




