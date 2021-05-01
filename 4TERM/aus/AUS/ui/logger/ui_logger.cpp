#include "ui_logger.h"

using namespace System;
using namespace std;

namespace ui {
	namespace log {

		Logger ^ Logger::getInstance()
		{
			if (Logger::logger_ == nullptr) 
				Logger::logger_ = gcnew Logger();
			return Logger::logger_;
		}

		Logger::Logger()
		{
			providers_ = gcnew List<ILoggerProvider^>;
		}

		bool Logger::registerProvider(ILoggerProvider ^ provider)
		{
			if (!providers_->Contains(provider))
			{
				providers_->Add(provider);
				return true;
			}
			else 
			{
				return false;
			}
		}

		bool Logger::unregisterProvider(ILoggerProvider ^ provider)
		{
			if (providers_->Contains(provider))
			{
				providers_->Remove(provider);
				return true;
			}
			else
			{
				return false;
			}
		}

		void Logger::logError(string message)
		{
			Logger::logError(gcnew String(message.c_str()));
		}

		void Logger::logError(String ^ message)
		{
			notifyProviders(LogType::ltERROR, message);
		}

		void Logger::logWarning(string message)
		{
			Logger::logWarning(gcnew String(message.c_str()));
		}

		void Logger::logWarning(String ^ message)
		{
			notifyProviders(LogType::ltWARNING, message);
		}

		void Logger::logHint(string message)
		{
			Logger::logHint(gcnew String(message.c_str()));
		}

		void Logger::logHint(String ^ message)
		{
			notifyProviders(LogType::ltHINT, message);
		}

		void Logger::logWait(string message)
		{
			Logger::logWait(gcnew String(message.c_str()));
		}

		void Logger::logWait(String ^ message)
		{
			notifyProviders(LogType::ltWAIT, message);
		}

		void Logger::logDebug(string message)
		{
			Logger::logDebug(gcnew String(message.c_str()));
		}

		void Logger::logDebug(String ^ message)
		{
			notifyProviders(LogType::ltDEBUG, message);
		}

		void Logger::notifyProviders(LogType lt, System::String ^ message)
		{
			for each(ILoggerProvider^ provider in providers_)
				provider->log(lt, message);
		}

	}
}