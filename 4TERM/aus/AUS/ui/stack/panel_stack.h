#pragma once

#include "../../structures/stack/stack.h"
#include "../controls/controls.h"
#include "../controls/controls_list.h"
#include "../ui_routines.h"
#include "../../data/data_routines.h"
#include "../../data/data_types.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace ui 
{
	/// <summary>
	/// Summary for PanelPresentPriorityQueue
	/// </summary>
	public ref class PanelPresentStack : public UserControl
	{
	public:
		PanelPresentStack(void);

		void initialize(ControlsHolder^ holder);
		void visualize(structures::Stack<data::DataType>* stack);
	protected:
		~PanelPresentStack();
	private:
		ControlsHolder^ controls;
	private: System::Windows::Forms::Panel^  panelData;
	protected:
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::Label^  lblPeek;

	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::Label^  lblValue;
	private: System::Windows::Forms::Label^  lblBits;
	private: System::Windows::Forms::TextBox^  txtPeek;

	private: System::Windows::Forms::TextBox^  txtPeekBits;


	protected:

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
			this->panelData = (gcnew System::Windows::Forms::Panel());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->lblPeek = (gcnew System::Windows::Forms::Label());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->txtPeek = (gcnew System::Windows::Forms::TextBox());
			this->lblValue = (gcnew System::Windows::Forms::Label());
			this->txtPeekBits = (gcnew System::Windows::Forms::TextBox());
			this->lblBits = (gcnew System::Windows::Forms::Label());
			this->panelData->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panelData
			// 
			this->panelData->BackColor = System::Drawing::Color::White;
			this->panelData->Controls->Add(this->splitContainer1);
			this->panelData->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelData->Location = System::Drawing::Point(0, 0);
			this->panelData->Name = L"panelData";
			this->panelData->Size = System::Drawing::Size(444, 40);
			this->panelData->TabIndex = 3;
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->lblPeek);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->splitContainer2);
			this->splitContainer1->Size = System::Drawing::Size(444, 40);
			this->splitContainer1->SplitterDistance = 84;
			this->splitContainer1->TabIndex = 0;
			// 
			// lblPeek
			// 
			this->lblPeek->AutoSize = true;
			this->lblPeek->Location = System::Drawing::Point(3, 23);
			this->lblPeek->Name = L"lblPeek";
			this->lblPeek->Size = System::Drawing::Size(35, 13);
			this->lblPeek->TabIndex = 2;
			this->lblPeek->Text = L"Peek:";
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->txtPeek);
			this->splitContainer2->Panel1->Controls->Add(this->lblValue);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->txtPeekBits);
			this->splitContainer2->Panel2->Controls->Add(this->lblBits);
			this->splitContainer2->Size = System::Drawing::Size(356, 40);
			this->splitContainer2->SplitterDistance = 157;
			this->splitContainer2->TabIndex = 0;
			// 
			// txtPeek
			// 
			this->txtPeek->BackColor = System::Drawing::Color::White;
			this->txtPeek->Dock = System::Windows::Forms::DockStyle::Top;
			this->txtPeek->ForeColor = System::Drawing::Color::Black;
			this->txtPeek->Location = System::Drawing::Point(0, 20);
			this->txtPeek->Name = L"txtPeek";
			this->txtPeek->ReadOnly = true;
			this->txtPeek->Size = System::Drawing::Size(157, 20);
			this->txtPeek->TabIndex = 9;
			// 
			// lblValue
			// 
			this->lblValue->Dock = System::Windows::Forms::DockStyle::Top;
			this->lblValue->Location = System::Drawing::Point(0, 0);
			this->lblValue->Name = L"lblValue";
			this->lblValue->Padding = System::Windows::Forms::Padding(4, 4, 0, 0);
			this->lblValue->Size = System::Drawing::Size(157, 20);
			this->lblValue->TabIndex = 4;
			this->lblValue->Text = L"Value";
			// 
			// txtPeekBits
			// 
			this->txtPeekBits->BackColor = System::Drawing::Color::White;
			this->txtPeekBits->Dock = System::Windows::Forms::DockStyle::Top;
			this->txtPeekBits->ForeColor = System::Drawing::Color::Black;
			this->txtPeekBits->Location = System::Drawing::Point(0, 20);
			this->txtPeekBits->Name = L"txtPeekBits";
			this->txtPeekBits->ReadOnly = true;
			this->txtPeekBits->Size = System::Drawing::Size(195, 20);
			this->txtPeekBits->TabIndex = 11;
			// 
			// lblBits
			// 
			this->lblBits->Dock = System::Windows::Forms::DockStyle::Top;
			this->lblBits->Location = System::Drawing::Point(0, 0);
			this->lblBits->Name = L"lblBits";
			this->lblBits->Padding = System::Windows::Forms::Padding(4, 4, 0, 0);
			this->lblBits->Size = System::Drawing::Size(195, 20);
			this->lblBits->TabIndex = 9;
			this->lblBits->Text = L"Bits";
			// 
			// PanelPresentStack
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->panelData);
			this->Name = L"PanelPresentStack";
			this->Size = System::Drawing::Size(444, 150);
			this->panelData->ResumeLayout(false);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel1->PerformLayout();
			this->splitContainer2->Panel2->ResumeLayout(false);
			this->splitContainer2->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	};

	PanelPresentStack::PanelPresentStack(void) :
		controls(nullptr)
	{
		InitializeComponent();
	}

	inline void PanelPresentStack::initialize(ControlsHolder ^ holder)
	{
		controls = holder;
	}

	PanelPresentStack::~PanelPresentStack()
	{
		if (components)
		{
			delete components;
		}
	}

	void PanelPresentStack::visualize(structures::Stack<data::DataType>* stack)
	{
		size_t size = stack->size();

		if (size > 0)
		{
			data::DataType data = stack->peek();

			// data
			txtPeek->Text = Convert::ToString(data);

			// data bits
			txtPeekBits->Text = UIRoutines::convertMemoryToString(&data, sizeof(data::DataType));
		}
		else
		{
			txtPeek->Clear();
			txtPeekBits->Clear();
		}
	}
}