#pragma once
#include<chrono>
namespace gameUtility
{
	class Timer
	{
	private:

		typedef std::chrono::high_resolution_clock::time_point TIME_POINT;
		typedef std::chrono::high_resolution_clock CLOCK;
		typedef std::chrono::milliseconds MILLIS;

		TIME_POINT start;
		int millis_epleased;
		int tick;
		
	public:

		Timer();
		Timer(int tick);
		~Timer();
		bool isTime();
		void reset();
		void setTick(int tick);
	};
}