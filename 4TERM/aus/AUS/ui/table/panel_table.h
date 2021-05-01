#pragma once

#include "../../structures/table/table.h"
#include "../controls/controls.h"
#include "../controls/controls_table.h"
#include "../ui_routines.h"
#include "../../data/data_routines.h"
#include "../../data/data_types.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ui {

	public ref class PanelPresentTable: public UserControl
	{
	public:
		property ListViewItem^ SelectedItem
		{
			ListViewItem^ get() { return selectedItem_; };
		}

		property structures::Table<data::KeyType, data::DataType>* Table
		{
			structures::Table<data::KeyType, data::DataType>* get() { return dynamic_cast<structures::Table<data::KeyType, data::DataType>*>(controls_->Structure); };
		}

		PanelPresentTable(void);
		void initialize(ControlsHolder^ holder);

		void visualize(structures::Table<data::KeyType, data::DataType>* table);
		void refreshItem(ListViewItem^ item, data::KeyType key, data::DataType data);
	protected:
		~PanelPresentTable();
	private:
		ListViewItem^ selectedItem_;
		ControlsHolder^ controls_;
	private: System::Windows::Forms::ListView^  lviewTable;
	private: System::Windows::Forms::ColumnHeader^  columnKey;
	private: System::Windows::Forms::ColumnHeader^  columnKeyBits;
	private: System::Windows::Forms::ColumnHeader^  columnData;
	private: System::Windows::Forms::ColumnHeader^  columnDataBits;

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
			this->lviewTable = (gcnew System::Windows::Forms::ListView());
			this->columnKey = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnKeyBits = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnData = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnDataBits = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// lviewTable
			// 
			this->lviewTable->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnKey, this->columnKeyBits,
					this->columnData, this->columnDataBits
			});
			this->lviewTable->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewTable->FullRowSelect = true;
			this->lviewTable->GridLines = true;
			this->lviewTable->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewTable->HideSelection = false;
			this->lviewTable->Location = System::Drawing::Point(0, 0);
			this->lviewTable->MultiSelect = false;
			this->lviewTable->Name = L"lviewTable";
			this->lviewTable->Size = System::Drawing::Size(554, 387);
			this->lviewTable->TabIndex = 4;
			this->lviewTable->UseCompatibleStateImageBehavior = false;
			this->lviewTable->View = System::Windows::Forms::View::Details;
			this->lviewTable->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelPresentTable::lviewTable_ItemSelectionChanged);
			// 
			// columnKey
			// 
			this->columnKey->Text = L"Key";
			// 
			// columnKeyBits
			// 
			this->columnKeyBits->Text = L"Key bits";
			this->columnKeyBits->Width = 300;
			// 
			// columnData
			// 
			this->columnData->Text = L"Data";
			// 
			// columnDataBits
			// 
			this->columnDataBits->Text = L"Data bits";
			this->columnDataBits->Width = 300;
			// 
			// PanelPresentTable
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->lviewTable);
			this->Name = L"PanelPresentTable";
			this->Size = System::Drawing::Size(554, 387);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void lviewTable_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
		if (e->IsSelected)
		{
			selectedItem_ = e->Item;
		}
		else
		{
			selectedItem_ = nullptr;
		}

		controls_->enableControls();
	}

	};

	PanelPresentTable::PanelPresentTable(void) :
		selectedItem_(nullptr),
		controls_(nullptr)
	{
		InitializeComponent();
	}

	inline void PanelPresentTable::initialize(ControlsHolder ^ holder)
	{
		controls_ = holder;
	}


	PanelPresentTable::~PanelPresentTable()
	{
		if (components)
		{
			delete components;
		}
	}

	void PanelPresentTable::visualize(structures::Table<data::KeyType, data::DataType>* table)
	{
		lviewTable->Items->Clear();

		for (structures::TableItem<data::KeyType, data::DataType>* tableItem: *Table)
		{
			ListViewItem^ item = gcnew ListViewItem();
			lviewTable->Items->Add(item);
			refreshItem(item, tableItem->getKey(), tableItem->accessData());
		}

		selectedItem_ = nullptr;
	}

	inline void PanelPresentTable::refreshItem(ListViewItem ^ item, data::KeyType key, data::DataType data)
	{
		if (item == nullptr)
			return;

		// key
		item->Text = Convert::ToString(key);

		// key bits
		if (item->SubItems->Count < 2)
			item->SubItems->Add("");
		item->SubItems[1]->Text = UIRoutines::convertMemoryToString(&key, sizeof(data::KeyType));

		// data
		if (item->SubItems->Count < 3)
			item->SubItems->Add("");
		item->SubItems[2]->Text = Convert::ToString(data);

		// data bits
		if (item->SubItems->Count < 4)
			item->SubItems->Add("");
		item->SubItems[3]->Text = UIRoutines::convertMemoryToString(&data, sizeof(data::DataType));
	}
}
