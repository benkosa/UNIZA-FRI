#include "structure_info_holder.h"

namespace ui
{

	SingleInfoContainer::SingleInfoContainer(InfoItem* parent, int id) :
		InfoItem(parent),
		id_(id),
		infoVector_(new StructureInfoVector())
	{
	}

	SingleInfoContainer::~SingleInfoContainer()
	{
		for (StructureInfo* info : (*infoVector_))
		{
			delete info;
		}

		delete infoVector_;
		infoVector_ = nullptr;
	}

	int SingleInfoContainer::getID()
	{
		return id_;
	}

	typename const SingleInfoContainer::StructureInfoVector * SingleInfoContainer::getInfoVector()
	{
		return infoVector_;
	}

	StructureInfo * SingleInfoContainer::lastInfo()
	{
		return infoAt(infoVector_->size() - 1);
	}

	StructureInfo * SingleInfoContainer::infoAt(size_t index)
	{
		return index >= 0 && index < infoVector_->size() ? (*infoVector_)[index] : nullptr;
	}

	StructureInfo * SingleInfoContainer::storeInfo(InfoRegistrationParams* params)
	{
		beforeInfoStored(params);
		StructureInfo* result = doStoreInfo(params);
		afterInfoStored(result, params);

		return result;
	}

	void SingleInfoContainer::removeInfo(StructureInfo * info)
	{
	}

	StructureInfo * SingleInfoContainer::doStoreInfo(InfoRegistrationParams* params)
	{
		return nullptr;
	}

	void SingleInfoContainer::beforeInfoStored(InfoRegistrationParams* params)
	{
	}

	void SingleInfoContainer::afterInfoStored(StructureInfo * createdInfo, InfoRegistrationParams* params)
	{
	}

	StructureInfoHolder::StructureInfoHolder(InfoItem* parent, structures::Structure * structure, structures::StructureADT adt) :
		InfoItem(parent),
		structure_(structure),
		adt_(adt),
		structureInfoMap_(new InfoMap())
	{
	}

	StructureInfoHolder::~StructureInfoHolder()
	{
		for (InfoMapPair pair : *structureInfoMap_)
		{
			delete pair.second;
		}

		delete structureInfoMap_;
		structureInfoMap_ = nullptr;
	}

	structures::Structure * StructureInfoHolder::getStructure()
	{
		return structure_;
	}

	structures::StructureADT StructureInfoHolder::getADT()
	{
		return adt_;
	}

	typename StructureInfoHolder::InfoMap * StructureInfoHolder::getStructureInfoMap()
	{
		return structureInfoMap_;
	}

	StructureInfo * StructureInfoHolder::createAndStoreInfo(InfoRegistrationParams* params)
	{
		SingleInfoContainer* infoContainer;

		if (structureInfoMap_->find(params->InfoID) == structureInfoMap_->end())
		{
			infoContainer = getSingleInfoContainerInstance(params);
			(*structureInfoMap_)[params->InfoID] = infoContainer;
		}
		else
		{
			infoContainer = (*structureInfoMap_)[params->InfoID];
		}

		beforeInfoStored(params);
		StructureInfo* result = infoContainer->storeInfo(params);
		afterInfoStored(result, params);

		return result;
	}

	void StructureInfoHolder::removeInfo(StructureInfo * info)
	{
		beforeInfoRemoved(info);

		SingleInfoContainer* infoContainer = (*structureInfoMap_)[info->getID()];
		infoContainer->removeInfo(info);
	}

	SingleInfoContainer* StructureInfoHolder::getSingleInfoContainerInstance(InfoRegistrationParams* params)
	{
		return new SingleInfoContainer(dynamic_cast<InfoItem*>(this), params->InfoID);
	}

	void StructureInfoHolder::beforeInfoStored(InfoRegistrationParams* params)
	{
	}

	void StructureInfoHolder::afterInfoStored(StructureInfo * createdInfo, InfoRegistrationParams* params)
	{
	}

	void StructureInfoHolder::beforeInfoRemoved(StructureInfo * info)
	{
	}

	StructuresInfoHolder::StructuresInfoHolder() :
		InfoItem(nullptr),
		structuresInfo_(new StructureInfoHolderMap()),
		registeredInfo_(new ADTInfoCodeNamesMap())
	{
	}

	StructuresInfoHolder::~StructuresInfoHolder()
	{
		typename StructureInfoHolderMap::iterator itStructure;
		for (itStructure = structuresInfo_->begin(); itStructure != structuresInfo_->end(); itStructure++)
		{
			delete itStructure->second;
		}

		typename ADTInfoCodeNamesMap::iterator itRegister;
		for (itRegister = registeredInfo_->begin(); itRegister != registeredInfo_->end(); itRegister++)
		{
			delete itRegister->second;
		}

		delete structuresInfo_;
		structuresInfo_ = nullptr;

		delete registeredInfo_;
		registeredInfo_ = nullptr;
	}

	StructureInfoHolder* StructuresInfoHolder::getStructureInfoHolder(structures::Structure * structure)
	{
		return structuresInfo_->find(structure) != structuresInfo_->end() ? (*structuresInfo_)[structure] : nullptr;
	}

	void StructuresInfoHolder::registerInfo(structures::StructureADT adt, int infoID, std::string infoCaption)
	{
		typename StructuresInfoHolder::InfoCodeNamesMap* adtInfo = getRegisteredInfoOfADT(adt);

		if (adtInfo == nullptr)
		{
			adtInfo = new StructuresInfoHolder::InfoCodeNamesMap();
			(*registeredInfo_)[adt] = adtInfo;
		}

		(*adtInfo)[infoID] = infoCaption;
	}

	std::string StructuresInfoHolder::infoCaption(structures::StructureADT adt, int infoID)
	{
		InfoCodeNamesMap* adtInfo = getRegisteredInfoOfADT(adt);
		if (adtInfo != nullptr)
		{
			return adtInfo->find(infoID) != adtInfo->end() ? (*adtInfo)[infoID] : std::string();
		}
		else
		{
			return std::string();
		}
	}

	StructureInfo * StructuresInfoHolder::createAndStoreInfo(InfoRegistrationParams* params)
	{
		if (isInfoRegistered(params->ADT, params->InfoID))
		{
			StructureInfoHolder* structureInfo = getStructureInfoHolder(params->Structure);

			if (structureInfo == nullptr)
			{
				structureInfo = getStructureInfoHolderInstance(params);
				(*structuresInfo_)[params->Structure] = structureInfo;
			}

			beforeInfoStored(params);
			StructureInfo * result = structureInfo->createAndStoreInfo(params);
			afterInfoStored(result, params);

			return result;
		}
		else
		{
			return nullptr;
		};
	}

	void StructuresInfoHolder::removeInfo(StructureInfo * info)
	{
		beforeInfoRemoved(info);
		
		StructureInfoHolder* structureInfoHolder = getStructureInfoHolder(info->getStructure());
		structureInfoHolder->removeInfo(info);

		delete info;
	}

	StructureInfoHolder* StructuresInfoHolder::getStructureInfoHolderInstance(InfoRegistrationParams* params)
	{
		return new StructureInfoHolder(this, params->Structure, params->ADT);
	}

	void StructuresInfoHolder::beforeInfoStored(InfoRegistrationParams* params)
	{
	}

	void StructuresInfoHolder::afterInfoStored(StructureInfo * createdInfo, InfoRegistrationParams* params)
	{
	}

	void StructuresInfoHolder::beforeInfoRemoved(StructureInfo * info)
	{
	}

	bool StructuresInfoHolder::isInfoRegistered(structures::StructureADT adt, int infoID)
	{
		InfoCodeNamesMap* adtInfo = getRegisteredInfoOfADT(adt);
		return adtInfo != nullptr && adtInfo->find(infoID) != adtInfo->end();
	}

	typename StructuresInfoHolder::InfoCodeNamesMap * StructuresInfoHolder::getRegisteredInfoOfADT(structures::StructureADT adt)
	{
		return registeredInfo_->find(adt) != registeredInfo_->end() ? (*registeredInfo_)[adt] : nullptr;
	}

	InfoItem * InfoItem::getParent()
	{
		return parent_;
	}

	int InfoItem::getID()
	{
		return parent_ != nullptr ? parent_->getID() : -1;
	}

	structures::Structure * InfoItem::getStructure()
	{
		return parent_ != nullptr ? parent_->getStructure() : nullptr;
	}

	structures::StructureADT InfoItem::getADT()
	{
		return parent_ != nullptr ? parent_->getADT() : structures::StructureADT::adtCount;
	}

}