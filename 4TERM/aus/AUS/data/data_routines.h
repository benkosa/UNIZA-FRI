#pragma once

#include "data_types.h"
#include "form_data.h"
#include "../structures/ds_structure_types.h"

namespace data
{

	typedef System::String ^ (*ToStringFuncPtr)(void*);

	/*Kniznicna trieda obsahujuca rutinne metody pre pracu s datami.*/
	class DataRoutines
	{
	public:
		
		/*Vytvori preddefinovane data*/
		static DataType defaultDataValue();
		/*Vytvori preddefinovany kluc*/
		static KeyType defaultKeyValue();

		/*Vytvori nahodne data*/
		static DataType randomDataValue();
		/*Vytvori nahodnu prioritu*/
		static PriorityType randomPriorityValue();
		/*Vytvori nahodny kluc*/
		static KeyType randomKeyValue();

		/*Porovna, ci su data rovnake*/
		static bool areEqual(const DataType& a, const DataType& b);
		/*Porovna priority. Vrati zaporne cislo, ak je a < b, kladne cislo ak a > b, 0 ak su rovne*/
		static int comparePriorities(const PriorityType& a, const PriorityType& b);
		/*Porovna kluce. Vrati zaporne cislo, ak je a < b, kladne cislo ak a > b, 0 ak su rovne*/
		static int compareKeys(const KeyType& a, const KeyType& b);

		/// <summary> Zobrazi byte pomocou okna. </summary>
		/// <param name = "B"> Byte, ktory ma byt zobrazeny. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showByte(const structures::byte B, String^ caption);

		/// <summary> Zobrazi data pomocou okna. </summary>
		/// <param name = "data"> Data, ktore maju byt zobrazene. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showData(const DataType data, String^ caption);
		
		/// <summary> Zobrazi prioritu pomocou okna. </summary>
		/// <param name = "priority"> Priorita, ktora ma byt zobrazena. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showPriority(const PriorityType priority, String^ caption);
		
		/// <summary> Zobrazi kluc pomocou okna. </summary>
		/// <param name = "key"> Kluc, ktory ma byt zobrazeny. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showKey(const KeyType key, String^ caption);

		/// <summary> Zobrazi id vrcholu pomocou okna. </summary>
		/// <param name = "vertexId"> Id, ktore ma byt zobrazene. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showVertexId(const VertexIdType vertexId, String^ caption);

		/// <summary> Zobrazi cele cislo pomocou okna. </summary>
		/// <param name = "number"> Cele cislo, ktore ma byt zobrazene. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showNumber(const int number, String^ caption);

		/// <summary> Zobrazi desatinne cislo pomocou okna. </summary>
		/// <param name = "number"> Desatinne cislo, ktore ma byt zobrazene. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showNumber(const double number, String^ caption);

		/// <summary> Zobrazi retazec pomocou okna. </summary>
		/// <param name = "str"> Retazec, ktory ma byt zobrazeny. </param>
		/// <param name = "caption"> Popis okna. </param>
		static void showString(const std::string& str, String^ caption);

		/// <summary> Upravi byte pomocou okna. </summary>
		/// <param name = "B"> Byte, ktory ma byt upraveny. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bol byte upraveny, false inak. </returns>
		static bool editByte(structures::byte& B, String^ caption);

		/// <summary> Upravi byte pomocou okna. </summary>
		/// <param name = "B"> Byte, ktory ma byt upraveny. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bol byte upraveny, false inak. </returns>
		static bool editByteManaged(structures::byte% B, String^ caption);

		/// <summary> Upravi data pomocou okna. </summary>
		/// <param name = "data"> Data, ktore maju byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak boli data upravene, false inak. </returns>
		static bool editData(DataType& data, String^ caption);
		
		/// <summary> Upravi data pomocou okna. </summary>
		/// <param name = "data"> Data, ktore maju byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak boli data upravene, false inak. </returns>
		static bool editDataManaged(DataType% data, String^ caption);

		/// <summary> Upravi prioritu pomocou okna. </summary>
		/// <param name = "priority"> Priorita, ktora ma byt upravena. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bola priorita upravena, false inak. </returns>
		static bool editPriority(PriorityType& priority, String^ caption);

		/// <summary> Upravi prioritu pomocou okna. </summary>
		/// <param name = "priority"> Priorita, ktora ma byt upravena. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bola priorita upravena, false inak. </returns>
		static bool editPriorityManaged(PriorityType% priority, String^ caption);

		/// <summary> Upravi kluc pomocou okna. </summary>
		/// <param name = "key"> Kluc, ktory ma byt upraveny. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bol kluc upraveny, false inak. </returns>
		static bool editKey(KeyType& key, String^ caption);

		/// <summary> Upravi kluc pomocou okna. </summary>
		/// <param name = "key"> Kluc, ktory ma byt upraveny. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bol kluc upraveny, false inak. </returns>
		static bool editKeyManaged(KeyType% key, String^ caption);

		/// <summary> Upravi id vrcholu grafu pomocou okna. </summary>
		/// <param name = "vertexId"> Id, ktore ma byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bolo id upravene, false inak. </returns>
		static bool editVertexId(VertexIdType& vertexId, String^ caption);

		/// <summary> Upravi id vrcholu grafu pomocou okna. </summary>
		/// <param name = "vertexId"> Id, ktore ma byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bolo id upravene, false inak. </returns>
		static bool editVertexIdManaged(VertexIdType% vertexId, String^ caption);

		/// <summary> Upravi cele cislo pomocou okna. </summary>
		/// <param name = "number"> Cele cislo, ktore ma byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bolo cele cislo upravene, false inak. </returns>
		static bool editNumber(int& number, String^ caption);

		/// <summary> Upravi desatinne cislo pomocou okna. </summary>
		/// <param name = "number"> Desatinne cislo, ktore ma byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bolo desatinne cislo upravene, false inak. </returns>
		static bool editNumber(double& number, String^ caption);

		/// <summary> Upravi cele cislo pomocou okna. </summary>
		/// <param name = "number"> Cele cislo, ktore ma byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bolo cele cislo upravene, false inak. </returns>
		static bool editNumberManaged(int% number, String^ caption);

		/// <summary> Upravi desatinne cislo pomocou okna. </summary>
		/// <param name = "number"> Desatinne cislo, ktore ma byt upravene. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bolo desatinne cislo upravene, false inak. </returns>
		static bool editNumberManaged(double% number, String^ caption);

		/// <summary> Upravi retazec pomocou okna. </summary>
		/// <param name = "str"> Retazec, ktory ma byt upraveny. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bol retazec upraveny, false inak. </returns>
		static bool editString(std::string& str, String^ caption);

		/// <summary> Upravi retazec pomocou okna. </summary>
		/// <param name = "str"> Retazec, ktory ma byt upraveny. </param>
		/// <param name = "caption"> Popis okna. </param>
		/// <returns> true, ak bol retazec upraveny, false inak. </returns>
		static bool editStringManaged(std::string% str, String^ caption);
	private:
		/*Sukromny konstruktor znemoznuje vytvorenie instancie kniznicnej triedy.*/
		DataRoutines();

		template <typename T>
		static bool initEditForm(T& data, FormData::FormType formType, String^ caption);

		template <typename T>
		static void initViewForm(T data, FormData::FormType formType, String^ caption);
	};

	template<typename T>
	inline bool DataRoutines::initEditForm(T & data, FormData::FormType formType, String^ caption)
	{
		FormData^ frmData = gcnew FormData(formType, FormData::FormMode::fmEDIT, caption, true);
		T dataCopy = data;
		frmData->setData(&dataCopy, sizeof(T));
		frmData->ShowDialog();

		bool result;

		switch (frmData->DialogResult)
		{
		case DialogResult::OK:
			result = true;
			data = dataCopy;
			break;
		default:
			result = false;
		}

		delete frmData;
		return result;
	}

	template<typename T>
	inline void DataRoutines::initViewForm(T data, FormData::FormType formType, String^ caption)
	{
		FormData^ frmData = gcnew FormData(formType, FormData::FormMode::fmVIEW, caption, false);
		frmData->setData(&data, sizeof(T));
		frmData->ShowDialog();
		delete frmData;
	}

}
