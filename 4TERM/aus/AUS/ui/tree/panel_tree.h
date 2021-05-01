#pragma once

#include "../../structures/tree/tree.h"
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

	public ref class PanelPresentTree : public UserControl
	{
	private:
		/// <summary> Obalovaci objekt pre vrchol stromu. </summary>
		ref class TreeNodeData
		{
		public:
			property structures::TreeNode<data::DataType>* Node
			{
				structures::TreeNode<data::DataType>* get() { return node_; }
				void set(structures::TreeNode<data::DataType>* node) { node_ = node; }
			}

			TreeNodeData(structures::TreeNode<data::DataType>* node) : node_(node) {}
		private:
			/// <summary> Vrchol stromu. </summary>
			structures::TreeNode<data::DataType>* node_;
		};
	public:
		property TreeNode^ SelectedNode
		{
			TreeNode^ get() { return treeTree->SelectedNode; };
		}

		property structures::TreeNode<data::DataType>* SelectedTreeNode
		{
			structures::TreeNode<data::DataType>* get() { return SelectedNode != nullptr ? dynamic_cast<TreeNodeData^>(SelectedNode->Tag)->Node: nullptr; };
		}

		property structures::Tree<data::DataType>* Tree
		{
			structures::Tree<data::DataType>* get() { return dynamic_cast<structures::Tree<data::DataType>*>(controls_->Structure); };
		}

		PanelPresentTree(void);
		void initialize(ControlsHolder^ holder);

		void visualize(structures::Tree<data::DataType>* tree);
		void refreshNode(TreeNode^ node, data::DataType data);
		void listSubtreeOfSelectedNode();
	protected:
		~PanelPresentTree();
		
		void listSubtree(structures::TreeNode<data::DataType>* dataNode, TreeNode^ presentNode);
	private:
		ControlsHolder^ controls_;
	private: System::Windows::Forms::TreeView^  treeTree;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->treeTree = (gcnew System::Windows::Forms::TreeView());
			this->SuspendLayout();
			// 
			// treeTree
			// 
			this->treeTree->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->treeTree->Dock = System::Windows::Forms::DockStyle::Fill;
			this->treeTree->FullRowSelect = true;
			this->treeTree->HideSelection = false;
			this->treeTree->Location = System::Drawing::Point(0, 0);
			this->treeTree->Name = L"treeTree";
			this->treeTree->Size = System::Drawing::Size(472, 332);
			this->treeTree->TabIndex = 0;
			this->treeTree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &PanelPresentTree::treeTree_AfterSelect);
			// 
			// PanelPresentTree
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->treeTree);
			this->Name = L"PanelPresentTree";
			this->Size = System::Drawing::Size(472, 332);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void treeTree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
		controls_->enableControls();
	}
	};

	PanelPresentTree::PanelPresentTree(void) :
		controls_(nullptr)
	{
		InitializeComponent();
	}

	inline void PanelPresentTree::initialize(ControlsHolder ^ holder)
	{
		controls_ = holder;
	}


	PanelPresentTree::~PanelPresentTree()
	{
		if (components)
		{
			delete components;
		}
	}

	inline void PanelPresentTree::refreshNode(TreeNode ^ node, data::DataType data)
	{
		node->Text = Convert::ToString(data) + " [" + UIRoutines::convertMemoryToString(&data, sizeof(data)) + "]";
	}

	inline void PanelPresentTree::listSubtreeOfSelectedNode()
	{
		listSubtree(SelectedTreeNode, SelectedNode);
	}

	inline void PanelPresentTree::listSubtree(structures::TreeNode<data::DataType>* dataNode, TreeNode ^ presentNode)
	{
		presentNode->Tag = gcnew TreeNodeData(dataNode);
		presentNode->Nodes->Clear();

		if (dataNode != nullptr)
		{
			refreshNode(presentNode, dataNode->accessData());

			for (int i = 0; i < dataNode->degree(); i++)
			{
				TreeNode^ subNode = gcnew TreeNode();
				presentNode->Nodes->Add(subNode);
				listSubtree(dataNode->getSon(i), subNode);
			}

			presentNode->Expand();
		}
		else
		{
			presentNode->Text = "NULL";
		}


	}

	void PanelPresentTree::visualize(structures::Tree<data::DataType>* tree)
	{
		treeTree->Nodes->Clear();

		TreeNode^ node = gcnew TreeNode();
		treeTree->Nodes->Add(node);
		listSubtree(tree->getRoot(), node);
	}

}
