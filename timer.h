#pragma once

#include <iostream>
#include <fstream>
#include <chrono>

namespace rot
{
	class ProfilerTimer
	{
	public:
		ProfilerTimer(const char* File);
		~ProfilerTimer();

		void init(const char* Name_ID);
		void stop(const char* Name_ID);

		
	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_End;

		const char* m_Name;
		const char* Filepath;

		std::ofstream m_EventOutput;
	};

	ProfilerTimer::ProfilerTimer(const char* File)
	{
		Filepath = File;

		m_EventOutput.open(Filepath, std::ios::out);
		
		if (m_EventOutput)
		{
			m_EventOutput << "{" << "\"traceEvents\": [";
			m_EventOutput.flush();
		}
		init("TopTop");
	}

	ProfilerTimer::~ProfilerTimer()
	{
		stop("TopTop");
		if (m_EventOutput)
		{
			m_EventOutput << "], \n";
			m_EventOutput << "\"displayTimeUnit\": "<< "\"ns\"}";
			m_EventOutput.flush();

			m_EventOutput.close();
		}

	}
	void ProfilerTimer::init(const char* Name_ID)
	{
		m_Start = std::chrono::high_resolution_clock::now();
		

		
		if (m_EventOutput)
		{
			m_EventOutput << "{";
			m_EventOutput << "\"name\":" << "\"" << Name_ID << "\"" << ",";
			m_EventOutput << "\"cat\":" << "\"" << "TESTE" << "\"" << ",";
			m_EventOutput << "\"ph\":" << "\"" << "B" << "\"" << ",";
			m_EventOutput << "\"ts\":" << m_Start.time_since_epoch().count() / 1000 << ",";
			m_EventOutput << "\"pid\":" << 0 << ",";
			m_EventOutput << "\"tid\":" << 0 << ",";
			m_EventOutput << "\"args\":" << "{}";
			m_EventOutput << "}";


			m_EventOutput.flush();
		}

	}

	inline void ProfilerTimer::stop(const char* Name_ID)
	{
		m_End = std::chrono::high_resolution_clock::now();

		if (m_EventOutput)
		{
			m_EventOutput << ",";
			m_EventOutput << "{";
			m_EventOutput << "\"name\":" << "\"" << Name_ID << "\"" << ",";
			m_EventOutput << "\"cat\":" << "\"" << "TESTE" << "\"" << ",";
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