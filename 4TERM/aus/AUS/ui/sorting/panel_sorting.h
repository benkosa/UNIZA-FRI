#pragma once

#include "../../structures/table/unsorted_sequence_table.h"
#include "../../structures/table/sorting/sort.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace ui {

	ref class PanelSorting;

	/// <summary> Notifikacny objekt rozhrania s triedenim. </summary>
	public class UISortNotifier : public structures::SortNotifier
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "panelSorting"> Odkaz na panel s triedenim. </param>
		UISortNotifier(PanelSorting^* panelSorting);
	protected:
		/// <summary> Vyvolanie notifikacie. </summary>
		void doNotify() override;
	private:
		/// <summary> Odkaz na panel s triedenim. </summary>
		PanelSorting^* panelSorting_;
	};

	public ref class PanelSorting : public UserControl
	{
	public:
		/// <summary> Vytvori a vlozi panel pre ovladanie struktur do daneho komponentu. </summary>
		/// <param name = "owner"> Vlastnik panela so strukturami. Mal by to byt iny prazdny panel. </param>
		/// <returns> Vytvoreny panel pre ovladanie struktur. </returns>
		static PanelSorting^ createAndIntegratePanelSorting(Panel^ owner);

		void doSortUpdate();
	protected:
		/// <summary> Chraneny konstruktor umoznuje vytvarat instance iba pomocou metody createAndIntegratePanelSorting. </summary>
		PanelSorting(void);
		/// <summary> Destruktor. </summary>
		~PanelSorting();
		/// <summary> Inicializuje panel triedeni. </summary>
		/// <remarks> Je automaticky volana z metody createAndIntegratePanelSorting. </remarks>
		void initialize();

	private:
		structures::UnsortedSequenceTable<int, int>* table_;

		void performSort(structures::Sort<int, int>* sorter);

	private: System::Windows::Forms::FlowLayoutPanel^  pnlSorting;
	private: System::Windows::Forms::PictureBox^  pictureTable;
	private: System::Windows::Forms::Button^  btnShuffle;
	private: System::Windows::Forms::Button^  btnInsertSort;
	private: System::Windows::Forms::Button^  btnSelectSort;
	private: System::Windows::Forms::Button^  btnBubbleSort;
	private: System::Windows::Forms::Button^  btnQuickSort;
	private: System::Windows::Forms::Button^  btnHeapSort;
	private: System::Windows::Forms::Button^  btnShellSort;
	private: System::Windows::Forms::Button^  btnRadixSort;
	private: System::Windows::Forms::Button^  btnMergeSort;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pnlSorting = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btnShuffle = (gcnew System::Windows::Forms::Button());
			this->btnInsertSort = (gcnew System::Windows::Forms::Button());
			this->btnSelectSort = (gcnew System::Windows::Forms::Button());
			this->btnBubbleSort = (gcnew System::Windows::Forms::Button());
			this->btnQuickSort = (gcnew System::Windows::Forms::Button());
			this->btnHeapSort = (gcnew System::Windows::Forms::Button());
			this->btnShellSort = (gcnew System::Windows::Forms::Button());
			this->btnRadixSort = (gcnew System::Windows::Forms::Button());
			this->btnMergeSort = (gcnew System::Windows::Forms::Button());
			this->pictureTable = (gcnew System::Windows::Forms::PictureBox());
			this->pnlSorting->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureTable))->BeginInit();
			this->SuspendLayout();
			this->pnlSorting->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(78)),
				static_cast<System::Int32>(static_cast<System::Byte>(111)));
			this->pnlSorting->Controls->Add(this->btnShuffle);
			this->pnlSorting->Controls->Add(this->btnInsertSort);
			this->pnlSorting->Controls->Add(this->btnSelectSort);
			this->pnlSorting->Controls->Add(this->btnBubbleSort);
			this->pnlSorting->Controls->Add(this->btnQuickSort);
			this->pnlSorting->Controls->Add(this->btnHeapSort);
			this->pnlSorting->Controls->Add(this->btnShellSort);
			this->pnlSorting->Controls->Add(this->btnRadixSort);
			this->pnlSorting->Controls->Add(this->btnMergeSort);
			this->pnlSorting->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlSorting->Location = System::Drawing::Point(0, 0);
			this->pnlSorting->Name = L"pnlSorting";
			this->pnlSorting->Size = System::Drawing::Size(786, 30);
			this->pnlSorting->TabIndex = 0;
			this->btnShuffle->Location = System::Drawing::Point(3, 3);
			this->btnShuffle->Name = L"btnShuffle";
			this->btnShuffle->Size = System::Drawing::Size(75, 23);
			this->btnShuffle->TabIndex = 0;
			this->btnShuffle->Text = L"Shuffle";
			this->btnShuffle->UseVisualStyleBackColor = true;
			this->btnShuffle->Click += gcnew System::EventHandler(this, &PanelSorting::btnShuffle_Click);
			this->btnInsertSort->Location = System::Drawing::Point(84, 3);
			this->btnInsertSort->Name = L"btnInsertSort";
			this->btnInsertSort->Size = System::Drawing::Size(75, 23);
			this->btnInsertSort->TabIndex = 1;
			this->btnInsertSort->Text = L"Insert Sort";
			this->btnInsertSort->UseVisualStyleBackColor = true;
			this->btnInsertSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnInsertSort_Click);
			this->btnSelectSort->Location = System::Drawing::Point(165, 3);
			this->btnSelectSort->Name = L"btnSelectSort";
			this->btnSelectSort->Size = System::Drawing::Size(75, 23);
			this->btnSelectSort->TabIndex = 2;
			this->btnSelectSort->Text = L"Select Sort";
			this->btnSelectSort->UseVisualStyleBackColor = true;
			this->btnSelectSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnSelectSort_Click);
			this->btnBubbleSort->Location = System::Drawing::Point(246, 3);
			this->btnBubbleSort->Name = L"btnBubbleSort";
			this->btnBubbleSort->Size = System::Drawing::Size(75, 23);
			this->btnBubbleSort->TabIndex = 3;
			this->btnBubbleSort->Text = L"Bubble Sort";
			this->btnBubbleSort->UseVisualStyleBackColor = true;
			this->btnBubbleSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnBubbleSort_Click);
			this->btnQuickSort->Location = System::Drawing::Point(327, 3);
			this->btnQuickSort->Name = L"btnQuickSort";
			this->btnQuickSort->Size = System::Drawing::Size(75, 23);
			this->btnQuickSort->TabIndex = 4;
			this->btnQuickSort->Text = L"Quick Sort";
			this->btnQuickSort->UseVisualStyleBackColor = true;
			this->btnQuickSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnQuickSort_Click);
			this->btnHeapSort->Location = System::Drawing::Point(408, 3);
			this->btnHeapSort->Name = L"btnHeapSort";
			this->btnHeapSort->Size = System::Drawing::Size(75, 23);
			this->btnHeapSort->TabIndex = 4;
			this->btnHeapSort->Text = L"Heap Sort";
			this->btnHeapSort->UseVisualStyleBackColor = true;
			this->btnHeapSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnHeapSort_Click);
			this->btnShellSort->Location = System::Drawing::Point(489, 3);
			this->btnShellSort->Name = L"btnShellSort";
			this->btnShellSort->Size = System::Drawing::Size(75, 23);
			this->btnShellSort->TabIndex = 4;
			this->btnShellSort->Text = L"Shell Sort";
			this->btnShellSort->UseVisualStyleBackColor = true;
			this->btnShellSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnShellSort_Click);
			this->btnRadixSort->Location = System::Drawing::Point(570, 3);
			this->btnRadixSort->Name = L"btnRadixSort";
			this->btnRadixSort->Size = System::Drawing::Size(75, 23);
			this->btnRadixSort->TabIndex = 4;
			this->btnRadixSort->Text = L"Radix Sort";
			this->btnRadixSort->UseVisualStyleBackColor = true;
			this->btnRadixSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnRadixSort_Click);
			this->btnMergeSort->Location = System::Drawing::Point(651, 3);
			this->btnMergeSort->Name = L"btnMergeSort";
			this->btnMergeSort->Size = System::Drawing::Size(75, 23);
			this->btnMergeSort->TabIndex = 4;
			this->btnMergeSort->Text = L"Merge Sort";
			this->btnMergeSort->UseVisualStyleBackColor = true;
			this->btnMergeSort->Click += gcnew System::EventHandler(this, &PanelSorting::btnMergeSort_Click);
			this->pictureTable->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureTable->Location = System::Drawing::Point(0, 30);
			this->pictureTable->Name = L"pictureTable";
			this->pictureTable->Size = System::Drawing::Size(786, 325);
			this->pictureTable->TabIndex = 1;
			this->pictureTable->TabStop = false;
			this->pictureTable->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &PanelSorting::pictureTable_Paint);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->pictureTable);
			this->Controls->Add(this->pnlSorting);
			this->Name = L"PanelSorting";
			this->Size = System::Drawing::Size(786, 355);
			this->pnlSorting->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureTable))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: System::Void pictureTable_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
	private: System::Void btnShuffle_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnInsertSort_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnSelectSort_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnBubbleSort_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnQuickSort_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnHeapSort_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnShellSort_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnRadixSort_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnMergeSort_Click(System::Object^  sender, System::EventArgs^  e);
};
}
