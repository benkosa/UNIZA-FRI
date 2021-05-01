#pragma once

#include "../../structures/table/table.h"
#include "controls.h"
#include "../table/panel_table.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"
#include "../ui_routines.h"

using namespace System::Windows::Forms;
using namespace System;
using namespace ui::log;

namespace ui
{

	/// <summary> Memento akcii tabuliek. </summary>
	private class TableActionMemento : public ActionMemento
	{
	public:
		data::KeyType getKey() { return key_; }
		data::DataType getDataBefore() { return dataBefore_; }
		data::DataType getDataAfter() { return dataAfter_; }

		void setKey(data::KeyType key) { key_ = key; }
		void setDataBefore(data::DataType byteBefore) { dataBefore_ = byteBefore; }
		void setDataAfter(data::DataType byteAfter) { dataAfter_ = byteAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		TableActionMemento(int actionID) :
			ActionMemento(actionID),
			key_(data::KeyType()),
			dataBefore_(data::DataType()),
			dataAfter_(data::DataType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		TableActionMemento(const TableActionMemento& other) :
			ActionMemento(other),
			key_(other.key_),
			dataBefore_(other.dataBefore_),
			dataAfter_(other.dataAfter_)
		{}

		ActionMemento* clone() override
		{
			return new TableActionMemento(*this);
		}
	private:
		/// <summary> Kluc. </summary>
		data::KeyType key_;
		/// <summary> Stav dat pred operaciou. </summary>
		data::DataType dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		data::DataType dataAfter_;
	};

	/// <summary> Ovladace pre tabulky. </summary>
	ref class ControlsTable : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim zoznamu. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentTable^ result = gcnew PanelPresentTable();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (Table != nullptr)
			{
				TablePanel->visualize(Table);
			}
		}
	public:
		property structures::Table<data::KeyType, data::DataType>* Table
		{
			structures::Table<data::KeyType, data::DataType>* get() { return dynamic_cast<structures::Table<data::KeyType, data::DataType>*>(Structure); };
		}

		property PanelPresentTable^ TablePanel
		{
			PanelPresentTable^ get() { return dynamic_cast<PanelPresentTable^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsTable() : ControlsHolder(structures::StructureADT::adtTABLE) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu v tabulke. </summary>
	ref class ActionTable abstract : public Action
	{
	public:
		static const int idaTableINSERT = 0;
		static const int idaTableEDIT = 1;
		static const int idaTableREMOVE = 2;
		static const int idaTableTRY_FIND = 3;
		static const int idaTableCONTAINS_KEY = 4;
		static const int idaTableCLEAR = 5;
		static const int idaTableSIZE = 6;
		static const int idaTableIS_EMPTY = 7;

	public:
		property ControlsTable^ TableControls
		{
			ControlsTable^ get() { return dynamic_cast<ControlsTable^>(Controls); };
		}

		/// <summary> Vytvori akciu nad tabulkou. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "tableControls"> Ovladanie, do ktoreho patri. </param>
		ActionTable(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ tableControls) :
			Action(id, caption, supportsUndo, supportsRedo, tableControls),
			key_(data::KeyType()),
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
			key_ = data::KeyType();
			dataEdit_ = data::DataType();
			result_ = false;
				
			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			TableActionMemento* tableMemento = dynamic_cast<TableActionMemento*>(memento);
			key_ = tableMemento->getKey();
			dataEdit_ = tableMemento->getDataBefore();
			result_ = false;
		}

		/// <summary> Prezentuje vysledok akcie pouzivatelovi. </summary>
		void doPresentResult() override
		{
			TableControls->visualizeStructure();
		}

	protected:
		data::KeyType key_;
		data::DataType dataEdit_;
		bool result_;
	};

	/// <summary> Trieda predstavuje akciu vloz data s danym klucom do tabulky. </summary>
	ref class ActionTableInsert : public ActionTable
	{
	public:
		/// <summary> Vytvori akciu vloz data s danym klucom do tabulky. </summary>
		/// <param name = "tableControls"> Ovladanie, do ktoreho patri. </param>
		ActionTableInsert(ControlsHolder^ tableControls) : 
			ActionTable(idaTableINSERT, "Insert", true, true, tableControls) 
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTable::doFormat() &&
				data::DataRoutines::editKeyManaged(key_, "Key of data") &&
				data::DataRoutines::editDataManaged(dataEdit_, "Data to insert");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::KeyType keyToInsert = key_;
			data::DataType dataToInsert = dataEdit_;

			TableControls->Table->insert(keyToInsert, dataToInsert);

			TableActionMemento* result = new TableActionMemento(ID);
			result->setKey(keyToInsert);
			result->setDataBefore(dataToInsert);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			TableActionMemento* tableMemento = dynamic_cast<TableActionMemento*>(memento);
			TableControls->Table->remove(tableMemento->getKey());
		}
	};

	/// <summary> Trieda predstavuje akciu uprav data s danym klucom v tabulke. </summary>
	ref class ActionTableEdit : public ActionTable
	{
	public:
		/// <summary> Vytvori akciu uprav data s danym klucom v tabulke. </summary>
		/// <param name = "tableControls"> Ovladanie, do ktoreho patri. </param>
		ActionTableEdit(ControlsHolder^ tableControls) : 
			ActionTable(idaTableEDIT, "Edit", true, true, tableControls) 
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (ActionTable::doFormat() &&
				data::DataRoutines::editKeyManaged(key_, "Key of data"))
			{
				dataEdit_ = (*TableControls->Table)[key_];

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
			data::DataType dataBefore = (*TableControls->Table)[key_];
			(*TableControls->Table)[key_] = dataEdit_;
			data::DataType dataAfter = dataEdit_;

			TableActionMemento* result = new TableActionMemento(ID);
			result->setKey(key_);
			result->setDataBefore(dataBefore);
			result->setDataAfter(dataAfter);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			TableActionMemento* tableMemento = dynamic_cast<TableActionMemento*>(memento);
			(*TableControls->Table)[tableMemento->getKey()] = tableMemento->getDataBefore();
		}
	};

	/// <summary> Trieda predstavuje akciu odstran z tabulky data s danym klucom. </summary>
	ref class ActionTableRemove : public ActionTable
	{
	public:
		/// <summary> Vytvori akciu odstran z tabulky data s danym klucom. </summary>
		/// <param name = "tableControls"> Ovladanie, do ktoreho patri. </param>
		ActionTableRemove(ControlsHolder^ tableControls) : 
			ActionTable(idaTableREMOVE, "Remove", true, true, tableControls) 
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTable::doFormat() &&
				data::DataRoutines::editKeyManaged(key_, "Remove data with key");
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			TableActionMemento* tableMemento = dynamic_cast<TableActionMemento*>(memento);
			key_ = tableMemento->getKey();
			dataEdit_ = tableMemento->getDataAfter();
			result_ = false;
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::KeyType keyToRemove = key_;
			dataEdit_ = TableControls->Table->remove(keyToRemove);

			TableActionMemento* result = new TableActionMemento(ID);
			result->setKey(key_);
			result->setDataAfter(dataEdit_);
			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			TableActionMemento* tableMemento = dynamic_cast<TableActionMemento*>(memento);
			TableControls->Table->insert(tableMemento->getKey(), tableMemento->getDataAfter());
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showData(dataEdit_, "Removed data");
			ActionTable::doPresentResult();
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu bezpecne ziskaj data s danym klucom z tabulky. </summary>
	ref class ActionTableTryFind : public ActionTable
	{
	public:
		/// <summary> Vytvori akciu bezpecne ziskaj data s danym klucom z tabulky. </summary>
		/// <param name = "tableControls"> Ovladanie, do ktoreho patri. </param>
		ActionTableTryFind(ControlsHolder^ tableControls) : 
			ActionTable(idaTableTRY_FIND, "Try find", false, true, tableControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTable::doFormat() &&
				data::DataRoutines::editKeyManaged(key_, "Try find data with key");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::KeyType keyToFind = key_;
			data::DataType data = data::DataType();
			
			result_ = TableControls->Table->tryFind(keyToFind, data);
			dataEdit_ = data;

			TableActionMemento* result = new TableActionMemento(ID);
			result->setKey(key_);
			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			if (result_)
			{
				data::DataRoutines::showData(dataEdit_, "Found data");
			}
			else
			{
				Logger::getInstance()->logWarning("Action " + Caption + ": data with key " + Convert::ToString(key_) + " not found.");
			}
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}

	};

	/// <summary> Trieda predstavuje akciu obsahuje tabulka data s danym klucom. </summary>
	ref class ActionTableContainsKey : public ActionTable
	{
	public:
		/// <summary> Vytvori akciu obsahuje tabulka data s danym klucom. </summary>
		/// <param name = "tableControls"> Ovladanie, do ktoreho patri. </param>
		ActionTableContainsKey(ControlsHolder^ tableControls) : 
			ActionTable(idaTableCONTAINS_KEY, "Contains key", false, true, tableControls) 
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionTable::doFormat() &&
				data::DataRoutines::editKeyManaged(key_, "Enter key");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::KeyType keyToFind = key_;

			result_ = TableControls->Table->containsKey(keyToFind);

			TableActionMemento* result = new TableActionMemento(ID);
			result->setKey(key_);
			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			UIRoutines::showMessage(Caption, Convert::ToString(result_));
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu vymaz tabulku. </summary>
	ref class ActionTableClear : public ActionTable
	{
	public:
		/// <summary> Vytvori akciu vymaz tabulku. </summary>
		/// <param name = "tableControls"> Ovladanie, do ktoreho patri. </param>
		ActionTableClear(ControlsHolder^ tableControls) : 
			ActionTable(idaTableCLEAR, "Clear", false, true, tableControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			TableControls->Table->clear();

			return new TableActionMemento(ID);
		}
	};

	void ControlsTable::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionTableInsert(this));
		actions->Add(gcnew ActionTableEdit(this));
		actions->Add(gcnew ActionTableRemove(this));
		actions->Add(gcnew ActionTableTryFind(this));
		actions->Add(gcnew ActionTableContainsKey(this));
		actions->Add(gcnew ActionTableClear(this));
		actions->Add(gcnew ActionStructureSize(ActionTable::idaTableSIZE ,this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionTable::idaTableIS_EMPTY, this));
	}
}