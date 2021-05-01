#include "action_history.h"

namespace ui
{

	StructuresActionHistoryHolder* StructuresActionHistoryHolder::structuresActionHistoryHolder_ = nullptr;

	ActionMemento::ActionMemento(int actionID) :
		actionID_(actionID)
	{
	}

	ActionMemento::ActionMemento(const ActionMemento& other) :
		ActionMemento(other.actionID_)
	{
	}

	ActionMemento::~ActionMemento()
	{
	}

	ActionMemento * ActionMemento::clone()
	{
		return new ActionMemento(*this);
	}

	int ActionMemento::getActionID()
	{
		return actionID_;
	}

	OperationInfo::OperationInfo(InfoItem* parent, ActionMemento* memento, long duration) :
		StructureInfo(parent),
		memento_(memento),
		time_(duration)
	{
	}

	OperationInfo::~OperationInfo()
	{
		delete memento_;
		memento_ = nullptr;
	}

	long OperationInfo::getTime()
	{
		return time_;
	}

	ActionMemento * OperationInfo::getMemento()
	{
		return memento_;
	}

	SingleActionHistoryContainer::SingleActionHistoryContainer(InfoItem* parent, int id):
		SingleInfoContainer(parent, id)
	{
	}

	void SingleActionHistoryContainer::removeInfo(StructureInfo * info)
	{
		StructureInfoVector::iterator result = std::find(infoVector_->begin(), infoVector_->end(), info);
		infoVector_->erase(result);
	}

	StructureInfo * SingleActionHistoryContainer::doStoreInfo(InfoRegistrationParams * params)
	{
		OperationParams* operationParams = dynamic_cast<OperationParams*>(params);

		OperationInfo* info = new OperationInfo(this, operationParams->Memento, operationParams->Time);
		infoVector_->push_back(info);
		return info;
	}

	StructureActionHistoryHolder::StructureActionHistoryHolder(InfoItem* parent, structures::Structure * structure, structures::StructureADT adt):
		StructureInfoHolder(parent, structure, adt),
		allOperations_(new OperationInfoDeque())
	{
	}

	StructureActionHistoryHolder::~StructureActionHistoryHolder()
	{
		delete allOperations_;
		allOperations_ = nullptr;
	}

	typename StructureActionHistoryHolder::OperationInfoDeque * StructureActionHistoryHolder::getAllOperations()
	{
		return allOperations_;
	}

	SingleInfoContainer* StructureActionHistoryHolder::getSingleInfoContainerInstance(InfoRegistrationParams * params)
	{
		return new SingleActionHistoryContainer(this, params->InfoID);
	}

	void StructureActionHistoryHolder::afterInfoStored(StructureInfo * createdInfo, InfoRegistrationParams * params)
	{
		if (createdInfo != nullptr)
		{
			allOperations_->push_front(dynamic_cast<OperationInfo*>(createdInfo));
		}
	}

	void StructureActionHistoryHolder::beforeInfoRemoved(StructureInfo * info)
	{
		OperationInfoDeque::iterator result = std::find(allOperations_->begin(), allOperations_->end(), info);
		allOperations_->erase(result);
	}

	StructuresActionHistoryHolder * StructuresActionHistoryHolder::getInstance()
	{
		if (structuresActionHistoryHolder_ == nullptr)
			structuresActionHistoryHolder_ = new StructuresActionHistoryHolder();
		return structuresActionHistoryHolder_;
	}

	void StructuresActionHistoryHolder::finalize()
	{
		delete structuresActionHistoryHolder_;
		structuresActionHistoryHolder_ = nullptr;
	}

	OperationInfo * StructuresActionHistoryHolder::createAndStoreInfo(structures::Structure* structure, structures::StructureADT adt, ActionMemento* memento, long time)
	{
		OperationParams* params = new OperationParams();

		params->Structure = structure;
		params->ADT = adt;
		params->InfoID = memento->getActionID();

		params->Time = time;
		params->Memento = memento;

		StructureInfo * result = StructuresInfoHolder::createAndStoreInfo(params);

		delete params;
		return dynamic_cast<OperationInfo*>(result);
	}

	StructureInfoHolder* StructuresActionHistoryHolder::getStructureInfoHolderInstance(InfoRegistrationParams * params)
	{
		return new StructureActionHistoryHolder(this, params->Structure, params->ADT);
	}

	StructuresActionHistoryHolder::StructuresActionHistoryHolder():
		StructuresInfoHolder()
	{
	}

	



}