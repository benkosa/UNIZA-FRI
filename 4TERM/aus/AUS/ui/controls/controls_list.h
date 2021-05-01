#pragma once

#include "../../structures/list/list.h"
#include "controls.h"
#include "../list/panel_list.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"

using namespace System::Windows::Forms;
using namespace System;
using namespace ui::log;

namespace ui
{

	/// <summary> Memento akcii zoznamov. </summary>
	private class ListActionMemento : public ActionMemento
	{
	public:
		int getIndex() { return index_; }
		data::DataType getDataBefore() { return dataBefore_; }
		data::DataType getDataAfter() { return dataAfter_; }

		void setIndex(int index) { index_ = index; }
		void setDataBefore(data::DataType byteBefore) { dataBefore_ = byteBefore; }
		void setDataAfter(data::DataType byteAfter) { dataAfter_ = byteAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		ListActionMemento(int actionID) :
			ActionMemento(actionID),
			index_(0),
			dataBefore_(data::DataType()),
			dataAfter_(data::DataType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		ListActionMemento(const ListActionMemento& other) :
			ActionMemento(other),
			index_(other.index_),
			dataBefore_(other.dataBefore_),
			dataAfter_(other.dataAfter_)
		{}

		ActionMemento* clone() override
		{
			return new ListActionMemento(*this);
		}
	private:
		/// <summary> Index dat. </summary>
		int index_;
		/// <summary> Stav dat pred operaciou. </summary>
		data::DataType dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		data::DataType dataAfter_;
	};

	/// <summary> Ovladace pre zoznamy. </summary>
	ref class ControlsList : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim zoznamu. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentList^ result = gcnew PanelPresentList();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (List != nullptr)
			{
				ListPanel->visualize(List);
			}
		}
	public:
		property structures::List<data::DataType>* List
		{
			structures::List<data::DataType>* get() { return dynamic_cast<structures::List<data::DataType>*>(Structure); };
		}

		property PanelPresentList^ ListPanel
		{
			PanelPresentList^ get() { return dynamic_cast<PanelPresentList^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsList() : ControlsHolder(structures::StructureADT::adtLIST) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu v zozname. </summary>
	ref class ActionList abstract : public Action
	{
	public:
		static const int idaListADD = 0;
		static const int idaListINSERT = 1;
		static const int idaListEDIT = 2;
		static const int idaListREMOVE = 3;
		static const int idaListREMOVE_AT_INDEX = 4;
		static const int idaListINDEX_OF = 5;
		static const int idaListCLEAR = 6;
		static const int idaListSIZE = 7;
		static const int idaListIS_EMPTY = 8;
	public:
		property ControlsList^ ListControls
		{
			ControlsList^ get() { return dynamic_cast<ControlsList^>(Controls); };
		}

		/// <summary> Vytvori akciu nad zoznamom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionList(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ listControls) : 
			Action(id, caption, supportsUndo, supportsRedo, listControls),
			index_(0),
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
			index_ = 0;
			dataEdit_ = data::DataType();
			result_ = false;

			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			index_ = listMemento->getIndex();
			dataEdit_ = listMemento->getDataBefore();
			result_ = false;
		}

	protected:
		int index_;
		data::DataType dataEdit_;
		bool result_;
	};

	/// <summary> Trieda predstavuje akciu vloz data na koniec zoznamu. </summary>
	ref class ActionListAdd : public ActionList
	{
	public:
		/// <summary> Vytvori akciu vloz data na koniec zoznamu. </summary>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionListAdd(ControlsHolder^ listControls) : 
			ActionList(idaListADD, "Add", true, true, listControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionList::doFormat() && 
				data::DataRoutines::editDataManaged(dataEdit_, "Data to add");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::DataType dataToAdd = dataEdit_;

			ListControls->List->add(dataToAdd);

			ListActionMemento* result = new ListActionMemento(ID);
			result->setDataBefore(dataToAdd);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			ListControls->List->tryRemove(listMemento->getDataBefore());
		}
	};

	/// <summary> Trieda predstavuje akciu vloz data do zoznamu na dany index. </summary>
	ref class ActionListInsert : public ActionList
	{
	public:
		/// <summary> Vytvori akciu vloz data do zoznamu na dany index. </summary>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionListInsert(ControlsHolder^ listControls) : 
			ActionList(idaListINSERT, "Insert", true, true, listControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionList::doFormat() && 
				data::DataRoutines::editDataManaged(dataEdit_, "Data to insert") && 
				data::DataRoutines::editNumberManaged(index_, "Enter index");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::DataType dataToInsert = dataEdit_;

			ListControls->List->insert(dataToInsert, index_);

			ListActionMemento* result = new ListActionMemento(ID);
			result->setDataBefore(dataToInsert);
			result->setIndex(index_);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			ListControls->List->removeAt(listMemento->getIndex());
		}
	};

	/// <summary> Trieda predstavuje operaciu uprav data v zozname. </summary>
	ref class ActionListEdit : public ActionList
	{
	public:
		/// <summary> Vytvori akciu uprav data v zozname. </summary>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionListEdit(ControlsHolder^ listControls) : 
			ActionList(idaListEDIT, "Edit", true,  true, listControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return ListControls->ListPanel->SelectedItem != nullptr;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (ActionList::doFormat())
			{
				index_ = ListControls->ListPanel->SelectedItem->Index;
				dataEdit_ = (*ListControls->List)[index_];

				return data::DataRoutines::editDataManaged(dataEdit_, "Edit data");
			}
			else
			{
				return false;
			}
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			index_ = listMemento->getIndex();
			dataEdit_ = listMemento->getDataAfter();
			result_ = false;
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{

			data::DataType dataBefore = (*ListControls->List)[index_];
			(*ListControls->List)[index_] = dataEdit_;
			data::DataType dataAfter = dataEdit_;

			ListActionMemento* result = new ListActionMemento(ID);
			result->setIndex(index_);
			result->setDataBefore(dataBefore);
			result->setDataAfter(dataAfter);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			(*ListControls->List)[listMemento->getIndex()] = listMemento->getDataBefore();
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			ListControls->ListPanel->refreshItem(ListControls->ListPanel->SelectedItem, dataEdit_);
		}
	};

	/// <summary> Trieda predstavuje akciu odstran data zo zoznamu. </summary>
	ref class ActionListTryToRemove : public ActionList
	{
	public:
		/// <summary> Vytvori akciu odstran data zo zoznamu. </summary>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionListTryToRemove(ControlsHolder^ listControls) : 
			ActionList(idaListREMOVE, "Remove", true, true, listControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (ActionList::doFormat() &&
				data::DataRoutines::editDataManaged(dataEdit_, "Data to remove"))
			{
				data::DataType dataToRemove = dataEdit_;
				index_ = ListControls->List->getIndexOf(dataToRemove);
				return true;
			}
			return false;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			dataEdit_ = listMemento->getDataAfter();

			data::DataType dataToRemove = dataEdit_;
			index_ = ListControls->List->getIndexOf(dataToRemove);
			result_ = false;
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::DataType dataToRemove = dataEdit_;

			result_ = ListControls->List->tryRemove(dataToRemove);
			
			ListActionMemento* result = new ListActionMemento(ID);
			result->setDataAfter(dataToRemove);
			result->setIndex(index_);
			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			if (listMemento->getIndex() >= 0)
			{
				ListControls->List->insert(listMemento->getDataAfter(), listMemento->getIndex());
			}
			else
			{
				Logger::getInstance()->logWarning("Revert of failed action " + Caption + " not possible.");
			}
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			if (result_)
			{
				ListControls->visualizeStructure();
			}
			else
			{
				Logger::getInstance()->logWarning("Action " + Caption + ": data " + Convert::ToString(dataEdit_) + " not found.");
			}
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu odstran zo zoznamu data na indexe. </summary>
	ref class ActionListRemoveAtIndex : public ActionList
	{
	public:
		/// <summary> Vytvori akciu odstran zo zoznamu zo zoznamu data na indexe. </summary>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionListRemoveAtIndex(ControlsHolder^ listControls) : 
			ActionList(idaListREMOVE_AT_INDEX, "Remove at index", true, true, listControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return ListControls->ListPanel->SelectedItem != nullptr;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (Action::doFormat())
			{
				index_ = ListControls->ListPanel->SelectedItem->Index;
				return true;
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
			dataEdit_ = ListControls->List->removeAt(index_);

			ListActionMemento* result = new ListActionMemento(ID);
			result->setIndex(index_);
			result->setDataAfter(dataEdit_);
			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			ListActionMemento* listMemento = dynamic_cast<ListActionMemento*>(memento);
			ListControls->List->insert(listMemento->getDataAfter(), listMemento->getIndex());
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showData(dataEdit_, "Removed data");
			ListControls->visualizeStructure();
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu index prvku v zozname. </summary>
	ref class ActionListIndexOf : public ActionList
	{
	public:
		/// <summary> Vytvori akciu index prvku v zozname. </summary>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionListIndexOf(ControlsHolder^ listControls) : 
			ActionList(idaListINDEX_OF, "Index of", false, true, listControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return Action::doFormat() && 
				data::DataRoutines::editDataManaged(dataEdit_, "Data to find index of");
		}
		
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::DataType dataToFindIndex = dataEdit_;

			index_ = ListControls->List->getIndexOf(dataToFindIndex);
			
			ListActionMemento* result = new ListActionMemento(ID);
			result->setDataBefore(dataEdit_);
			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showNumber(index_, "Index of data");
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu vymaz zoznam. </summary>
	ref class ActionListClear : public ActionList
	{
	public:
		/// <summary> Vytvori akciu vymaz zoznam. </summary>
		/// <param name = "listControls"> Ovladanie, do ktoreho patri. </param>
		ActionListClear(ControlsHolder^ listControls) : 
			ActionList(idaListCLEAR, "Clear", false, true, listControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			ListControls->List->clear();

			return new ListActionMemento(ID);
		}
	};

	void ControlsList::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionListAdd(this));
		actions->Add(gcnew ActionListInsert(this));
		actions->Add(gcnew ActionListEdit(this));
		actions->Add(gcnew ActionListTryToRemove(this));
		actions->Add(gcnew ActionListRemoveAtIndex(this));
		actions->Add(gcnew ActionListIndexOf(this));
		actions->Add(gcnew ActionListClear(this));
		actions->Add(gcnew ActionStructureSize(ActionList::idaListSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionList::idaListIS_EMPTY, this));
	}

}