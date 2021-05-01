#include "panel_sorting.h"
#include "../color_scheme.h"

#include "../logger/ui_logger.h"
#include "../../structures/table/sorting/shuffle.h"
#include "../../structures/table/sorting/insert_sort.h"
#include "../../structures/table/sorting/select_sort.h"
#include "../../structures/table/sorting/bubble_sort.h"
#include "../../structures/table/sorting/quick_sort.h"
#include "../../structures/table/sorting/heap_sort.h"
#include "../../structures/table/sorting/shell_sort.h"
#include "../../structures/table/sorting/radix_sort.h"
#include "../../structures/table/sorting/merge_sort.h"

namespace ui
{

	PanelSorting ^ PanelSorting::createAndIntegratePanelSorting(Panel ^ owner)
	{
		PanelSorting ^ result = gcnew PanelSorting();
		result->initialize();
		owner->Controls->Add(result);
		result->Dock = DockStyle::Fill;
		return result;
	}

	ui::PanelSorting::PanelSorting(void):
		table_(new structures::UnsortedSequenceTable<int, int>())
	{
		InitializeComponent();
	}

	ui::PanelSorting::~PanelSorting()
	{
		if (components)
		{
			delete components;
		}

		delete table_;
		table_ = nullptr;
	}

	void PanelSorting::initialize()
	{
		try
		{
			table_->clear();
			for (int i = 0; i < 1000; i++)
			{
				table_->insert(i, i);
			}
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
		}
	}

	void PanelSorting::performSort(structures::Sort<int, int>* sorter)
	{
		try
		{
			PanelSorting^ temp = this;
			UISortNotifier notifier(&temp);
			sorter->setNotifier(&notifier);
			(*sorter)(*table_);
			pictureTable->Refresh();
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
		}
		catch (System::Exception^ ex)
		{
			log::Logger::getInstance()->logError(ex->Message);
		}
	}

	void PanelSorting::doSortUpdate()
	{
		pictureTable->Refresh();
	}

	System::Void PanelSorting::pictureTable_Paint(System::Object ^ sender, System::Windows::Forms::PaintEventArgs ^ e)
	{
		try
		{
			int sizeI = static_cast<int>(table_->size());
			float sizeF = static_cast<float>(table_->size());

			Graphics^ g = e->Graphics;
			float penWidth = pictureTable->Width / sizeF;

			float y1 = static_cast<float>(pictureTable->Height);
			float keyRatio = pictureTable->Height / sizeF;

			for (int i = 0; i < static_cast<int>(table_->size()); i++)
			{
				structures::TableItem<int, int>&  tableItem = table_->getItemAtIndex(i);

				float x = i * penWidth;
				float y2 = y1 - keyRatio * tableItem.getKey();

				Pen^ pen = gcnew Pen(Color(ColorSchemeJet::getInstance()->getColor(tableItem.getKey(), 0, sizeI)), penWidth);

				g->DrawLine(pen, x, y1, x, y2);
			}
		}
		catch (std::exception ex)
		{
			log::Logger::getInstance()->logError(ex.what());
		}
	}

	System::Void PanelSorting::btnShuffle_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::Shuffle<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnInsertSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::InsertSort<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnSelectSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::SelectSort<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnBubbleSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::BubbleSort<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnQuickSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::QuickSort<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnHeapSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::HeapSort<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnShellSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::ShellSort<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnRadixSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::RadixSort<int, int> sorter;
		performSort(&sorter);
	}

	System::Void PanelSorting::btnMergeSort_Click(System::Object ^ sender, System::EventArgs ^ e)
	{
		structures::MergeSort<int, int> sorter;
		performSort(&sorter);
	}

	UISortNotifier::UISortNotifier(PanelSorting ^* panelSorting):
		SortNotifier(25),
		panelSorting_(panelSorting)
	{
	}

	void UISortNotifier::doNotify()
	{
		(*panelSorting_)->doSortUpdate();
	}

}
