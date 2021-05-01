#pragma once

#include "../../structures/list/list.h"
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


namespace ui {

	public ref class PanelPresentList : public UserControl
	{
	public:
		property ListViewItem^ SelectedItem
		{
			ListViewItem^ get() { return selectedItem_; };
		}

		property structures::List<data::DataType>* List
		{
			structures::List<data::DataType>* get() { return dynamic_cast<structures::List<data::DataType>*>(controls->Structure); };
		}

		PanelPresentList(void);
		void initialize(ControlsHolder^ holder);

		void visualize(structures::List<data::DataType>* list);
		void refreshItem(ListViewItem^ item);
		void refreshItem(ListViewItem^ item, data::DataType data);
		void refreshSelectedItem();
	protected:
		~PanelPresentList();
	private:
		ListViewItem^ selectedItem_;
		ControlsHolder^ controls;
	private: System::Windows::Forms::ListView^  lviewList;
	private: System::Windows::Forms::ColumnHeader^  columnIndex;
	private: System::Windows::Forms::ColumnHeader^  columnData;
	private: System::Windows::Forms::ColumnHeader^  columnBits;

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
			this->lviewList = (gcnew System::Windows::Forms::ListView());
			this->columnIndex = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnData = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnBits = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// lviewList
			// 
			this->lviewList->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnIndex, this->columnData,
					this->columnBits
			});
			this->lviewList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewList->FullRowSelect = true;
			this->lviewList->GridLines = true;
			this->lviewList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewList->HideSelection = false;
			this->lviewList->Location = System::Drawing::Point(0, 0);
			this->lviewList->MultiSelect = false;
			this->lviewList->Name = L"lviewList";
			this->lviewList->Size = System::Drawing::Size(443, 281);
			this->lviewList->TabIndex = 3;
			this->lviewList->UseCompatibleStateImageBehavior = false;
			this->lviewList->View = System::Windows::Forms::View::Details;
			this->lviewList->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelPresentList::lviewList_ItemSelectionChanged);
			// 
			// columnIndex
			// 
			this->columnIndex->Text = L"Index";
			// 
			// columnData
			// 
			this->columnData->Text = L"Data";
			// 
			// columnBits
			// 
			this->columnBits->Text = L"Bits";
			this->columnBits->Width = 300;
			// 
			// PanelPresentList
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->lviewList);
			this->Name = L"PanelPresentList";
			this->Size = System::Drawing::Size(443, 281);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void lviewList_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
		if (e->IsSelected)
		{
			selectedItem_ = e->Item;
		}
		else
		{
			selectedItem_ = nullptr;
		}

		controls->enableControls();
	}
	
};

	PanelPresentList::PanelPresentList(void) :
		selectedItem_(nullptr),
		controls(nullptr)
	{
		InitializeComponent();
	}

	inline void PanelPresentList::initialize(ControlsHolder ^ holder)
	{
		controls = holder;
	}


	PanelPresentList::~PanelPresentList()
	{
		if (components)
		{
			delete components;
		}
	}

	void PanelPresentList::visualize(structures::List<data::DataType>* list)
	{
		lviewList->Items->Clear();

		for (data::DataType data : *List)
		{
			ListViewItem^ item = gcnew ListViewItem();
			lviewList->Items->Add(item);
			refreshItem(item, data);
		}

		selectedItem_ = nullptr;
	}

	inline void PanelPresentList::refreshItem(ListViewItem ^ item)
	{
		if (item == nullptr)
			return;

		refreshItem(item, (*List)[item->Index]);
	}

	inline void PanelPresentList::refreshItem(ListViewItem ^ item, data::DataType data)
	{
		if (item == nullptr)
			return;

		// index
		item->Text = Convert::ToString(item->Index);

		// data
		if (item->SubItems->Count < 2)
			item->SubItems->Add("");
		item->SubItems[1]->Text = System::Convert::ToString(data);

		// bits
		if (item->SubItems->Count < 3)
			item->SubItems->Add("");
		item->SubItems[2]->Text = UIRoutines::convertMemoryToString(&data, sizeof(data::DataType));
	}

	inline void PanelPresentList::refreshSelectedItem()
	{
		refreshItem(SelectedItem);
	}

}
