
#include"MyTimer.h"

bool MyTimer::Start()
{
	__int64 frequency;;
	
	if (!QueryPerformanceFrequency((LARGE_INTEGER*)&frequency))
	{
		return false;
	}

	mSecondPerCount = 1.0 / frequency;

	QueryPerformanceCounter((LARGE_INTEGER*)&mStartTimeCount);

	mPrevTimeCount = mCurrentTimeCount = mStartTimeCount;
	mDeltaTime = 0.0;

	return true;
}

float MyTimer::DeltaTime()
{
	return mDeltaTime;
}

float MyTimer::TotalTime()
{
	return (mCurrentTimeCount - mStartTimeCount)*mSecondPerCount;
}

void MyTimer::Tick()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mCurrentTimeCount);

	mDeltaTime = (double)(mCurrentTimeCount - mPrevTimeCount)*mSecondPerCount;


	mPrevTimeCount = mCurrentTimeCount;

}
