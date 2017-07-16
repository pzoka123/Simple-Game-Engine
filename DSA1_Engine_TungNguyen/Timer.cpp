#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Update()
{
	prev = curr;
	curr = (float)glfwGetTime();
	deltaT = curr - prev;
}
