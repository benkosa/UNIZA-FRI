#pragma once

#include "../../structures/ds_structure_types.h"
#include "../../structures/structure.h"
#include "../panel_controls.h"
#include "../action_history/action_history.h"
#include <chrono>

using namespace System::Windows::Forms;
using namespace System::Collections;
using namespace System;

namespace ui {

	ref class ControlsHolder;
	ref class Action;

	/// <summary>
	/// Trieda, ktorej instancie pocitaju zmeny.
	/// </summary>
	public ref class ControlsLock
	{
	private:
		/// <summary> Pocitadlo zmien. </summary>
		int updates_;
	public:
		ControlsLock() : updates_(0) {}
		~ControlsLock() { updates_ = 0; }

		/// <summary> Metoda volana na zaciatku bloku, ktory ma byt zamknuty. </summary>
		void beginUpdate() { updates_++; }
		/// <summary> Metoda volana na konci bloku, ktory bol predtym zamknuty. </summary>
		void endUpdate() { updates_--; }
		/// <summary> Metoda kontroluje, ci je mozne robit zmeny. </summary>
		/// <returns> true, ak je mozne robit zmeny, false inak. </returns>
		bool isUpdating() { return updates_ > 0; }
	};

	/// <summary> Meranie casu. </summary>
	class TimeMeasurement
	{
	public:
		typedef std::chrono::milliseconds TimerUnits;
	public:
		TimeMeasurement();

		void start();
		void stop();
		void reset();

		TimerUnits elapsed();
	private:
		std::chrono::high_resolution_clock clock_;
		std::chrono::high_resolution_clock::time_point timeStart_;
		TimerUnits timeSum_;

		bool started_;
	};

	/// <summary>
	/// Sluzi na vytvorenie panelu na ovladanie struktury.
	/// Je navrhnuty ako Singleton, a tvori riadiaci objekt vzoru Builder.
	/// </summary>
	public ref class ControlsDirector 
	{
	private:
		/// <summary> Premenna triedy obsahujuca odkaz na jedinu instanciu triedy. </summary>
		static ControlsDirector^ director_ = nullptr;
		/// <summary> Tabulka builderov. </summary>
		System::Collections::Generic::IDictionary<int, ControlsHolder^>^ controlsHolders_;
	protected:
		/// <summary> Chraneny konstruktor. </summary>
		ControlsDirector();
	public:
		/// <summary> Jednoducha tovarenska metoda pre ziskanie instancie jedinacika. </summary>
		/// <returns> Instancia triedy ControlsDirector. </returns>
		/// <remarks> Vyuziva Lazy initialization. </remarks>
		static ControlsDirector^ getInstance();

		/// <summary>
		/// Vrati instanciu ControlsBuilder podla ADT. 
		/// Ak taka instancia este neexistuje, tak ju vytvori a spravne zapoji do uzivatelskeho rozhrania.
		/// Ak uz taka instancia ControlsBuilder existuje, vrati tu.
		/// </summary>
		/// <param name = "adt"> Typ ADT. </param>
		/// <param name = "parent"> Rodicovsky komponent pre ovladacie prvky. </param>
		ControlsHolder^ createControlsHolderInstance(structures::StructureADT adt, Control^ parent);

		/// <summary>
		/// Vrati instanciu ControlsBuilder podla ADT. 
		/// Ak taka instancia este neexistuje, tak ju iba vytvori, ale nevlozi do rozhrania!
		/// Ak uz taka instancia ControlsBuilder existuje, vrati tu.
		/// </summary>
		/// <param name = "adt"> Typ ADT. </param>
		ControlsHolder^ getControlsHolderInstance(structures::StructureADT adt);
	};

	/// <summary>
	/// Ovladace pre ovladacie prvky.
	/// Tvori vykonny objekt vzoru Builder.
	/// </summary>
	public ref class ControlsHolder abstract
	{
	public:
		property structures::StructureADT ADT
		{
			structures::StructureADT get() { return adt_; };
		}

		property structures::Structure* Structure
		{
			structures::Structure* get();
			void set(structures::Structure* structure);
		}

		property Generic::List<Action^>^ Actions
		{
			Generic::List<Action^>^ get() { return actions_; };
		}
		
		property ControlsLock^ Lock 
		{ 
			ControlsLock^ get() { return lock_; };
		}

		property PanelControls^ ControlsPanel
		{
			PanelControls^ get() { return panelControls_; };
		}

		/// <summary> Konstruktor. </summary>
		/// <param name = "adt"> ADT ovladanych struktur. </param>
		ControlsHolder(structures::StructureADT adt);

		/// <summary> Vytvori vsetky ovladacie panely. </summary>
		/// <param name = "parent"> Rodicovsky komponent pre ovladacie prvky. </param>
		void createPanels(Control^ parent);

		/// <summary> Bezpecne vizualizuje strukturu. Vyuziva metodu doVisualuzeStructure. </summary>
		void visualizeStructure();

		/// <summary> Zobrazi hlavny panel. </summary>
		void show();
		/// <summary> Skryje hlvny panel. </summary>
		void hide();

		/// <summary> Vrati akciu podla jej ID. </summary>
		/// <param name = "actionID"> ID akcie. </param>
		/// <returns> Akciu s danym ID. Ak neexistuje, vrati nullptr. </returns>
		Action^ getAction(int actionID);

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		virtual void createActions(Generic::List<Action^>^ actions) = 0;

		/// <summary> Aktualizuje ovladacie prvky na panely. </summary>
		void enableControls();
	protected:
		/// <summary> Virtualna abstraktna metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim struktury. </returns>
		virtual Control^ doCreatePresentPanel() = 0;

		/// <summary> Vizualizuje strukturu. </summary>
		virtual void doVisualizeStructure() = 0;
	private:
		/// <summary> ADT ovladanych struktur. </summary>
		structures::StructureADT adt_;

		/// <summary> Aktualne spravovana udajova strutura. </summary>
		structures::Structure* structure_;

		/// <summary> Akcie. </summary>
		Generic::List<Action^>^ actions_;

		/// <summary> Panel s rozlozenim ovladania. </summary>
		PanelControls^ panelControls_;
		
		/// <summary> Zamok pre ovladacie prvky. </summary>
		ControlsLock^ lock_;
	};

	/// <summary>
	/// Trieda zastresujuca operaciu s udajovou strukturou.
	/// Je navrhnuta podla vzoru Command.
	/// </summary>
	ref class Action abstract
	{
	public:
		property int ID
		{
			int get();
		}

		property bool Enabled
		{
			bool get();
		}

		property ControlsHolder^ Controls
		{
			ControlsHolder^ get() { return controlsHolder_; }
		}

		property String^ Caption
		{
			String^ get();
		}

		property TimeMeasurement* Timer
		{
			TimeMeasurement* get() { return timer_; }
		}

		/// <summary> Vytvori akciu. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "controlsHolder"> Ovladanie, do ktoreho patri. </param>
		Action(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ controlsHolder);

		/// <summary> Destruktor. </summary>
		~Action();

		/// <summary> Finalizer. </summary>
		!Action();

		/// <summary> Bezpecne vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		/// <remarks> 
		/// Sprava sa ako sablonova metoda (vzor template method):
		///   1) Naformatuje akciu. Ak sa akciu nepodari naformatovat, skonci. (prekrytelna metoda)
		///   2) Vykona akciu, ktorej memento vrati. (abstraktna metoda)
		///   3) Prezentuje uzivatelovi vysledok akcie. (prekrytelna metoda)
		///   4) Vynesie do rozhrania:
		///      a) informaciu o trvani. (logger) 
		///      b) informaciu o vykonani akcie. (historia)
		///      c) informaciu o vykone. (graf)
		/// </remarks>
		ActionMemento* execute();
		
		/// <summary> Bezpecne zopakuje akciu s danymi nastaveniami. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		/// <param name = "interact"> Ak je parameter nastaveny, tak bude interagovat s pouzivatelom. </param>
		/// <returns> Memento vykonanej akcie. Ak je parameter interact nastaveny na false, vrati nullptr. </returns>
		/// <remarks> 
		/// Sprava sa ako sablonova metoda (vzor template method):
		///   1) Obnovi vnutorny stav akcie. (prekrytelna metoda)
		///   2) Znovu vykona ackiu, ktorej memento vrati. (abstraktna metoda)
		///   == Ak je nastaveny parmeter interact, vykona nasledujuce kroky ==
		///   3) Znovu prezentuje strukturu. (prekrytelna metoda)
		///   4) Vynesie do rozhrania:
		///      a) informaciu o trvani. (logger) 
		///      b) informaciu o vykonani akcie. (historia)
		///      c) informaciu o vykone. (graf)
		/// </remarks>
		ActionMemento* redo(ActionMemento* memento, bool interact);

		/// <summary> Bezpecne zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		/// <remarks> 
		/// Sprava sa ako sablonova metoda (vzor template method):
		///   1) Zvrati akciu. (abstraktna metoda)
		///   2) Prezentuje uzivatelovi vysledok akcie. (prekrytelna metoda)
		///   3) Vynesie do rozhrania informaciu o trvani. (neprekrytelna metoda)
		/// </remarks>
		void undo(ActionMemento* memento);
		
		/// <summary> Pokusi sa povolit akciu. </summary>
		/// <remarks> Vyuziva metodu canBeEnabled. </remarks>
		void tryEnable();

		/// <summary> Vytvori tlacitko a napoji sa ako jeho akcia po kliknuti </summary>
		/// <param name = "owner"> Prvok, ktory bude obsahovat vytvorene tlacitko. </param>
		/// <returns> Vytvorrene tlacitko. </returns>
		Button^ createButton(Control^ owner);
	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		/// <remarks> Defult true. </remarks>
		virtual bool canBeEnabled();

		/// <summary> Vrati instanciu mementa. </summary>
		/// <returns> Memento uchovavajuce data potrebne pre rekonstrukciu akcie (undo aj redo). </returns>
		/// <remarks> Volana v konstruktore. </remarks>
		virtual ActionMemento* doCreateMementoInstance();

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		/// <remarks> 
		/// Krok 1 sablonovej metody execute().
		/// Ak je to potrebne, moze merat cas.
		/// </remarks>
		virtual bool doFormat();

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		/// <remarks> 
		/// Krok 1 sablonovej metody redo().
		/// Ak je to potrebne, moze merat cas.
		/// </remarks>
		virtual void doFormat(ActionMemento* memento);

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		/// <remarks> Abstraktna metoda (krok 2) sablonovej metody execute(). Cas trvania je automaticky merany. </remarks>
		virtual ActionMemento* doExecute() = 0;

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		/// <remarks> Abstraktna metoda (krok 1) sablonovej metody undo(). </remarks>
		virtual void doUndo(ActionMemento* memento);

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		/// <remarks> Necha vypisat strukturu. Prekrytelna metoda (krok 3) sablonovej metody execute(). Ak je to potrebne, moze merat cas. </remarks>
		virtual void doPresentResult();

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		/// <remarks> Necha vypisat strukturu. Prekrytelna metoda (krok 3) sablonovej metody redo(). Ak je to potrebne, moze merat cas. </remarks>
		virtual void doPresentRedoResult();

		/// <summary> Prezentuje vysledok akcie, ktora bola zvratena, uzivatelovi. </summary>
		/// <remarks> Necha vypisat strukturu. Prekrytelna metoda (krok 2) sablonovej metody undo(). Ak je to potrebne, moze merat cas. </remarks>
		virtual void doPresentUndoResult();
	private:
		/// <summary> ID akcie. </summary>
		int id_;
		/// <summary> Popis akcie. </summary>
		String^ caption_;
		/// <summary> Priznak, ci je akcia povolena. </summary>
		bool enabled_;
		/// <summary> Priznak, ci moze byt akcia zvratena. </summary>
		bool supportsUndo_;
		/// <summary> Priznak, ci moze byt akcia zopakovana. </summary>
		bool supportsRedo_;
		/// <summary> Ovladaci panel so strukturou. </summary>
		ControlsHolder^ controlsHolder_;
		/// <summary> Vsetky ovladacie prvky spojene s touto akciou. </summary>
		Generic::List<Control^>^ controls_;
		/// <summary> Merac casu. </summary>
		TimeMeasurement* timer_;

		private: System::Void onButtonClick(System::Object^ sender, System::EventArgs^ e);
	};

	/// <summary> Trieda predstavuje operaciu zisti velkost struktury. </summary>
	ref class ActionStructureSize : public Action
	{
	public:
		/// <summary> Vytvori akciu zisti velkost struktury. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "structureControls"> Ovladanie, do ktoreho patri. </param>
		ActionStructureSize(int id, ControlsHolder^ structureControls);
	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override;
		/// <summary> Vykona akciu. </summary>
		ActionMemento* doExecute() override;
		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override;
		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override;
	private:
		size_t result_;
	};

	/// <summary> Trieda predstavuje operaciu zisti, ci je struktura prazdna. </summary>
	ref class ActionStructureIsEmpty : public Action
	{
	public:
		/// <summary> Vytvori akciu zisti, ci je struktura prazdna. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "structureControls"> Ovladanie, do ktoreho patri. </param>
		ActionStructureIsEmpty(int id, ControlsHolder^ structureControls);
	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override;
		/// <summary> Vykona akciu. </summary>
		ActionMemento* doExecute() override;
		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override;
		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override;
	private:
		bool result_;
	};

}

