#include "ROTProfiller.h"
#include <string>



int main()
{	
	ROTPROFILLERSTART("START.json")
	double a = 1;
	uint64_t b = 0;


	{
		ROTPROFILLERFUNCION

		for (int i = 0; i < 1020; i++)
		{
			a = a + i;			
			ROTPROFILLERFUNCION
			for (int j = 0; j < 451; j++)			
			{
				
				b = b * j;				
			}
		}
		
	}
	
	
}