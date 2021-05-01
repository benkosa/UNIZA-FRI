#pragma once

#include "../structures/structure.h"
#include "../structures/ds_structure_types.h"
#include "../structures/ds_structure_factory.h"
#include "ui_routines.h"
#include "../ui/controls/controls.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace ui {

	public ref class PanelStructures : public UserControl
	{

	private:
		/// <summary> Obalovaci objekt pre strukturu. </summary>
		ref class StructureItemData
		{
		public:
			property structures::Structure* Structure 
			{
				structures::Structure* get() { return structure_; }
				void set(structures::Structure* structure) { structure_ = structure; }
			}

			StructureItemData(structures::Structure* structure) : structure_(structure) {}
		private:
			/// <summary> Struktura. </summary>
			structures::Structure* structure_;
		};

	public:
		property structures::Structure* StructureByItem[ListViewItem^]
		{
			structures::Structure* get(ListViewItem^ item) { return item != nullptr ? dynamic_cast<StructureItemData^>(item->Tag)->Structure : nullptr; }
		}

		property structures::Structure* SelectedStructure 
		{ 
			structures::Structure* get() { return lviewStructures->SelectedItems->Count > 0 ? StructureByItem[lviewStructures->SelectedItems[0]] : nullptr;	}
		}

		property structures::StructureADS SelectedADS
		{
			structures::StructureADS get() { return adtManager_->getADSFactoryByIndex(cbxADS->SelectedIndex)->getADS(); };
		}

		/// <summary> Vytvori a vlozi panel pre ovladanie struktur do daneho komponentu. </summary>
		/// <param name = "owner"> Vlastnik panela so strukturami. Mal by to byt iny prazdny panel. </param>
		/// <param name = "adt"> ADT struktur, ktory bude tento panel ovladat. </param>
		/// <returns> Vytvoreny panel pre ovladanie struktur. </returns>
		static PanelStructures^ createAndIntegratePanelStructures(Panel^ owner, structures::StructureADT adt);
	protected:
		/// <summary> Chraneny konstruktor umoznuje vytvarat instance iba pomocou metody createAndIntegratePanelStructures. </summary>
		PanelStructures(void);
		/// <summary> Inicializuje panel pre ovladanie konkretneho ADT. </summary>
		/// <param name = "adt"> ADT struktur, ktory bude tento panel ovladat. </param>
		/// <remarks> Je automaticky volana z metody createAndIntegratePanelStructures. </remarks>
		void initialize(const structures::StructureADT adt);
		/// <summary> Destruktor. </summary>
		~PanelStructures();

	private:
		/// <summary> ADTFactoryManager, s ktorym panel spolupracuje. </summary> 
		structures::ADTFactoryManager* adtManager_;
	private: System::Windows::Forms::Panel^  pnlStructure;

			 /// <summary> Ovladanie rozhrania. </summary>
		ControlsHolder^ control_;

		/// <summary> Aktualizuje ovladacie prvky. </summary>
		void updateControls();
		/// <summary> Vytvori novu strukturu podla aktualneho stavu rozhrania. </summary>
		/// <param name = "cloneIndex"> Ak je aspon 0, tak novu strukturu spravi ako klon struktury na danom indexe. </param>
		/// <param name = "selectIt"> Ak je true, vytvorena struktura bude vybrana. </param>
		void createStructure(int cloneIndex, bool selectIt);

	private: System::Windows::Forms::ColumnHeader^  colStructures;
	private: System::Windows::Forms::Button^  btnClone;
	private: System::Windows::Forms::FlowLayoutPanel^  pnlStructures;
	private: System::Windows::Forms::Button^  btnNew;
	private: System::Windows::Forms::Button^  btnDelete;
	private: System::Windows::Forms::ListView^  lviewStructures;
	private: System::Windows::Forms::Splitter^  splitterStructures;

	private: System::Windows::Forms::ComboBox^  cbxADS;

	private:  
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pnlStructures = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->cbxADS = (gcnew System::Windows::Forms::ComboBox());
			this->btnNew = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->btnClone = (gcnew System::Windows::Forms::Button());
			this->lviewStructures = (gcnew System::Windows::Forms::ListView());
			this->colStructures = (gcnew System::Windows::Forms::ColumnHeader());
			this->splitterStructures = (gcnew System::Windows::Forms::Splitter());
			this->pnlStructure = (gcnew System::Windows::Forms::Panel());
			this->pnlStructures->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlStructures
			// 
			this->pnlStructures->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
				static_cast<System::Int32>(static_cast<System::Byte>(111)));
			this->pnlStructures->Controls->Add(this->cbxADS);
			this->pnlStructures->Controls->Add(this->btnNew);
			this->pnlStructures->Controls->Add(this->btnDelete);
			this->pnlStructures->Controls->Add(this->btnClone);
			this->pnlStructures->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlStructures->Location = System::Drawing::Point(0, 0);
			this->pnlStructures->Name = L"pnlStructures";
			this->pnlStructures->Size = System::Drawing::Size(595, 30);
			this->pnlStructures->TabIndex = 0;
			// 
			// cbxADS
			// 
			this->cbxADS->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbxADS->FormattingEnabled = true;
			this->cbxADS->Location = System::Drawing::Point(3, 3);
			this->cbxADS->Name = L"cbxADS";
			this->cbxADS->Size = System::Drawing::Size(200, 21);
			this->cbxADS->TabIndex = 3;
			// 
			// btnNew
			// 
			this->btnNew->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btnNew->Location = System::Drawing::Point(209, 3);
			this->btnNew->Name = L"btnNew";
			this->btnNew->Size = System::Drawing::Size(100, 23);
			this->btnNew->TabIndex = 0;
			this->btnNew->Text = L"New";
			this->btnNew->UseVisualStyleBackColor = true;
			this->btnNew->Click += gcnew System::EventHandler(this, &PanelStructures::btnNew_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->Enabled = false;
			this->btnDelete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btnDelete->Location = System::Drawing::Point(315, 3);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(100, 23);
			this->btnDelete->TabIndex = 1;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &PanelStructures::btnDelete_Click);
			// 
			// btnClone
			// 
			this->btnClone->Enabled = false;
			this->btnClone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btnClone->Location = System::Drawing::Point(421, 3);
			this->btnClone->Name = L"btnClone";
			this->btnClone->Size = System::Drawing::Size(100, 23);
			this->btnClone->TabIndex = 2;
			this->btnClone->Text = L"Clone";
			this->btnClone->UseVisualStyleBackColor = true;
			this->btnClone->Click += gcnew System::EventHandler(this, &PanelStructures::btnClone_Click);
			// 
			// lviewStructures
			// 
			this->lviewStructures->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewStructures->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->colStructures });
			this->lviewStructures->Dock = System::Windows::Forms::DockStyle::Left;
			this->lviewStructures->FullRowSelect = true;
			this->lviewStructures->GridLines = true;
			this->lviewStructures->HideSelection = false;
			this->lviewStructures->Location = System::Drawing::Point(0, 30);
			this->lviewStructures->MultiSelect = false;
			this->lviewStructures->Name = L"lviewStructures";
			this->lviewStructures->Size = System::Drawing::Size(250, 357);
			this->lviewStructures->TabIndex = 1;
			this->lviewStructures->UseCompatibleStateImageBehavior = false;
			this->lviewStructures->View = System::Windows::Forms::View::Details;
			this->lviewStructures->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelStructures::lviewStructures_ItemSelectionChanged);
			// 
			// colStructures
			// 
			this->colStructures->Text = L"Structures";
			this->colStructures->Width = 228;
			// 
			// splitterStructures
			// 
			this->splitterStructures->Location = System::Drawing::Point(250, 30);
			this->splitterStructures->Name = L"splitterStructures";
			this->splitterStructures->Size = System::Drawing::Size(3, 357);
			this->splitterStructures->TabIndex = 2;
			this->splitterStructures->TabStop = false;
			// 
			// pnlStructure
			// 
			this->pnlStructure->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlStructure->Location = System::Drawing::Point(253, 30);
			this->pnlStructure->Name = L"pnlStructure";
			this->pnlStructure->Size = System::Drawing::Size(342, 357);
			this->pnlStructure->TabIndex = 3;
			// 
			// PanelStructures
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->pnlStructure);
			this->Controls->Add(this->splitterStructures);
			this->Controls->Add(this->lviewStructures);
			this->Controls->Add(this->pnlStructures);
			this->Name = L"PanelStructures";
			this->Size = System::Drawing::Size(595, 387);
			this->pnlStructures->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: System::Void btnNew_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			createStructure(-1, true);
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
		}
		catch (System::Exception^ ex)
		{
			log::Logger::getInstance()->logError(ex->Message);
		}
	}
	
	private: System::Void btnDelete_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			ListView::SelectedListViewItemCollection^ selected = lviewStructures->SelectedItems;

			while (selected->Count > 0)
			{
				ListViewItem^ item = selected[selected->Count - 1];
				adtManager_->removeStructure(item->Index);
				lviewStructures->Items->Remove(item);
			}

			control_->Structure = SelectedStructure;
			updateControls();
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
		}
		catch (System::Exception^ ex)
		{
			log::Logger::getInstance()->logError(ex->Message);
		}
	}

	private: System::Void btnClone_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			ListView::SelectedListViewItemCollection^ selected = lviewStructures->SelectedItems;

			for (int i = 0; i < selected->Count; i++)
			{
				ListViewItem^ item = selected[i];
				createStructure(item->Index, false);
			}

			control_->Structure = SelectedStructure;
			updateControls();
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
		}
		catch (System::Exception^ ex)
		{
			log::Logger::getInstance()->logError(ex->Message);
		}
	}

	private: System::Void lviewStructures_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e)
	{
		control_->Structure = SelectedStructure;
		updateControls();
	}
};

PanelStructures::PanelStructures(void) :
	adtManager_(nullptr),
	control_(nullptr)
{
	InitializeComponent();
}

inline PanelStructures ^ PanelStructures::createAndIntegratePanelStructures(Panel ^ owner, structures::StructureADT adt)
{
	PanelStructures ^ result = gcnew PanelStructures();
	owner->Controls->Add(result);
	result->Dock = DockStyle::Fill;
	result->initialize(adt);
	result->updateControls();
	return result;
}

PanelStructures::~PanelStructures()
{
	if (components)
	{
		delete components;
	}
}

void PanelStructures::initialize(const structures::StructureADT adt)
{
	adtManager_ = structures::StructureFactory::getInstance()->getADTManagerByType(adt);
	bool existADS = false;

	if (adtManager_ != nullptr)
	{
		for (int i = 0; i < static_cast<int>(adtManager_->factoriesSize()); i++)
		{
			structures::ADSFactory* adsFactory = adtManager_->getADSFactoryByIndex(i);
			if (adsFactory != nullptr)
			{
				String^ str = gcnew String(UIRoutines::convertStructureADSToStr(adsFactory->getADS()).c_str());
				cbxADS->Items->Add(str);
				existADS = true;
			}
		}
	}

	if (existADS)
	{
		control_ = ControlsDirector::getInstance()->createControlsHolderInstance(adt, pnlStructure);
		cbxADS->SelectedIndex = 0;
	}
	else
	{
		pnlStructures->BackColor = Color::Salmon;
	}

	cbxADS->Enabled = existADS;
	btnNew->Enabled = existADS;
}

void PanelStructures::updateControls()
{
	bool selected = SelectedStructure != nullptr;

	btnDelete->Enabled = selected;
	btnClone->Enabled = selected;

	if (selected)
	{
		if (control_ != nullptr)
		{
			control_->show();
		}
	}
	else
	{
		if (control_ != nullptr)
		{
			control_->hide();
		}
	}
}

inline void PanelStructures::createStructure(int cloneIndex, bool selectIt)
{

	structures::Structure* structure;
	String^ caption = "";

	if (cloneIndex >= 0)
	{
		structure = adtManager_->cloneStructureAtIndex(cloneIndex);
		caption = "Copy of " + lviewStructures->SelectedItems[0]->Text;
	}
	else
	{
		structure = adtManager_->getStructureInstance(SelectedADS);
		String^ adsStr = gcnew String(UIRoutines::convertStructureADSToStr(SelectedADS).c_str());
		String^ numStr = gcnew String(UIRoutines::convertIntToStr(static_cast<int>(adtManager_->getADSFactoryByType(SelectedADS)->size())).c_str());
		caption = adsStr + numStr;
	}

	ListViewItem^ item = gcnew ListViewItem(caption);
	lviewStructures->Items->Add(item);

	item->Tag = gcnew StructureItemData(structure);

	if (selectIt)
	{
		item->Selected = true;
		control_->Structure = SelectedStructure;
		updateControls();
	}
}

}
