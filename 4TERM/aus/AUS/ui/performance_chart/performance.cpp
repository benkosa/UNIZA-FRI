#include "performance.h"

namespace ui
{

	StructuresPerformanceHolder* StructuresPerformanceHolder::structuresPerformanceHolder_ = nullptr;

	PerformanceInfo::PerformanceInfo(InfoItem* parent, size_t size):
		StructureInfo(parent),
		size_(size),
		time_(0),
		timeSum_(0)
	{
	}

	PerformanceInfo::PerformanceInfo(InfoItem* parent, size_t size, long time):
		StructureInfo(parent),
		size_(size),
		time_(time),
		timeSum_(1)
	{
	}

	size_t PerformanceInfo::getSize()
	{
		return size_;
	}

	double PerformanceInfo::complexity()
	{
		return time_ / static_cast<double>(timeSum_);
	}

	void PerformanceInfo::incTime(long time)
	{
		time_ += time;
		timeSum_++;
	}


	StructureInfo * SinglePerformanceContainer::doStoreInfo(InfoRegistrationParams* params)
	{
		PerformanceParams* performanceParams = dynamic_cast<PerformanceParams*>(params);

		PerformanceInfo* info = dynamic_cast<PerformanceInfo*>(infoAt(performanceParams->Size));
		info->incTime(performanceParams->Time);
		return info;
	}

	void SinglePerformanceContainer::beforeInfoStored(InfoRegistrationParams* params)
	{
		PerformanceParams* performanceParams = dynamic_cast<PerformanceParams*>(params);

		ensureInfoUpToSize(performanceParams->Size);
	}

	SinglePerformanceContainer::SinglePerformanceContainer(InfoItem* parent, int id):
		SingleInfoContainer(parent, id)
	{
	}

	void SinglePerformanceContainer::ensureInfoUpToSize(size_t size)
	{
		PerformanceInfo * last = dynamic_cast<PerformanceInfo*>(lastInfo());

		size_t sizeToCreate = last == nullptr ? 0 : last->getSize() + 1;
		while (sizeToCreate <= size)
		{
			last = new PerformanceInfo(this, sizeToCreate);
			infoVector_->push_back(last);
			sizeToCreate++;
		}
	}

	StructurePerformanceHolder::StructurePerformanceHolder(InfoItem* parent, structures::Structure* structure, structures::StructureADT adt) :
		StructureInfoHolder(parent, structure, adt),
		maxSize_(0)
	{
	}

	SingleInfoContainer* StructurePerformanceHolder::getSingleInfoContainerInstance(InfoRegistrationParams * params)
	{
		return new SinglePerformanceContainer(this, params->InfoID);
	}

	void StructurePerformanceHolder::beforeInfoStored(InfoRegistrationParams * params)
	{
		PerformanceParams* performanceParams = dynamic_cast<PerformanceParams*>(params);

		if (performanceParams->Size > maxSize_)
		{
			maxSize_ = performanceParams->Size;
		}

		for (InfoMapPair pair : *getStructureInfoMap())
		{
			dynamic_cast<SinglePerformanceContainer*>(pair.second)->ensureInfoUpToSize(maxSize_);
		}
	}

	StructuresPerformanceHolder * StructuresPerformanceHolder::getInstance()
	{
		if (structuresPerformanceHolder_ == nullptr)
			structuresPerformanceHolder_ = new StructuresPerformanceHolder();
		return structuresPerformanceHolder_;
	}

	void StructuresPerformanceHolder::finalize()
	{
		delete structuresPerformanceHolder_;
		structuresPerformanceHolder_ = nullptr;
	}

	PerformanceInfo * StructuresPerformanceHolder::createAndStoreInfo(structures::Structure * structure, structures::StructureADT adt, int operationID, size_t size, long time)
	{
		PerformanceParams* params = new PerformanceParams();

		params->Structure = structure;
		params->ADT = adt;
		params->InfoID = operationID;

		params->Size = size;
		params->Time = time;

		StructureInfo * result = StructuresInfoHolder::createAndStoreInfo(params);

		delete params;
		return dynamic_cast<PerformanceInfo*>(result);
	}

	StructureInfoHolder* StructuresPerformanceHolder::getStructureInfoHolderInstance(InfoRegistrationParams * params)
	{
		return new StructurePerformanceHolder(this, params->Structure, params->ADT);
	}

	StructuresPerformanceHolder::StructuresPerformanceHolder() :
		StructuresInfoHolder()
	{
	}


}
