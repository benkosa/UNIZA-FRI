#include "controls.h"
#include "controls_vector.h"
#include "controls_array.h"
#include "controls_list.h"
#include "controls_stack.h"
#include "controls_queue.h"
#include "controls_priority_queue.h"
#include "controls_tree.h"
#include "controls_table.h"
#include "controls_graph.h"
#include "../ui_routines.h"
#include "../logger/ui_logger.h"
#include "../performance_chart/performance.h"
#include "../action_history/action_history.h"

using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace ui {
	
	ControlsDirector::ControlsDirector() :
		controlsHolders_(gcnew Dictionary<int, ControlsHolder^>)
	{
	}

	ControlsDirector ^ ControlsDirector::getInstance()
	{
		if (director_ == nullptr)
		{
			director_ = gcnew ControlsDirector();
		}
		return director_;
	}

	ControlsHolder ^ ControlsDirector::createControlsHolderInstance(structures::StructureADT adt, Control^ parent)
	{
		ControlsHolder^ result = getControlsHolderInstance(adt);

		if (result != nullptr)
		{
			controlsHolders_->Add(adt, result);

			// vytvorenie instance:
			result->createPanels(parent);
			result->createActions(result->Actions);

			for each (Action^ action in result->Actions)
			{
				action->createButton(result->ControlsPanel->ControlsPanel);
			}

			result->enableControls();
			
		}
		return result;
	}

	ControlsHolder ^ ControlsDirector::getControlsHolderInstance(structures::StructureADT adt)
	{
		ControlsHolder^ result = nullptr;

		if (!controlsHolders_->TryGetValue(adt, result))
		{
			switch (adt)
			{
			case structures::StructureADT::adtVECTOR:
				result = gcnew ControlsVector();
				break;
			case structures::StructureADT::adtARRAY:
				result = gcnew ControlsArray();
				break;
			case structures::StructureADT::adtLIST:
				result = gcnew ControlsList();
				break;
			case structures::StructureADT::adtSTACK:
				result = gcnew ControlsStack();
				break;
			case structures::StructureADT::adtQUEUE:
				result = gcnew ControlsQueue();
				break;
			case structures::StructureADT::adtPRIORITY_QUEUE:
				result = gcnew ControlsPriorityQueue();
				break;
			case structures::StructureADT::adtTREE:
				result = gcnew ControlsTree();
				break;
			case structures::StructureADT::adtTABLE:
				result = gcnew ControlsTable();
				break;
			case structures::StructureADT::adtGRAPH:
				result = gcnew ControlsGraph();
				break;
			}
						
		}
		return result;
	}

	structures::Structure* ControlsHolder::Structure::get()
	{
		return structure_;
	}

	void ControlsHolder::Structure::set(structures::Structure* structure)
	{
		structure_ = structure;

		lock_->beginUpdate();

		if (structure != nullptr)
		{
			visualizeStructure();
			panelControls_->PanelPerformance->presentStructure(Structure, ADT);
			panelControls_->PanelHistory->presentStructure(Structure, ADT);
			show();
		}
		else
		{
			hide();
		}

		lock_->endUpdate();
	}

	ControlsHolder::ControlsHolder(structures::StructureADT adt) :
		adt_(adt),
		actions_(gcnew Generic::List<Action^>),
		panelControls_(nullptr),
		lock_(gcnew ControlsLock())
	{
	}

	void ControlsHolder::createPanels(Control^ parent)
	{
		// vytvorim panely
		panelControls_ = gcnew PanelControls();
		panelControls_->SuspendLayout();
		panelControls_->PanelPresent = doCreatePresentPanel();
		panelControls_->Dock = DockStyle::Fill;
		parent->Controls->Add(panelControls_);
		panelControls_->ResumeLayout();		
	}

	void ControlsHolder::visualizeStructure()
	{
		try
		{
			doVisualizeStructure();
			panelControls_->showPresentPanel(true);
			enableControls();
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
			log::Logger::getInstance()->logWarning("Structure can not be visualized.");
			panelControls_->showPresentPanel(false);
		}
		catch (System::Exception^ ex)
		{
			log::Logger::getInstance()->logError(ex->Message);
			log::Logger::getInstance()->logWarning("Structure can not be visualized.");
			panelControls_->showPresentPanel(false);
		}
	}

	void ControlsHolder::show()
	{
		if (panelControls_ != nullptr)
		{
			panelControls_->Visible = true;
		}
	}

	void ControlsHolder::hide()
	{
		if (panelControls_ != nullptr)
		{
			panelControls_->Visible = false;
		}
	}

	Action ^ ControlsHolder::getAction(int actionID)
	{
		for each(Action^ action in actions_)
		{
			if (action->ID == actionID)
			{
				return action;
			}
		}

		return nullptr;
	}

	void ControlsHolder::enableControls()
	{
		for each (Action^ action in actions_)
		{
			action->tryEnable();
		}
	}

	Action::Action(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ controlsHolder):
		id_(id),
		caption_(caption),
		enabled_(false),
		supportsUndo_(supportsUndo),
		supportsRedo_(supportsRedo),
		controlsHolder_(controlsHolder),
		controls_(gcnew Generic::List<Control^>()),
		timer_(new TimeMeasurement())
	{
		StructuresPerformanceHolder::getInstance()->registerInfo(controlsHolder_->ADT, id_, UIRoutines::convertStringtoStr(caption_));
		StructuresActionHistoryHolder::getInstance()->registerInfo(controlsHolder_->ADT, id_, UIRoutines::convertStringtoStr(caption_));
	}

	Action::~Action()
	{
		this->!Action();
	}

	Action::!Action()
	{
		delete timer_;
		timer_ = nullptr;
	}

	ActionMemento* Action::execute()
	{
		ActionMemento* result = nullptr;

		try
		{
			size_t size = Controls->Structure->size();
			timer_->reset();

			// krok 1
			if (doFormat())
			{
				// krok 2
				timer_->start();
				result = doExecute();
				timer_->stop();

				// krok 3
				doPresentResult();

				// krok 4
				long elapsed = static_cast<long>(timer_->elapsed().count());
				
					// 4 a) Log
					Logger::getInstance()->logDebug("Operation " + Caption + " finished in " + System::Convert::ToString(elapsed) + " ms."); 

					// 4 b) Historia
					OperationInfo* historyInfo = StructuresActionHistoryHolder::getInstance()->createAndStoreInfo(Controls->Structure, Controls->ADT, result, elapsed);
					Controls->ControlsPanel->PanelHistory->actionPerformed(historyInfo);

					// 4 c) Vykon
					PerformanceInfo* performanceInfo = StructuresPerformanceHolder::getInstance()->createAndStoreInfo(Controls->Structure, Controls->ADT, id_, size, elapsed);
					Controls->ControlsPanel->PanelPerformance->actionPerformed(performanceInfo);
			}
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
		}
		catch (System::Exception^ ex)
		{
			log::Logger::getInstance()->logError(ex->Message);
		}
		Controls->enableControls();
		return result;
	}

	ActionMemento * Action::redo(ActionMemento * memento, bool interact)
	{
		ActionMemento* result = nullptr;

		if (supportsRedo_)
		{
			try
			{
				size_t size = Controls->Structure->size();
				timer_->reset();

				// krok 1
				doFormat(memento);

				// krok 2
				timer_->start();
				result = doExecute();
				timer_->stop();

				if (interact)
				{
					// krok 3
					doPresentRedoResult();

					// krok 4
					long elapsed = static_cast<long>(timer_->elapsed().count());

					// 4 a) Log
					Logger::getInstance()->logDebug("Operation " + Caption + " finished in " + System::Convert::ToString(elapsed) + " ms.");

					// 4 b) Historia
					OperationInfo* historyInfo = StructuresActionHistoryHolder::getInstance()->createAndStoreInfo(Controls->Structure, Controls->ADT, result, elapsed);
					Controls->ControlsPanel->PanelHistory->actionPerformed(historyInfo);

					// 4 c) Vykon
					PerformanceInfo* performanceInfo = StructuresPerformanceHolder::getInstance()->createAndStoreInfo(Controls->Structure, Controls->ADT, id_, size, elapsed);
					Controls->ControlsPanel->PanelPerformance->actionPerformed(performanceInfo);
				}
			}
			catch (std::exception ex)
			{
				log::Logger::getInstance()->logError(ex.what());
			}
			catch (System::Exception^ ex)
			{
				log::Logger::getInstance()->logError(ex->Message);
			}
		}
		else
		{
			Logger::getInstance()->logWarning("Operation " + Caption + " does not support redo operation.");
		}
		Controls->enableControls();
		return result;
	}

	void Action::undo(ActionMemento * memento)
	{
		if (supportsUndo_)
		{
			try
			{
				//size_t size = Controls->Structure->size();
				timer_->reset();

				// krok 1
				timer_->start();
				doUndo(memento);
				timer_->stop();

				// krok 2
				doPresentUndoResult();

				// krok 3
				Logger::getInstance()->logDebug("Operation " + Caption + " reverted in " + System::Convert::ToString(timer_->elapsed().count()) + " ms.");
			}
			catch (std::exception ex)
			{
				log::Logger::getInstance()->logError(ex.what());
			}
			catch (System::Exception^ ex)
			{
				log::Logger::getInstance()->logError(ex->Message);
			}
			Controls->enableControls();
		} 
		else
		{
			Logger::getInstance()->logWarning("Operation " + Caption + " does not support undo operation.");
		}
	}

	void Action::tryEnable()
	{
		enabled_ = canBeEnabled();

		for each(Control^ control in controls_)
		{
			control->Enabled = enabled_;
		}
	}

	bool Action::canBeEnabled()
	{
		return true;
	}

	ActionMemento * Action::doCreateMementoInstance()
	{
		return new ActionMemento(ID);
	}

	Button ^ Action::createButton(Control ^ owner)
	{
		Button^ result = gcnew Button();
		owner->Controls->Add(result);

		result->Enabled = enabled_;
		result->Size = Size(78, 35);
		result->Text = caption_;
		result->BackColor = SystemColors::Control;
		result->Click += gcnew EventHandler(this, &Action::onButtonClick);

		controls_->Add(result);
		return result;
	}

	void Action::doUndo(ActionMemento* memento)
	{
	}

	bool Action::doFormat()
	{
		return true;
	}

	void Action::doFormat(ActionMemento * memento)
	{
	}

	void Action::doPresentResult()
	{
		Controls->visualizeStructure();
	}

	void Action::doPresentRedoResult()
	{
		if (supportsRedo_)
		{
			Controls->visualizeStructure();
		}
	}

	void Action::doPresentUndoResult()
	{
		if (supportsUndo_)
		{
			Controls->visualizeStructure();
		}
	}

	System::Void Action::onButtonClick(Object ^ sender, EventArgs ^ e)
	{
		execute();
		return System::Void();
	}

	int Action::ID::get()
	{
		return id_;
	}

	bool Action::Enabled::get()
	{
		return enabled_;
	}

	String^ Action::Caption::get()
	{
		return caption_;
	}

	TimeMeasurement::TimeMeasurement()
	{
		reset();
	}

	void TimeMeasurement::start()
	{
		if (!started_)
		{
			timeStart_ = clock_.now();
			started_ = true;
		}
	}

	void TimeMeasurement::stop()
	{
		if (started_)
		{
			timeSum_ += std::chrono::duration_cast<TimeMeasurement::TimerUnits>(clock_.now() - timeStart_);
			started_ = false;
		}
	}

	void TimeMeasurement::reset()
	{
		timeSum_ = TimeMeasurement::TimerUnits::zero();
		started_ = false;
	}

	TimeMeasurement::TimerUnits TimeMeasurement::elapsed()
	{
		return timeSum_;
	}


	ActionStructureSize::ActionStructureSize(int id, ControlsHolder ^ structureControls) : 
		Action(id, "Size", false, true, structureControls),
		result_(0)
	{
	}

	bool ActionStructureSize::doFormat()
	{
		result_ = 0;
		return true;
	}

	ActionMemento* ActionStructureSize::doExecute()
	{
		result_ = Controls->Structure->size();
		return new ActionMemento(ID);
	}

	void ActionStructureSize::doPresentResult()
	{
		data::DataRoutines::showNumber(static_cast<int>(result_), Caption);
	}

	void ActionStructureSize::doPresentRedoResult()
	{
		doPresentResult();
	}

	ActionStructureIsEmpty::ActionStructureIsEmpty(int id, ControlsHolder ^ structureControls) :
		Action(id, "Is empty?", false, true, structureControls),
		result_(false)
	{
	}

	bool ActionStructureIsEmpty::doFormat()
	{
		result_ = false;
		return true;
	}

	ActionMemento* ActionStructureIsEmpty::doExecute()
	{
		result_ = Controls->Structure->isEmpty();
		return new ActionMemento(ID);
	}

	void ActionStructureIsEmpty::doPresentResult()
	{
		ui::UIRoutines::showMessage(Caption, System::Convert::ToString(result_));
	}

	void ActionStructureIsEmpty::doPresentRedoResult()
	{
		doPresentResult();
	}

}
