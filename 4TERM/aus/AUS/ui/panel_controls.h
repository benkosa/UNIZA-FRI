#pragma once

#include "../ui/performance_chart/panel_performance_chart.h"
#include "../ui/action_history/panel_action_history.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ui {

	public ref class PanelControls : public UserControl
	{
	public:
		property Control^ PanelPresent
		{
			Control^ get() 
			{ 
				return panelPresent_; 
			};

			void set(Control^ panelPresent) 
			{
				panelPresent_ = panelPresent;
				if (panelPresent_ != nullptr)
				{
					pnlPresent->Controls->Add(panelPresent_);
					panelPresent_->Dock = DockStyle::Fill;
				}
			}
		}

		property FlowLayoutPanel^ ControlsPanel
		{
			FlowLayoutPanel^ get() { return pnlControls; };
		}

		property PanelPerformanceChart^ PanelPerformance
		{
			PanelPerformanceChart^ get() { return panelPerformance_; };
		}

		property PanelActionHistory^ PanelHistory
		{
			PanelActionHistory^ get() { return panelActionHistory_; };
		}

		PanelControls(void);

		void showPresentPanel(bool value);
	protected:
		~PanelControls();

	private:
		/// <summary> Prezentacny panel struktury. </summary>
		Control^ panelPresent_;
		/// <summary> Graf s vykonmi struktur. </summary>
		PanelPerformanceChart^ panelPerformance_;
		/// <summary> Tabulka s historiou operacii. </summary>
		PanelActionHistory^ panelActionHistory_;

	private: System::Windows::Forms::FlowLayoutPanel^  pnlControls;
	private: System::Windows::Forms::Panel^  pnlPerformance;
	private: System::Windows::Forms::Panel^  pnlPresent;
	private: System::Windows::Forms::Label^  lblNoVisualization;
	private: System::Windows::Forms::Panel^  pnlHistory;
	private: System::Windows::Forms::Splitter^  splitterPerformance;
	private: System::Windows::Forms::Splitter^  splitterHistory;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pnlControls = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pnlPerformance = (gcnew System::Windows::Forms::Panel());
			this->splitterPerformance = (gcnew System::Windows::Forms::Splitter());
			this->pnlPresent = (gcnew System::Windows::Forms::Panel());
			this->lblNoVisualization = (gcnew System::Windows::Forms::Label());
			this->pnlHistory = (gcnew System::Windows::Forms::Panel());
			this->splitterHistory = (gcnew System::Windows::Forms::Splitter());
			this->pnlPresent->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlControls
			// 
			this->pnlControls->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(41)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->pnlControls->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlControls->Location = System::Drawing::Point(0, 0);
			this->pnlControls->Name = L"pnlControls";
			this->pnlControls->Size = System::Drawing::Size(792, 40);
			this->pnlControls->TabIndex = 0;
			// 
			// pnlPerformance
			// 
			this->pnlPerformance->BackColor = System::Drawing::SystemColors::Control;
			this->pnlPerformance->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->pnlPerformance->Location = System::Drawing::Point(0, 367);
			this->pnlPerformance->Name = L"pnlPerformance";
			this->pnlPerformance->Size = System::Drawing::Size(792, 126);
			this->pnlPerformance->TabIndex = 1;
			// 
			// splitterPerformance
			// 
			this->splitterPerformance->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->splitterPerformance->Location = System::Drawing::Point(0, 364);
			this->splitterPerformance->Name = L"splitterPerformance";
			this->splitterPerformance->Size = System::Drawing::Size(792, 3);
			this->splitterPerformance->TabIndex = 2;
			this->splitterPerformance->TabStop = false;
			// 
			// pnlPresent
			// 
			this->pnlPresent->Controls->Add(this->lblNoVisualization);
			this->pnlPresent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlPresent->Location = System::Drawing::Point(0, 40);
			this->pnlPresent->Name = L"pnlPresent";
			this->pnlPresent->Size = System::Drawing::Size(377, 324);
			this->pnlPresent->TabIndex = 3;
			// 
			// lblNoVisualization
			// 
			this->lblNoVisualization->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblNoVisualization->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->lblNoVisualization->Location = System::Drawing::Point(0, 0);
			this->lblNoVisualization->Name = L"lblNoVisualization";
			this->lblNoVisualization->Size = System::Drawing::Size(377, 324);
			this->lblNoVisualization->TabIndex = 0;
			this->lblNoVisualization->Text = L"Structure can not be visualized";
			this->lblNoVisualization->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pnlHistory
			// 
			this->pnlHistory->Dock = System::Windows::Forms::DockStyle::Right;
			this->pnlHistory->Location = System::Drawing::Point(380, 40);
			this->pnlHistory->Name = L"pnlHistory";
			this->pnlHistory->Size = System::Drawing::Size(412, 324);
			this->pnlHistory->TabIndex = 5;
			// 
			// splitterHistory
			// 
			this->splitterHistory->Dock = System::Windows::Forms::DockStyle::Right;
			this->splitterHistory->Location = System::Drawing::Point(377, 40);
			this->splitterHistory->Name = L"splitterHistory";
			this->splitterHistory->Size = System::Drawing::Size(3, 324);
			this->splitterHistory->TabIndex = 5;
			this->splitterHistory->TabStop = false;
			// 
			// PanelControls
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->Controls->Add(this->pnlPresent);
			this->Controls->Add(this->splitterHistory);
			this->Controls->Add(this->pnlHistory);
			this->Controls->Add(this->splitterPerformance);
			this->Controls->Add(this->pnlPerformance);
			this->Controls->Add(this->pnlControls);
			this->Name = L"PanelControls";
			this->Size = System::Drawing::Size(792, 493);
			this->pnlPresent->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	};

	
}
