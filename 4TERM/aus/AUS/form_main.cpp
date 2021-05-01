#include "form_main.h"

#include "structures/heap_monitor.h"

#include "structures/ds_structure_types.h"
#include "structures/ds_structure_factory.h"

#include "structures/vector/vector.h"
#include "structures/array/array.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/stack/implicit_stack.h"
#include "structures/stack/explicit_stack.h"
#include "structures/queue/implicit_queue.h"
#include "structures/queue/explicit_queue.h"
#include "structures/priority_queue/priority_queue_sorted_array_list.h"
#include "structures/priority_queue/priority_queue_unsorted_array_list.h"
#include "structures/priority_queue/priority_queue_linked_list.h"
#include "structures/priority_queue/priority_queue_two_lists.h"
#include "structures/priority_queue/heap.h"
#include "structures/tree/multi_way_tree.h"
#include "structures/tree/k_way_tree.h"
#include "structures/tree/binary_tree.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/linked_table.h"
#include "structures/table/binary_search_tree.h"
#include "structures/table/treap.h"
#include "structures/table/hash_table.h"
#include "structures/graph/forward_star_graph.h"
#include "structures/graph/bi_star_graph.h"

#include "data/data_types.h"
#include "data/graph_data.h"

#include "ui/panel_structures.h"
#include "ui/sorting/panel_sorting.h"
#include "ui/logger/ui_logger.h"
#include "ui/logger/panel_logger.h"
#include "ui/performance_chart/performance.h"
#include "ui/action_history/action_history.h"

[STAThread]
void Main(array<String^>^ args)
{
	initHeapMonitor();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ui::FormMain form;
	Application::Run(%form);
}

namespace ui
{

	FormMain::FormMain(void)
	{
		InitializeComponent();
		PanelLogger::createAndIntegrateLogger(pnlLogger);
		structures::StructureFactory* factory = structures::StructureFactory::getInstance();


#pragma region registration
		factory->registerPrototype(structures::StructureADS::adsVECTOR, new structures::Vector(10));

		//TODO 02: Array: register prototype
		factory->registerPrototype(structures::StructureADS::adsARRAY, new structures::Array<data::DataType>(10));

		//TODO 03: ArrayList: register prototype
		factory->registerPrototype(structures::StructureADS::adsLIST_ARRAY, new structures::ArrayList<data::DataType>());

		//TODO 04: LinkedList: register prototype
		//factory->registerPrototype(structures::StructureADS::adsLIST_LINKED, new structures::LinkedList<data::DataType>());

		//TODO 05: Stack: register prototype
		//factory->registerPrototype(structures::StructureADS::adsSTACK_ARRAY, new structures::ImplicitStack<data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsSTACK_LIST, new structures::ExplicitStack<data::DataType>());

		//TODO 05: Queue: register prototype
		//factory->registerPrototype(structures::StructureADS::adsQUEUE_ARRAY, new structures::ImplicitQueue<data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsQUEUE_LIST, new structures::ExplicitQueue<data::DataType>());

		//TODO 06: PriorityQueue: register prototype
		//factory->registerPrototype(structures::StructureADS::adsPRIORITY_QUEUE_ARRAY_LIST_SORTED, new structures::PriorityQueueSortedArrayList<data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsPRIORITY_QUEUE_ARRAY_LIST_UNSORTED, new structures::PriorityQueueUnsortedArrayList<data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsPRIORITY_QUEUE_LINKED_LIST, new structures::PriorityQueueLinkedList<data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsPRIORITY_QUEUE_TWO_LISTS, new structures::PriorityQueueTwoLists<data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsPRIORITY_QUEUE_HEAP, new structures::Heap<data::DataType>());

		//TODO 08: Tree: register prototype
		//factory->registerPrototype(structures::StructureADS::adsTREE_MULTI_WAY, new structures::MultiWayTree<data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsTREE_K_WAY, new structures::KWayTree<data::DataType, 5>());
		//factory->registerPrototype(structures::StructureADS::adsTREE_BINARY, new structures::BinaryTree<data::DataType>());

		//TODO 09: SequenceTable: register prototype
		//factory->registerPrototype(structures::StructureADS::adsTABLE_SEQUENCE_UNSORTED, new structures::UnsortedSequenceTable<data::KeyType, data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsTABLE_SEQUENCE_SORTED, new structures::SortedSequenceTable<data::KeyType, data::DataType>());
		//factory->registerPrototype(structures::StructureADS::adsTABLE_LINKED, new structures::LinkedTable<data::KeyType, data::DataType>());

		//TODO 09: HashTable: register prototype
		//factory->registerPrototype(structures::StructureADS::adsTABLE_HASH, new structures::HashTable<data::KeyType, data::DataType>());

		//TODO 10: BinarySearchTree: register prototype
		//factory->registerPrototype(structures::StructureADS::adsTABLE_BST, new structures::BinarySearchTree<data::KeyType, data::DataType>());

		//TODO 10: Treap: register prototype
		//factory->registerPrototype(structures::StructureADS::adsTABLE_TREAP, new structures::Treap<data::KeyType, data::DataType>());

		//TODO 11: ForwardStarGraph: register prototype
		/*
		{
			data::GraphDataVertex vertexData;
			data::GraphDataEdge edgeData;

			structures::Graph * graph = new structures::ForwardStarGraph();
			graph->registerData(structures::GraphDataType::VERTEX_DATA, &vertexData);
			graph->registerData(structures::GraphDataType::EDGE_DATA, &edgeData);

			factory->registerPrototype(structures::StructureADS::adsGRAPH_FORWARD_STAR, graph);
		}
		*/

		//TODO 11: BiStarGraph: register prototype
		/*
		{
			data::GraphDataVertex vertexData;
			data::GraphDataEdge edgeData;

			structures::Graph * graph = new structures::BiStarGraph();
			graph->registerData(structures::GraphDataType::VERTEX_DATA, &vertexData);
			graph->registerData(structures::GraphDataType::EDGE_DATA, &edgeData);

			factory->registerPrototype(structures::StructureADS::adsGRAPH_BI_STAR, graph);
		}
		*/
#pragma endregion


		PanelStructures::createAndIntegratePanelStructures(pnlVector, structures::StructureADT::adtVECTOR);
		PanelStructures::createAndIntegratePanelStructures(pnlArray, structures::StructureADT::adtARRAY);
		PanelStructures::createAndIntegratePanelStructures(pnlList, structures::StructureADT::adtLIST);
		PanelStructures::createAndIntegratePanelStructures(pnlQueue, structures::StructureADT::adtQUEUE);
		PanelStructures::createAndIntegratePanelStructures(pnlStack, structures::StructureADT::adtSTACK);
		PanelStructures::createAndIntegratePanelStructures(pnlPriorityQueue, structures::StructureADT::adtPRIORITY_QUEUE);
		PanelStructures::createAndIntegratePanelStructures(pnlTree, structures::StructureADT::adtTREE);
		PanelStructures::createAndIntegratePanelStructures(pnlTable, structures::StructureADT::adtTABLE);
		PanelStructures::createAndIntegratePanelStructures(pnlGraph, structures::StructureADT::adtGRAPH);

		//TODO 12: Sorting: register panel for sorting
		//PanelSorting::createAndIntegratePanelSorting(pnlSorting);
	}

	FormMain::~FormMain()
	{
		if (components)
		{
			delete components;
		}
		
		StructuresPerformanceHolder::finalize();
		StructuresActionHistoryHolder::finalize();
		structures::StructureFactory::finalize();
	}
}