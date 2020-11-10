#pragma once

#include <iostream>
#include <fstream>
#include <chrono>

namespace rot
{
	class ProfilerTimer
	{
	public:
		ProfilerTimer(const char* Name_ID, const char* Cat);
		~ProfilerTimer();

		static void Setup();

		void init();
		void stop();

		
	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_End;

		const char* m_Name;
		const char* m_Cat;

		static std::ofstream m_EventOutput;
	};

	ProfilerTimer::ProfilerTimer(const char* EventName, const char* Cat)
	{
		m_Name = EventName;
		m_Cat = Cat;
				
		init();
	}

	ProfilerTimer::~ProfilerTimer()
	{
		stop();		

	}
	void ProfilerTimer::Setup()
	{

		if (m_EventOutput)
		{
			m_EventOutput << "{" << "\"traceEvents\": [";
			m_EventOutput.flush();
		}
	}
	void ProfilerTimer::init()
	{
		m_Start = std::chrono::high_resolution_clock::now();	


		
		if (m_EventOutput)
		{		
		
			m_EventOutput << ",";			
			m_EventOutput << "{";
			m_EventOutput << "\"name\":" << "\"" << m_Name << "\"" << ",";
			m_EventOutput << "\"cat\":" << "\"" << m_Cat << "\"" << ",";
			m_EventOutput << "\"ph\":" << "\"" << "B" << "\"" << ",";
			m_EventOutput << "\"ts\":" << m_Start.time_since_epoch().count() / 1000 << ",";
			m_EventOutput << "\"pid\":" << 0 << ",";
			m_EventOutput << "\"tid\":" << 0 << ",";
			m_EventOutput << "\"args\":" << "{}";
			m_EventOutput << "}";


			m_EventOutput.flush();
		}

	}

	void ProfilerTimer::stop()
	{
		m_End = std::chrono::high_resolution_clock::now();

		if (m_EventOutput)
		{
			m_EventOutput << ",";
			m_EventOutput << "{";
			m_EventOutput << "\"name\":" << "\"" << m_Name << "\"" << ",";
			m_EventOutput << "\"cat\":" << "\"" << m_Cat << "\"" << ",";
			m_EventOutput << "\"ph\":" << "\"" << "E" << "\"" << ",";
			m_EventOutput << "\"ts\":" << m_End.time_since_epoch().count() / 1000 << ",";
			m_EventOutput << "\"pid\":" << 0 << ",";
			m_EventOutput << "\"tid\":" << 0 << ",";
			m_EventOutput << "\"args\":" << "{}";
			m_EventOutput << "}";

			m_EventOutput.flush();
			
		}	

	}
	 
}