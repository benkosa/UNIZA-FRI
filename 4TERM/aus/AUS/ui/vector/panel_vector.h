#pragma once

#include "../../structures/vector/vector.h"
#include "../controls/controls.h"
#include "../controls/controls_vector.h"
#include "../ui_routines.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace ui {

	public ref class PanelPresentVector : public UserControl
	{
	public:
		property ListViewItem^ SelectedItem
		{
			ListViewItem^ get() { return selectedItem_; };
		}

		property structures::Vector* Vector
		{
			structures::Vector* get() { return dynamic_cast<structures::Vector*>(controls_->Structure); };
		}

		PanelPresentVector(void);
		void initialize(ControlsHolder^ holder);

		void visualize(structures::Vector* vector);
		void refreshItem(ListViewItem^ item);
		void refreshSelectedItem();
	protected:
		~PanelPresentVector();
	private:
		ListViewItem^ selectedItem_;
		ControlsHolder^ controls_;

	private: System::Windows::Forms::ListView^  lviewVector;

	private: System::Windows::Forms::ColumnHeader^  columnByte;
	private: System::Windows::Forms::ColumnHeader^  columnBits;
	private: System::Windows::Forms::ColumnHeader^  columnIndex;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) 
		{
			this->lviewVector = (gcnew System::Windows::Forms::ListView());
			this->columnIndex = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnByte = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnBits = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// lviewVector
			// 
			this->lviewVector->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewVector->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnIndex, this->columnByte,
					this->columnBits
			});
			this->lviewVector->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewVector->FullRowSelect = true;
			this->lviewVector->GridLines = true;
			this->lviewVector->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewVector->HideSelection = false;
			this->lviewVector->Location = System::Drawing::Point(0, 0);
			this->lviewVector->MultiSelect = false;
			this->lviewVector->Name = L"lviewVector";
			this->lviewVector->Size = System::Drawing::Size(433, 264);
			this->lviewVector->TabIndex = 1;
			this->lviewVector->UseCompatibleStateImageBehavior = false;
			this->lviewVector->View = System::Windows::Forms::View::Details;
			this->lviewVector->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelPresentVector::lviewVector_ItemSelectionChanged);
			// 
			// columnIndex
			// 
			this->columnIndex->Text = L"Index";
			// 
			// columnByte
			// 
			this->columnByte->Text = L"Byte";
			// 
			// columnBits
			// 
			this->columnBits->Text = L"Bits";
			this->columnBits->Width = 300;
			// 
			// PanelPresentVector
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->lviewVector);
			this->Name = L"PanelPresentVector";
			this->Size = System::Drawing::Size(433, 264);
			this->ResumeLayout(false);

		}
#pragma endregion
  
  private: System::Void lviewVector_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e)
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

PanelPresentVector::PanelPresentVector(void) :
	selectedItem_(nullptr),
	controls_(nullptr)
{
	InitializeComponent();
}

inline void PanelPresentVector::initialize(ControlsHolder ^ holder)
{
	controls_ = holder;
}

PanelPresentVector::~PanelPresentVector()
{
	if (components)
	{
		delete components;
	}
}

inline void PanelPresentVector::visualize(structures::Vector* vector)
{
	lviewVector->Items->Clear();

    for (int i = 0; (size_t)i < vector->size(); i++)
	{
		ListViewItem^ item = gcnew ListViewItem();
		lviewVector->Items->Add(item);
		refreshItem(item);
	}
}

inline void PanelPresentVector::refreshItem(ListViewItem ^ item)
{
	if (item == nullptr)
		return;

	// index
	item->Text = Convert::ToString(item->Index);

	// byte
	if (item->SubItems->Count < 2)
		item->SubItems->Add("");
	item->SubItems[1]->Text = Convert::ToString(Convert::ToInt32((*Vector)[item->Index]));

	// bits
	if (item->SubItems->Count < 3)
		item->SubItems->Add("");
	item->SubItems[2]->Text = UIRoutines::convertMemoryToString(&(*Vector)[item->Index], sizeof(structures::byte));
}

inline void PanelPresentVector::refreshSelectedItem()
{
	refreshItem(SelectedItem);
}

}
