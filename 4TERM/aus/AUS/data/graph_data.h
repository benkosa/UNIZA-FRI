#pragma once

#include "../structures/graph/graph.h"
#include "data_routines.h"
#include <string>

namespace data
{
	/// <summary> Data ukladane vo vrchole grafu registrovaneho v aplikacii DataStructures. </summary>
	class GraphDataVertex : public structures::GraphData
	{
	public:
		/// <summary> Getter, ktory vrati data typu GraphDataVertex z daneho vrcholu grafu. </summary>
		/// <param name = "vertex"> Vrchol grafu, z ktoreho ma vratit data typu GraphDataVertex. </param>
		/// <returns> Smernik na data typu GraphDataVertex ulozene v danom vrchole grafu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak dany vrchol neobsahuje data typu GraphDataVertex. </exception>  
		static GraphDataVertex * getData(structures::GraphVertex* vertex);

		/// <summary> Getter vracajuci jedinecny identifikator triedy GraphDataVertex. </summary>
		/// <returns> Adresa, na ktorej je "ulozena" trieda GraphDataVertex. </returns>
		static const GraphDataVertex * getKey();
	public:
		/// <summary> Konstruktor. </summary>
		GraphDataVertex();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Data typu GraphDataVertex, z ktorych sa prevezmu vlastnosti. </param>
		GraphDataVertex(const GraphDataVertex& other);

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je typu GraphDataVertex. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual GraphData& operator=(const GraphData& other) override;

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat dat. </summary>
		/// <returns> Ukazovatel na klon dat. </returns>
		virtual GraphData * clone() const override;

		/// <summary> Getter vracajuci jedinecny identifikator triedy GraphDataVertex. </summary>
		/// <returns> Adresa, na ktorej je "ulozena" trieda GraphDataVertex. </returns>
		virtual const GraphData * getClassKey() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
		GraphDataVertex& operator=(const GraphDataVertex& other);

		/// <summary> Resetne data na defaultne hodnoty. </summary>
		void reset();

		/// <summary> Upravi data pomocou okna. </summary>
		/// <returns> true, ak boli data upravene, false inak. </returns>
		bool edit();

		/// <summary> Prevedie data na retazec. </summary>
		/// <returns> Retazec s datami. </returns>
		System::String^ toString() const;
	private:
		/// <summary> Objekt predstavujuci jednoznacny identifikator triedy GraphDataVertex. </summary>
		/// <remarks> Pod jednoznacnym identifikatorom sa rozumie adresa objektu classKey_. </remarks>
		static const GraphDataVertex classKey_;

		/// <summary> Konkretne data - popisok vrcholu. </summary>
		std::string label_;
	};


	/// <summary> Data ukladane v hrane grafu registrovaneho v aplikacii DataStructures. </summary>
	class GraphDataEdge : public structures::GraphDataLength
	{
	public:
		/// <summary> Getter, ktory vrati data typu GraphDataEdge z danej hrany grafu. </summary>
		/// <param name = "edge"> Hrana grafu, z ktorej ma vratit data typu GraphDataEdge. </param>
		/// <returns> Smernik na data typu GraphDataEdge ulozene v danej hrane grafu. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak dana hrana neobsahuje data typu GraphDataEdge. </exception>  
		static GraphDataEdge * getData(structures::GraphEdge* edge);

		/// <summary> Getter vracajuci jedinecny identifikator triedy GraphDataEdge. </summary>
		/// <returns> Adresa, na ktorej je "ulozena" trieda GraphDataEdge. </returns>
		static const GraphDataEdge * getKey();
	public:
		/// <summary> Konstruktor. </summary>
		GraphDataEdge();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Data typu GraphDataEdge, z ktorych sa prevezmu vlastnosti. </param>
		GraphDataEdge(const GraphDataEdge& other);

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je typu GraphDataEdge. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		GraphDataLength& operator=(const GraphDataLength& other) override;

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat dat. </summary>
		/// <returns> Ukazovatel na klon dat. </returns>
		virtual GraphData * clone() const override;

		/// <summary> Getter vracajuci jedinecny identifikator triedy GraphDataEdge. </summary>
		/// <returns> Adresa, na ktorej je "ulozena" trieda GraphDataEdge. </returns>
		virtual const GraphData * getClassKey() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Data, z ktorych ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tieto data nachadzaju po priradeni. </returns>
		GraphDataEdge& operator=(const GraphDataEdge& other);

		/// <summary> Resetne data na defaultne hodnoty. </summary>
		void reset();

		/// <summary> Upravi data pomocou okna. </summary>
		/// <returns> true, ak boli data upravene, false inak. </returns>
		bool edit();

		/// <summary> Vracia priznak, ci je hrana s tymito datami vybrata. </summary>
		/// <returns> Adresa, na ktorej sa nachadza dany priznak. </returns>
		/// <remarks> Jedna sa o umelu metodu, ktora sa vyuziva pri zobrazovani predchodcov/nasledovnikov daneho vrcholu. </remarks>
		bool& selected();

		/// <summary> Vracia priznak, ci je hrana s tymito datami vybrata. </summary>
		/// <returns> Hodnota priznaku. </returns>
		/// <remarks> Jedna sa o umelu metodu, ktora sa vyuziva pri zobrazovani predchodcov/nasledovnikov daneho vrcholu. </remarks>
		bool selected() const;

		/// <summary> Prevedie data na retazec. </summary>
		/// <returns> Retazec s datami. </returns>
		System::String^ toString() const;
	private:
		/// <summary> Objekt predstavujuci jednoznacny identifikator triedy GraphDataEdge. </summary>
		/// <remarks> Pod jednoznacnym identifikatorom sa rozumie adresa objektu classKey_. </remarks>
		static const GraphDataEdge classKey_;

		/// <summary> Umele data  - priznak sluziaci pri zobrazovani predchodcov/nasledovnikov daneho vrcholu. </summary>
		bool selected_;
	};
}