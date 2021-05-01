#pragma once

#include "../../structures/priority_queue/priority_queue.h"
#include "controls.h"
#include "../priority_queue/panel_priority_queue.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"

using namespace System::Windows::Forms;
using namespace System;
using namespace ui::log;

namespace ui
{
	/// <summary> Memento akcii prioritnych frontov. </summary>
	private class PriorityQueueActionMemento : public ActionMemento
	{
	public:
		data::PriorityType getPriority() { return priority_; }
		data::DataType getDataBefore() { return dataBefore_; }
		data::DataType getDataAfter() { return dataAfter_; }

		void setPriority(data::PriorityType priority) { priority_ = priority; }
		void setDataBefore(data::DataType byteBefore) { dataBefore_ = byteBefore; }
		void setDataAfter(data::DataType byteAfter) { dataAfter_ = byteAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		PriorityQueueActionMemento(int actionID) :
			ActionMemento(actionID),
			priority_(data::PriorityType()),
			dataBefore_(data::DataType()),
			dataAfter_(data::DataType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		PriorityQueueActionMemento(const PriorityQueueActionMemento& other) :
			ActionMemento(other),
			priority_(other.priority_),
			dataBefore_(other.dataBefore_),
			dataAfter_(other.dataAfter_)
		{}

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat mementa typu PriorityQueueActionMemento. </summary>
		/// <returns> Ukazovatel na klon mementa. </returns>
		ActionMemento* clone() override
		{
			return new PriorityQueueActionMemento(*this);
		}
	private:
		/// <summary> Priorita. </summary>
		data::PriorityType priority_;
		/// <summary> Stav dat pred operaciou. </summary>
		data::DataType dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		data::DataType dataAfter_;
	};

	/// <summary> Ovladace pre prioritne fronty. </summary>
	ref class ControlsPriorityQueue : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim prioritneho frontu. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentPriorityQueue^ result = gcnew PanelPresentPriorityQueue();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (PriorityQueue != nullptr)
			{
				PriorityQueuePanel->visualize(PriorityQueue);
			}
		}
	public:
		property structures::PriorityQueue<data::DataType>* PriorityQueue
		{
			structures::PriorityQueue<data::DataType>* get() { return dynamic_cast<structures::PriorityQueue<data::DataType>*>(Structure); };
		}

		property PanelPresentPriorityQueue^ PriorityQueuePanel
		{
			PanelPresentPriorityQueue^ get() { return dynamic_cast<PanelPresentPriorityQueue^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsPriorityQueue() : ControlsHolder(structures::StructureADT::adtPRIORITY_QUEUE) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu v prioritnom fronte. </summary>
	ref class ActionPriorityQueue abstract : public Action
	{
	public:
		static const int idaPriorityQueuePUSH = 0;
		static const int idaPriorityQueuePOP = 1;
		static const int idaPriorityQueuePEEK = 2;
		static const int idaPriorityQueuePEEK_PRIORITY = 3;
		static const int idaPriorityQueueCLEAR = 4;
		static const int idaPriorityQueueSIZE = 5;
		static const int idaPriorityQueueIS_EMPTY = 6;
	public:
		property ControlsPriorityQueue^ PriorityQueueControls
		{
			ControlsPriorityQueue^ get() { return dynamic_cast<ControlsPriorityQueue^>(Controls); };
		}

		/// <summary> Vytvori akciu nad prioritnym frontom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "priorityQueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionPriorityQueue(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ priorityQueueControls) :
			Action(id, caption, supportsUndo, supportsRedo, priorityQueueControls),
			priority_(data::PriorityType()),
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
			priority_ = data::PriorityType();
			dataEdit_ = data::DataType();

			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			PriorityQueueActionMemento* priorityQueueMemento = dynamic_cast<PriorityQueueActionMemento*>(memento);
			priority_ = priorityQueueMemento->getPriority();
			dataEdit_ = priorityQueueMemento->getDataBefore();
		}

		/// <summary> Prezentuje vysledok akcie pouzivatelovi. </summary>
		void doPresentResult() override
		{
			PriorityQueueControls->visualizeStructure();
		}

	protected:
		/// <summary> Priorita. </summary>
		data::PriorityType priority_;
		/// <summary> Editovane data. </summary>
		data::DataType dataEdit_;
	};

	/// <summary> Trieda predstavuje akciu vloz data s danou prioritou do prioritneho frontu. </summary>
	ref class ActionPriorityQueuePush : public ActionPriorityQueue
	{
	public:
		/// <summary> Vytvori akciu vloz data s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priorityQueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionPriorityQueuePush(ControlsHolder^ priorityQueueControls) :
			ActionPriorityQueue(idaPriorityQueuePUSH, "Push", false, true, priorityQueueControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionPriorityQueue::doFormat() &&
				data::DataRoutines::editPriorityManaged(priority_, "Priority of data") &&
				data::DataRoutines::editDataManaged(dataEdit_, "Data to insert");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::PriorityType priorityToPush = priority_;
			data::DataType dataToPush = dataEdit_;

			PriorityQueueControls->PriorityQueue->push(priorityToPush, dataToPush);

			PriorityQueueActionMemento* result = new PriorityQueueActionMemento(ID);
			result->setPriority(priorityToPush);
			result->setDataBefore(dataToPush);

			return result;
		}
	};

	/// <summary> Trieda predstavuje akciu odstran prvok s najvacsou prioritou z prioritneho frontu. </summary>
	ref class ActionPriorityQueuePop : public ActionPriorityQueue
	{
	public:
		/// <summary> Vytvori akciu vloz data s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priorityQueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionPriorityQueuePop(ControlsHolder^ priorityQueueControls) :
			ActionPriorityQueue(idaPriorityQueuePOP, "Pop", true, true, priorityQueueControls)
		{}

		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			structures::PriorityQueue<data::DataType>* priorityQueue = PriorityQueueControls->PriorityQueue;
			return priorityQueue != nullptr && !PriorityQueueControls->PriorityQueue->isEmpty();
		}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			PriorityQueueActionMemento* priorityQueueMemento = dynamic_cast<PriorityQueueActionMemento*>(memento);
			priority_ = priorityQueueMemento->getPriority();
			dataEdit_ = priorityQueueMemento->getDataAfter();
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::PriorityType priorityToPop = PriorityQueueControls->PriorityQueue->peekPriority();
			dataEdit_ = PriorityQueueControls->PriorityQueue->pop();

			PriorityQueueActionMemento* result = new PriorityQueueActionMemento(ID);
			result->setPriority(priorityToPop);
			result->setDataAfter(dataEdit_);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			PriorityQueueActionMemento* priorityQueueMemento = dynamic_cast<PriorityQueueActionMemento*>(memento);
			PriorityQueueControls->PriorityQueue->push(priorityQueueMemento->getPriority(), priorityQueueMemento->getDataAfter());
		}
	};

	/// <summary> Trieda predstavuje akciu spristupni prvok s najvacsou prioritou v priortnom fronte. </summary>
	ref class ActionPriorityQueuePeek : public ActionPriorityQueue
	{
	public:
		/// <summary> Vytvori akciu spristupni prvok s najvacsou prioritou v prioritnom fronte. </summary>
		/// <param name = "priorityQueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionPriorityQueuePeek(ControlsHolder^ priorityQueueControls) :
			ActionPriorityQueue(idaPriorityQueuePEEK, "Peek", false, true, priorityQueueControls)
		{}

		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			structures::PriorityQueue<data::DataType>* priorityQueue = PriorityQueueControls->PriorityQueue;
			return priorityQueue != nullptr && !PriorityQueueControls->PriorityQueue->isEmpty();
		}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			dataEdit_ = PriorityQueueControls->PriorityQueue->peek();

			PriorityQueueActionMemento* result = new PriorityQueueActionMemento(ID);
			result->setDataBefore(dataEdit_);
			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showData(dataEdit_, "Data with maximal priority");
			ActionPriorityQueue::doPresentResult();
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu spristupni najvacsiu prioritu v prioritnom fronte. </summary>
	ref class ActionPriorityQueuePeekPriority : public ActionPriorityQueue
	{
	public:
		/// <summary> Vytvori akciu spristupni prvok s najvacsou prioritou v priortnom fronte. </summary>
		/// <param name = "priorityQueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionPriorityQueuePeekPriority(ControlsHolder^ priorityQueueControls) :
			ActionPriorityQueue(idaPriorityQueuePEEK_PRIORITY, "Peek priority", false, true, priorityQueueControls)
		{}

		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			structures::PriorityQueue<data::DataType>* priorityQueue = PriorityQueueControls->PriorityQueue;
			return priorityQueue != nullptr && !PriorityQueueControls->PriorityQueue->isEmpty();
		}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			priority_ = PriorityQueueControls->PriorityQueue->peekPriority();

			PriorityQueueActionMemento* result = new PriorityQueueActionMemento(ID);
			result->setPriority(priority_);
			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showData(priority_, "Maximal priority");
			ActionPriorityQueue::doPresentResult();
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu vyprazdni prioritny front. </summary>
	ref class ActionPriorityQueueClear : public ActionPriorityQueue
	{
	public:
		/// <summary> Vytvori akciu akciu vyprazdni prioritny front. </summary>
		/// <param name = "priorityQueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionPriorityQueueClear(ControlsHolder^ priorityQueueControls) :
			ActionPriorityQueue(idaPriorityQueueCLEAR, "Clear", false, true, priorityQueueControls)
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			PriorityQueueControls->PriorityQueue->clear();

			return new PriorityQueueActionMemento(ID);
		}
	};

	void ControlsPriorityQueue::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionPriorityQueuePush(this));
		actions->Add(gcnew ActionPriorityQueuePop(this));
		actions->Add(gcnew ActionPriorityQueuePeek(this));
		actions->Add(gcnew ActionPriorityQueuePeekPriority(this));
		actions->Add(gcnew ActionPriorityQueueClear(this));
		actions->Add(gcnew ActionStructureSize(ActionPriorityQueue::idaPriorityQueueSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionPriorityQueue::idaPriorityQueueIS_EMPTY, this));
	}
}