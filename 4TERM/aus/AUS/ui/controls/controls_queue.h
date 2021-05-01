#pragma once

#include "../../structures/queue/queue.h"
#include "controls.h"
#include "../queue/panel_queue.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"

using namespace System::Windows::Forms;
using namespace System;
using namespace ui::log;

namespace ui
{
	/// <summary> Memento akcii frontov. </summary>
	private class QueueActionMemento : public ActionMemento
	{
	public:
		data::DataType getDataBefore() { return dataBefore_; }
		data::DataType getDataAfter() { return dataAfter_; }

		void setDataBefore(data::DataType byteBefore) { dataBefore_ = byteBefore; }
		void setDataAfter(data::DataType byteAfter) { dataAfter_ = byteAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		QueueActionMemento(int actionID) :
			ActionMemento(actionID),
			dataBefore_(data::DataType()),
			dataAfter_(data::DataType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		QueueActionMemento(const QueueActionMemento& other) :
			ActionMemento(other),
			dataBefore_(other.dataBefore_),
			dataAfter_(other.dataAfter_)
		{}

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat mementa typu QueueActionMemento. </summary>
		/// <returns> Ukazovatel na klon mementa. </returns>
		ActionMemento* clone() override
		{
			return new QueueActionMemento(*this);
		}
	private:
		/// <summary> Stav dat pred operaciou. </summary>
		data::DataType dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		data::DataType dataAfter_;
	};

	/// <summary> Ovladace pre fronty. </summary>
	ref class ControlsQueue : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim frontu. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentQueue^ result = gcnew PanelPresentQueue();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (Queue != nullptr)
			{
				QueuePanel->visualize(Queue);
			}
		}
	public:
		property structures::Queue<data::DataType>* Queue
		{
			structures::Queue<data::DataType>* get() { return dynamic_cast<structures::Queue<data::DataType>*>(Structure); };
		}

		property PanelPresentQueue^ QueuePanel
		{
			PanelPresentQueue^ get() { return dynamic_cast<PanelPresentQueue^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsQueue() : ControlsHolder(structures::StructureADT::adtQUEUE) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu vo fronte. </summary>
	ref class ActionQueue abstract : public Action
	{
	public:
		static const int idaQueuePUSH = 0;
		static const int idaQueuePOP = 1;
		static const int idaQueuePEEK = 2;
		static const int idaQueueCLEAR = 3;
		static const int idaQueueSIZE = 4;
		static const int idaQueueIS_EMPTY = 5;
	public:
		property ControlsQueue^ QueueControls
		{
			ControlsQueue^ get() { return dynamic_cast<ControlsQueue^>(Controls); };
		}

		/// <summary> Vytvori akciu nad frontom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "QueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionQueue(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ QueueControls) :
			Action(id, caption, supportsUndo, supportsRedo, QueueControls),
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
			QueueActionMemento* QueueMemento = dynamic_cast<QueueActionMemento*>(memento);
			dataEdit_ = QueueMemento->getDataBefore();
		}

		/// <summary> Prezentuje vysledok akcie pouzivatelovi. </summary>
		void doPresentResult() override
		{
			QueueControls->visualizeStructure();
		}

	protected:
		/// <summary> Editovane data. </summary>
		data::DataType dataEdit_;
	};

	/// <summary> Trieda predstavuje akciu vloz data do frontu. </summary>
	ref class ActionQueuePush : public ActionQueue
	{
	public:
		/// <summary> Vytvori akciu vloz data do frontu. </summary>
		/// <param name = "QueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionQueuePush(ControlsHolder^ QueueControls) :
			ActionQueue(idaQueuePUSH, "Push", false, true, QueueControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionQueue::doFormat() &&
				data::DataRoutines::editDataManaged(dataEdit_, "Data to insert");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::DataType dataToPush = dataEdit_;

			QueueControls->Queue->push(dataToPush);

			QueueActionMemento* result = new QueueActionMemento(ID);
			result->setDataBefore(dataToPush);

			return result;
		}
	};

	/// <summary> Trieda predstavuje akciu odstran prvok z frontu. </summary>
	ref class ActionQueuePop : public ActionQueue
	{
	public:
		/// <summary> Vytvori akciu vloz data z frontu. </summary>
		/// <param name = "QueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionQueuePop(ControlsHolder^ QueueControls) :
			ActionQueue(idaQueuePOP, "Pop", false, true, QueueControls)
		{}

		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			structures::Queue<data::DataType>* Queue = QueueControls->Queue;
			return Queue != nullptr && !QueueControls->Queue->isEmpty();
		}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			QueueActionMemento* QueueMemento = dynamic_cast<QueueActionMemento*>(memento);
			dataEdit_ = QueueMemento->getDataAfter();
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			dataEdit_ = QueueControls->Queue->pop();

			QueueActionMemento* result = new QueueActionMemento(ID);
			result->setDataAfter(dataEdit_);

			return result;
		}
	};

	/// <summary> Trieda predstavuje akciu spristupni prvok vo fronte. </summary>
	ref class ActionQueuePeek : public ActionQueue
	{
	public:
		/// <summary> Vytvori akciu spristupni prvok vo fronte. </summary>
		/// <param name = "QueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionQueuePeek(ControlsHolder^ QueueControls) :
			ActionQueue(idaQueuePEEK, "Peek", false, true, QueueControls)
		{}

		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			structures::Queue<data::DataType>* Queue = QueueControls->Queue;
			return Queue != nullptr && !QueueControls->Queue->isEmpty();
		}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			dataEdit_ = QueueControls->Queue->peek();

			QueueActionMemento* result = new QueueActionMemento(ID);
			result->setDataBefore(dataEdit_);
			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			data::DataRoutines::showData(dataEdit_, "Data");
			ActionQueue::doPresentResult();
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	};

	/// <summary> Trieda predstavuje akciu vyprazdni front. </summary>
	ref class ActionQueueClear : public ActionQueue
	{
	public:
		/// <summary> Vytvori akciu akciu vyprazdni front. </summary>
		/// <param name = "QueueControls"> Ovladanie, do ktoreho patri. </param>
		ActionQueueClear(ControlsHolder^ QueueControls) :
			ActionQueue(idaQueueCLEAR, "Clear", false, true, QueueControls)
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			QueueControls->Queue->clear();

			return new QueueActionMemento(ID);
		}
	};

	void ControlsQueue::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionQueuePush(this));
		actions->Add(gcnew ActionQueuePop(this));
		actions->Add(gcnew ActionQueuePeek(this));
		actions->Add(gcnew ActionQueueClear(this));
		actions->Add(gcnew ActionStructureSize(ActionQueue::idaQueueSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionQueue::idaQueueIS_EMPTY, this));
	}
}