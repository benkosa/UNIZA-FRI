#pragma once

#include "../../structures/structure.h"
#include "../../structures/ds_structure_types.h"
#include <vector>
#include <map>
#include <string>

namespace ui
{

	/// <summary> Predstavuje parametre potrebne pre registraciu informacie. </summary>
	public class InfoRegistrationParams
	{
	public:
		virtual ~InfoRegistrationParams()
		{
		}

		/// <summary> Struktura, ku ktorej patri informacia. </summary>
		structures::Structure* Structure;
		/// <summary> ADT struktury, ktorej patri informacia. </summary>
		structures::StructureADT ADT;
		/// <summary> ID informacie. </summary>
		int InfoID;
	};

	/// <summary> Predstavuje prvok v retazi vlastnikov informacii. </summary>
	public class InfoItem
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		InfoItem(InfoItem* parent):
			parent_(parent)
		{}

		/// <summary> Destruktor. </summary>
		virtual ~InfoItem()
		{
		}

		/// <summary> Getter rodica. </summary>
		/// <returns> Rodic prvku. </returns>
		InfoItem* getParent();

		/// <summary> Getter ID operacie. </summary>
		/// <returns> ID operacie. </returns>
		/// <remarks> Defaultne vrati ID rodica. Niekto v hierarchii musi tuto metodu spravne implementovat. </remarks>
		virtual int getID();

		/// <summary> Getter struktury. </summary>
		/// <returns> Struktura. </returns>
		/// <remarks> Defaultne vrati strukturu rodica. Niekto v hierarchii musi tuto metodu spravne implementovat. </remarks>
		virtual structures::Structure* getStructure();

		/// <summary> Getter ADT. </summary>
		/// <returns> ADT. </returns>
		/// <remarks> Defaultne vrati ADT rodica. Niekto v hierarchii musi tuto metodu spravne implementovat. </remarks>
		virtual structures::StructureADT getADT();
	private:
		/// <summary> Rodic prvku. </summary>
		InfoItem* parent_;
	};

	/// <summary> Predstavuje informaciu o strukture. </summary>
	public class StructureInfo : public InfoItem
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		StructureInfo(InfoItem* parent) :
			InfoItem(parent)
		{}
	};

	/// <summary> Zdruzuje informacie rovnakeho ID. </summary>
	public class SingleInfoContainer : public InfoItem
	{
	public:
		typedef std::vector<StructureInfo*> StructureInfoVector;
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "id"> ID informacie. </param>
		SingleInfoContainer(InfoItem* parent, int id);

		/// <summary> Destruktor. </summary>
		virtual ~SingleInfoContainer();

		/// <summary> Getter ID operacie. </summary>
		/// <returns> ID operacie. </returns>
		/// <remarks> Prekryva metodu getID v retazi zodpovednosti. </remarks>
		int getID() override;

		/// <summary> Getter vsetkych zaznamov operacie. </summary>
		/// <returns> Vsetky zaznamy operacie. </returns>
		typename const StructureInfoVector* getInfoVector();

		/// <summary> Ak existuje, vrati poslednu informaciu. </summary>
		/// <returns> Posledna informacia. Ak neexistuje, vrati nullptr. </returns>
		StructureInfo* lastInfo();

		/// <summary> Ak existuje, vrati informaciu na danom indexe. </summary>
		/// <param name = "index"> Index informacie. </param>
		/// <returns> Informacia na danom indexe. Ak neexistuje, vrati nullptr. </returns>
		StructureInfo* infoAt(size_t index);

		/// <summary> Zaznamena informaciu nad strukturou. </summary>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <returns> Zaznamenany zaznam o operacii. </returns>
		/// <remarks> 
		/// Navrhnuta ako template method. 
		/// Upravit spravanie je mozne metodami doStoreInfo, beforeInfoStored a afterInfoStored;
		/// </remarks>
		StructureInfo* storeInfo(InfoRegistrationParams* params);

		/// <summary> Odstrani tuto informaciu. Nevola jej destruktor! </summary>
		/// <param name = "info"> Odstranena informacia. </param>
		/// <remarks> U predka nerobi nic. </remarks>
		virtual void removeInfo(StructureInfo* info);
	protected:
		/// <summary> Vytvori instanciu StructureInfo. </summary>
		/// <param name = "params"> Parametre potrebne pre vytvorenie instance StructureInfo. </param>
		/// <returns> Instancia StructureInfo pre danu informaciu. </returns>
		/// <remarks> Potomok moze predefinovat vytvaranu triedu SingleInfoContainer. </remarks>
		virtual StructureInfo* doStoreInfo(InfoRegistrationParams* params);

		/// <summary> Volana pred registrovanim informacie. </summary>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vyuziva sa v sablonovej metode createAndStoreInfo. U predka nerobi nic. </remarks>
		virtual void beforeInfoStored(InfoRegistrationParams* params);

		/// <summary> Volana po registrovanie informacie. </summary>
		/// <param name = "createdInfo"> Registrovana informacia. </param>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vyuziva sa v sablonovej metode createAndStoreInfo. U predka nerobi nic. </remarks>
		virtual void afterInfoStored(StructureInfo* createdInfo, InfoRegistrationParams* params);
	protected:
		/// <summary> Zoznam zaznamov o operacii. </summary>
		StructureInfoVector* infoVector_;
	private:
		/// <summary> ID informacie. </summary>
		int id_;
	};

	/// <summary> Zapuzdrje informacie patriace konkretnej udajovej strukture. </summary>
	class StructureInfoHolder : public InfoItem
	{
	public:
		typedef std::map<int, SingleInfoContainer*> InfoMap;
		typedef std::pair<int, SingleInfoContainer*> InfoMapPair;
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "structure"> Struktura, ktorej patria zaznamy. </param>
		/// <param name = "adt"> ADT struktury, ktorej patria zaznamy. </param>
		StructureInfoHolder(InfoItem* parent, structures::Structure* structure, structures::StructureADT adt);

		/// <summary> Destruktor. </summary>
		virtual ~StructureInfoHolder();

		/// <summary> Getter struktury. </summary>
		/// <returns> Struktura. </returns>
		/// <remarks> Prekryva metodu getStructure v retazi zodpovednosti. </remarks>
		virtual structures::Structure* getStructure();

		/// <summary> Getter ADT. </summary>
		/// <returns> ADT. </returns>
		/// <remarks> Prekryva metodu getADT v retazi zodpovednosti. </remarks>
		virtual structures::StructureADT getADT();

		/// <summary> Vrati vsetky informacie.  </summary>
		/// <returns> Vsetky informacie. </returns>
		typename InfoMap* getStructureInfoMap();

		/// <summary> Zaznamena informaciu nad strukturou. </summary>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <returns> Zaznamenany zaznam o operacii. </returns>
		/// <remarks> 
		/// Navrhnuta ako template method. 
		/// Upravit spravanie je mozne upravit metodami getSingleInfoContainerInstance, beforeInfoStored a afterInfoStored.
		/// </remarks>
		StructureInfo* createAndStoreInfo(InfoRegistrationParams* params);

		/// <summary> Odstrani tuto informaciu. Nevola jej destruktor! </summary>
		/// <param name = "info"> Odstranena informacia. </param>
		/// <remarks> Spravanie je mozne upravit metodou beforeInfoRemoved. </remarks>
		void removeInfo(StructureInfo* info);
	protected:
		/// <summary> Vytvori instanciu SingleInfoContainer. </summary>
		/// <param name = "params"> Parametre potrebne pre vytvorenie instance SingleInfoContainer. </param>
		/// <returns> Instancia SingleInfoContainer pre danu informaciu. </returns>
		/// <remarks> Potomok moze predefinovat vytvaranu triedu SingleInfoContainer. </remarks>
		virtual SingleInfoContainer* getSingleInfoContainerInstance(InfoRegistrationParams* params);

		/// <summary> Volana pred poziadanim instancie SingleInfoContainer o registrovanie informacie. </summary>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vyuziva sa v sablonovej metode createAndStoreInfo. U predka nerobi nic. </remarks>
		virtual void beforeInfoStored(InfoRegistrationParams* params);

		/// <summary> Volana po poziadani instancie SingleInfoContainer o registrovanie informacie. </summary>
		/// <param name = "createdInfo"> Informacia vytvorena prislusnym objektom SingleInfoContainer. </param>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vyuziva sa v sablonovej metode createAndStoreInfo. U predka nerobi nic. </remarks>
		virtual void afterInfoStored(StructureInfo* createdInfo, InfoRegistrationParams* params);

		/// <summary> Volana po poziadani instancie SingleInfoContainer o vymazanie informacie. </summary>
		/// <param name = "info"> Odstranena informacia. </param>
		/// <remarks> Vyuziva sa v sablonovej metode removeInfo. U predka nerobi nic. </remarks>
		virtual void beforeInfoRemoved(StructureInfo* info);
	private:
		/// <summary> Struktura, ktorej patria zaznamy. </summary>
		structures::Structure* structure_;
		/// <summary> ADT struktury, ktorej patria zaznamy. </summary>
		structures::StructureADT adt_;
		/// <summary> Tabulka, ktorej klucom je typ informacie a datami su vsetky informacie tohto typu. </summary>
		InfoMap* structureInfoMap_;
	};

	/// <summary> Zdruzuje informacie o vsetkych udajovych strukturach. </summary>
	class StructuresInfoHolder : public InfoItem
	{
	private:
		typedef std::map<int, std::string> InfoCodeNamesMap;
		typedef std::map<structures::StructureADT, InfoCodeNamesMap*> ADTInfoCodeNamesMap;
		typedef std::map<structures::Structure*, StructureInfoHolder*> StructureInfoHolderMap;
	public:
		/// <summary> Skryty konsktruktor. </summary>
		StructuresInfoHolder();

		/// <summary> Destruktor. </summary>
		virtual ~StructuresInfoHolder();

		/// <summary> Vrati informacie danej udajovej struktury. </summary>
		/// <param name = "structure"> Struktura, ktorej informacie su ziadane. </param>
		/// <returns> Informacie danej udajovej struktury. Ak este neexistuju, vrati nullptr. </returns>
		StructureInfoHolder* getStructureInfoHolder(structures::Structure* structure);

		/// <summary> Zaregistruje pre dane ADT zbieranie informacii s danym id a nazvom. Ak uz je taka informacia zaregistrovana, prepise jej nazov. </summary>
		/// <param name = "adt"> ADT struktury. </param>
		/// <param name = "infoID"> ID informacie. </param>
		/// <param name = "infoCaption"> Nazov informacie. </param>
		void registerInfo(structures::StructureADT adt, int infoID, std::string infoCaption);

		/// <summary> Ziska nazov zaregistrovanej informacie. </summary>
		/// <param name = "adt"> ADT struktury. </param>
		/// <param name = "infoID"> ID informacie. </param>
		/// <returns> Nazov operacie. Ak informacia nie je zaregistrovana, vrati prazdny retazec. </returns>
		std::string infoCaption(structures::StructureADT adt, int infoID);

		/// <summary> Zaznamena informaciu nad strukturou. </summary>
		/// <param name = "params"> Parametre potrene pre registraciu informacie. </param>
		/// <returns> Zaznamenany zaznam o operacii. </returns>
		/// <remarks> 
		/// Skontroluje, ci zbiera taku operaciu nad ADT. Ak nie, vrati nullptr. 
		/// Jednotlive instancie tried, z ktorych sa sklada vysledna struktura su vytvarane prislusnymi tovarenskymi metodami.
		/// Navrhnuta ako template method. 
		/// Upravit spravanie je mozne upravit metodami getStructureInfoHolderInstance, beforeInfoStored a afterInfoStored.
		/// </remarks>
		StructureInfo* createAndStoreInfo(InfoRegistrationParams* params);

		/// <summary> Odstrani tuto informaciu. Vola destruktor! </summary>
		/// <param name = "info"> Odstranena informacia. </param>
		/// <remarks> Spravanie je mozne upravit metodou beforeInfoRemoved. </remarks>
		void removeInfo(StructureInfo* info);
	protected:
		/// <summary> Vytvori instanciu StructureInfoHolder pre danu strukturu. </summary>
		/// <param name = "params"> Parametre potrene pre vytvorenie instance StructureInfoHolder. </param>
		/// <returns> Instanciu StructureInfoHolder pre danu strukturu. </returns>
		/// <remarks> Potomok moze predefinovat vytvaranu triedu StructureInfoHolder. </remarks>
		virtual StructureInfoHolder* getStructureInfoHolderInstance(InfoRegistrationParams* params);

		/// <summary> Volana pred poziadanim instancie StructureInfoHolder o registrovanie informacie. </summary>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vyuziva sa v sablonovej metode createAndStoreInfo. U predka nerobi nic. </remarks>
		virtual void beforeInfoStored(InfoRegistrationParams* params);

		/// <summary> Volana po poziadani instancie StructureInfoHolder o registrovanie informacie. </summary>
		/// <param name = "createdInfo"> Informacia vytvorena prislusnym objektom StructureInfoHolder. </param>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vyuziva sa v sablonovej metode createAndStoreInfo. U predka nerobi nic. </remarks>
		virtual void afterInfoStored(StructureInfo* createdInfo, InfoRegistrationParams* params);

		/// <summary> Volana po poziadani instancie StructureInfoHolder o vymazanie informacie. </summary>
		/// <param name = "info"> Odstranena informacia. </param>
		/// <remarks> Vyuziva sa v sablonovej metode removeInfo. U predka nerobi nic. </remarks>
		virtual void beforeInfoRemoved(StructureInfo* info);
	private:
		/// <summary> Tabulka, ktorej klucom je struktura a datami su vsetky jej informacie. </summary>
		StructureInfoHolderMap* structuresInfo_;

		/// <summary> Tabulka, ktora sluzi ako filter informacii. Prvym klucom je ADT struktury, druhym klucom je ID informacie. Data su nazov tejto informacie. </summary>
		ADTInfoCodeNamesMap* registeredInfo_;

		/// <summary> Zisti, ci je pre dane ADT zaregistrovana informacia s danym ID. </summary>
		/// <param name = "adt"> ADT struktury. </param>
		/// <param name = "infoID"> ID informacie. </param>
		/// <returns> true, ak je taka informacia pre ADT zaregistrovana, false inak. </returns>
		bool isInfoRegistered(structures::StructureADT adt, int infoID);

		/// <summary> Vrati filter informacii daneho ADT. </summary>
		/// <param name = "adt"> ADT, ktoreho filter sa ma vratit. </param>
		/// <returns> Filter informacii daneho ADT. Ak este neexistuje, vrati nullptr. </returns>
		typename InfoCodeNamesMap* getRegisteredInfoOfADT(structures::StructureADT adt);
	};



}