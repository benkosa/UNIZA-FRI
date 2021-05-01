#pragma once

#include "ui_logger.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ui {

	/// <summary>
	/// Definuje panel, do ktoreho je mozne logovat.
	/// Panel sa pri vytvoreni automaticky zaregistruje ako LoggerProvider.
	/// Pri zruseni panela sa automaticky odregistruje.
	/// </summary>
	public ref class PanelLogger : public UserControl, public log::ILoggerProvider
	{
	public:
		PanelLogger(void);
		
		/// <summary> Vytvori a vlozi logger do daneho komponentu. </summary>
		/// <param name = "owner"> Vlastnik panela s logerom. Mal by to byt iny prazdny panel. </param>
		/// <returns> Vytvoreny logger. </returns>
		static PanelLogger^ createAndIntegrateLogger(Panel^ owner);

		/// <summary> Zaloguje spravu daneho typu. </summary>
		/// <param name = "lt"> Typ spravy. </param>
		/// <param name = "message"> Sprava. </param>
		virtual void log(log::LogType lt, System::String^ message);

	protected:
		~PanelLogger();

	private:
		const int LOG_IMAGE_NONE    = -1;
		const int LOG_IMAGE_ERROR   = 0;
		const int LOG_IMAGE_WARNING = 1;
		const int LOG_IMAGE_HINT    = 2;
		const int LOG_IMAGE_DEBUG   = 3;
		const int LOG_IMAGE_WAIT    = LOG_IMAGE_NONE;

		String^ convertLogTypeToString(const log::LogType lt);
		int convertLogTypeToImageIndex(const log::LogType lt);

	private: System::Windows::Forms::ImageList^  imagesLog;

	private: System::Windows::Forms::Panel^  pnlLoggerHead;
	private: System::Windows::Forms::Label^  lblLoggerHead;
	private: System::Windows::Forms::ListView^  lviewLogger;

	private: System::Windows::Forms::ColumnHeader^  colLogType;
	private: System::Windows::Forms::ColumnHeader^  colLogMessage;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pnlLoggerHead = (gcnew System::Windows::Forms::Panel());
			this->lblLoggerHead = (gcnew System::Windows::Forms::Label());
			this->lviewLogger = (gcnew System::Windows::Forms::ListView());
			this->colLogType = (gcnew System::Windows::Forms::ColumnHeader());
			this->colLogMessage = (gcnew System::Windows::Forms::ColumnHeader());
			this->imagesLog = (gcnew System::Windows::Forms::ImageList(this->components));
			this->pnlLoggerHead->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlLoggerHead
			// 
			this->pnlLoggerHead->BackColor = System::Drawing::SystemColors::Control;
			this->pnlLoggerHead->Controls->Add(this->lblLoggerHead);
			this->pnlLoggerHead->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlLoggerHead->Location = System::Drawing::Point(0, 0);
			this->pnlLoggerHead->Name = L"pnlLoggerHead";
			this->pnlLoggerHead->Size = System::Drawing::Size(650, 25);
			this->pnlLoggerHead->TabIndex = 0;
			// 
			// lblLoggerHead
			// 
			this->lblLoggerHead->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				static_cast<System::Int32>(static_cast<System::Byte>(157)));
			this->lblLoggerHead->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblLoggerHead->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->lblLoggerHead->Location = System::Drawing::Point(0, 0);
			this->lblLoggerHead->Margin = System::Windows::Forms::Padding(2, 0, 0, 4);
			this->lblLoggerHead->Name = L"lblLoggerHead";
			this->lblLoggerHead->Size = System::Drawing::Size(650, 25);
			this->lblLoggerHead->TabIndex = 0;
			this->lblLoggerHead->Text = L"Logger";
			this->lblLoggerHead->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lviewLogger
			// 
			this->lviewLogger->AutoArrange = false;
			this->lviewLogger->BackgroundImageTiled = true;
			this->lviewLogger->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewLogger->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->colLogType, this->colLogMessage });
			this->lviewLogger->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewLogger->FullRowSelect = true;
			this->lviewLogger->GridLines = true;
			this->lviewLogger->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewLogger->HideSelection = false;
			this->lviewLogger->Location = System::Drawing::Point(0, 25);
			this->lviewLogger->Margin = System::Windows::Forms::Padding(2, 0, 0, 4);
			this->lviewLogger->MultiSelect = false;
			this->lviewLogger->Name = L"lviewLogger";
			this->lviewLogger->ShowGroups = false;
			this->lviewLogger->Size = System::Drawing::Size(650, 125);
			this->lviewLogger->SmallImageList = this->imagesLog;
			this->lviewLogger->TabIndex = 1;
			this->lviewLogger->UseCompatibleStateImageBehavior = false;
			this->lviewLogger->View = System::Windows::Forms::View::Details;
			// 
			// colLogType
			// 
			this->colLogType->Text = L"Message type";
			this->colLogType->Width = 150;
			// 
			// colLogMessage
			// 
			this->colLogMessage->Text = L"Message";
			this->colLogMessage->Width = 1500;
			// 
			// imagesLog
			// 
			this->imagesLog->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
			this->imagesLog->ImageSize = System::Drawing::Size(16, 16);
			this->imagesLog->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// PanelLogger
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->lviewLogger);
			this->Controls->Add(this->pnlLoggerHead);
			this->Name = L"PanelLogger";
			this->Size = System::Drawing::Size(650, 150);
			this->pnlLoggerHead->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	
};
}
