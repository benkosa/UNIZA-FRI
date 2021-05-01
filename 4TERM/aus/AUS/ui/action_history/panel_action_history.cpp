#include "panel_action_history.h"
#include "../controls/controls.h"
#include "../ui_routines.h"

namespace ui
{

	PanelActionHistory::PanelActionHistory(void)
	{
		InitializeComponent();

		enableControls();
	}

	void PanelActionHistory::presentStructure(structures::Structure * structure, structures::StructureADT adt)
	{
		lviewHistory->Items->Clear();

		StructureActionHistoryHolder* operations = dynamic_cast<StructureActionHistoryHolder*>(StructuresActionHistoryHolder::getInstance()->getStructureInfoHolder(structure));

		if (operations != nullptr)
		{
			for (OperationInfo* operation : *operations->getAllOperations())
			{
				lviewHistory->Items->Add(createListViewItem(operation));
			}
		}

		enableControls();
	}

	void PanelActionHistory::actionPerformed(OperationInfo* operationInfo)
	{
		lviewHistory->Items->Insert(0, createListViewItem(operationInfo));
		enableControls();
	}

	PanelActionHistory::~PanelActionHistory()
	{
		if (components)
		{
			delete components;
		}
	}

	ListViewItem^ PanelActionHistory::createListViewItem( OperationInfo * operationInfo)
	{
		std::string caption = StructuresActionHistoryHolder::getInstance()->infoCaption(operationInfo->getADT(), operationInfo->getID());
		
		ListViewItem^ result = gcnew ListViewItem();
		result->Text = gcnew String(caption.c_str());
		result->SubItems->Add(Convert::ToString(operationInfo->getTime()));
		result->Tag = gcnew InfoItemData(operationInfo);

		return result;
	}

	void PanelActionHistory::enableControls()
	{
		bool areThereItems = lviewHistory->Items->Count > 0;
		bool isSelectedItem = lviewHistory->SelectedItems->Count == 1;

		btnUndoLast->Enabled = areThereItems;
		btnRedoLast->Enabled = areThereItems;
		btnClear->Enabled = areThereItems;
		btnUndoThis->Enabled = isSelectedItem;
		btnRedoThis->Enabled = isSelectedItem;
	}

	void PanelActionHistory::undo(ListViewItem ^ item)
	{
		InfoItemData^ itemData = dynamic_cast<InfoItemData^>(item->Tag);
		OperationInfo* operationInfo = itemData->Info;

		Action^ action = ControlsDirector::getInstance()->getControlsHolderInstance(operationInfo->getADT())->getAction(operationInfo->getID());
		action->undo(operationInfo->getMemento());

		remove(item);
	}

	void PanelActionHistory::redo(ListViewItem ^ item)
	{
		InfoItemData^ itemData = dynamic_cast<InfoItemData^>(item->Tag);
		OperationInfo* operationInfo = itemData->Info;

		Action^ action = ControlsDirector::getInstance()->getControlsHolderInstance(operationInfo->getADT())->getAction(operationInfo->getID());
		action->redo(operationInfo->getMemento(), true);
	}

	void PanelActionHistory::remove(ListViewItem ^ item)
	{
		InfoItemData^ itemData = dynamic_cast<InfoItemData^>(item->Tag);
		OperationInfo* operationInfo = itemData->Info;

		StructuresActionHistoryHolder::getInstance()->removeInfo(operationInfo);
		lviewHistory->Items->Remove(item);
	}

	System::Void PanelActionHistory::btnUndoLast_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		undo(lviewHistory->Items[0]);
		enableControls();
	}

	System::Void PanelActionHistory::btnRedoLast_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		redo(lviewHistory->Items[0]);
		enableControls();
	}

	System::Void PanelActionHistory::btnClear_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		if (UIRoutines::confirmDialog("Clear", "Are you sure you want to clear whole operation history?"))
		{
			while (lviewHistory->Items->Count > 0)
			{
				remove(lviewHistory->Items[0]);
			}
		}

		enableControls();
	}

	System::Void PanelActionHistory::btnUndoThis_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		ListViewItem^ litem = lviewHistory->SelectedItems[0];
		if (UIRoutines::confirmDialog("Undo " + litem->Text, "Undo of operation that is out of order can fail what can potentially cause the operation stack inoperative. Continue?"))
		{
			undo(litem);
			enableControls();
		}
	}

	System::Void PanelActionHistory::btnRedoThis_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		ListViewItem^ litem = lviewHistory->SelectedItems[0];
		if (UIRoutines::confirmDialog("Redo " + litem->Text, "Redo of operation that is out of order can fail what can potentially cause the operation stack inoperative. Continue?"))
		{
			redo(litem);
			enableControls();
		}
	}

	System::Void PanelActionHistory::lviewHistory_ItemSelectionChanged(System::Object ^ sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs ^ e)
	{
		enableControls();
	}

}
