#pragma once

#include "../../structures/stack/stack.h"
#include "controls.h"
#include "../stack/panel_stack.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"

using namespace System::Windows::Forms;
using namespace System;
using namespace ui::log;

namespace ui
{
	/// <summary> Memento akcii zasobnikov. </summary>
	private class StackActionMemento : public ActionMemento
	{
	public:
		data::DataType getDataBefore() { return dataBefore_; }
		data::DataType getDataAfter() { return dataAfter_; }

		void setDataBefore(data::DataType byteBefore) { dataBefore_ = byteBefore; }
		void setDataAfter(data::DataType byteAfter) { dataAfter_ = byteAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		StackActionMemento(int actionID) :
			ActionMemento(actionID),
			dataBefore_(data::DataType()),
			dataAfter_(data::DataType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		StackActionMemento(const StackActionMemento& other) :
			ActionMemento(other),
			dataBefore_(other.dataBefore_),
			dataAfter_(other.dataAfter_)
		{}

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat mementa typu StackActionMemento. </summary>
		/// <returns> Ukazovatel na klon mementa. </returns>
		ActionMemento* clone() override
		{
			return new StackActionMemento(*this);
		}
	private:
		/// <summary> Stav dat pred operaciou. </summary>
		data::DataType dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		data::DataType dataAfter_;
	};

	/// <summary> Ovladace pre zasobniky. </summary>
	ref class ControlsStack : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim zasobnika. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentStack^ result = gcnew PanelPresentStack();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (Stack != nullptr)
			{
				StackPanel->visualize(Stack);
			}
		}
	public:
		property structures::Stack<data::DataType>* Stack
		{
			structures::Stack<data::DataType>* get() { return dynamic_cast<structures::Stack<data::DataType>*>(Structure); };
		}

		property PanelPresentStack^ StackPanel
		{
			PanelPresentStack^ get() { return dynamic_cast<PanelPresentStack^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsStack() : ControlsHolder(structures::StructureADT::adtSTACK) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu v zasobniku. </summary>
	ref class ActionStack abstract : public Action
	{
	public:
		static const int idaStackPUSH = 0;
		static const int idaStackPOP = 1;
		static const int idaStackPEEK = 2;
		static const int idaStackCLEAR = 3;
		static const int idaStackSIZE = 4;
		static const int idaStackIS_EMPTY = 5;
	public:
		property ControlsStack^ StackControls
		{
			ControlsStack^ get() { return dynamic_cast<ControlsStack^>(Controls); };
		}

		/// <summary> Vytvori akciu nad zasobnikom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "StackControls"> Ovladanie, do ktoreho patri. </param>
		ActionStack(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ StackControls) :
			Action(id, caption, supportsUndo, supportsRedo, StackControls),
			dataEdit_(data::DataType())
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
			dataEdit_ = data::DataType();

			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			StackActionMemento* StackMemento = dynamic_cast<StackActionMemento*>(memento);
			dataEdit_ = StackMemento->getDataBefore();
		}

		/// <summary> Prezentuje vysledok akcie pouzivatelovi. </summary>
		void doPresentResult() override
		{
			StackControls->visualizeStructure();
		}

	protected:
		/// <summary> Editovane data. </summary>
		data::DataType dataEdit_;
	};

	/// <summary> Trieda predstavuje akciu vloz data do zasobnika. </summary>
	ref class ActionStackPush : public ActionStack
	{
	public:
		/// <summary> Vytvori akciu vloz data do zasobnika. </summary>
		/// <param name = "StackControls"> Ovladanie, do ktoreho patri. </param>
		ActionStackPush(ControlsHolder^ StackControls) :
			ActionStack(idaStackPUSH, "Push", true, true, StackControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionStack::doFormat() &&
				data::DataRoutines::editDataManaged(dataEdit_, "Data to insert");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::DataType dataToPush = dataEdit_;

			StackControls->Stack->push(dataToPush);

			StackActionMemento* result = new StackActionMemento(ID);
			result->setDataBefore(dataToPush);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			StackControls->Stack->pop();
		}
	};

	/// <summary> Trieda predstavuje akciu odstran prvok zo zasobnika. </summary>
	ref class ActionStackPop : public ActionStack
	{
	public:
		/// <summary> Vytvori akciu vloz data zo zasobnika. </summary>
		/// <param name = "StackControls"> Ovladanie, do ktoreho patri. </param>
		ActionStackPop(ControlsHolder^ StackControls) :
			ActionStack(idaStackPOP, "Pop", true, true, StackControls)
		{}

		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			structures::Stack<data::DataType>* Stack = StackControls->Stack;
			return Stack != nullptr && !StackControls->Stack->isEmpty();
		}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			StackActionMemento* StackMemento = dynamic_cast<StackActionMemento*>(memento);
			dataEdit_ = StackMemento->getDataAfter();
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			dataEdit_ = StackControls->Stack->pop();

			StackActionMemento* result = new StackActionMemento(ID);
			result->setDataAfter(dataEdit_);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			StackActionMemento* StackMemento = dynamic_cast<StackActionMemento*>(memento);
			StackControls->Stack->push(StackMemento->getDataAfter());
		}
	};

	/// <summary> Trieda predstavuje akciu spristupni prvok v zasobniku. </summary>
	ref class ActionStackPeek : public ActionStack
	{
	public:
		/// <summary> Vytvori akciu spristupni prvok v zasobniku. </summary>
		/// <param name = "StackControls"> Ovladanie, do ktoreho patri. </param>
		ActionStackPeek(ControlsHolder^ StackControls) :
			ActionStack(idaStackPEEK, "Peek", false, true, StackControls)
		{}

		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			structures::Stack<data::DataType>* Stack = StackControls->Stack;
			return Stack != nullptr && !StackControls->Stack->isEmpty();
		}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			dataEdit_ = StackControls->Stack->peek();

			StackActionMemento* result = new StackActionMemento(ID);
			result->setDataBefore(dataEdit_);
			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showData(dataEdit_, "Data");
			ActionStack::doPresentResult();
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu vyprazdni zasobnik. </summary>
	ref class ActionStackClear : public ActionStack
	{
	public:
		/// <summary> Vytvori akciu akciu vyprazdni zasobnik. </summary>
		/// <param name = "StackControls"> Ovladanie, do ktoreho patri. </param>
		ActionStackClear(ControlsHolder^ StackControls) :
			ActionStack(idaStackCLEAR, "Clear", false, true, StackControls)
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			StackControls->Stack->clear();

			return new StackActionMemento(ID);
		}
	};

	void ControlsStack::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionStackPush(this));
		actions->Add(gcnew ActionStackPop(this));
		actions->Add(gcnew ActionStackPeek(this));
		actions->Add(gcnew ActionStackClear(this));
		actions->Add(gcnew ActionStructureSize(ActionStack::idaStackSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionStack::idaStackIS_EMPTY, this));
	}
}