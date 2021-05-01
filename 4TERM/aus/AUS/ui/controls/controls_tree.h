#pragma once

#include "../../structures/tree/tree.h"
#include "controls.h"
#include "../tree/panel_tree.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"

using namespace System::Windows::Forms;
using namespace System;

namespace ui
{

	/// <summary> Memento akcii stromov. </summary>
	private class TreeActionMemento : public ActionMemento
	{
	public:
		int getOrder() { return order_; }
		data::DataType getDataBefore() { return dataBefore_; }
		data::DataType getDataAfter() { return dataAfter_; }

		void setOrder(int order) { order_ = order; }
		void setDataBefore(data::DataType byteBefore) { dataBefore_ = byteBefore; }
		void setDataAfter(data::DataType byteAfter) { dataAfter_ = byteAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		TreeActionMemento(int actionID) :
			ActionMemento(actionID),
			order_(0),
			dataBefore_(data::DataType()),
			dataAfter_(data::DataType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		TreeActionMemento(const TreeActionMemento& other) :
			ActionMemento(other),
			order_(other.order_),
			dataBefore_(other.dataBefore_),
			dataAfter_(other.dataAfter_)
		{}

		ActionMemento* clone() override
		{
			return new TreeActionMemento(*this);
		}
	private:
		/// <summary> Poradie vrchola. </summary>
		int order_;
		/// <summary> Stav dat pred operaciou. </summary>
		data::DataType dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		data::DataType dataAfter_;
	};

	/// <summary> Ovladace pre stromy. </summary>
	ref class ControlsTree : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim stromu. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentTree^ result = gcnew PanelPresentTree();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (Tree != nullptr)
			{
				TreePanel->visualize(Tree);
			}
		}
	public:
		property structures::Tree<data::DataType>* Tree
		{
			structures::Tree<data::DataType>* get() { return dynamic_cast<structures::Tree<data::DataType>*>(Structure); };
		}

		property PanelPresentTree^ TreePanel
		{
			PanelPresentTree^ get() { return dynamic_cast<PanelPresentTree^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsTree() : ControlsHolder(structures::StructureADT::adtTREE) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu v strome. </summary>
	ref class ActionTree abstract : public Action
	{
	public:
		static const int idaTreeCREATE_NEW_ROOT = 0;
		static const int idaTreeNodeEDIT = 1;
		static const int idaTreeNodeIS_ROOT = 2;
		static const int idaTreeNodeIS_LEAF = 3;
		static const int idaTreeNodeGET_PARENT = 4;
		static const int idaTreeNodeGET_BROTHER = 5;
		static const int idaTreeNodeGET_SON = 6;
		static const int idaTreeNodeINSERT_SON = 7;
		static const int idaTreeNodeREMOVE_SON = 8;
		static const int idaTreeNodeSUBTREE_SIZE = 9;
		static const int idaTreeSIZE = 10;
		static const int idaTreeCLEAR = 11;
		static const int idaTreeIS_EMPTY = 12;

	public:
		property ControlsTree^ TreeControls
		{
			ControlsTree^ get() { return dynamic_cast<ControlsTree^>(Controls); };
		}

		/// <summary> Vytvori akciu nad stromom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTree(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ treeControls) : 
			Action(id, caption, supportsUndo, supportsRedo, treeControls) ,
			order_(0),
			dataEdit_(data::DataType()),
			result_(false)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			order_ = 0;
			dataEdit_ = data::DataType();
			result_ = false;

			return true;
		}

	protected:
		int order_;
		data::DataType dataEdit_;
		bool result_;
	};

	/// <summary> Trieda predstavuje operaciu vo vrchole v strome. </summary>
	ref class ActionTreeNode abstract : public ActionTree
	{
	public:
		/// <summary> Vytvori akciu nad vrcholom stromu. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNode(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ treeControls) : 
			ActionTree(id, caption, supportsUndo, supportsRedo, treeControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return TreeControls->TreePanel->SelectedTreeNode != nullptr;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			if (result_)
			{
				data::DataRoutines::showData(dataEdit_, Caption);
			}
			else
			{
				UIRoutines::showMessage(Caption, "NULL");
			}
		}

		/// <summary> Nastavi do atributov data_ a result_ formatu hodnoty podla vrchola stromu. </summary>
		/// <param name = "resultTreeNode"> Vrchol stromu vrateny operaciou. </param>
		void setAttributes(structures::TreeNode<data::DataType>* resultTreeNode)
		{
			if (resultTreeNode != nullptr)
			{
				dataEdit_ = resultTreeNode->accessData();
				result_ = true;
			}
			else
			{
				result_ = false;
			}
		}
	};

	/// <summary> Trieda predstavuje operaciu vytvor koren stromu. </summary>
	ref class ActionTreeCreateNewRoot : public ActionTree
	{
	public:
		/// <summary> Vytvori akciu vytvor koren stromu. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeCreateNewRoot(ControlsHolder^ treeControls) : 
			ActionTree(idaTreeCREATE_NEW_ROOT, "New root", true, false, treeControls) 
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTree::doFormat() &&
				data::DataRoutines::editDataManaged(dataEdit_, "Root data");
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			TreeActionMemento* treeMemento = dynamic_cast<TreeActionMemento*>(memento);
			dataEdit_ = treeMemento->getDataBefore();
			result_ = false;
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::TreeNode<data::DataType>* treeNode = TreeControls->Tree->createTreeNodeInstance();
			treeNode->accessData() = dataEdit_;
			structures::TreeNode<data::DataType>* oldRoot = TreeControls->Tree->replaceRoot(treeNode);
			if (oldRoot != nullptr)
			{
				delete oldRoot;
				oldRoot = nullptr;
			}

			TreeActionMemento* result = new TreeActionMemento(ID);
			result->setDataBefore(dataEdit_);
			
			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			structures::TreeNode<data::DataType>* oldRoot = TreeControls->Tree->replaceRoot(nullptr);
			if (oldRoot != nullptr)
			{
				delete oldRoot;
				oldRoot = nullptr;
			}
		}
	};

	/// <summary> Trieda predstavuje operaciu uprav data v uzle stromu. </summary>
	ref class ActionTreeNodeEdit : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu uprav data v uzle stromu. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeEdit(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeEDIT, "Edit", false, false, treeControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (ActionTree::doFormat())
			{
				dataEdit_ = TreeControls->TreePanel->SelectedTreeNode->accessData();

				return data::DataRoutines::editDataManaged(dataEdit_, "Edit data");
			}
			else
			{
				return false;
			}

		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			TreeControls->TreePanel->SelectedTreeNode->accessData() = dataEdit_;

			return new TreeActionMemento(ID);
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			TreeControls->TreePanel->refreshNode(TreeControls->TreePanel->SelectedNode, dataEdit_);
		}
	};

	/// <summary> Trieda predstavuje operaciu je uzol stromu koren? </summary>
	ref class ActionTreeNodeIsRoot : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu je uzol stromu koren? </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeIsRoot(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeIS_ROOT, "Is root?", false, false, treeControls)
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			result_ = TreeControls->TreePanel->SelectedTreeNode->isRoot();

			return new TreeActionMemento(ID);
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			UIRoutines::showMessage(Caption, Convert::ToString(result_));
		}
	};

	/// <summary> Trieda predstavuje operaciu je uzol stromu list? </summary>
	ref class ActionTreeNodeIsLeaf : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu je uzol stromu list? </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeIsLeaf(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeIS_LEAF, "Is leaf?", false, false, treeControls)
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			result_ = TreeControls->TreePanel->SelectedTreeNode->isLeaf();

			return new TreeActionMemento(ID);
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			UIRoutines::showMessage(Caption, Convert::ToString(result_));
		}
	};

	/// <summary> Trieda predstavuje operaciu daj otca. </summary>
	ref class ActionTreeNodeGetParent : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu daj otca. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeGetParent(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeGET_PARENT, "Get parent", false, false, treeControls)
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::TreeNode<data::DataType>* parent = TreeControls->TreePanel->SelectedTreeNode->getParent();
			setAttributes(parent);

			return new TreeActionMemento(ID);
		}
	};

	/// <summary> Trieda predstavuje operaciu daj brata. </summary>
	ref class ActionTreeNodeGetBrother : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu daj brata. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeGetBrother(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeGET_BROTHER, "Get brother", false, false, treeControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTree::doFormat() &&
				data::DataRoutines::editNumberManaged(order_, "Brother's order");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::TreeNode<data::DataType>* brother = TreeControls->TreePanel->SelectedTreeNode->getBrother(order_);
			setAttributes(brother);

			return new TreeActionMemento(ID);
		}
	};

	/// <summary> Trieda predstavuje operaciu daj syna. </summary>
	ref class ActionTreeNodeGetSon : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu daj syna. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeGetSon(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeGET_SON, "Get son", false, false, treeControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTree::doFormat() &&
				data::DataRoutines::editNumberManaged(order_, "Son's order");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::TreeNode<data::DataType>* son = TreeControls->TreePanel->SelectedTreeNode->getSon(order_);
			setAttributes(son);

			return new TreeActionMemento(ID);
		}
	};

	/// <summary> Trieda predstavuje operaciu vloz syna. </summary>
	ref class ActionTreeNodeInsertSon : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu vloz syna. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeInsertSon(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeINSERT_SON, "Insert son", false, false, treeControls) 
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTree::doFormat() && 
				data::DataRoutines::editDataManaged(dataEdit_, "Data to insert") && 
				data::DataRoutines::editNumberManaged(order_, "Enter order");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::TreeNode<data::DataType>* son = TreeControls->Tree->createTreeNodeInstance();
			son->accessData() = dataEdit_;
			try
			{
				TreeControls->TreePanel->SelectedTreeNode->insertSon(son, order_);
			}
			catch (std::exception ex)
			{
				delete son;
				son = nullptr;
				throw ex;
			}

			return new TreeActionMemento(ID);
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			TreeControls->TreePanel->listSubtreeOfSelectedNode();
		}
	};

	/// <summary> Trieda predstavuje operaciu odstran syna. </summary>
	ref class ActionTreeNodeRemoveSon : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu odstran syna. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeRemoveSon(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeREMOVE_SON, "Remove son", false, false, treeControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTree::doFormat() &&
				data::DataRoutines::editNumberManaged(order_, "Enter order");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::TreeNode<data::DataType>* deleteNode = TreeControls->TreePanel->SelectedTreeNode->removeSon(order_);
			setAttributes(deleteNode);
			delete deleteNode;

			return new TreeActionMemento(ID);
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			ActionTreeNode::doPresentResult();
			if (result_)
			{
				TreeControls->TreePanel->listSubtreeOfSelectedNode();
			}
		}
	};

	/// <summary> Trieda predstavuje operaciu pocet vrcholov v podstrome. </summary>
	ref class ActionTreeNodeSubtreeSize : public ActionTreeNode
	{
	public:
		/// <summary> Vytvori akciu pocet vrcholov v podstrome. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeNodeSubtreeSize(ControlsHolder^ treeControls) : 
			ActionTreeNode(idaTreeNodeSUBTREE_SIZE, "Subtree size", false, false, treeControls),
			size_(0)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (!ActionTreeNode::doFormat())
			{
				return false;
			}

			size_ = 0;
			return true;
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			size_ = TreeControls->TreePanel->SelectedTreeNode->sizeOfSubtree();

			return new TreeActionMemento(ID);
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showNumber(static_cast<int>(size_), Caption);
		}

	private:
		size_t size_;
	};

	/// <summary> Trieda predstavuje akciu vymaz strom. </summary>
	ref class ActionTreeClear : public ActionTree
	{
	public:
		/// <summary> Vytvori akciu vymaz strom. </summary>
		/// <param name = "treeControls"> Ovladanie, do ktoreho patri. </param>
		ActionTreeClear(ControlsHolder^ treeControls) : 
			ActionTree(idaTreeCLEAR, "Clear", false, false, treeControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			TreeControls->Tree->clear();

			return new TreeActionMemento(ID);
		}
	};

	void ControlsTree::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionTreeCreateNewRoot(this));
		actions->Add(gcnew ActionTreeNodeEdit(this));
		actions->Add(gcnew ActionTreeNodeIsRoot(this));
		actions->Add(gcnew ActionTreeNodeIsLeaf(this));
		actions->Add(gcnew ActionTreeNodeGetParent(this));
		actions->Add(gcnew ActionTreeNodeGetBrother(this));
		actions->Add(gcnew ActionTreeNodeGetSon(this));
		actions->Add(gcnew ActionTreeNodeInsertSon(this));
		actions->Add(gcnew ActionTreeNodeRemoveSon(this));
		actions->Add(gcnew ActionTreeNodeSubtreeSize(this));
		actions->Add(gcnew ActionTreeClear(this));
		actions->Add(gcnew ActionStructureSize(ActionTree::idaTreeSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionTree::idaTreeIS_EMPTY, this));
	}
}