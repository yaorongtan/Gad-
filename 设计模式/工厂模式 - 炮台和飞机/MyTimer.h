#pragma once

#include<Windows.h>


class MyTimer
{
public:
	bool Start();
	float DeltaTime();
	float TotalTime();
	void Tick();

protected:
	__int64 mStartTimeCount;
	__int64 mCurrentTimeCount;
	__int64 mPrevTimeCount;
	double mSecondPerCount;
	double mDeltaTime;

};


