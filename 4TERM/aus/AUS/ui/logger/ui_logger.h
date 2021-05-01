#pragma once

#include <string>

using namespace System::Collections::Generic;

namespace ui {

	namespace log {

		/// <summary> Rozne druhy logov. </summary>
		enum LogType
		{
			ltERROR,
			ltWARNING,
			ltHINT,
			ltWAIT,
			ltDEBUG
		};

		/// <summary> 
		/// Rozhranie, ktore musia implementovat triedy poskytujuce logovanie. 
		/// Navrh vychadza zo vzoru Mediator.
		/// </summary>
		interface class ILoggerProvider
		{
			/// <summary> Zaloguje spravu daneho typu. </summary>
			/// <param name = "lt"> Typ spravy. </param>
			/// <param name = "message"> Sprava. </param>
			void log(LogType lt, System::String^ message);
		};

		/// <summary>
		/// Trieda predstavuje centralny bod pre logovanie. 
		/// Je navrhnuta podla vzoru Mediator a Singleton.
		/// Spolupracuje s triedami ILogger, ktore notifikuje o zmenach.
		/// </summary>
		ref class Logger
		{
		public:
			/// <summary> Jednoducha tovarenska metoda pre ziskanie instancie jedinacika </summary>
			/// <returns> Instancia triedy logger. </returns>
			/// <remarks> Instancia je inicializovana pomocou lazy initialization. O jej spravu sa stara trieda. </remarks>
			static Logger^ getInstance();

			/// <summary> Zaregistruje poskytovatela logovacich sluzieb. </summary>
			/// <param name = "provider"> Poskytovatel logovacich sluzieb. </param>
			/// <returns> true, ak sa podarilo poskytovatela zaregistrovat, false inak. </returns>
			bool registerProvider(ILoggerProvider^ provider);

			/// <summary> Odregistruje poskytovatela logovacich sluzieb. </summary>
			/// <param name = "provider"> Poskytovatel logovacich sluzieb. </param>
			/// <returns> true, ak sa podarilo poskytovatela odregistrovat, false inak. </returns>
			bool unregisterProvider(ILoggerProvider^ provider);

			/// <summary> Zaloguje chybu. </summary>
			/// <param name = "message"> Sprava. </param>
			void logError(std::string message);
			/// <summary> Zaloguje chybu. </summary>
			/// <param name = "message"> Sprava. </param>
			void logError(System::String^ message);

			/// <summary> Zaloguje vystrahu. </summary>
			/// <param name = "message"> Sprava. </param>
			void logWarning(std::string message);
			/// <summary> Zaloguje vystrahu. </summary>
			/// <param name = "message"> Sprava. </param>
			void logWarning(System::String^ message);

			/// <summary> Zaloguje oznam. </summary>
			/// <param name = "message"> Sprava. </param>
			void logHint(std::string message);
			/// <summary> Zaloguje oznam. </summary>
			/// <param name = "message"> Sprava. </param>
			void logHint(System::String^ message);

			/// <summary> Zaloguje cakanie. </summary>
			/// <param name = "message"> Sprava. </param>
			void logWait(std::string message);
			/// <summary> Zaloguje cakanie. </summary>
			/// <param name = "message"> Sprava. </param>
			void logWait(System::String^ message);

			/// <summary> Zaloguje debugovaciu spravu. </summary>
			/// <param name = "message"> Sprava. </param>
			void logDebug(std::string message);
			/// <summary> Zaloguje debugovaciu spravu. </summary>
			/// <param name = "message"> Sprava. </param>
			void logDebug(System::String^ message);

		private:
			/// <summary> Necha zalogovat kazdeho zaregistrovaneho providera spravu s danym typom. </summary>
			/// <param name = "lt"> Typ spravy. </param>
			/// <param name = "message"> Sprava. </param>
			void notifyProviders(LogType lt, System::String^ message);

			/// <summary> Konstruktor. </summary>
			Logger();
		private:
			/// <summary> Premenna triedy obsahujuca odkaz na jedinu instanciu triedy. </summary>
			static Logger^ logger_ = nullptr;

			/// <summary> Zoznam poskytovatelov logovacich sluzieb. </summary>
			List<ILoggerProvider^>^ providers_;
		};

	}

}
