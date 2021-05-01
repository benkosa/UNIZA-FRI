#pragma once

#include "../../structures/graph/graph.h"
#include "../../structures/list/linked_list.h"
#include "../controls/controls.h"
#include "../controls/controls_table.h"
#include "../ui_routines.h"
#include "../../data/data_routines.h"
#include "../../data/data_types.h"
#include "../../data/graph_data.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ui {

	public ref class PanelPresentGraph: public UserControl
	{
	public:
		property structures::Graph* Graph
		{
			structures::Graph* get() { return dynamic_cast<structures::Graph*>(controls_->Structure); };
		}

		PanelPresentGraph(void);
		void initialize(ControlsHolder^ holder);

		void visualize(structures::Graph* graph);
		void refreshVertexItem(ListViewItem^ item, structures::GraphVertex* vertex);
		void refreshEdgeItem(ListViewItem^ item, structures::GraphEdge* edge);
		bool tryGetSelectedVertexId(data::VertexIdType% vertexId);
		bool tryGetSelectedEdgeBeginVertexId(data::VertexIdType% beginVertexId);
		bool tryGetSelectedEdgeEndVertexId(data::VertexIdType% endVertexId);
	protected:
		~PanelPresentGraph();
	private:
		ListViewItem^ selectedVertexItem_;
		ListViewItem^ selectedEdgeItem_;
		ControlsHolder^ controls_;
	private: System::Windows::Forms::SplitContainer^  splitContainer;
	private: System::Windows::Forms::ListView^  lviewVertices;
	private: System::Windows::Forms::ColumnHeader^  columnVertexId;
	private: System::Windows::Forms::ColumnHeader^  columnVertexData;
	private: System::Windows::Forms::ListView^  lviewEdges;
	private: System::Windows::Forms::ColumnHeader^  columnBeginVertexId;
	private: System::Windows::Forms::ColumnHeader^  columnEndVertexId;
	private: System::Windows::Forms::ColumnHeader^  columnEdgeData;






















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
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->lviewVertices = (gcnew System::Windows::Forms::ListView());
			this->columnVertexId = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnVertexData = (gcnew System::Windows::Forms::ColumnHeader());
			this->lviewEdges = (gcnew System::Windows::Forms::ListView());
			this->columnBeginVertexId = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnEndVertexId = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnEdgeData = (gcnew System::Windows::Forms::ColumnHeader());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer
			// 
			this->splitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer->Location = System::Drawing::Point(0, 0);
			this->splitContainer->Name = L"splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->Controls->Add(this->lviewVertices);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->Controls->Add(this->lviewEdges);
			this->splitContainer->Size = System::Drawing::Size(554, 387);
			this->splitContainer->SplitterDistance = 184;
			this->splitContainer->TabIndex = 5;
			// 
			// lviewVertices
			// 
			this->lviewVertices->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewVertices->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->columnVertexId,
					this->columnVertexData
			});
			this->lviewVertices->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewVertices->FullRowSelect = true;
			this->lviewVertices->GridLines = true;
			this->lviewVertices->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewVertices->HideSelection = false;
			this->lviewVertices->Location = System::Drawing::Point(0, 0);
			this->lviewVertices->MultiSelect = false;
			this->lviewVertices->Name = L"lviewVertices";
			this->lviewVertices->Size = System::Drawing::Size(184, 387);
			this->lviewVertices->TabIndex = 5;
			this->lviewVertices->UseCompatibleStateImageBehavior = false;
			this->lviewVertices->View = System::Windows::Forms::View::Details;
			this->lviewVertices->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelPresentGraph::lviewVertices_ItemSelectionChanged);
			// 
			// columnVertexId
			// 
			this->columnVertexId->Text = L"Vertex id";
			// 
			// columnVertexData
			// 
			this->columnVertexData->Text = L"Vertex label";
			this->columnVertexData->Width = 122;
			// 
			// lviewEdges
			// 
			this->lviewEdges->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lviewEdges->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnBeginVertexId,
					this->columnEndVertexId, this->columnEdgeData
			});
			this->lviewEdges->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lviewEdges->FullRowSelect = true;
			this->lviewEdges->GridLines = true;
			this->lviewEdges->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lviewEdges->HideSelection = false;
			this->lviewEdges->Location = System::Drawing::Point(0, 0);
			this->lviewEdges->MultiSelect = false;
			this->lviewEdges->Name = L"lviewEdges";
			this->lviewEdges->Size = System::Drawing::Size(366, 387);
			this->lviewEdges->TabIndex = 6;
			this->lviewEdges->UseCompatibleStateImageBehavior = false;
			this->lviewEdges->View = System::Windows::Forms::View::Details;
			this->lviewEdges->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &PanelPresentGraph::lviewEdges_ItemSelectionChanged);
			// 
			// columnBeginVertexId
			// 
			this->columnBeginVertexId->Text = L"Begin vertex id";
			this->columnBeginVertexId->Width = 88;
			// 
			// columnEndVertexId
			// 
			this->columnEndVertexId->Text = L"End vertex id";
			this->columnEndVertexId->Width = 85;
			// 
			// columnEdgeData
			// 
			this->columnEdgeData->Text = L"Edge length";
			this->columnEdgeData->Width = 190;
			// 
			// PanelPresentGraph
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->splitContainer);
			this->Name = L"PanelPresentGraph";
			this->Size = System::Drawing::Size(554, 387);
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->EndInit();
			this->splitContainer->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void lviewVertices_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
		if (e->IsSelected)
		{
			selectedVertexItem_ = e->Item;
		}
		else
		{
			selectedVertexItem_ = nullptr;
		}

		controls_->enableControls();
	}

	private: System::Void lviewEdges_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
		if (e->IsSelected)
		{
			selectedEdgeItem_ = e->Item;
		}
		else
		{
			selectedEdgeItem_ = nullptr;
		}

		controls_->enableControls();
	}
};

	PanelPresentGraph::PanelPresentGraph(void) :
		selectedVertexItem_(nullptr),
		selectedEdgeItem_(nullptr),
		controls_(nullptr)
	{
		InitializeComponent();
	}

	inline void PanelPresentGraph::initialize(ControlsHolder ^ holder)
	{
		controls_ = holder;
	}


	PanelPresentGraph::~PanelPresentGraph()
	{
		if (components)
		{
			delete components;
		}
	}

	void PanelPresentGraph::visualize(structures::Graph* graph)
	{
		lviewVertices->Items->Clear();
		structures::LinkedList<structures::GraphVertex*> vertices;
		graph->getVertices(vertices);
		for (structures::GraphVertex* vertex: vertices)
		{
			ListViewItem^ item = gcnew ListViewItem();
			lviewVertices->Items->Add(item);
			refreshVertexItem(item, vertex);
		}
		selectedVertexItem_ = nullptr;

		lviewEdges->Items->Clear();
		structures::LinkedList<structures::GraphEdge*> edges;
		graph->getEdges(edges);
		lviewEdges->MultiSelect = true;
		for (structures::GraphEdge* edge : edges)
		{
			ListViewItem^ item = gcnew ListViewItem();
			lviewEdges->Items->Add(item);
			refreshEdgeItem(item, edge);

			// oznacenie predchodcov/nasledovnikov
			item->Selected = data::GraphDataEdge::getData(edge)->selected();
			data::GraphDataEdge::getData(edge)->selected() = false;
		}
		lviewEdges->MultiSelect = false;
		selectedEdgeItem_ = nullptr;
	}

	inline void PanelPresentGraph::refreshVertexItem(ListViewItem^ item, structures::GraphVertex* vertex)
	{
		if (item == nullptr)
			return;

		// id
		item->Text = Convert::ToString(vertex->getId());

		// data
		if (item->SubItems->Count < 2)
			item->SubItems->Add("");
		item->SubItems[1]->Text = data::GraphDataVertex::getData(vertex)->toString();
	}

	inline void PanelPresentGraph::refreshEdgeItem(ListViewItem ^ item, structures::GraphEdge * edge)
	{
		if (item == nullptr)
			return;

		// begin vertex id
		item->Text = Convert::ToString(edge->getBeginVertex()->getId());

		// end vertex id
		if (item->SubItems->Count < 2)
			item->SubItems->Add("");
		item->SubItems[1]->Text = Convert::ToString(edge->getEndVertex()->getId());

		// data
		if (item->SubItems->Count < 3)
			item->SubItems->Add("");
		item->SubItems[2]->Text = data::GraphDataEdge::getData(edge)->toString();
	}

	inline bool PanelPresentGraph::tryGetSelectedVertexId(data::VertexIdType % vertexId)
	{
		if (selectedVertexItem_ != nullptr)
		{
			vertexId = Convert::ToInt32(selectedVertexItem_->SubItems[0]->Text);
			return true;
		}
		return false;
	}

	inline bool PanelPresentGraph::tryGetSelectedEdgeBeginVertexId(data::VertexIdType % beginVertexId)
	{
		if (selectedEdgeItem_ != nullptr)
		{
			beginVertexId = Convert::ToInt32(selectedEdgeItem_->SubItems[0]->Text);
			return true;
		}
		return false;
	}

	inline bool PanelPresentGraph::tryGetSelectedEdgeEndVertexId(data::VertexIdType % endVertexId)
	{
		if (selectedEdgeItem_ != nullptr)
		{
			endVertexId = Convert::ToInt32(selectedEdgeItem_->SubItems[1]->Text);
			return true;
		}
		return false;
	}
}
