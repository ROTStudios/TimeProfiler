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
		EventLogger* Get();
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
		if (m_File)
		{
			m_File << "]}";
			m_File.flush();
		}
		m_File.close();
	}

	EventLogger* EventLogger::Get()
	{
		static EventLogger* Instance = this;
		return Instance;
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
		Timer(EventLogger* LoggerInstace, const std::string& Name, const std::string& Category);
		~Timer();

	private:		
		EventLogger* m_LoggerInstance;
		TimerAtributes TimerInfo;
	};

	Timer::Timer(EventLogger* LoggerInstace, const std::string& Name, const std::string& Category)
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

#ifdef ROTPROFILLERTOOL
#define ROTPROFILLERSTART(x) rot::EventLogger EVLOG(x);
#define ROTPROFILLERFUNCION rot::Timer pt(EVLOG.Get(), __func__ , "Category 1");
#else
#define ROTPROFILLERSTART(x) 
#define ROTPROFILLERFUNCION
#endif