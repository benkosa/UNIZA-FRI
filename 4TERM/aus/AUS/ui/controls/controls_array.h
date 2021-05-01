#pragma once

#include "../../structures/array/array.h"
#include "controls.h"
#include "../array/panel_array.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"

using namespace System::Windows::Forms;
using namespace System;

namespace ui
{

	/// <summary> Memento akcii poli. </summary>
	private class ArrayActionMemento : public ActionMemento
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
		ArrayActionMemento(int actionID) :
			ActionMemento(actionID),
			index_(0),
			dataBefore_(data::DataType()),
			dataAfter_(data::DataType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		ArrayActionMemento(const ArrayActionMemento& other) :
			ActionMemento(other),
			index_(other.index_),
			dataBefore_(other.dataBefore_),
			dataAfter_(other.dataAfter_)
		{}

		ActionMemento* clone() override
		{
			return new ArrayActionMemento(*this);
		}

	private:
		/// <summary> Index dat. </summary>
		int index_;
		/// <summary> Stav dat pred operaciou. </summary>
		data::DataType dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		data::DataType dataAfter_;
	};

	/// <summary> Ovladace pre polia. </summary>
	ref class ControlsArray : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim pola. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentArray^ result = gcnew PanelPresentArray();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (Array != nullptr)
			{
				ArrayPanel->visualize(Array);
			}
		}

	public:
		property structures::Array<data::DataType>* Array
		{
			structures::Array<data::DataType>* get() { return dynamic_cast<structures::Array<data::DataType>*>(Structure); };
		}

		property PanelPresentArray^ ArrayPanel
		{
			PanelPresentArray^ get() { return dynamic_cast<PanelPresentArray^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsArray() : ControlsHolder(structures::StructureADT::adtARRAY) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu v poli. </summary>
	ref class ActionArray abstract : public Action
	{
	public:
		static const int idaArrEDIT = 0;
		static const int idaArrSIZE = 1;
		static const int idaArrIS_EMPTY = 2;

	public:
		property ControlsArray^ ArrayControls
		{
			ControlsArray^ get() { return dynamic_cast<ControlsArray^>(Controls); };
		}

		/// <summary> Vytvori akciu nad polom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "arrayControls"> Ovladanie, do ktoreho patri. </param>
		ActionArray(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ arrayControls) : 
			Action(id, caption, supportsUndo, supportsRedo, arrayControls),
			index_(0),
			dataEdit_(data::DataType())
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return ArrayControls->ArrayPanel->SelectedItem != nullptr;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			index_ = ArrayControls->ArrayPanel->SelectedItem->Index;
			dataEdit_ = (*ArrayControls->Array)[index_];

			return true;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			ArrayActionMemento* arrayMemento = dynamic_cast<ArrayActionMemento*>(memento);
			(*ArrayControls->Array)[arrayMemento->getIndex()] = arrayMemento->getDataBefore();
		}

	protected:
		int index_;
		data::DataType dataEdit_;
	};

	/// <summary> Trieda predstavuje operaciu uprav data v poli. </summary>
	ref class ActionArrayEdit : public ActionArray
	{
	public:
		/// <summary> Vytvori akciu uprav data v poli. </summary>
		/// <param name = "arrayControls"> Ovladanie, do ktoreho patri. </param>
		ActionArrayEdit(ControlsHolder^ arrayControls) : 
			ActionArray(idaArrEDIT, "Edit", true, true, arrayControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionArray::doFormat() && 
				data::DataRoutines::editDataManaged(dataEdit_, "Edit data");
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			ArrayActionMemento* arrayMemento = dynamic_cast<ArrayActionMemento*>(memento);
			index_ = arrayMemento->getIndex();
			dataEdit_ = arrayMemento->getDataAfter();
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::DataType dataBefore = (*ArrayControls->Array)[index_];
			(*ArrayControls->Array)[index_] = dataEdit_;
			data::DataType dataAfter = dataEdit_;

			ArrayActionMemento* result = new ArrayActionMemento(ID);
			result->setIndex(index_);
			result->setDataBefore(dataBefore);
			result->setDataAfter(dataAfter);

			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			ArrayControls->ArrayPanel->refreshSelectedItem();
		}
	};

	void ControlsArray::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionArrayEdit(this));
		actions->Add(gcnew ActionStructureSize(ActionArray::idaArrSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionArray::idaArrIS_EMPTY, this));
	}
}