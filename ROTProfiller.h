#pragma once

#include<fstream>
#include<chrono>
#include<string>

namespace rot
{
	struct TimerAtributes
	{
		std::string Name;
		std::string Category;
		std::chrono::time_point<std::chrono::high_resolution_clock> StartTime;
		std::chrono::high_resolution_clock::duration EventDuration;

	};

	class EventLogger
	{
	public:
		EventLogger(std::string Filepath);
		~EventLogger();
		void EndSession();
		void RecordTimer(const TimerAtributes& TimerInfo);

	private:
		std::fstream m_File;
		bool bFirstEntry;
	};

	EventLogger::EventLogger(std::string Filepath)
	{
		m_File.open(Filepath, std::ios::out);
		if (m_File)
		{
			m_File << "{\"traceEvents\":[";
			m_File.flush();
		}
		bFirstEntry = true;
	}

	EventLogger::~EventLogger()
	{
		EndSession();
	}

	void EventLogger::EndSession()
	{
		if (m_File)
		{
			m_File << "]}";
			m_File.flush();
			m_File.close();
		}
		
	}	

	void EventLogger::RecordTimer(const TimerAtributes& TimerInfo)
	{
		if (m_File)
		{
			if (!bFirstEntry)
			{
				m_File << ",";
				
			}
			m_File << "{";
			m_File << "\"name\":" << "\"" << TimerInfo.Name << "\"" << ",";
			m_File << "\"cat\":" << "\"" << TimerInfo.Category << "\"" << ",";
			m_File << "\"ph\":" << "\"" << "X" << "\"" << ",";
			m_File << "\"ts\":" << TimerInfo.StartTime.time_since_epoch().count()/1000 << ",";
			m_File << "\"dur\":" << TimerInfo.EventDuration.count()/1000 << ",";
			m_File << "\"pid\":" << 0 << ",";
			m_File << "\"tid\":" << 0 << ",";
			m_File << "\"args\":" << "{}";
			m_File << "}";
			bFirstEntry = false;
		}
	}


	class Timer
	{
	public:
		Timer(const std::string& Name, const std::string& Category, EventLogger* LoggerInstace);
		~Timer();

	private:		
		EventLogger* m_LoggerInstance;
		TimerAtributes TimerInfo;
	};

	Timer::Timer(const std::string& Name, const std::string& Category, EventLogger* LoggerInstace)
	{
		m_LoggerInstance = LoggerInstace;
		TimerInfo.Name = Name;
		TimerInfo.Category = Category;
		TimerInfo.StartTime = std::chrono::high_resolution_clock::now();

	};

	Timer::~Timer()
	{
		TimerInfo.EventDuration = (std::chrono::high_resolution_clock::now() - TimerInfo.StartTime);
		m_LoggerInstance->RecordTimer(TimerInfo);
	};

}


//PREPROCESSOR STATMENTS FOR MACRO USE. JUST COPY AT THE START OF YOU MAIN FILE

#ifdef ROTPROFILLERTOOL
#define ROTPROFILLERSTART(x) rot::EventLogger EVLOG(x);
#define ROTPROFILLEREND EVLOG.EndSession();
#define ROTPROFILLERFUNCION rot::Timer pt(__func__ , "Category 1", &EVLOG);
#define ROTPROFILERNAMED(x) rot::Timer pt(x , "Category 1", &EVLOG);
#else
#define ROTPROFILLERSTART(x) 
#define ROTPROFILLERFUNCION
#define ROTPROFILLEREND(x) 
#define ROTPROFILERNAMED(x)
#endif

//END OF PREPROCESSOR STATMENTS