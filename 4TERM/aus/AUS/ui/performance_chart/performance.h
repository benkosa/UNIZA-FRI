#pragma once

#include "../controls/structure_info_holder.h"

namespace ui
{

	/// <summary> Predstavuje parametre potrebne pre registraciu informacie of vykone operacie v strukture. </summary>
	public class PerformanceParams : public InfoRegistrationParams
	{
	public:
		/// <summary>  Velkost udajovej struktury v dobe, kedy bola operacia vykonana. </summary>
		size_t Size;
		/// <summary> Cas, kolko trvalo vykonat operaciu. </summary>
		long Time;
	};

	/// <summary> Predstavuje informaciu o vykone operacie v strukture. </summary>
	class PerformanceInfo : public StructureInfo
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "size"> Velkost udajovej struktury v dobe, kedy bola operacia vykonana. </param>
		PerformanceInfo(InfoItem* parent, size_t size);

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "size"> Velkost udajovej struktury v dobe, kedy bola operacia vykonana. </param>
		/// <param name = "time"> Cas, ktory trvalo vykonat operaciu. </param>
		PerformanceInfo(InfoItem* parent, size_t size, long time);

		/// <summary> Getter atributu size_. </summary>
		/// <returns> Hodnota atributu size_. </returns>
		size_t getSize();

		/// <summary> Vrati priemernu casovu narocnost. </summary>
		/// <returns> Priemerna casova narocnost. </returns>
		double complexity();

		/// <summary> Prida do zlozitosti dalsiu hodnotu casu. </summary>
		/// <param name = "time"> Cas, ktory trvalo vykonat operaciu. </param>
		void incTime(long time);
	private:
		/// <summary>  Velkost udajovej struktury v dobe, kedy bola operacia vykonana. </summary>
		size_t size_;
		/// <summary> Sumar casov, ktore trvalo vykonat operaciu. </summary>
		long time_;
		/// <summary> Pocet casov </summary>
		long timeSum_;
	};
	
	/// <summary> Zdruzuje informacie o vykone rovnakej operacie v strukture. </summary>
	class SinglePerformanceContainer : public SingleInfoContainer
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "id"> ID informacie. </param>
		SinglePerformanceContainer(InfoItem* parent, int id);

		/// <summary> Zabezpeci, aby existovali (aspon prazdne) zaznamy po danu velkost udajovej struktury (vratane). </summary>
		/// <param name = "size"> Velkost udajovej struktury. </param>
		void ensureInfoUpToSize(size_t size);
	protected:
		/// <summary> Vytvori instanciu StructureInfo. </summary>
		/// <param name = "params"> Parametre potrebne pre vytvorenie instance StructureInfo. </param>
		/// <returns> Instancia StructureInfo pre danu informaciu. </returns>
		/// <remarks> Potomok moze predefinovat vytvaranu triedu SingleInfoContainer. </remarks>
		StructureInfo* doStoreInfo(InfoRegistrationParams* params) override;

		/// <summary> Volana pred registrovanim informacie. </summary>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vola ensureRecordsUpToSize </remarks>
		void beforeInfoStored(InfoRegistrationParams* params) override;
	};
		
	/// <summary> Zapuzdrje informacie o vykone operacii patriacich konkretnej udajovej strukture. </summary>
	class StructurePerformanceHolder : public StructureInfoHolder
	{
	public:
		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "parent"> Rodic prvku. </param>
		/// <param name = "structure"> Struktura, ktorej patria zaznamy. </param>
		/// <param name = "adt"> ADT struktury, ktorej patria zaznamy. </param>
		StructurePerformanceHolder(InfoItem* parent, structures::Structure* structure, structures::StructureADT adt);
	protected:
		/// <summary> Vytvori instanciu SingleInfoContainer. </summary>
		/// <param name = "params"> Parametre potrebne pre vytvorenie instance SingleInfoContainer. </param>
		/// <returns> Instancia SingleInfoContainer pre danu informaciu. </returns>
		SingleInfoContainer* getSingleInfoContainerInstance(InfoRegistrationParams* params) override;

		/// <summary> Volana pred poziadanim instancie SingleInfoContainer o registrovanie informacie. </summary>
		/// <param name = "params"> Parametre potrebne pre registraciu informacie. </param>
		/// <remarks> Vyuziva sa v sablonovej metode createAndStoreInfo. U predka nerobi nic. </remarks>
		void beforeInfoStored(InfoRegistrationParams* params) override;
	private:
		/// <summary> Maximalna velkost struktury. </summary>
		size_t maxSize_;
	};

	/// <summary> 
	/// Zdruzuje informacie o vykone operacii vsetkych udajovych struktur.  
	/// Navrhnuta podla vzoru Signleton.
	/// </summary>
	class StructuresPerformanceHolder : public StructuresInfoHolder
	{	
	public:
		/// <summary> Jednoducha tovarenska metoda pre ziskanie instancie jedinacika. </summary>
		/// <returns> Instancia triedy StructuresPerformanceHolder. </returns>
		/// <remarks> Vyuziva Lazy initialization. </remarks>
		static StructuresPerformanceHolder* getInstance();

		/// <summary> Odstrani instanciu jedinacika. </summary>
		static void finalize();

		/// <summary> Zaznamena informaciu o vykone operacie struktury. </summary>
		/// <param name = "structure"> Struktura, nad ktorou bola operacia vykonana. </param>
		/// <param name = "adt"> ADT struktury, ktorej patri operacia. </param>
		/// <param name = "operationID"> ID vykonanej operacie. </param>
		/// <param name = "size"> Velkost udajovej struktury v dobe, kedy bola operacia vykonana. </param>
		/// <param name = "time"> Cas, kolko trvalo vykonat operaciu. </param>
		/// <returns> Zaznamenany zaznam o operacii. </returns>
		/// <remarks> Vyuziva metodu createAndStoreInfo, ktorej pripravi objekt s parametrami. Postara sa o jeho zrusenie. </remarks>
		PerformanceInfo* createAndStoreInfo(structures::Structure* structure, structures::StructureADT adt, int operationID, size_t size, long time);
	protected:
		/// <summary> Vytvori instanciu StructureInfoHolder pre danu strukturu. </summary>
		/// <param name = "params"> Parametre potrene pre vytvorenie instance StructureInfoHolder. </param>
		/// <returns> Instanciu StructureInfoHolder pre danu strukturu. </returns>
		/// <remarks> Potomok moze predefinovat vytvaranu triedu StructureInfoHolder. </remarks>
		StructureInfoHolder* getStructureInfoHolderInstance(InfoRegistrationParams* params) override;
	private:
		/// <summary> Skryty konsktruktor. </summary>
		StructuresPerformanceHolder();

		/// <summary> Premenna triedy obsahujuca odkaz na jedinu instanciu triedy. </summary>
		static StructuresPerformanceHolder* structuresPerformanceHolder_;
	};

}