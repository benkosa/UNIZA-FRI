#pragma once

#include "performance.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Windows::Forms::DataVisualization::Charting;

namespace ui {
	/// <summary>
	/// Panel prezentujuci vykon udajovej struktury.
	/// </summary>
	public ref class PanelPerformanceChart: public UserControl
	{
	public:
		PanelPerformanceChart(void);

		/// <summary> Odprezentuje v grafe historiu vsetkych operacii nad udajovou strukturou. </summary>
		/// <param name = "structure"> Struktura, ktora ma byt prezentovana. </param>
		/// <param name = "adt"> ADT struktury. </param>
		void presentStructure(structures::Structure* structure, structures::StructureADT adt);

		/// <summary> Upravi graf tak, aby obsahoval nove trvanie operacie nad udajovou strukturou. </summary>
		/// <param name = "performanceInfo"> Informacie o operacii. </param>
		void actionPerformed(PerformanceInfo* performanceInfo);
	protected:
		~PanelPerformanceChart();
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chartPerformance;
	private: System::Windows::Forms::Panel^  pnlPerformanceHead;
	private: System::Windows::Forms::Label^  lblPerformanceHead;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		array<Color^>^ colors_;
		structures::Structure* structure_;

		/// <summary> Ak neexistuje, tak vrati series pre danu operaciu. </summary>
		/// <param name = "adt"> ADT struktury. </param>
		/// <param name = "operationID"> ID operacie. </param>
		/// <returns> Series pre danu operaciu. Ak neexistuje, podla parametrov vytvori novu. </returns>
		Series^ getSeries(structures::StructureADT adt, int operationID, String^ caption);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			this->chartPerformance = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->pnlPerformanceHead = (gcnew System::Windows::Forms::Panel());
			this->lblPerformanceHead = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartPerformance))->BeginInit();
			this->pnlPerformanceHead->SuspendLayout();
			this->SuspendLayout();
			// 
			// chartPerformance
			// 
			this->chartPerformance->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
				static_cast<System::Int32>(static_cast<System::Byte>(111)));
			chartArea1->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea1->AxisX->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisX->Title = L"Size";
			chartArea1->AxisX->TitleForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->LabelStyle->ForeColor = System::Drawing::Color::White;
			chartArea1->AxisY->Title = L"Time [ms]";
			chartArea1->AxisY->TitleForeColor = System::Drawing::Color::White;
			chartArea1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
				static_cast<System::Int32>(static_cast<System::Byte>(233)));
			chartArea1->Name = L"chartArea";
			this->chartPerformance->ChartAreas->Add(chartArea1);
			this->chartPerformance->Dock = System::Windows::Forms::DockStyle::Fill;
			legend1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
				static_cast<System::Int32>(static_cast<System::Byte>(233)));
			legend1->Name = L"Legend1";
			legend1->Title = L"Operations";
			this->chartPerformance->Legends->Add(legend1);
			this->chartPerformance->Location = System::Drawing::Point(0, 25);
			this->chartPerformance->Name = L"chartPerformance";
			this->chartPerformance->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::SeaGreen;
			this->chartPerformance->Size = System::Drawing::Size(516, 303);
			this->chartPerformance->TabIndex = 0;
			this->chartPerformance->Text = L"Performance";
			// 
			// pnlPerformanceHead
			// 
			this->pnlPerformanceHead->BackColor = System::Drawing::SystemColors::Control;
			this->pnlPerformanceHead->Controls->Add(this->lblPerformanceHead);
			this->pnlPerformanceHead->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlPerformanceHead->Location = System::Drawing::Point(0, 0);
			this->pnlPerformanceHead->Name = L"pnlPerformanceHead";
			this->pnlPerformanceHead->Size = System::Drawing::Size(516, 25);
			this->pnlPerformanceHead->TabIndex = 2;
			// 
			// lblPerformanceHead
			// 
			this->lblPerformanceHead->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)), static_cast<System::Int32>(static_cast<System::Byte>(157)));
			this->lblPerformanceHead->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblPerformanceHead->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->lblPerformanceHead->Location = System::Drawing::Point(0, 0);
			this->lblPerformanceHead->Margin = System::Windows::Forms::Padding(2, 0, 0, 4);
			this->lblPerformanceHead->Name = L"lblPerformanceHead";
			this->lblPerformanceHead->Size = System::Drawing::Size(516, 25);
			this->lblPerformanceHead->TabIndex = 0;
			this->lblPerformanceHead->Text = L"Performance";
			this->lblPerformanceHead->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// PanelPerformanceChart
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->chartPerformance);
			this->Controls->Add(this->pnlPerformanceHead);
			this->Name = L"PanelPerformanceChart";
			this->Size = System::Drawing::Size(516, 328);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartPerformance))->EndInit();
			this->pnlPerformanceHead->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	
};
}
