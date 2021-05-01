#include "form_data.h"

namespace data
{

	FormData::FormData(const FormType formType, const FormMode formMode, String^ caption, bool showBytes) :
		dataPtr_(nullptr),
		dataSize_(0),
		updates_(0),
		showBytes_(showBytes),
		checkboxes_(gcnew array<CheckBox^>(8)),
		selectedItem_(nullptr),
		formType_(formType),
		formMode_(formMode)
	{
		InitializeComponent();

		checkboxes_[0] = chbBit0;
		checkboxes_[1] = chbBit1;
		checkboxes_[2] = chbBit2;
		checkboxes_[3] = chbBit3;
		checkboxes_[4] = chbBit4;
		checkboxes_[5] = chbBit5;
		checkboxes_[6] = chbBit6;
		checkboxes_[7] = chbBit7;

		switch (formMode_)
		{
		case FormMode::fmVIEW:
			pnlTop->BackColor = *clrVIEW;
			pnlBytes->BackColor = *clrVIEW;
			btnCancel->Visible = false;
			txtValue->Enabled = false;
			break;
		case FormMode::fmEDIT:
			pnlTop->BackColor = *clrEDIT;
			pnlBytes->BackColor = *clrEDIT;
			break;
		}

		AcceptButton = btnOK;

		this->Text = caption;

		adjustHeight();
	}

	FormData::~FormData()
	{
		if (components)
		{
			delete components;
		}
	}

	inline void FormData::setData(void * data, size_t size)
	{
		dataPtr_ = data;
		dataSize_ = size;
		presentData(true);
		adjustHeight();
	}

	void FormData::checkedBit(int bit)
	{
		if (!isUpdating())
		{
			structures::MemoryRoutines::byteNthBitToggle(*selectedByte(), bit);
			refreshItem(selectedItem_);
			refreshData();
		}
	}

	inline void FormData::enableControls()
	{
		btnByteSet->Enabled = areEnabledBitOperation();
		btnByteReset->Enabled = areEnabledBitOperation();
		btnByteXOR->Enabled = areEnabledBitOperation();
		btnByteSHL->Enabled = areEnabledBitOperation();
		btnByteSHR->Enabled = areEnabledBitOperation();
	}

	void FormData::adjustHeight()
	{
		Height = showBytes_ ? frmHEIGHT_BYTES + static_cast<int>(dataSize_) * frmHEIGHT_BYTE : frmHEIGHT_SIMPLE;
	}

	bool FormData::areEnabledBitOperation()
	{
		return formMode_ == FormMode::fmEDIT && selectedItem_ != nullptr;
	}

	inline void FormData::beginUpdate()
	{
		updates_++;
	}

	inline void FormData::endUpdate()
	{
		updates_--;
	}

	inline bool FormData::isUpdating()
	{
		return updates_ > 0;
	}

	inline structures::byte * FormData::selectedByte()
	{
		return selectedItem_ == nullptr ? nullptr : reinterpret_cast<structures::byte*>(dataPtr_) + selectedItem_->Index;
	}

	inline void FormData::presentData(bool refreshTxt)
	{
		beginUpdate();

		lviewBytes->Items->Clear();

		for (int i = 0; i < static_cast<int>(dataSize_); i++)
		{
			ListViewItem^ item = gcnew ListViewItem();
			lviewBytes->Items->Add(item);
			refreshItem(item);
		}

		if (refreshTxt)
		{
			refreshData();
		}

		endUpdate();

		enableControls();
	}

	inline void FormData::refreshItem(ListViewItem ^ item)
	{
		beginUpdate();

		structures::byte* B = reinterpret_cast<structures::byte*>(dataPtr_) + item->Index;
		item->Text = Convert::ToString(*B);

		while (item->SubItems->Count < 9)
			item->SubItems->Add("");

		for (int bitIndex = 0; bitIndex < 8; bitIndex++)
		{
			bool bit = structures::MemoryRoutines::byteNthBitGet(*B, bitIndex);
			ListViewItem::ListViewSubItem^ subitem = item->SubItems[8 - bitIndex];

			bool asCheckboxes = areEnabledBitOperation();

			if (asCheckboxes)
			{
				Rectangle rect = subitem->Bounds;
				ui::UIRoutines::layoutControlToCenter(checkboxes_[bitIndex], rect, lviewBytes->Left, lviewBytes->Top);
				checkboxes_[bitIndex]->Checked = bit;
			}

			subitem->Text = asCheckboxes ? "" : Convert::ToString(static_cast<int>(bit));
			checkboxes_[bitIndex]->Visible = asCheckboxes;
		}

		endUpdate();
	}

	inline void FormData::refreshData()
	{
		beginUpdate();

		switch (formType_)
		{
		case FormType::dftBYTE:
			txtValue->Text = System::Convert::ToString(*reinterpret_cast<structures::byte*>(dataPtr_));
			break;
		case FormType::dftDATA:
			txtValue->Text = System::Convert::ToString(*reinterpret_cast<DataType*>(dataPtr_));
			break;
		case FormType::dftPRIORITY:
			txtValue->Text = System::Convert::ToString(*reinterpret_cast<PriorityType*>(dataPtr_));
			break;
		case FormType::dftKEY:
			txtValue->Text = System::Convert::ToString(*reinterpret_cast<KeyType*>(dataPtr_));
			break;
		case FormType::dftVERTEX_ID:
			txtValue->Text = System::Convert::ToString(*reinterpret_cast<VertexIdType*>(dataPtr_));
			break;
		case FormType::dftINT:
			txtValue->Text = System::Convert::ToString(*reinterpret_cast<int*>(dataPtr_));
			break;
		case FormType::dftDOUBLE:
			txtValue->Text = System::Convert::ToString(*reinterpret_cast<double*>(dataPtr_));
			break;
		case FormType::dftSTRING:
			txtValue->Text = gcnew System::String(reinterpret_cast<std::string*>(dataPtr_)->c_str());
			break;
		default:
			txtValue->Text = "";
		}

		endUpdate();
	}

}