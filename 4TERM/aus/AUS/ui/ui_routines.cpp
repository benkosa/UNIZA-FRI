#include "ui_routines.h"
#include "../structures/ds_structure_types.h"
#include <sstream>
#include <vcclr.h>


using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;

namespace ui {

	void UIRoutines::layoutControlToCenter(Control^ control, Rectangle^ rect, int offsetLeft, int offsetTop)
	{
		control->Left = offsetLeft + rect->Left + rect->Width / 2 - control->Width / 2;
		control->Top = offsetTop + rect->Top + rect->Height / 2 - control->Height / 2;
	}

	void UIRoutines::layoutControlFillRect(Control^ control, Rectangle^ rect, int offsetLeft, int offsetTop)
	{
		control->Left = offsetLeft + rect->Left;
		control->Top = offsetTop + rect->Top;
		control->Width = rect->Width;
		control->Height = rect->Height;
	}

	string UIRoutines::convertStructureADTToStr(const structures::StructureADT adt)
	{
		switch (adt)
		{
			case structures::StructureADT::adtVECTOR:
				return "Vector";
			case structures::StructureADT::adtARRAY:
				return "Array";
			case structures::StructureADT::adtLIST:
				return "List";
			case structures::StructureADT::adtQUEUE:
				return "Queue";
			case structures::StructureADT::adtSTACK:
				return "Stack";
			case structures::StructureADT::adtPRIORITY_QUEUE:
				return "Priority queue";
			case structures::StructureADT::adtTREE:
				return "Tree";
			case structures::StructureADT::adtGRAPH:
				return "Graph";
			case structures::StructureADT::adtTABLE:
				return "Table";
			default:
				return "Unknown ADT";
		}
	}

	string  UIRoutines::convertStructureADSToStr(const structures::StructureADS ads)
	{
		switch (ads)
		{
			case structures::StructureADS::adsVECTOR:
				return "Vector";

			case structures::StructureADS::adsARRAY:
				return "Array";

			case structures::StructureADS::adsLIST_ARRAY:
				return "Array list";
			case structures::StructureADS::adsLIST_LINKED:
				return "Linked list";
			case structures::StructureADS::adsLIST_DOUBLE_LINKED:
				return "Double-linked list";
			case structures::StructureADS::adsLIST_CYCLICAL:
				return "Cyclical list";

			case structures::StructureADS::adsQUEUE_ARRAY:
				return "Queue by array";
			case structures::StructureADS::adsQUEUE_LIST:
				return "Queue by list";

			case structures::StructureADS::adsSTACK_ARRAY:
				return "Stack by array";
			case structures::StructureADS::adsSTACK_LIST:
				return "Stack by list";

			case structures::StructureADS::adsPRIORITY_QUEUE_ARRAY_LIST_SORTED:
				return "Priority queue by sorted array list";
			case structures::StructureADS::adsPRIORITY_QUEUE_ARRAY_LIST_UNSORTED:
				return "Priority queue by unsorted array list";
			case structures::StructureADS::adsPRIORITY_QUEUE_LINKED_LIST:
				return "Priority queue by linked list";
			case structures::StructureADS::adsPRIORITY_QUEUE_TWO_LISTS:
				return "Priority queue by two lists";
			case structures::StructureADS::adsPRIORITY_QUEUE_DOUBLE_LAYER:
				return "Priority queue double layer implementation";
			case structures::StructureADS::adsPRIORITY_QUEUE_HEAP:
				return "Heap";

			case structures::StructureADS::adsTREE_MULTI_WAY:
				return "Multi way tree";
			case structures::StructureADS::adsTREE_K_WAY:
				return "K way tree";
			case structures::StructureADS::adsTREE_BINARY:
				return "Binary tree";

			case structures::StructureADS::adsGRAPH_MATRIX:
				return "Graph by matrix";
			case structures::StructureADS::adsGRAPH_FORWARD_STAR:
				return "Graph by forward star";
			case structures::StructureADS::adsGRAPH_BI_STAR:
				return "Graph by bidirectional star";

			case structures::StructureADS::adsTABLE_SEQUENCE_SORTED:
				return "Sorted sequence table";
			case structures::StructureADS::adsTABLE_SEQUENCE_UNSORTED:
				return "Nonsorted sequence table";
			case structures::StructureADS::adsTABLE_LINKED:
				return "Linked table";
			case structures::StructureADS::adsTABLE_DIAMOND:
				return "Diamond table";
			case structures::StructureADS::adsTABLE_HASH:
				return "Hash table";
			case structures::StructureADS::adsTABLE_BST:
				return "Binary search tree";
			case structures::StructureADS::adsTABLE_TREAP:
				return "Treap";
			default:
				return "Unknown ADS";
		}
	}

	string UIRoutines::convertIntToStr(int i)
	{
		return std::to_string(i);
	}

	std::string UIRoutines::convertStringtoStr(String ^ str)
	{
		pin_ptr<const wchar_t> p = PtrToStringChars(str);
		wstring s(p);                                                        
		return string(s.begin(), s.end());
	}

	System::String ^ UIRoutines::convertMemoryToString(const void * ptr, const int bytes)
	{
		String^ result = "";
		for (int iB = 0; iB < bytes; iB++)
		{
			const structures::byte B = *(reinterpret_cast<const structures::byte*>(ptr) + iB);
			for (int ib = 7; ib >= 0; ib--)
				result += (B >> ib) & 1 ? "1" : "0";
			result += " ";
		}
		return result;
	}

	Color UIRoutines::createRGBColor(int r, int g, int b)
	{
		return Color::FromArgb(static_cast<Int32>(static_cast<Byte>(r)),
			                   static_cast<Int32>(static_cast<Byte>(g)),
			                   static_cast<Int32>(static_cast<Byte>(b)));
	}

	void UIRoutines::showMessage(String ^ caption, String ^ message)
	{
		MessageBox::Show(nullptr, message, caption, MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	bool UIRoutines::confirmDialog(String ^ caption, String ^ message)
	{
		return MessageBox::Show(nullptr, message, caption, MessageBoxButtons::YesNo, MessageBoxIcon::Question) == DialogResult::Yes;
	}

	UIRoutines::UIRoutines()
	{
	}

}