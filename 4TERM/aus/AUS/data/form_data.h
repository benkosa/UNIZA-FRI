#pragma once

#include "data_types.h"
#include "../structures/memory_routines.h"
#include "../ui/ui_routines.h"
#include "../ui/logger/ui_logger.h"

namespace data {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ui::log;

	public ref class FormData : public Form
	{
	private:
		static const Color^ clrEDIT = ui::UIRoutines::createRGBColor(41, 57, 85);  // modra
		static const Color^ clrVIEW = ui::UIRoutines::createRGBColor(255, 242, 157); // zlta

		static const int frmHEIGHT_SIMPLE = 105;
		static const int frmHEIGHT_BYTES = 160;
	private: System::Windows::Forms::Button^  btnBytes;
			 static const int frmHEIGHT_BYTE = 20;
	public:
		enum class FormType
		{
			dftBYTE,
			dftDATA,
			dftPRIORITY,
			dftKEY,
			dftVERTEX_ID,
			dftINT,
			dftDOUBLE,
			dftSTRING
		};

		enum class ModalResult
		{
			mrOK,
			mrCANCEL,
			mrNONE
		};

		enum class FormMode
		{
			fmVIEW,
			fmEDIT
		};

		FormData(const FormType formType, const FormMode formMode, String^ caption, bool showBytes);
		~FormData();

		void setData(void* data, size_t size);

	private:
		void* dataPtr_;
		size_t dataSize_;
		int updates_;
		bool showBytes_;

		array<System::Windows::Forms::CheckBox^>^ checkboxes_;
		ListViewItem^ selectedItem_;

		structures::byte* selectedByte();

		void presentData(bool refreshTxt);
		void refreshItem(ListViewItem^ item);
		void refreshData();

		void checkedBit(int bit);

		void enableControls();
		void adjustHeight();
		bool areEnabledBitOperation();

		void beginUpdate();
		void endUpdate();
		bool isUpdating();

		FormType formType_;
		FormMode formMode_;
	private: System::Windows::Forms::CheckBox^  chbBit7;
	private: System::Windows::Forms::ListView^  lviewBytes;
	private: System::Windows::Forms::ColumnHeader^  colByte;
	private: System::Windows::Forms::ColumnHeader^  colBit7;
	private: System::Windows::Forms::ColumnHeader^  colBit6;
	private: System::Windows::Forms::ColumnHeader^  colBit5;
	private: System::Windows::Forms::ColumnHeader^  colBit4;
	private: System::Windows::Forms::ColumnHeader^  colBit3;
	private: System::Windows::Forms::ColumnHeader^  colBit2;
	private: System::Windows::Forms::ColumnHeader^  colBit1;
	private: System::Windows::Forms::ColumnHeader^  colBit0;
	private: System::Windows::Forms::CheckBox^  chbBit6;
	private: System::Windows::Forms::FlowLayoutPanel^  pnlBytes;
	private: System::Windows::Forms::Button^  btnByteSet;
	private: System::Windows::Forms::Button^  btnByteReset;
	private: System::Windows::Forms::Button^  btnByteXOR;
	private: System::Windows::Forms::Button^  btnByteSHL;
	private: System::Windows::Forms::Button^  btnByteSHR;

	private: System::Windows::Forms::CheckBox^  chbBit5;
	private: System::Windows::Forms::CheckBox^  chbBit0;
	private: System::Windows::Forms::CheckBox^  chbBit4;
	private: System::Windows::Forms::CheckBox^  chbBit1;
	private: System::Windows::Forms::CheckBox^  chbBit3;
	private: System::Windows::Forms::CheckBox^  chbBit2;
	private: System::Windows::Forms::Panel^  pnlTop;
	private: System::Windows::Forms::Button^  btnOK;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::TextBox^  txtValue;
	private: System::Windows::Forms::Label^  lblValue;
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
			this->txtValue = (gcnew System::Windows::Forms::TextBox());
			this->lblValue = (gcnew System::Windows::Forms::Label());
			this->pnlTop = (gcnew System::Windows::Forms::Panel());
			this->btnBytes = (gcnew System::Windows::Forms::Button());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->lviewBytes = (gcnew System::Windows::Forms::ListView());
			this->colByte = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit7 = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBit0 = (gcnew System::Windows::Forms::ColumnHeader());
			this->pnlBytes = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btnByteSet = (gcnew System::Windows::Forms::Button());
			this->btnByteReset = (gcnew System::Windows::Forms::Button());
			this->btnByteXOR = (gcnew System::Windows::Forms::Button());
			this->btnByteSHL = (gcnew System::Windows::Forms::Button());
			this->btnByteSHR = (gcnew System::Windows::Forms::Button());
			this->chbBit7 = (gcnew System::Windows::Forms::CheckBox());
			this->chbBit6 = (gcnew System::Windows::Forms::CheckBox());
			this->chbBit5 = (gcnew System::Windows::Forms::CheckBox());
			this->chbBit4 = (gcnew System::Windows::Forms::CheckBox());
			this->chbBit3 = (gcnew System::Windows::Forms::CheckBox());
			this->chbBit2 = (gcnew System::Windows::Forms::CheckBox());
			this->chbBit1 = (gcnew System::Windows::Forms::CheckBox());
			this->chbBit0 = (gcnew System::Windows::Forms::CheckBox());
			this->pnlTop->SuspendLayout();
			this->pnlBytes->SuspendLayout();
			this->SuspendLayout();
			// 
			// txtValue
			// 
			this->txtValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtValue->Location = System::Drawing::Point(52, 36);
			this->txtValue->Name = L"txtValue";
			this->txtValue->Size = System::Drawing::Size(363, 20);
			this->txtValue->TabIndex = 1;
			this->txtValue->TextChanged += gcnew System::EventHandler(this, &FormData::txtData_TextChanged);
			this->txtValue->Enter += gcnew System::EventHandler(this, &FormData::txtValue_Enter);
			// 
			// lblValue
			// 
			this->lblValue->AutoSize = true;
			this->lblValue->Location = System::Drawing::Point(12, 39);
			this->lblValue->Name = L"lblValue";
			this->lblValue->Size = System::Drawing::Size(34, 13);
			this->lblValue->TabIndex = 0;
			this->lblValue->Text = L"Value";
			// 
			// pnlTop
			// 
			this->pnlTop->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(41)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->pnlTop->Controls->Add(this->btnBytes);
			this->pnlTop->Controls->Add(this->btnOK);
			this->pnlTop->Controls->Add(this->btnCancel);
			this->pnlTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlTop->Location = System::Drawing::Point(0, 0);
			this->pnlTop->Name = L"pnlTop";
			this->pnlTop->Size = System::Drawing::Size(415, 30);
			this->pnlTop->TabIndex = 9;
			// 
			// btnBytes
			// 
			this->btnBytes->Location = System::Drawing::Point(337, 3);
			this->btnBytes->Name = L"btnBytes";
			this->btnBytes->Size = System::Drawing::Size(75, 23);
			this->btnBytes->TabIndex = 2;
			this->btnBytes->Text = L"Bytes";
			this->btnBytes->UseVisualStyleBackColor = true;
			this->btnBytes->Click += gcnew System::EventHandler(this, &FormData::btnBytes_Click);
			// 
			// btnOK
			// 
			this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btnOK->ForeColor = System::Drawing::SystemColors::ControlText;
			this->btnOK->Location = System::Drawing::Point(3, 3);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(75, 23);
			this->btnOK->TabIndex = 0;
			this->btnOK->Text = L"OK";
			this->btnOK->UseVisualStyleBackColor = true;
			// 
			// btnCancel
			// 
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->ForeColor = System::Drawing::SystemColors::ControlText;
			this->btnCancel->Location = System::Drawing::Point(84, 3);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(75, 23);
			this->btnCancel->TabIndex = 1;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			// 
			// lviewBytes
			// 
			this->lviewBytes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lviewBytes->BackColor = System::Drawing::SystemColors::Window;
			this->lviewBytes->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(9) {
				this->colByte, this->colBit7,
					this->colBit6, this->colBit5, this->colBit4, this->colBit3, this->colBit2, this->colBit1, this->colBit0
			});
			this->lviewBytes->FullRowSelect = true;
			this->lviewBytes->GridLines = true;
			this->lviewBytes->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewBytes->HideSelection = false;
			this->lviewBytes->Location = System::Drawing::Point(0, 94);
			this->lviewBytes->MultiSelect = false;
			this->lviewBytes->Name = L"lviewBytes";
			this->lviewBytes->Size = System::Drawing::Size(415, 56);
			this->lviewBytes->TabIndex = 20;
			this->lviewBytes->UseCompatibleStateImageBehavior = false;
			this->lviewBytes->View = System::Windows::Forms::View::Details;
			this->lviewBytes->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &FormData::lviewBytes_ItemSelectionChanged);
			// 
			// colByte
			// 
			this->colByte->Text = L"Byte";
			this->colByte->Width = 40;
			// 
			// colBit7
			// 
			this->colBit7->Text = L"Bit 7";
			this->colBit7->Width = 35;
			// 
			// colBit6
			// 
			this->colBit6->Text = L"Bit 6";
			this->colBit6->Width = 35;
			// 
			// colBit5
			// 
			this->colBit5->Text = L"Bit 5";
			this->colBit5->Width = 35;
			// 
			// colBit4
			// 
			this->colBit4->Text = L"Bit 4";
			this->colBit4->Width = 35;
			// 
			// colBit3
			// 
			this->colBit3->Text = L"Bit 3";
			this->colBit3->Width = 35;
			// 
			// colBit2
			// 
			this->colBit2->Text = L"Bit 2";
			this->colBit2->Width = 35;
			// 
			// colBit1
			// 
			this->colBit1->Text = L"Bit 1";
			this->colBit1->Width = 35;
			// 
			// colBit0
			// 
			this->colBit0->Text = L"Bit 0";
			this->colBit0->Width = 35;
			// 
			// pnlBytes
			// 
			this->pnlBytes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pnlBytes->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(41)), static_cast<System::Int32>(static_cast<System::Byte>(57)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->pnlBytes->Controls->Add(this->btnByteSet);
			this->pnlBytes->Controls->Add(this->btnByteReset);
			this->pnlBytes->Controls->Add(this->btnByteXOR);
			this->pnlBytes->Controls->Add(this->btnByteSHL);
			this->pnlBytes->Controls->Add(this->btnByteSHR);
			this->pnlBytes->Location = System::Drawing::Point(0, 62);
			this->pnlBytes->Name = L"pnlBytes";
			this->pnlBytes->Size = System::Drawing::Size(415, 30);
			this->pnlBytes->TabIndex = 19;
			// 
			// btnByteSet
			// 
			this->btnByteSet->ForeColor = System::Drawing::SystemColors::ControlText;
			this->btnByteSet->Location = System::Drawing::Point(3, 3);
			this->btnByteSet->Name = L"btnByteSet";
			this->btnByteSet->Size = System::Drawing::Size(75, 23);
			this->btnByteSet->TabIndex = 0;
			this->btnByteSet->Text = L"Set byte";
			this->btnByteSet->UseVisualStyleBackColor = true;
			this->btnByteSet->Click += gcnew System::EventHandler(this, &FormData::btnByteSet_Click);
			// 
			// btnByteReset
			// 
			this->btnByteReset->ForeColor = System::Drawing::SystemColors::ControlText;
			this->btnByteReset->Location = System::Drawing::Point(84, 3);
			this->btnByteReset->Name = L"btnByteReset";
			this->btnByteReset->Size = System::Drawing::Size(75, 23);
			this->btnByteReset->TabIndex = 1;
			this->btnByteReset->Text = L"Reset byte";
			this->btnByteReset->UseVisualStyleBackColor = true;
			this->btnByteReset->Click += gcnew System::EventHandler(this, &FormData::btnByteReset_Click);
			// 
			// btnByteXOR
			// 
			this->btnByteXOR->ForeColor = System::Drawing::SystemColors::ControlText;
			this->btnByteXOR->Location = System::Drawing::Point(165, 3);
			this->btnByteXOR->Name = L"btnByteXOR";
			this->btnByteXOR->Size = System::Drawing::Size(75, 23);
			this->btnByteXOR->TabIndex = 2;
			this->btnByteXOR->Text = L"XOR byte";
			this->btnByteXOR->UseVisualStyleBackColor = true;
			this->btnByteXOR->Click += gcnew System::EventHandler(this, &FormData::btnByteXOR_Click);
			// 
			// btnByteSHL
			// 
			this->btnByteSHL->ForeColor = System::Drawing::SystemColors::ControlText;
			this->btnByteSHL->Location = System::Drawing::Point(246, 3);
			this->btnByteSHL->Name = L"btnByteSHL";
			this->btnByteSHL->Size = System::Drawing::Size(75, 23);
			this->btnByteSHL->TabIndex = 3;
			this->btnByteSHL->Text = L"<< byte";
			this->btnByteSHL->UseVisualStyleBackColor = true;
			this->btnByteSHL->Click += gcnew System::EventHandler(this, &FormData::btnByteSHL_Click);
			// 
			// btnByteSHR
			// 
			this->btnByteSHR->ForeColor = System::Drawing::SystemColors::ControlText;
			this->btnByteSHR->Location = System::Drawing::Point(327, 3);
			this->btnByteSHR->Name = L"btnByteSHR";
			this->btnByteSHR->Size = System::Drawing::Size(75, 23);
			this->btnByteSHR->TabIndex = 4;
			this->btnByteSHR->Text = L">> byte";
			this->btnByteSHR->UseVisualStyleBackColor = true;
			this->btnByteSHR->Click += gcnew System::EventHandler(this, &FormData::btnByteSHR_Click);
			// 
			// chbBit7
			// 
			this->chbBit7->AutoSize = true;
			this->chbBit7->Location = System::Drawing::Point(246, 39);
			this->chbBit7->Name = L"chbBit7";
			this->chbBit7->Size = System::Drawing::Size(15, 14);
			this->chbBit7->TabIndex = 27;
			this->chbBit7->UseVisualStyleBackColor = true;
			this->chbBit7->Visible = false;
			this->chbBit7->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit7_CheckedChanged);
			// 
			// chbBit6
			// 
			this->chbBit6->AutoSize = true;
			this->chbBit6->Location = System::Drawing::Point(267, 39);
			this->chbBit6->Name = L"chbBit6";
			this->chbBit6->Size = System::Drawing::Size(15, 14);
			this->chbBit6->TabIndex = 26;
			this->chbBit6->UseVisualStyleBackColor = true;
			this->chbBit6->Visible = false;
			this->chbBit6->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit6_CheckedChanged);
			// 
			// chbBit5
			// 
			this->chbBit5->AutoSize = true;
			this->chbBit5->Location = System::Drawing::Point(288, 39);
			this->chbBit5->Name = L"chbBit5";
			this->chbBit5->Size = System::Drawing::Size(15, 14);
			this->chbBit5->TabIndex = 25;
			this->chbBit5->UseVisualStyleBackColor = true;
			this->chbBit5->Visible = false;
			this->chbBit5->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit5_CheckedChanged);
			// 
			// chbBit4
			// 
			this->chbBit4->AutoSize = true;
			this->chbBit4->Location = System::Drawing::Point(309, 39);
			this->chbBit4->Name = L"chbBit4";
			this->chbBit4->Size = System::Drawing::Size(15, 14);
			this->chbBit4->TabIndex = 24;
			this->chbBit4->UseVisualStyleBackColor = true;
			this->chbBit4->Visible = false;
			this->chbBit4->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit4_CheckedChanged);
			// 
			// chbBit3
			// 
			this->chbBit3->AutoSize = true;
			this->chbBit3->Location = System::Drawing::Point(330, 39);
			this->chbBit3->Name = L"chbBit3";
			this->chbBit3->Size = System::Drawing::Size(15, 14);
			this->chbBit3->TabIndex = 23;
			this->chbBit3->UseVisualStyleBackColor = true;
			this->chbBit3->Visible = false;
			this->chbBit3->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit3_CheckedChanged);
			// 
			// chbBit2
			// 
			this->chbBit2->AutoSize = true;
			this->chbBit2->Location = System::Drawing::Point(351, 39);
			this->chbBit2->Name = L"chbBit2";
			this->chbBit2->Size = System::Drawing::Size(15, 14);
			this->chbBit2->TabIndex = 22;
			this->chbBit2->UseVisualStyleBackColor = true;
			this->chbBit2->Visible = false;
			this->chbBit2->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit2_CheckedChanged);
			// 
			// chbBit1
			// 
			this->chbBit1->AutoSize = true;
			this->chbBit1->Location = System::Drawing::Point(372, 39);
			this->chbBit1->Name = L"chbBit1";
			this->chbBit1->Size = System::Drawing::Size(15, 14);
			this->chbBit1->TabIndex = 21;
			this->chbBit1->UseVisualStyleBackColor = true;
			this->chbBit1->Visible = false;
			this->chbBit1->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit1_CheckedChanged);
			// 
			// chbBit0
			// 
			this->chbBit0->AutoSize = true;
			this->chbBit0->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
				static_cast<System::Int32>(static_cast<System::Byte>(233)));
			this->chbBit0->Location = System::Drawing::Point(393, 39);
			this->chbBit0->Name = L"chbBit0";
			this->chbBit0->Size = System::Drawing::Size(15, 14);
			this->chbBit0->TabIndex = 20;
			this->chbBit0->UseVisualStyleBackColor = false;
			this->chbBit0->Visible = false;
			this->chbBit0->CheckedChanged += gcnew System::EventHandler(this, &FormData::chbBit0_CheckedChanged);
			// 
			// FormData
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(214)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
				static_cast<System::Int32>(static_cast<System::Byte>(233)));
			this->ClientSize = System::Drawing::Size(415, 118);
			this->Controls->Add(this->chbBit7);
			this->Controls->Add(this->chbBit6);
			this->Controls->Add(this->chbBit5);
			this->Controls->Add(this->chbBit4);
			this->Controls->Add(this->chbBit3);
			this->Controls->Add(this->chbBit2);
			this->Controls->Add(this->chbBit1);
			this->Controls->Add(this->chbBit0);
			this->Controls->Add(this->pnlTop);
			this->Controls->Add(this->txtValue);
			this->Controls->Add(this->lblValue);
			this->Controls->Add(this->lviewBytes);
			this->Controls->Add(this->pnlBytes);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FormData";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Data";
			this->pnlTop->ResumeLayout(false);
			this->pnlBytes->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void chbBit7_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(7);
	}

	private: System::Void chbBit6_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(6);
	}

	private: System::Void chbBit5_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(5);
	}

	private: System::Void chbBit4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(4);
	}

	private: System::Void chbBit3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(3);
	}

	private: System::Void chbBit2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(2);
	}

	private: System::Void chbBit1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(1);
	}

	private: System::Void chbBit0_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		checkedBit(0);
	}

	private: System::Void btnByteSet_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			structures::MemoryRoutines::byteSet(*selectedByte());
			refreshItem(selectedItem_);
			refreshData();
		}
		catch (std::exception ex)
		{
			Logger::getInstance()->logError(ex.what());
			presentData(true);
		}
		catch (System::Exception^ ex)
		{
			Logger::getInstance()->logError(ex->Message);
			presentData(true);
		}
	}

	private: System::Void btnByteReset_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			structures::MemoryRoutines::byteReset(*selectedByte());
			refreshItem(selectedItem_);
			refreshData();
		}
		catch (std::exception ex)
		{
			Logger::getInstance()->logError(ex.what());
			presentData(true);
		}
		catch (System::Exception^ ex)
		{
			Logger::getInstance()->logError(ex->Message);
			presentData(true);
		}
	}

	private: System::Void btnByteXOR_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			structures::MemoryRoutines::byteXOR(*selectedByte());
			refreshItem(selectedItem_);
			refreshData();
		}
		catch (std::exception ex)
		{
			Logger::getInstance()->logError(ex.what());
			presentData(true);
		}
		catch (System::Exception^ ex)
		{
			Logger::getInstance()->logError(ex->Message);
			presentData(true);
		}
	}

	private: System::Void btnByteSHL_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			structures::MemoryRoutines::byteSHL(*selectedByte());
			refreshItem(selectedItem_);
			refreshData();
		}
		catch (std::exception ex)
		{
			Logger::getInstance()->logError(ex.what());
			presentData(true);
		}
		catch (System::Exception^ ex)
		{
			Logger::getInstance()->logError(ex->Message);
			presentData(true);
		}
	}

	private: System::Void btnByteSHR_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			structures::MemoryRoutines::byteSHR(*selectedByte());
			refreshItem(selectedItem_);
			refreshData();
		}
		catch (std::exception ex)
		{
			Logger::getInstance()->logError(ex.what());
			presentData(true);
		}
		catch (System::Exception^ ex)
		{
			Logger::getInstance()->logError(ex->Message);
			presentData(true);
		}
	}

	private: System::Void txtData_TextChanged(System::Object^ sender, System::EventArgs^  e) {
		if (isUpdating())
			return;

		try
		{
			switch (formType_)
			{
			case FormType::dftBYTE:
				*reinterpret_cast<structures::byte*>(dataPtr_) = Convert::ToByte(txtValue->Text);
				presentData(false);
				break;
			case FormType::dftDATA:
				*reinterpret_cast<DataType*>(dataPtr_) = DataType::Parse(txtValue->Text);
				presentData(false);
				break;
			case FormType::dftPRIORITY:
				*reinterpret_cast<PriorityType*>(dataPtr_) = PriorityType::Parse(txtValue->Text);
				presentData(false);
				break;
			case FormType::dftKEY:
				*reinterpret_cast<KeyType*>(dataPtr_) = KeyType::Parse(txtValue->Text);
				presentData(false);
				break;
			case FormType::dftVERTEX_ID:
				*reinterpret_cast<VertexIdType*>(dataPtr_) = VertexIdType::Parse(txtValue->Text);
				presentData(false);
				break;
			case FormType::dftINT:
				*reinterpret_cast<int*>(dataPtr_) = Convert::ToInt32(txtValue->Text);
				presentData(false);
				break;
			case FormType::dftDOUBLE:
				*reinterpret_cast<double*>(dataPtr_) = Convert::ToDouble(txtValue->Text);
				presentData(false);
				break;
			case FormType::dftSTRING:
			{
				const char* chars =
					(const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txtValue->Text)).ToPointer();
				*reinterpret_cast<std::string*>(dataPtr_) = std::string(chars);
				Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
				presentData(false);
			}
			break;
			}
		}
		catch (std::exception ex)
		{
			Logger::getInstance()->logError(ex.what());
			presentData(true);
		}
		catch (System::Exception^ ex)
		{
			Logger::getInstance()->logError(ex->Message);
			presentData(true);
		}
	}


	private: System::Void lviewBytes_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
		selectedItem_ = e->IsSelected ? e->Item : nullptr;
		refreshItem(e->Item);
		enableControls();
	}

	private: System::Void btnBytes_Click(System::Object^  sender, System::EventArgs^  e) {
		showBytes_ = !showBytes_;
		adjustHeight();
		enableControls();
	}

	private: System::Void txtValue_Enter(System::Object^  sender, System::EventArgs^  e) {
		selectedItem_ = nullptr;
	}
};

}
