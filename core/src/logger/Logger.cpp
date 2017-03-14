#include "LogSink.hpp"
#include "Logger.hpp"

namespace Nope
{
	namespace Log
	{
		using namespace std::chrono;
		// Do not touch
		time_point<high_resolution_clock, milliseconds> const Logger::startTime =
			time_point_cast<milliseconds>(high_resolution_clock::now());

		LogLevel Logger::logLevel = LogLevel::INFO;

		Logger Trace(LogLevel::TRACE);
#ifdef DEBUG
		Logger Debug(LogLevel::DBG);
#endif
		Logger Info(LogLevel::INFO);
		Logger Warning(LogLevel::WARNING);
		Logger Error(LogLevel::ERROR);

		Logger::Logger(LogLevel level) : m_level(level)
		{
		}

		void Logger::addSink(LogSink const &s)
		{
			m_sinks.push_back(s);
		}

#ifdef DEBUG
		LogMessage Logger::operator()(std::string &&file, size_t line)
		{
			return LogMessage(this, std::move(file), line);
		}
#endif

		void Logger::flush(LogMessage const &msg) const
		{
			if (m_level >= logLevel)
			{
				for (auto &s : m_sinks)
				{
					s(msg, m_level);
				}
			}
		}

		void Logger::start()
		{
			LogSink console = LogSink::makeOstream(std::cout);
			LogSink file = LogSink::makeFile("nope.log");

			Trace.addSink(console);
#ifdef DEBUG
			Debug.addSink(console);
#endif
			Info.addSink(console);
			Warning.addSink(console);
			Error.addSink(console);

#ifdef DEBUG
			Debug.addSink(file);
#endif
			Warning.addSink(file);
			Error.addSink(file);
		}

		std::ostream &operator<<(std::ostream &os, LogLevel level)
		{
			switch (level)
			{
			case LogLevel::TRACE:
				os << "{{TRACE}}";
				break;
#ifdef DEBUG
			case LogLevel::DBG:
				os << "[DEBUG]\t";
				break;
#endif
			case LogLevel::INFO:
				os << "[INFO]\t";
				break;
			case LogLevel::WARNING:
				os << "**WARNING**";
				break;
			case LogLevel::ERROR:
				os << "!!ERROR!!";
				break;
			default:
				os << "? Unknown ?";
			}
			os << "\t";
			return os;
		}
	}
}