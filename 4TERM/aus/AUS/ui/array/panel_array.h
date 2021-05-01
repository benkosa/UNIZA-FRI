#pragma once

#include "../../structures/array/array.h"
#include "../controls/controls.h"
#include "../controls/controls_array.h"
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

	public ref class PanelPresentArray : public UserControl
	{
	public:
		property ListViewItem^ SelectedItem
		{
			ListViewItem^ get() { return selectedItem_; };
		}

		property structures::Array<data::DataType>* Array
		{
			structures::Array<data::DataType>* get() { return dynamic_cast<structures::Array<data::DataType>*>(controls_->Structure); };
		}

		PanelPresentArray(void);
		void initialize(ControlsHolder^ holder);

		void visualize(structures::Array<data::DataType>* array);
		void refreshItem(ListViewItem^ item);
		void refreshSelectedItem();
	protected:
		~PanelPresentArray();
	private:
		ListViewItem^ selectedItem_;
		ControlsHolder^ controls_;


	private: System::Windows::Forms::ListView^  lviewArray;
	private: System::Windows::Forms::ColumnHeader^  columnIndex;
	private: System::Windows::Forms::ColumnHeader^  columnData;
	private: System::Windows::Forms::ColumnHeader^  columnBits;


	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lviewArray = (gcnew System::Windows::Forms::ListView());
			this->columnIndex = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnData = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnBits = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// lviewArray
			// 
			this->lviewArray->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewArray->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnIndex, this->columnData,
					this->columnBits
			});
			this->lviewArray->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewArray->FullRowSelect = true;
			this->lviewArray->GridLines = true;
			this->lviewArray->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewArray->HideSelection = false;
			this->lviewArray->Location = System::Drawing::Point(0, 0);
			this->lviewArray->MultiSelect = false;
			this->lviewArray->Name = L"lviewArray";
			this->lviewArray->Size = System::Drawing::Size(424, 215);
			this->lviewArray->TabIndex = 2;
			this->lviewArray->UseCompatibleStateImageBehavior = false;
			this->lviewArray->View = System::Windows::Forms::View::Details;
			this->lviewArray->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelPresentArray::lviewArray_ItemSelectionChanged);
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
			// PanelPresentArray
			// 
			this->Controls->Add(this->lviewArray);
			this->Name = L"PanelPresentArray";
			this->Size = System::Drawing::Size(424, 215);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void lviewArray_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e)
	{
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

	PanelPresentArray::PanelPresentArray(void) :
		selectedItem_(nullptr),
		controls_(nullptr)
	{
		InitializeComponent();
	}

	inline void PanelPresentArray::initialize(ControlsHolder ^ holder)
	{
		controls_ = holder;
	}


	PanelPresentArray::~PanelPresentArray()
	{
		if (components)
		{
			delete components;
		}
	}

	void PanelPresentArray::visualize(structures::Array<data::DataType>* array)
	{
		lviewArray->Items->Clear();

		for (int i = 0; (size_t)i < array->size(); i++)
		{
			ListViewItem^ item = gcnew ListViewItem();
			lviewArray->Items->Add(item);
			refreshItem(item);
		}
	}

	inline void PanelPresentArray::refreshItem(ListViewItem ^ item)
	{
		if (item == nullptr)
			return;

		// index
		item->Text = Convert::ToString(item->Index);

		// data
		if (item->SubItems->Count < 2)
			item->SubItems->Add("");
		item->SubItems[1]->Text = Convert::ToString((*Array)[item->Index]);
		
		// bits
		if (item->SubItems->Count < 3)
			item->SubItems->Add("");
		item->SubItems[2]->Text = UIRoutines::convertMemoryToString(&(*Array)[item->Index], sizeof(data::DataType));
	}

	inline void PanelPresentArray::refreshSelectedItem()
	{
		refreshItem(SelectedItem);
	}

}
