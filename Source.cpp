#include "timer.h"


int main()
{
	
	double a = 1;

	{
		
		rot::ProfilerTimer test("teste.json");
		for (int i = 0; i < 1020; i++)
		{
			a = a + i;
			std::cout << a << std::endl;
		}
		
	}
		
}