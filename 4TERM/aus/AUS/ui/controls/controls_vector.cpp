#include "controls_vector.h"

namespace ui
{

	Control ^ ControlsVector::doCreatePresentPanel()
	{
		PanelPresentVector^ result = gcnew PanelPresentVector();
		result->initialize(this);
		return result;
	}

	void ControlsVector::doVisualizeStructure()
	{
		if (Vector != nullptr)
		{
			VectorPanel->visualize(Vector);
		}
	}

	ControlsVector::ControlsVector():
		ControlsHolder(ds::StructureADT::adtVECTOR) 
	{
	}

	void ControlsVector::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionVectorByteSet(this));
		actions->Add(gcnew ActionVectorByteReset(this));
		actions->Add(gcnew ActionVectorByteXOR(this));
		actions->Add(gcnew ActionVectorByteSHL(this));
		actions->Add(gcnew ActionVectorByteSHR(this));
		actions->Add(gcnew ActionVectorByteEdit(this));
		actions->Add(gcnew ActionStructureSize(ActionVector::idaVecSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionVector::idaVecIS_EMPTY, this));
	}

	ds::Vector* ControlsVector::Vector::get()
	{ 
		return dynamic_cast<ds::Vector*>(Structure); 
	};

	PanelPresentVector^ ControlsVector::VectorPanel::get()
	{
		return dynamic_cast<PanelPresentVector^>(ControlsPanel->PanelPresent);
	};
	

}