#include"Utils.h"

using namespace gameUtility;

Timer::Timer()
{
	reset();
	tick = 1000;
}
Timer::Timer(int tick) : tick(tick) 
{ 
	reset(); 
}
Timer::~Timer() {}

void Timer::setTick(int tick) { this->tick = tick; }
bool Timer::isTime() 
{	
	millis_epleased = std::chrono::duration_cast<MILLIS>(CLOCK::now() - start).count();
	if (millis_epleased > tick) {
		reset();
		return true;
	}
	return false;
}
void Timer::reset()
{
	millis_epleased = 0;
	start = CLOCK::now();
}