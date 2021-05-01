#pragma once

#include "../../structures/ds_structure_types.h"
#include "../controls/structure_info_holder.h"
#include <deque>

namespace ui
{
	/// <summary> Memento akcie. </summary>
	public class ActionMemento 
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID akcie, ktorej patri. </param>
		ActionMemento(int actionID);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		ActionMemento(const ActionMemento & other);

		/// <summary> Destruktor. </summary>
		virtual ~ActionMemento();

		/// <summary> Operacia klonovania. </summary>
		/// <returns> Klon mementa. </returns>
		virtual ActionMemento* clone();

		/// <summary> Vrati ID akcie, ktorej patri. </summary>
		/// <returns> ID akcie, ktorej patri. </returns>
		int getActionID();
	private:
		/// <summary> ID akcie, ktorej patri. </summary>
		int actionID_;
	};

	/// <summary> Predstavuje parametre potrebne pre registraciu informacie of vykone operacie v strukture. </summary>
	public class OperationParams : public InfoRegistrationParams
	{
	public:
		/// <summary> Cas, kolko trvalo vykonat operaciu. </summary>
		long Time;
		/// <summary> Memento operacie. </summary>
		ActionMemento* Memento;
	};

	/// <summary> Predstavuje informaciu o vykone operacie v strukture. </summary>
	class OperationInfo : public StructureInfo
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "memento"> Memento operacie. </param>
		/// <param name = "time"> Trvanie operacie. </param>
		/// <remarks> Postara sa o uvolnenie mementa. </remarks>
		OperationInfo(InfoItem* parent, ActionMemento* memento, long time);

		/// <summary> Destruktor. </summary>
		~OperationInfo() override;

		/// <summary> Getter atributu duration_. </summary>
		/// <returns> Hodnota atributu duration_. </returns>
		long getTime();

		/// <summary> Getter atributu memento_. </summary>
		/// <returns> Hodnota atributu memento_. </returns>
		ActionMemento* getMemento();
	private:
		/// <summary> Cas, kolko trvalo vykonat operaciu. </summary>
		long time_;
		/// <summary> Memento operacie. </summary>
		ActionMemento* memento_;
	};

	/// <summary> Zdruzuje informacie o vykonanej operacii v strukture. </summary>
	class SingleActionHistoryContainer : public SingleInfoContainer
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "id"> ID informacie. </param>
		SingleActionHistoryContainer(InfoItem* parent, int id);

		/// <summary> Odstrani tuto informaciu. Nevola jej destruktor! </summary>
		/// <param name = "info"> Odstranena informacia. </param>
		virtual void removeInfo(StructureInfo* info);
	protected:
		/// <summary> Vytvori instanciu StructureInfo. </summary>
		/// <param name = "params"> Parametre potrebne pre vytvorenie instance StructureInfo. </param>
		/// <returns> Instancia StructureInfo pre danu informaciu. </returns>
		/// <remarks> Potomok moze predefinovat vytvaranu triedu SingleInfoContainer. </remarks>
		StructureInfo* doStoreInfo(InfoRegistrationParams* params) override;
	};

	/// <summary> Zapuzdrje informacie o vykonanych operaciach patriacich konkretnej udajovej strukture. </summary>
	class StructureActionHistoryHolder : public StructureInfoHolder
	{
	public:
		typedef std::deque<OperationInfo*> OperationInfoDeque;

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "structure"> Struktura, ktorej patria zaznamy. </param>
		/// <param name = "adt"> ADT struktury, ktorej patria zaznamy. </param>
		StructureActionHistoryHolder(InfoItem* parent, structures::Structure* structure, structures::StructureADT adt);

		/// <summary> Destruktor. </summary>
		~StructureActionHistoryHolder();

		/// <summary> Vrati vsetky zaznamy o operaciach.  </summary>
		/// <returns> Vsetky zaznamy o operaciach. </returns>
		typename OperationInfoDeque* getAllOperations();
	protected:
		/// <summary> Vytvori instanciu SingleInfoContainer. </summary>
		/// <param name = "params"> Parametre potrebne pre vytvorenie instance SingleInfoContainer. </param>
		/// <returns> Instancia SingleInfoContainer pre danu informaciu. </returns>
		SingleInfoContainer* getSingleInfoContainerInstance(InfoRegistrationParams* params) override;

		/// <summary> Volana po poziadani instancie SingleInfoContainer o registrovanie informacie. </summary>
		/// <param name = "createdInfo"> Informacia vytvorena prislusnym objektom SingleInfoContainer. </param>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Zaregistruje vytvorenu informaciu do zoznamu. </remarks>
		virtual void afterInfoStored(StructureInfo* createdInfo, InfoRegistrationParams* params);

		/// <summary> Volana po poziadani instancie SingleInfoContainer o vymazanie informacie. </summary>
		/// <param name = "info"> Odstranena informacia. </param>
		virtual void beforeInfoRemoved(StructureInfo* info);
	private:
		typename OperationInfoDeque* allOperations_;
	};

	/// <summary> 
	/// Zdruzuje informacie o vykonanych operaciach.  
	/// Navrhnuta podla vzoru Signleton.
	/// </summary>
	class StructuresActionHistoryHolder : public StructuresInfoHolder
	{
	public:
		/// <summary> Jednoducha tovarenska metoda pre ziskanie instancie jedinacika. </summary>
		/// <returns> Instancia triedy StructuresActionHistoryHolder. </returns>
		/// <remarks> Vyuziva Lazy initialization. </remarks>
		static StructuresActionHistoryHolder* getInstance();

		/// <summary> Odstrani instanciu jedinacika. </summary>
		static void finalize();

		/// <summary> Zaznamena informaciu o vykone operacie struktury. </summary>
		/// <param name = "structure"> Struktura, nad ktorou bola operacia vykonana. </param>
		/// <param name = "adt"> ADT struktury, ktorej patri operacia. </param>
		/// <param name = "memento"> Memento vykonanej operacie. </param>
		/// <param name = "time"> Cas, kolko trvalo vykonat operaciu. </param>
		/// <returns> Zaznamenany zaznam o operacii. </returns>
		/// <remarks> Vyuziva metodu createAndStoreInfo, ktorej pripravi objekt s parametrami. Postara sa o jeho zrusenie. </remarks>
		OperationInfo* createAndStoreInfo(structures::Structure* structure, structures::StructureADT adt, ActionMemento* memento, long time);
	protected:
		/// <summary> Vytvori instanciu StructureInfoHolder pre danu strukturu. </summary>
		/// <param name = "params"> Parametre potrene pre vytvorenie instance StructureInfoHolder. </param>
		/// <returns> Instanciu StructureInfoHolder pre danu strukturu. </returns>
		/// <remarks> Potomok moze predefinovat vytvaranu triedu StructureInfoHolder. </remarks>
		StructureInfoHolder* getStructureInfoHolderInstance(InfoRegistrationParams* params) override;
	private:
		/// <summary> Skryty konsktruktor. </summary>
		StructuresActionHistoryHolder();

		/// <summary> Premenna triedy obsahujuca odkaz na jedinu instanciu triedy. </summary>
		static StructuresActionHistoryHolder* structuresActionHistoryHolder_;
	};
}