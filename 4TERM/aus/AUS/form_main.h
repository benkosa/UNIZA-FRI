#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace ui {

public ref class FormMain sealed : public Form
{
	public:
		FormMain(void);

	protected:
		~FormMain();
		
	private: System::Windows::Forms::TabControl^  tabsStructures;
	private: System::Windows::Forms::TabPage^  tabVector;
	private: System::Windows::Forms::TabPage^  tabArray;
	private: System::Windows::Forms::TabPage^  tabList;
	private: System::Windows::Forms::TabPage^  tabQueue;
	private: System::Windows::Forms::TabPage^  tabStack;
	private: System::Windows::Forms::TabPage^  tabPriorityQueue;
	private: System::Windows::Forms::TabPage^  tabGraph;
	private: System::Windows::Forms::TabPage^  tabTree;
	private: System::Windows::Forms::TabPage^  tabTable;
	private: System::Windows::Forms::TabPage^  tabSorting;
	private: System::Windows::Forms::Panel^  pnlVector;
	private: System::Windows::Forms::Panel^  pnlArray;
	private: System::Windows::Forms::Panel^  pnlList;
	private: System::Windows::Forms::Panel^  pnlQueue;
	private: System::Windows::Forms::Panel^  pnlStack;
	private: System::Windows::Forms::Panel^  pnlPriorityQueue;
	private: System::Windows::Forms::Panel^  pnlGraph;
	private: System::Windows::Forms::Panel^  pnlTree;
	private: System::Windows::Forms::Panel^  pnlTable;
	private: System::Windows::Forms::Panel^  pnlSorting;
	private: System::Windows::Forms::Panel^  pnlLogger;
	private: System::Windows::Forms::Splitter^  splitterLog;
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->tabsStructures = (gcnew System::Windows::Forms::TabControl());
		this->tabVector = (gcnew System::Windows::Forms::TabPage());
		this->pnlVector = (gcnew System::Windows::Forms::Panel());
		this->tabArray = (gcnew System::Windows::Forms::TabPage());
		this->pnlArray = (gcnew System::Windows::Forms::Panel());
		this->tabList = (gcnew System::Windows::Forms::TabPage());
		this->pnlList = (gcnew System::Windows::Forms::Panel());
		this->tabQueue = (gcnew System::Windows::Forms::TabPage());
		this->pnlQueue = (gcnew System::Windows::Forms::Panel());
		this->tabStack = (gcnew System::Windows::Forms::TabPage());
		this->pnlStack = (gcnew System::Windows::Forms::Panel());
		this->tabPriorityQueue = (gcnew System::Windows::Forms::TabPage());
		this->pnlPriorityQueue = (gcnew System::Windows::Forms::Panel());
		this->tabGraph = (gcnew System::Windows::Forms::TabPage());
		this->pnlGraph = (gcnew System::Windows::Forms::Panel());
		this->tabTree = (gcnew System::Windows::Forms::TabPage());
		this->pnlTree = (gcnew System::Windows::Forms::Panel());
		this->tabTable = (gcnew System::Windows::Forms::TabPage());
		this->pnlTable = (gcnew System::Windows::Forms::Panel());
		this->tabSorting = (gcnew System::Windows::Forms::TabPage());
		this->pnlSorting = (gcnew System::Windows::Forms::Panel());
		this->pnlLogger = (gcnew System::Windows::Forms::Panel());
		this->splitterLog = (gcnew System::Windows::Forms::Splitter());
		this->tabsStructures->SuspendLayout();
		this->tabVector->SuspendLayout();
		this->tabArray->SuspendLayout();
		this->tabList->SuspendLayout();
		this->tabQueue->SuspendLayout();
		this->tabStack->SuspendLayout();
		this->tabPriorityQueue->SuspendLayout();
		this->tabGraph->SuspendLayout();
		this->tabTree->SuspendLayout();
		this->tabTable->SuspendLayout();
		this->tabSorting->SuspendLayout();
		this->SuspendLayout();
		// 
		// tabsStructures
		// 
		this->tabsStructures->Controls->Add(this->tabVector);
		this->tabsStructures->Controls->Add(this->tabArray);
		this->tabsStructures->Controls->Add(this->tabList);
		this->tabsStructures->Controls->Add(this->tabQueue);
		this->tabsStructures->Controls->Add(this->tabStack);
		this->tabsStructures->Controls->Add(this->tabPriorityQueue);
		this->tabsStructures->Controls->Add(this->tabGraph);
		this->tabsStructures->Controls->Add(this->tabTree);
		this->tabsStructures->Controls->Add(this->tabTable);
		this->tabsStructures->Controls->Add(this->tabSorting);
		this->tabsStructures->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tabsStructures->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(238)));
		this->tabsStructures->ItemSize = System::Drawing::Size(65, 28);
		this->tabsStructures->Location = System::Drawing::Point(0, 0);
		this->tabsStructures->Name = L"tabsStructures";
		this->tabsStructures->SelectedIndex = 0;
		this->tabsStructures->Size = System::Drawing::Size(784, 561);
		this->tabsStructures->TabIndex = 4;
		// 
		// tabVector
		// 
		this->tabVector->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabVector->Controls->Add(this->pnlVector);
		this->tabVector->ForeColor = System::Drawing::SystemColors::ControlText;
		this->tabVector->Location = System::Drawing::Point(4, 32);
		this->tabVector->Name = L"tabVector";
		this->tabVector->Padding = System::Windows::Forms::Padding(3);
		this->tabVector->Size = System::Drawing::Size(776, 525);
		this->tabVector->TabIndex = 11;
		this->tabVector->Text = L"Vector";
		// 
		// pnlVector
		// 
		this->pnlVector->BackColor = System::Drawing::Color::Transparent;
		this->pnlVector->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlVector->Location = System::Drawing::Point(3, 3);
		this->pnlVector->Name = L"pnlVector";
		this->pnlVector->Size = System::Drawing::Size(770, 519);
		this->pnlVector->TabIndex = 0;
		// 
		// tabArray
		// 
		this->tabArray->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabArray->Controls->Add(this->pnlArray);
		this->tabArray->Location = System::Drawing::Point(4, 32);
		this->tabArray->Name = L"tabArray";
		this->tabArray->Padding = System::Windows::Forms::Padding(3);
		this->tabArray->Size = System::Drawing::Size(776, 525);
		this->tabArray->TabIndex = 2;
		this->tabArray->Text = L"Array";
		// 
		// pnlArray
		// 
		this->pnlArray->BackColor = System::Drawing::Color::Transparent;
		this->pnlArray->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlArray->Location = System::Drawing::Point(3, 3);
		this->pnlArray->Name = L"pnlArray";
		this->pnlArray->Size = System::Drawing::Size(770, 519);
		this->pnlArray->TabIndex = 0;
		// 
		// tabList
		// 
		this->tabList->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabList->Controls->Add(this->pnlList);
		this->tabList->Location = System::Drawing::Point(4, 32);
		this->tabList->Name = L"tabList";
		this->tabList->Padding = System::Windows::Forms::Padding(3);
		this->tabList->Size = System::Drawing::Size(776, 525);
		this->tabList->TabIndex = 3;
		this->tabList->Text = L"List";
		// 
		// pnlList
		// 
		this->pnlList->BackColor = System::Drawing::Color::Transparent;
		this->pnlList->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlList->Location = System::Drawing::Point(3, 3);
		this->pnlList->Name = L"pnlList";
		this->pnlList->Size = System::Drawing::Size(770, 519);
		this->pnlList->TabIndex = 0;
		// 
		// tabQueue
		// 
		this->tabQueue->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabQueue->Controls->Add(this->pnlQueue);
		this->tabQueue->Location = System::Drawing::Point(4, 32);
		this->tabQueue->Name = L"tabQueue";
		this->tabQueue->Padding = System::Windows::Forms::Padding(3);
		this->tabQueue->Size = System::Drawing::Size(776, 525);
		this->tabQueue->TabIndex = 4;
		this->tabQueue->Text = L"Queue";
		// 
		// pnlQueue
		// 
		this->pnlQueue->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlQueue->Location = System::Drawing::Point(3, 3);
		this->pnlQueue->Name = L"pnlQueue";
		this->pnlQueue->Size = System::Drawing::Size(770, 519);
		this->pnlQueue->TabIndex = 0;
		// 
		// tabStack
		// 
		this->tabStack->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabStack->Controls->Add(this->pnlStack);
		this->tabStack->Location = System::Drawing::Point(4, 32);
		this->tabStack->Name = L"tabStack";
		this->tabStack->Padding = System::Windows::Forms::Padding(3);
		this->tabStack->Size = System::Drawing::Size(776, 525);
		this->tabStack->TabIndex = 5;
		this->tabStack->Text = L"Stack";
		// 
		// pnlStack
		// 
		this->pnlStack->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlStack->Location = System::Drawing::Point(3, 3);
		this->pnlStack->Name = L"pnlStack";
		this->pnlStack->Size = System::Drawing::Size(770, 519);
		this->pnlStack->TabIndex = 0;
		// 
		// tabPriorityQueue
		// 
		this->tabPriorityQueue->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)),
			static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabPriorityQueue->Controls->Add(this->pnlPriorityQueue);
		this->tabPriorityQueue->Location = System::Drawing::Point(4, 32);
		this->tabPriorityQueue->Name = L"tabPriorityQueue";
		this->tabPriorityQueue->Padding = System::Windows::Forms::Padding(3);
		this->tabPriorityQueue->Size = System::Drawing::Size(776, 525);
		this->tabPriorityQueue->TabIndex = 6;
		this->tabPriorityQueue->Text = L"Priority queue";
		// 
		// pnlPriorityQueue
		// 
		this->pnlPriorityQueue->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlPriorityQueue->Location = System::Drawing::Point(3, 3);
		this->pnlPriorityQueue->Name = L"pnlPriorityQueue";
		this->pnlPriorityQueue->Size = System::Drawing::Size(770, 519);
		this->pnlPriorityQueue->TabIndex = 0;
		// 
		// tabGraph
		// 
		this->tabGraph->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabGraph->Controls->Add(this->pnlGraph);
		this->tabGraph->Location = System::Drawing::Point(4, 32);
		this->tabGraph->Name = L"tabGraph";
		this->tabGraph->Padding = System::Windows::Forms::Padding(3);
		this->tabGraph->Size = System::Drawing::Size(776, 525);
		this->tabGraph->TabIndex = 10;
		this->tabGraph->Text = L"Graph";
		// 
		// pnlGraph
		// 
		this->pnlGraph->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlGraph->Location = System::Drawing::Point(3, 3);
		this->pnlGraph->Name = L"pnlGraph";
		this->pnlGraph->Size = System::Drawing::Size(770, 519);
		this->pnlGraph->TabIndex = 0;
		// 
		// tabTree
		// 
		this->tabTree->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabTree->Controls->Add(this->pnlTree);
		this->tabTree->Location = System::Drawing::Point(4, 32);
		this->tabTree->Name = L"tabTree";
		this->tabTree->Padding = System::Windows::Forms::Padding(3);
		this->tabTree->Size = System::Drawing::Size(776, 525);
		this->tabTree->TabIndex = 7;
		this->tabTree->Text = L"Tree";
		// 
		// pnlTree
		// 
		this->pnlTree->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlTree->Location = System::Drawing::Point(3, 3);
		this->pnlTree->Name = L"pnlTree";
		this->pnlTree->Size = System::Drawing::Size(770, 519);
		this->pnlTree->TabIndex = 0;
		// 
		// tabTable
		// 
		this->tabTable->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabTable->Controls->Add(this->pnlTable);
		this->tabTable->Location = System::Drawing::Point(4, 32);
		this->tabTable->Name = L"tabTable";
		this->tabTable->Padding = System::Windows::Forms::Padding(3);
		this->tabTable->Size = System::Drawing::Size(776, 525);
		this->tabTable->TabIndex = 8;
		this->tabTable->Text = L"Table";
		// 
		// pnlTable
		// 
		this->pnlTable->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlTable->Location = System::Drawing::Point(3, 3);
		this->pnlTable->Name = L"pnlTable";
		this->pnlTable->Size = System::Drawing::Size(770, 519);
		this->pnlTable->TabIndex = 0;
		// 
		// tabSorting
		// 
		this->tabSorting->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->tabSorting->Controls->Add(this->pnlSorting);
		this->tabSorting->Location = System::Drawing::Point(4, 32);
		this->tabSorting->Name = L"tabSorting";
		this->tabSorting->Padding = System::Windows::Forms::Padding(3);
		this->tabSorting->Size = System::Drawing::Size(776, 525);
		this->tabSorting->TabIndex = 9;
		this->tabSorting->Text = L"Sorting";
		// 
		// pnlSorting
		// 
		this->pnlSorting->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlSorting->Location = System::Drawing::Point(3, 3);
		this->pnlSorting->Name = L"pnlSorting";
		this->pnlSorting->Size = System::Drawing::Size(770, 519);
		this->pnlSorting->TabIndex = 0;
		// 
		// pnlLogger
		// 
		this->pnlLogger->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->pnlLogger->Location = System::Drawing::Point(0, 411);
		this->pnlLogger->Name = L"pnlLogger";
		this->pnlLogger->Size = System::Drawing::Size(784, 150);
		this->pnlLogger->TabIndex = 3;
		// 
		// splitterLog
		// 
		this->splitterLog->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->splitterLog->Location = System::Drawing::Point(0, 408);
		this->splitterLog->Name = L"splitterLog";
		this->splitterLog->RightToLeft = System::Windows::Forms::RightToLeft::No;
		this->splitterLog->Size = System::Drawing::Size(784, 3);
		this->splitterLog->TabIndex = 5;
		this->splitterLog->TabStop = false;
		// 
		// FormMain
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
			static_cast<System::Int32>(static_cast<System::Byte>(233)));
		this->ClientSize = System::Drawing::Size(784, 561);
		this->Controls->Add(this->tabsStructures);
		this->Controls->Add(this->splitterLog);
		this->Controls->Add(this->pnlLogger);
		this->Name = L"FormMain";
		this->Text = L"Datastructures";
		this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
		this->tabsStructures->ResumeLayout(false);
		this->tabVector->ResumeLayout(false);
		this->tabArray->ResumeLayout(false);
		this->tabList->ResumeLayout(false);
		this->tabQueue->ResumeLayout(false);
		this->tabStack->ResumeLayout(false);
		this->tabPriorityQueue->ResumeLayout(false);
		this->tabGraph->ResumeLayout(false);
		this->tabTree->ResumeLayout(false);
		this->tabTable->ResumeLayout(false);
		this->tabSorting->ResumeLayout(false);
		this->ResumeLayout(false);

	}
#pragma endregion

};

/*FormMain::~FormMain()
{
	
}*/

}

