#include "timer.h"
#include <string>


std::ofstream rot::ProfilerTimer::m_EventOutput = std::ofstream("Testes.txt", std::ios::out | std::ios::in);


int main()
{	
	rot::ProfilerTimer::Setup();
	double a = 1;
	uint64_t b = 0;


	{
		
		rot::ProfilerTimer pt("ForLoop", "ForLoop A");

		for (int i = 0; i < 1020; i++)
		{
			a = a + i;			
			rot::ProfilerTimer pt2((std::string("inner for loop") + std::to_string(i)).c_str(), "ForLoopB");
			for (int j = 0; j < 451; j++)			
			{

				b = b * j;				
			}
		}
		
	}
		
}