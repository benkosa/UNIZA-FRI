#pragma once

#include "../../structures/vector/vector.h"
#include "controls.h"
#include "../vector/panel_vector.h"
#include "../../structures/memory_routines.h"
#include "../../data/data_routines.h"

using namespace System::Windows::Forms;
using namespace System;

namespace ui 
{

	/// <summary> Memento akcii vektorov. </summary>
	private class VectorActionMemento : public ActionMemento
	{
	public:
		int getIndex() { return index_; }
		structures::byte getByteBefore() { return byteBefore_; }
		structures::byte getByteAfter() { return byteAfter_; }

		void setIndex(int index) { index_ = index; }
		void setByteBefore(structures::byte byteBefore) { byteBefore_ = byteBefore; }
		void setByteAfter(structures::byte byteAfter) { byteAfter_ = byteAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		VectorActionMemento(int actionID) :
			ActionMemento(actionID),
			index_(0),
			byteBefore_(0),
			byteAfter_(0)
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		VectorActionMemento(const VectorActionMemento& other) :
			ActionMemento(other),
			index_(other.index_),
			byteBefore_(other.byteBefore_),
			byteAfter_(other.byteAfter_)
		{}

		ActionMemento* clone() override
		{
			return new VectorActionMemento(*this);
		}

	private:
		/// <summary> Index bytu. </summary>
		int index_;
		/// <summary> Stav bytu pred operaciou. </summary>
		structures::byte byteBefore_;
		/// <summary> Stav bytu po operacii. </summary>
		structures::byte byteAfter_;
	};

	/// <summary> Ovladace pre vektory. </summary>
	ref class ControlsVector : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim vektora. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentVector^ result = gcnew PanelPresentVector();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (Vector != nullptr)
			{
				VectorPanel->visualize(Vector);
			}
		}
	public:
		property structures::Vector* Vector
		{
			structures::Vector* get() { return dynamic_cast<structures::Vector*>(Structure); };
		}

		property PanelPresentVector^ VectorPanel
		{
			PanelPresentVector^ get() { return dynamic_cast<PanelPresentVector^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsVector() : ControlsHolder(structures::StructureADT::adtVECTOR) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu vo vektore. </summary>
	ref class ActionVector abstract : public Action
	{
	public:
		static const int idaVecBYTE_SET = 0;
		static const int idaVecBYTE_RESET = 1;
		static const int idaVecBYTE_XOR = 2;
		static const int idaVecBYTE_SHL = 3;
		static const int idaVecBYTE_SHR = 4;
		static const int idaVecBYTE_EDIT = 5;
		static const int idaVecSIZE = 6;
		static const int idaVecIS_EMPTY = 7;

	public:
		property ControlsVector^ VectorControls
		{
			ControlsVector^ get() { return dynamic_cast<ControlsVector^>(Controls); };
		}

		/// <summary> Vytvori akciu nad vektorom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "vectorControls"> Ovladanie, do ktoreho patri. </param>
		ActionVector(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ vectorControls) :
			Action(id, caption, supportsUndo, supportsRedo, vectorControls),
			index_(0),
			byteEdit_(structures::byte())
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return VectorControls->VectorPanel->SelectedItem != nullptr;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			index_ = VectorControls->VectorPanel->SelectedItem->Index;
			byteEdit_ = (*VectorControls->Vector)[index_];

			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			VectorActionMemento* vectorMemento = dynamic_cast<VectorActionMemento*>(memento);
			index_ = vectorMemento->getIndex();
			byteEdit_ = vectorMemento->getByteBefore();
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::byte byteBefore = (*VectorControls->Vector)[index_];
			internalExecute();
			structures::byte byteAfter = (*VectorControls->Vector)[index_];

			VectorActionMemento* result = new VectorActionMemento(ID);
			result->setIndex(index_);
			result->setByteBefore(byteBefore);
			result->setByteAfter(byteAfter);
			
			return result;
		}

		/// <summary> Vykona akciu. </summary>
		virtual void internalExecute() = 0;

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			VectorControls->VectorPanel->refreshSelectedItem();
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			VectorActionMemento* vectorMemento = dynamic_cast<VectorActionMemento*>(memento);
			(*VectorControls->Vector)[vectorMemento->getIndex()] = vectorMemento->getByteBefore();
		}

	protected:
		int index_;
		data::Byte byteEdit_;
	};

	/// <summary> Trieda predstavuje operaciu nastav byte vo vektore. </summary>
	ref class ActionVectorByteSet : public ActionVector
	{
	public:
		/// <summary> Vytvori akciu set byte nad vektorom. </summary>
		/// <param name = "vectorControls"> Ovladanie, do ktoreho patri. </param>
		ActionVectorByteSet(ControlsHolder^ vectorControls) : 
			ActionVector(idaVecBYTE_SET, "Set Byte", true, true, vectorControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		void internalExecute() override
		{
			structures::MemoryRoutines::byteSet((*VectorControls->Vector)[index_]);
		}
	};

	/// <summary> Trieda predstavuje operaciu zrus byte vo vektore. </summary>
	ref class ActionVectorByteReset : public ActionVector
	{
	public:
		/// <summary> Vytvori akciu reset byte nad vektorom. </summary>
		/// <param name = "vectorControls"> Ovladanie, do ktoreho patri. </param>
		ActionVectorByteReset(ControlsHolder^ vectorControls) : 
			ActionVector(idaVecBYTE_RESET, "Reset Byte", true, true, vectorControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		void internalExecute() override
		{
			structures::MemoryRoutines::byteReset((*VectorControls->Vector)[index_]);
		}
	};

	/// <summary> Trieda predstavuje operaciu xor byte vo vektore. </summary>
	ref class ActionVectorByteXOR : public ActionVector
	{
	public:
		/// <summary> Vytvori akciu XOR byte nad vektorom. </summary>
		/// <param name = "vectorControls"> Ovladanie, do ktoreho patri. </param>
		ActionVectorByteXOR(ControlsHolder^ vectorControls) : 
			ActionVector(idaVecBYTE_XOR, "XOR Byte", true, true, vectorControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		void internalExecute() override
		{
			structures::MemoryRoutines::byteXOR((*VectorControls->Vector)[index_]);
		}
	};

	/// <summary> Trieda predstavuje operaciu posun byte vo vektore dolava. </summary>
	ref class ActionVectorByteSHL : public ActionVector
	{
	public:
		/// <summary> Vytvori akciu SHL nad vektorom. </summary>
		/// <param name = "vectorControls"> Ovladanie, do ktoreho patri. </param>
		ActionVectorByteSHL(ControlsHolder^ vectorControls) : 
			ActionVector(idaVecBYTE_SHL, "<< Byte", true, true, vectorControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		void internalExecute() override
		{
			structures::MemoryRoutines::byteSHL((*VectorControls->Vector)[index_]);
		}
	};

	/// <summary> Trieda predstavuje operaciu posun byte vo vektore doprava. </summary>
	ref class ActionVectorByteSHR : public ActionVector
	{
	public:
		/// <summary> Vytvori akciu SHR nad vektorom. </summary>
		/// <param name = "vectorControls"> Ovladanie, do ktoreho patri. </param>
		ActionVectorByteSHR(ControlsHolder^ vectorControls) : 
			ActionVector(idaVecBYTE_SHR, ">> Byte", true, true, vectorControls) 
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		void internalExecute() override
		{
			structures::MemoryRoutines::byteSHR((*VectorControls->Vector)[index_]);
		}
	};

	/// <summary> Trieda predstavuje operaciu uprav data vo vektore. </summary>
	ref class ActionVectorByteEdit : public ActionVector
	{
	public:
		/// <summary> Vytvori akciu uprav byte vo vektore. </summary>
		/// <param name = "vectorControls"> Ovladanie, do ktoreho patri. </param>
		ActionVectorByteEdit(ControlsHolder^ vectorControls) : 
			ActionVector(idaVecBYTE_EDIT, "Edit", true, true, vectorControls) 
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionVector::doFormat() && 
				data::DataRoutines::editByteManaged(byteEdit_, "Edit byte");
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			VectorActionMemento* vectorMemento = dynamic_cast<VectorActionMemento*>(memento);
			index_ = vectorMemento->getIndex();
			byteEdit_ = vectorMemento->getByteAfter();
		}

		/// <summary> Vykona akciu. </summary>
		void internalExecute() override
		{
			(*VectorControls->Vector)[index_] = byteEdit_;
		}
	};

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

}
