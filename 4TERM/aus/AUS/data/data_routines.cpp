#include "data_routines.h"
#include "data_types.h"
#include "form_data.h"
#include <sstream>

namespace data
{

	DataType DataRoutines::defaultDataValue()
	{
		return 0;
	}

	KeyType DataRoutines::defaultKeyValue()
	{
		return 0;
	}

	DataType DataRoutines::randomDataValue()
	{
		return rand() % 1000;
	}

	PriorityType DataRoutines::randomPriorityValue()
	{
		return rand() % 1000;
	}

	KeyType DataRoutines::randomKeyValue()
	{
		return rand() % 1000;
	}

	bool DataRoutines::areEqual(const DataType & a, const DataType & b)
	{
		return a == b;
	}

	int DataRoutines::comparePriorities(const PriorityType& a, const PriorityType& b)
	{
		return b - a;
	}

	int DataRoutines::compareKeys(const KeyType& a, const KeyType& b)
	{
		return a - b;
	}

	void DataRoutines::showByte(const structures::byte B, String^ caption)
	{
		DataRoutines::initViewForm<structures::byte>(B, FormData::FormType::dftBYTE, caption);
	}

	void DataRoutines::showData(const DataType data, String^ caption)
	{
		DataRoutines::initViewForm<DataType>(data, FormData::FormType::dftDATA, caption);
	}

	void DataRoutines::showPriority(const PriorityType priority, String^ caption)
	{
		DataRoutines::initViewForm<PriorityType>(priority, FormData::FormType::dftPRIORITY, caption);
	}

	void DataRoutines::showKey(const KeyType key, String^ caption)
	{
		DataRoutines::initViewForm<KeyType>(key, FormData::FormType::dftKEY, caption);
	}

	void DataRoutines::showVertexId(const VertexIdType vertexId, String ^ caption)
	{
		DataRoutines::initViewForm<VertexIdType>(vertexId, FormData::FormType::dftVERTEX_ID, caption);
	}

	void DataRoutines::showNumber(const int number, String ^ caption)
	{
		DataRoutines::initViewForm<int>(number, FormData::FormType::dftINT, caption);
	}

	void DataRoutines::showNumber(const double number, String ^ caption)
	{
		DataRoutines::initViewForm<double>(number, FormData::FormType::dftDOUBLE, caption);
	}

	void DataRoutines::showString(const std::string & str, String ^ caption)
	{
		DataRoutines::initViewForm<std::string>(str, FormData::FormType::dftSTRING, caption);
	}

	bool DataRoutines::editByte(structures::byte & B, String^ caption)
	{
		return DataRoutines::initEditForm<structures::byte>(B, FormData::FormType::dftBYTE, caption);
	}

	bool DataRoutines::editByteManaged(structures::byte % B, String ^ caption)
	{
		structures::byte localB = B;
		if (editByte(localB, caption))
		{
			B = localB;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataRoutines::editData(DataType & data, String^ caption)
	{
		return DataRoutines::initEditForm<DataType>(data, FormData::FormType::dftDATA, caption);
	}

	bool DataRoutines::editDataManaged(DataType % data, String^ caption)
	{
		DataType localData = data;
		if (editData(localData, caption))
		{
			data = localData;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataRoutines::editPriority(PriorityType & priority, String^ caption)
	{
		return DataRoutines::initEditForm<PriorityType>(priority, FormData::FormType::dftPRIORITY, caption);
	}

	bool DataRoutines::editPriorityManaged(PriorityType % priority, String ^ caption)
	{
		PriorityType localPriority = priority;
		if (editPriority(localPriority, caption))
		{
			priority = localPriority;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataRoutines::editKey(KeyType & key, String^ caption)
	{
		return DataRoutines::initEditForm<KeyType>(key, FormData::FormType::dftKEY, caption);
	}

	bool DataRoutines::editKeyManaged(KeyType % key, String ^ caption)
	{
		KeyType localKey = key;
		if (editKey(localKey, caption))
		{
			key = localKey;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataRoutines::editVertexId(VertexIdType & vertexId, String ^ caption)
	{
		return DataRoutines::initEditForm<VertexIdType>(vertexId, FormData::FormType::dftVERTEX_ID, caption);
	}

	bool DataRoutines::editVertexIdManaged(VertexIdType % vertexId, String ^ caption)
	{
		VertexIdType localVertexId = vertexId;
		if (editVertexId(localVertexId, caption))
		{
			vertexId = localVertexId;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataRoutines::editNumber(int & number, String^ caption)
	{
		return DataRoutines::initEditForm<int>(number, FormData::FormType::dftINT, caption);
	}

	bool DataRoutines::editNumber(double & number, String ^ caption)
	{
		return DataRoutines::initEditForm<double>(number, FormData::FormType::dftDOUBLE, caption);
	}

	bool DataRoutines::editNumberManaged(int % number, String ^ caption)
	{
		int localNumber = number;
		if (editNumber(localNumber, caption))
		{
			number = localNumber;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataRoutines::editNumberManaged(double % number, String ^ caption)
	{
		double localNumber = number;
		if (editNumber(localNumber, caption))
		{
			number = localNumber;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DataRoutines::editString(std::string & str, String ^ caption)
	{
		return DataRoutines::initEditForm<std::string>(str, FormData::FormType::dftSTRING, caption);
	}

	bool DataRoutines::editStringManaged(std::string % str, String ^ caption)
	{
		std::string localStr = str;
		if (editString(localStr, caption))
		{
			str = localStr;
			return true;
		}
		else
		{
			return false;
		}
	}

	DataRoutines::DataRoutines()
	{
	}

}
