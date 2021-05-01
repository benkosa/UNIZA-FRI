#pragma once

#include "action_history.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ui {

	/// <summary>
	/// Panel prezentujuci historiu akcii udajovej struktury.
	/// </summary>
	public ref class PanelActionHistory : public UserControl
	{
	private:
		/// <summary> Obalovaci objekt pre informacie. </summary>
		ref class InfoItemData
		{
		public:
			property OperationInfo* Info
			{
				OperationInfo* get() { return info_; }
				void set(OperationInfo* info) { info_ = info; }
			}

			InfoItemData(OperationInfo* info) : info_(info) {}
		private:
			/// <summary> Informacia. </summary>
			OperationInfo* info_;
		};

	public:
		/// <summary> Konstruktor. </summary>
		PanelActionHistory(void);

		/// <summary> Odprezentuje v zozname historiu vsetkych operacii nad udajovou strukturou. </summary>
		/// <param name = "structure"> Struktura, ktora ma byt prezentovana. </param>
		/// <param name = "adt"> ADT struktury. </param>
		void presentStructure(structures::Structure* structure, structures::StructureADT adt);

		/// <summary> Upravi graf tak, aby obsahoval nove trvanie operacie nad udajovou strukturou. </summary>
		/// <param name = "operationInfo"> Informacie o operacii. </param>
		void actionPerformed(OperationInfo* operationInfo);

	protected:
		/// <summary> Destruktor. </summary>
		~PanelActionHistory();

	private:
		/// <summary> Pre dany zaznam o operacii vytvori a naformatuje ListViewItem. </summary>
		/// <param name = "operationInfo"> Zaznam o operacii. </param>
		/// <returns> Naformatovana ListViewItem pre dany zaznam o operacii. </returns>
		ListViewItem^ createListViewItem(OperationInfo* operationInfo);

		/// <summary> Aktualizuje ovladacie prvky. </summary>
		void enableControls();

		void undo(ListViewItem^ item);
		void redo(ListViewItem^ item);
		void remove(ListViewItem^ item);

	private: System::Windows::Forms::Panel^  pnlActionHistoryHead;
	private: System::Windows::Forms::Label^  lblActionHistoryHead;
	private: System::Windows::Forms::ListView^  lviewHistory;
	private: System::Windows::Forms::ColumnHeader^  columnOperation;
	private: System::Windows::Forms::ColumnHeader^  columnDuration;
	private: System::Windows::Forms::FlowLayoutPanel^  pnlActionHistoryControls;
	private: System::Windows::Forms::Button^  btnUndoLast;
	private: System::Windows::Forms::Button^  btnRedoLast;
	private: System::Windows::Forms::Button^  btnClear;
	private: System::Windows::Forms::Button^  btnUndoThis;
	private: System::Windows::Forms::Button^  btnRedoThis;


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
			this->pnlActionHistoryHead = (gcnew System::Windows::Forms::Panel());
			this->lblActionHistoryHead = (gcnew System::Windows::Forms::Label());
			this->lviewHistory = (gcnew System::Windows::Forms::ListView());
			this->columnOperation = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnDuration = (gcnew System::Windows::Forms::ColumnHeader());
			this->pnlActionHistoryControls = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btnUndoLast = (gcnew System::Windows::Forms::Button());
			this->btnRedoLast = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->btnUndoThis = (gcnew System::Windows::Forms::Button());
			this->btnRedoThis = (gcnew System::Windows::Forms::Button());
			this->pnlActionHistoryHead->SuspendLayout();
			this->pnlActionHistoryControls->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlActionHistoryHead
			// 
			this->pnlActionHistoryHead->BackColor = System::Drawing::SystemColors::Control;
			this->pnlActionHistoryHead->Controls->Add(this->lblActionHistoryHead);
			this->pnlActionHistoryHead->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlActionHistoryHead->Location = System::Drawing::Point(0, 0);
			this->pnlActionHistoryHead->Name = L"pnlActionHistoryHead";
			this->pnlActionHistoryHead->Size = System::Drawing::Size(415, 25);
			this->pnlActionHistoryHead->TabIndex = 3;
			// 
			// lblActionHistoryHead
			// 
			this->lblActionHistoryHead->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)), static_cast<System::Int32>(static_cast<System::Byte>(157)));
			this->lblActionHistoryHead->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblActionHistoryHead->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->lblActionHistoryHead->Location = System::Drawing::Point(0, 0);
			this->lblActionHistoryHead->Margin = System::Windows::Forms::Padding(2, 0, 0, 4);
			this->lblActionHistoryHead->Name = L"lblActionHistoryHead";
			this->lblActionHistoryHead->Size = System::Drawing::Size(415, 25);
			this->lblActionHistoryHead->TabIndex = 0;
			this->lblActionHistoryHead->Text = L"Action history";
			this->lblActionHistoryHead->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lviewHistory
			// 
			this->lviewHistory->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewHistory->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->columnOperation,
					this->columnDuration
			});
			this->lviewHistory->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewHistory->FullRowSelect = true;
			this->lviewHistory->GridLines = true;
			this->lviewHistory->HideSelection = false;
			this->lviewHistory->Location = System::Drawing::Point(0, 55);
			this->lviewHistory->MultiSelect = false;
			this->lviewHistory->Name = L"lviewHistory";
			this->lviewHistory->Size = System::Drawing::Size(415, 244);
			this->lviewHistory->TabIndex = 5;
			this->lviewHistory->UseCompatibleStateImageBehavior = false;
			this->lviewHistory->View = System::Windows::Forms::View::Details;
			this->lviewHistory->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelActionHistory::lviewHistory_ItemSelectionChanged);
			// 
			// columnOperation
			// 
			this->columnOperation->Text = L"Operation";
			this->columnOperation->Width = 109;
			// 
			// columnDuration
			// 
			this->columnDuration->Text = L"Duration [ms]";
			this->columnDuration->Width = 94;
			// 
			// pnlActionHistoryControls
			// 
			this->pnlActionHistoryControls->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->pnlActionHistoryControls->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(41)),
				static_cast<System::Int32>(static_cast<System::Byte>(57)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->pnlActionHistoryControls->Controls->Add(this->btnUndoLast);
			this->pnlActionHistoryControls->Controls->Add(this->btnRedoLast);
			this->pnlActionHistoryControls->Controls->Add(this->btnClear);
			this->pnlActionHistoryControls->Controls->Add(this->btnUndoThis);
			this->pnlActionHistoryControls->Controls->Add(this->btnRedoThis);
			this->pnlActionHistoryControls->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlActionHistoryControls->Location = System::Drawing::Point(0, 25);
			this->pnlActionHistoryControls->Name = L"pnlActionHistoryControls";
			this->pnlActionHistoryControls->Size = System::Drawing::Size(415, 30);
			this->pnlActionHistoryControls->TabIndex = 6;
			// 
			// btnUndoLast
			// 
			this->btnUndoLast->Location = System::Drawing::Point(3, 3);
			this->btnUndoLast->Name = L"btnUndoLast";
			this->btnUndoLast->Size = System::Drawing::Size(75, 23);
			this->btnUndoLast->TabIndex = 0;
			this->btnUndoLast->Text = L"Undo last";
			this->btnUndoLast->UseVisualStyleBackColor = true;
			this->btnUndoLast->Click += gcnew System::EventHandler(this, &PanelActionHistory::btnUndoLast_Click);
			// 
			// btnRedoLast
			// 
			this->btnRedoLast->Location = System::Drawing::Point(84, 3);
			this->btnRedoLast->Name = L"btnRedoLast";
			this->btnRedoLast->Size = System::Drawing::Size(75, 23);
			this->btnRedoLast->TabIndex = 2;
			this->btnRedoLast->Text = L"Redo last";
			this->btnRedoLast->UseVisualStyleBackColor = true;
			this->btnRedoLast->Click += gcnew System::EventHandler(this, &PanelActionHistory::btnRedoLast_Click);
			// 
			// btnClear
			// 
			this->btnClear->Location = System::Drawing::Point(165, 3);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(75, 23);
			this->btnClear->TabIndex = 1;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &PanelActionHistory::btnClear_Click);
			// 
			// btnUndoThis
			// 
			this->btnUndoThis->Location = System::Drawing::Point(246, 3);
			this->btnUndoThis->Name = L"btnUndoThis";
			this->btnUndoThis->Size = System::Drawing::Size(75, 23);
			this->btnUndoThis->TabIndex = 3;
			this->btnUndoThis->Text = L"Undo this";
			this->btnUndoThis->UseVisualStyleBackColor = true;
			this->btnUndoThis->Click += gcnew System::EventHandler(this, &PanelActionHistory::btnUndoThis_Click);
			// 
			// btnRedoThis
			// 
			this->btnRedoThis->Location = System::Drawing::Point(327, 3);
			this->btnRedoThis->Name = L"btnRedoThis";
			this->btnRedoThis->Size = System::Drawing::Size(75, 23);
			this->btnRedoThis->TabIndex = 4;
			this->btnRedoThis->Text = L"Redo this";
			this->btnRedoThis->UseVisualStyleBackColor = true;
			this->btnRedoThis->Click += gcnew System::EventHandler(this, &PanelActionHistory::btnRedoThis_Click);
			// 
			// PanelActionHistory
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->lviewHistory);
			this->Controls->Add(this->pnlActionHistoryControls);
			this->Controls->Add(this->pnlActionHistoryHead);
			this->Name = L"PanelActionHistory";
			this->Size = System::Drawing::Size(415, 299);
			this->pnlActionHistoryHead->ResumeLayout(false);
			this->pnlActionHistoryControls->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnUndoLast_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnRedoLast_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnUndoThis_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnRedoThis_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void lviewHistory_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e);
};
}
