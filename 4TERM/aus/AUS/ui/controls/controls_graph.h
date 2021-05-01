#pragma once

#include "../../structures/graph/graph.h"
#include "../../structures/graph/algorithms/dijkstra.h"
#include "controls.h"
#include "../graph/panel_graph.h"
#include "../../data/data_types.h"
#include "../../data/data_routines.h"
#include "../../data/graph_data.h"
#include "../ui_routines.h"

using namespace System::Windows::Forms;
using namespace System;
using namespace ui::log;

namespace ui
{
	/// <summary> Vseobecny predok mementa akcii nad grafom. </summary>
	private class GraphActionMemento : public ActionMemento
	{
	public:
		const structures::GraphData& getDataBefore() { return *dataBefore_; }
		const structures::GraphData& getDataAfter() { return *dataAfter_; }

		void setDataBefore(const structures::GraphData& dataBefore) { *dataBefore_ = dataBefore; }
		void setDataAfter(const structures::GraphData& dataAfter) { *dataAfter_ = dataAfter; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID akcie, ktora ho vytvorila. </param>
		/// <param name = "defaultData"> Defaultna hodnota dat ulozenych v memente. </param>
		GraphActionMemento(int actionID, const structures::GraphData& defaultData) :
			ActionMemento(actionID),
			dataBefore_(defaultData.clone()),
			dataAfter_(defaultData.clone())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		GraphActionMemento(const GraphActionMemento& other) :
			ActionMemento(other),
			dataBefore_(other.dataBefore_->clone()),
			dataAfter_(other.dataAfter_->clone())
		{}

		/// <summary> Destruktor. </summary>
		~GraphActionMemento()
		{
			delete dataBefore_;
			dataBefore_ = nullptr;
			delete dataAfter_;
			dataAfter_ = nullptr;
		}

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat mementa typu GraphActionMemento. </summary>
		/// <returns> Ukazovatel na klon mementa. </returns>
		ActionMemento* clone() override
		{
			return new GraphActionMemento(*this);
		}

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Memento typu GraphActionMemento, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto memento typu GraphActionMemento nachadza po priradeni. </returns>
		GraphActionMemento& operator=(const GraphActionMemento& other)
		{
			if (this != &other)
			{
				*dataBefore_ = *other.dataBefore_;
				*dataAfter_ = *other.dataAfter_;
			}
			return *this;
		}
	private:
		/// <summary> Stav dat pred operaciou. </summary>
		structures::GraphData* dataBefore_;
		/// <summary> Stav dat po operacii. </summary>
		structures::GraphData* dataAfter_;
	};

	/// <summary> Memento akcii nad vrcholmi grafov. </summary>
	private class GraphVertexActionMemento : public GraphActionMemento
	{
	public:
		data::VertexIdType getVertexId() { return vertexId_; }

		void setVertexId(data::VertexIdType vertexId) { vertexId_ = vertexId; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		GraphVertexActionMemento(int actionID) :
			GraphActionMemento(actionID, data::GraphDataVertex()),
			vertexId_(data::VertexIdType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		GraphVertexActionMemento(const GraphVertexActionMemento& other) :
			GraphActionMemento(other),
			vertexId_(other.vertexId_)
		{}

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat mementa typu GraphVertexActionMemento. </summary>
		/// <returns> Ukazovatel na klon mementa. </returns>
		ActionMemento* clone() override
		{
			return new GraphVertexActionMemento(*this);
		}

	private:
		/// <summary> Id vrcholu. </summary>
		data::VertexIdType vertexId_;
	};

	/// <summary> Memento akcii nad hranami grafov. </summary>
	private class GraphEdgeActionMemento : public GraphActionMemento
	{
	public:
		data::VertexIdType getBeginVertexId() { return beginVertexId_; }
		data::VertexIdType getEndVertexId() { return endVertexId_; }

		void setBeginVertexId(data::VertexIdType beginVertexId) { beginVertexId_ = beginVertexId; }
		void setEndVertexId(data::VertexIdType endVertexId) { endVertexId_ = endVertexId; }

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "actionID"> ID ackie, ktora ho vytvorila. </param>
		GraphEdgeActionMemento(int actionID) :
			GraphActionMemento(actionID, data::GraphDataEdge()),
			beginVertexId_(data::VertexIdType()),
			endVertexId_(data::VertexIdType())
		{}

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Memento, z ktoreho ma prebrat vlastnosti. </param>
		GraphEdgeActionMemento(const GraphEdgeActionMemento& other) :
			GraphActionMemento(other),
			beginVertexId_(other.beginVertexId_),
			endVertexId_(other.endVertexId_)
		{}

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat mementa typu GraphEdgeActionMemento. </summary>
		/// <returns> Ukazovatel na klon mementa. </returns>
		ActionMemento* clone() override
		{
			return new GraphEdgeActionMemento(*this);
		}
	private:
		/// <summary> Id pociatocneho vrcholu. </summary>
		data::VertexIdType beginVertexId_;
		/// <summary> Id koncoveho vrcholu. </summary>
		data::VertexIdType endVertexId_;
	};

	/// <summary> Ovladace pre grafy. </summary>
	ref class ControlsGraph : public ControlsHolder
	{
	protected:
		/// <summary> Predefinovana metoda pre vytvorenie panelu s ovladanim struktury. </summary>
		/// <returns> Panel s ovladanim grafu. </returns>
		Control^ doCreatePresentPanel() override
		{
			PanelPresentGraph^ result = gcnew PanelPresentGraph();
			result->initialize(this);
			return result;
		}

		/// <summary> Vizualizuje strukturu. </summary>
		void doVisualizeStructure() override
		{
			if (Graph != nullptr)
			{
				GraphPanel->visualize(Graph);
			}
		}
	public:
		property structures::Graph* Graph
		{
			structures::Graph* get() { return dynamic_cast<structures::Graph*>(Structure); };
		}

		property PanelPresentGraph^ GraphPanel
		{
			PanelPresentGraph^ get() { return dynamic_cast<PanelPresentGraph^>(ControlsPanel->PanelPresent); };
		}

		/// <summary> Konstruktor. </summary>
		ControlsGraph() : ControlsHolder(structures::StructureADT::adtGRAPH) {};

		/// <summary> Virtualna abstraktna metoda pre vytvorenie akcii ovladajucich udajovu strukturu. </summary>
		/// <param name = "actions"> Zoznam akcii, kam je potrebne nove doregistrovat. </param>
		void createActions(Generic::List<Action^>^ actions) override; // musi byt definovana az pod akciami.
	};

	/// <summary> Trieda predstavuje operaciu v grafe. </summary>
	ref class ActionGraph abstract : public Action
	{
	public:
		static const int idaGraphCREATE_VERTEX = 0;
		static const int idaGraphREMOVE_VERTEX = 1;
		static const int idaGraphEDIT_VERTEX_DATA = 2;
		static const int idaGraphCREATE_EDGE = 3;
		static const int idaGraphREMOVE_EDGE = 4;
		static const int idaGraphEDIT_EDGE_DATA = 5;
		static const int idaGraphGET_SUCCESSORS = 6;
		static const int idaGraphGET_PREDECESSORS = 7;
		static const int idaGraphCLEAR = 8;
		static const int idaGraphSIZE = 9;
		static const int idaGraphIS_EMPTY = 10;
		static const int idaGraphDIJKSTRA = 11;

	public:
		property ControlsGraph^ GraphControls
		{
			ControlsGraph^ get() { return dynamic_cast<ControlsGraph^>(Controls); };
		}

		/// <summary> Vytvori akciu nad grafom. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		/// <param name = "dataEdit"> Data, ktore maju byt ulozene v akcii. </param>
		ActionGraph(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ graphControls, structures::GraphData* dataEdit) :
			Action(id, caption, supportsUndo, supportsRedo, graphControls),
			dataEdit_(dataEdit)
		{}

		/// <summary> Destruktor. </summary>
		/// <remarks> Upratuje vsetky zdroje. </remarks>
		~ActionGraph() override
		{
			this->!ActionGraph();
		}

		/// <summary> Finalizer. </summary>
		/// <remarks> Upratuje nemanazovane zdroje. </remarks>
		!ActionGraph()
		{
			if (dataEdit_ != nullptr)
			{
				delete dataEdit_;
				dataEdit_ = nullptr;
			}
		}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			GraphActionMemento* graphMemento = dynamic_cast<GraphActionMemento*>(memento);
			if (dataEdit_ != nullptr)
			{
				*dataEdit_ = graphMemento->getDataBefore();
			}
		}

		/// <summary> Prezentuje vysledok akcie pouzivatelovi. </summary>
		void doPresentResult() override
		{
			GraphControls->visualizeStructure();
		}

		/// <summary> Adresou vrati data na editovanie ulozene v prislusnej akcii. </summary>
		/// <returns> Adresa, na ktorej sa nachadzaju data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak v akcii nie su ziadne editovatelne data. </exception>  
		structures::GraphData& accessEditData()
		{
			if (dataEdit_ != nullptr)
			{
				return *dataEdit_;
			}
			else
			{
				throw std::logic_error("ActionGraph::accessEditData(): dataEdit_ are not set.");
			}
		}
	protected:
		/// <summary> Smernik na data ulozene v akcii. </summary>
		structures::GraphData* dataEdit_;
	};

	/// <summary> Trieda predstavuje operaciu nad vrcholom grafu. </summary>
	ref class ActionGraphVertex abstract : public ActionGraph
	{
	public:
		/// <summary> Vytvori akciu nad vrcholom grafu. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphVertex(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ graphControls) :
			ActionGraph(id, caption, supportsUndo, supportsRedo, graphControls, new data::GraphDataVertex()),
			vertexId_(data::VertexIdType()),
			edgeList_(new structures::LinkedList<structures::GraphEdge*>())
		{}

		/// <summary> Destruktor. </summary>
		/// <remarks> Upratuje vsetky zdroje. </remarks>
		~ActionGraphVertex() override
		{
			this->!ActionGraphVertex();
		}

		/// <summary> Finalizer. </summary>
		/// <remarks> Upratuje nemanazovane zdroje. </remarks>
		!ActionGraphVertex()
		{
			delete edgeList_;
			edgeList_ = nullptr;
		}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			accessEditData() = data::GraphDataVertex();
			vertexId_ = data::VertexIdType();
			edgeList_->clear();

			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			ActionGraph::doFormat(memento);

			GraphVertexActionMemento* graphVertexMemento = dynamic_cast<GraphVertexActionMemento*>(memento);
			vertexId_ = graphVertexMemento->getVertexId();
			edgeList_->clear();
		}

	protected:
		/// <summary> Id vrcholu, s ktorym pracuje akcia. </summary>
		data::VertexIdType vertexId_;
		/// <summary> Zoznam doprednych/spatnych hran. </summary>
		structures::List<structures::GraphEdge*> *edgeList_;
	};


	/// <summary> Trieda predstavuje operaciu nad hranou grafu. </summary>
	ref class ActionGraphEdge abstract : public ActionGraph
	{
	public:
		/// <summary> Vytvori akciu nad hranou grafu. </summary>
		/// <param name = "id"> ID akcie. </param>
		/// <param name = "caption"> Popis akcie. </param>
		/// <param name = "supportsUndo"> Priznak, ci moze byt akcia zvratena. </param>
		/// <param name = "supportsRedo"> Priznak, ci moze byt akcia zopakovana. </param>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphEdge(int id, String^ caption, bool supportsUndo, bool supportsRedo, ControlsHolder^ graphControls) :
			ActionGraph(id, caption, supportsUndo, supportsRedo, graphControls, new data::GraphDataEdge()),
			beginVertexId_(data::VertexIdType()),
			endVertexId_(data::VertexIdType())
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			accessEditData() = data::GraphDataEdge();
			beginVertexId_ = data::VertexIdType();
			endVertexId_ = data::VertexIdType();

			return true;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			ActionGraph::doFormat(memento);

			GraphEdgeActionMemento* graphMemento = dynamic_cast<GraphEdgeActionMemento*>(memento);
			beginVertexId_ = graphMemento->getBeginVertexId();
			endVertexId_ = graphMemento->getEndVertexId();
		}

	protected:
		/// <summary> Id pociatocneho vrcholu hrany, s ktorou pracuje akcia. </summary>
		data::VertexIdType beginVertexId_;
		/// <summary> Id koncoveho vrcholu hrany, s ktorou pracuje akcia. </summary>
		data::VertexIdType endVertexId_;
	};

	/// <summary> Trieda predstavuje akciu vytvor v grafe vrchol s danym id. </summary>
	ref class ActionGraphCreateVertex : public ActionGraphVertex
	{
	public:
		/// <summary> Vytvori akciu vytvor v grafe vrchol s danym id. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphCreateVertex(ControlsHolder^ graphControls) :
			ActionGraphVertex(idaGraphCREATE_VERTEX, "Create vertex", true, true, graphControls)
		{}

	protected:
		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionGraphVertex::doFormat() &&
				data::DataRoutines::editVertexIdManaged(vertexId_, "Vertex id");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::VertexIdType vertexIdToInsert = vertexId_;
			data::GraphDataVertex dataToInsert = dynamic_cast<data::GraphDataVertex&>(accessEditData());

			structures::GraphVertex * vertex = GraphControls->Graph->createVertex(vertexIdToInsert);
			vertex->setData(dataToInsert);

			GraphVertexActionMemento* result = new GraphVertexActionMemento(ID);
			result->setVertexId(vertexIdToInsert);
			result->setDataBefore(dataToInsert);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			GraphVertexActionMemento* graphMemento = dynamic_cast<GraphVertexActionMemento*>(memento);
			GraphControls->Graph->removeVertex(graphMemento->getVertexId());
		}
	};

	/// <summary> Trieda predstavuje akciu uprav data vrchola s danym id. </summary>
	ref class ActionGraphEditVertexData : public ActionGraphVertex
	{
	public:
		/// <summary> Vytvori akciu uprav data vrchola s danym id. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphEditVertexData(ControlsHolder^ graphControls) :
			ActionGraphVertex(idaGraphEDIT_VERTEX_DATA, "Edit vertex data", true, true, graphControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (ActionGraphVertex::doFormat() &&
				(GraphControls->GraphPanel->tryGetSelectedVertexId(vertexId_) ||
					data::DataRoutines::editVertexIdManaged(vertexId_, "Edit vertex with id")))
			{
				accessEditData() = GraphControls->Graph->getVertex(vertexId_)->accessData(data::GraphDataVertex::getKey());

				return dynamic_cast<data::GraphDataVertex&>(accessEditData()).edit();
			}
			else
			{
				return false;
			}
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::GraphVertex * vertex = GraphControls->Graph->getVertex(vertexId_);
			data::GraphDataVertex dataBefore = dynamic_cast<data::GraphDataVertex&>(vertex->accessData(data::GraphDataVertex::getKey()));
			vertex->setData(accessEditData());
			data::GraphDataVertex dataAfter = dynamic_cast<data::GraphDataVertex&>(accessEditData());

			GraphVertexActionMemento* result = new GraphVertexActionMemento(ID);
			result->setVertexId(vertexId_);
			result->setDataBefore(dataBefore);
			result->setDataAfter(dataAfter);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			GraphVertexActionMemento* graphMemento = dynamic_cast<GraphVertexActionMemento*>(memento);
			GraphControls->Graph->getVertex(graphMemento->getVertexId())->setData(graphMemento->getDataBefore());
		}
	};

	/// <summary> Trieda predstavuje akciu odstran z grafu vrchol s danym id. </summary>
	ref class ActionGraphRemoveVertex : public ActionGraphVertex
	{
	public:
		/// <summary> Vytvori akciu odstran z grafu vrchol s danym id. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphRemoveVertex(ControlsHolder^ graphControls) :
			ActionGraphVertex(idaGraphREMOVE_VERTEX, "Remove vertex", false, true, graphControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionGraphVertex::doFormat() &&
				(GraphControls->GraphPanel->tryGetSelectedVertexId(vertexId_) ||
					data::DataRoutines::editVertexIdManaged(vertexId_, "Remove vertex with id"));
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			GraphVertexActionMemento* graphMemento = dynamic_cast<GraphVertexActionMemento*>(memento);
			vertexId_ = graphMemento->getVertexId();
			accessEditData() = graphMemento->getDataAfter();
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::GraphVertex* vertex = GraphControls->Graph->getVertex(vertexId_);
			accessEditData() = vertex->accessData(data::GraphDataVertex::getKey());
			GraphControls->Graph->removeVertex(vertex);

			GraphVertexActionMemento* result = new GraphVertexActionMemento(ID);
			result->setVertexId(vertexId_);
			result->setDataAfter(accessEditData());
			return result;
		}
	};

	/// <summary> Trieda predstavuje akciu daj nasledovnikov vrchola s danym id. </summary>
	ref class ActionGraphGetSuccessors : public ActionGraphVertex
	{
	public:
		/// <summary> Vytvori akciu daj nasledovnikov vrchola s danym id. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphGetSuccessors(ControlsHolder^ graphControls) :
			ActionGraphVertex(idaGraphGET_SUCCESSORS, "Vertex successors", false, true, graphControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionGraphVertex::doFormat() &&
					(GraphControls->GraphPanel->tryGetSelectedVertexId(vertexId_) ||
						data::DataRoutines::editVertexIdManaged(vertexId_, "Get successors of vertex with id"));
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			GraphControls->Graph->getSuccessors(vertexId_, *edgeList_);
			for (structures::GraphEdge* edge : *edgeList_)
			{
				dynamic_cast<data::GraphDataEdge&>(edge->accessData(data::GraphDataEdge::getKey())).selected() = true;
			}

			GraphVertexActionMemento* result = new GraphVertexActionMemento(ID);
			result->setVertexId(vertexId_);

			return result;
		}
	};

	/// <summary> Trieda predstavuje akciu daj predchodcov vrchola s danym id. </summary>
	ref class ActionGraphGetPredecessors : public ActionGraphVertex
	{
	public:
		/// <summary> Vytvori akciu daj predchodcov vrchola s danym id. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphGetPredecessors(ControlsHolder^ graphControls) :
			ActionGraphVertex(idaGraphGET_PREDECESSORS, "Vertex predecessors", false, true, graphControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionGraphVertex::doFormat() &&
				(GraphControls->GraphPanel->tryGetSelectedVertexId(vertexId_) ||
					data::DataRoutines::editVertexIdManaged(vertexId_, "Get predecessors of vertex with id"));
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			GraphControls->Graph->getPredecessors(vertexId_, *edgeList_);
			for (structures::GraphEdge* edge : *edgeList_)
			{
				dynamic_cast<data::GraphDataEdge&>(edge->accessData(data::GraphDataEdge::getKey())).selected() = true;
			}

			GraphVertexActionMemento* result = new GraphVertexActionMemento(ID);
			result->setVertexId(vertexId_);

			return result;
		}
	};


	/// <summary> Trieda predstavuje akciu vytvor hranu medzi danymi vrcholmi grafu. </summary>
	ref class ActionGraphCreateEdge : public ActionGraphEdge
	{
	public:
		/// <summary> Vytvori akciu vytvor hranu medzi danymi vrcholmi grafu. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphCreateEdge(ControlsHolder^ graphControls) :
			ActionGraphEdge(idaGraphCREATE_EDGE, "Create edge", true, true, graphControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			return ActionGraphEdge::doFormat() &&
				data::DataRoutines::editVertexIdManaged(beginVertexId_, "Begin vertex id") &&
				data::DataRoutines::editVertexIdManaged(endVertexId_, "End vertex id");
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			data::VertexIdType beginVertexId = beginVertexId_;
			data::VertexIdType endVertexId = endVertexId_;
			data::GraphDataEdge dataToInsert = dynamic_cast<data::GraphDataEdge&>(accessEditData());

			structures::GraphEdge * edge = GraphControls->Graph->createEdge(beginVertexId, endVertexId);
			edge->setData(dataToInsert);

			GraphEdgeActionMemento* result = new GraphEdgeActionMemento(ID);
			result->setBeginVertexId(beginVertexId);
			result->setEndVertexId(endVertexId);
			result->setDataBefore(dataToInsert);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			GraphEdgeActionMemento* graphMemento = dynamic_cast<GraphEdgeActionMemento*>(memento);
			GraphControls->Graph->removeEdge(graphMemento->getBeginVertexId(), graphMemento->getEndVertexId());
		}
	};

	/// <summary> Trieda predstavuje akciu uprav data danej hrany. </summary>
	ref class ActionGraphEditEdgeData : public ActionGraphEdge
	{
	public:
		/// <summary> Vytvori akciu uprav data danej hrany. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphEditEdgeData(ControlsHolder^ graphControls) :
			ActionGraphEdge(idaGraphEDIT_EDGE_DATA, "Edit edge data", true, true, graphControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			data::VertexIdType tmpBeginVertexId = beginVertexId_;

			if (ActionGraphEdge::doFormat() &&
				(GraphControls->GraphPanel->tryGetSelectedEdgeBeginVertexId(tmpBeginVertexId) ||
					data::DataRoutines::editVertexIdManaged(tmpBeginVertexId, "Edit edge beginning in vertex with id")) &&
				(GraphControls->GraphPanel->tryGetSelectedEdgeEndVertexId(endVertexId_) ||
					data::DataRoutines::editVertexIdManaged(endVertexId_, "Edit edge ending in vertex with id")))
			{
				beginVertexId_ = tmpBeginVertexId;
				accessEditData() = GraphControls->Graph->getEdge(beginVertexId_, endVertexId_)->accessData(data::GraphDataEdge::getKey());

				return dynamic_cast<data::GraphDataEdge&>(accessEditData()).edit();
			}
			else
			{
				return false;
			}
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::GraphEdge * edge = GraphControls->Graph->getEdge(beginVertexId_, endVertexId_);
			data::GraphDataEdge dataBefore = dynamic_cast<data::GraphDataEdge&>(edge->accessData(data::GraphDataEdge::getKey()));
			edge->setData(accessEditData());
			data::GraphDataEdge dataAfter = dynamic_cast<data::GraphDataEdge&>(accessEditData());

			GraphEdgeActionMemento* result = new GraphEdgeActionMemento(ID);
			result->setBeginVertexId(beginVertexId_);
			result->setEndVertexId(endVertexId_);
			result->setDataBefore(dataBefore);
			result->setDataAfter(dataAfter);

			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			GraphEdgeActionMemento* graphMemento = dynamic_cast<GraphEdgeActionMemento*>(memento);
			GraphControls->Graph->getEdge(graphMemento->getBeginVertexId(), graphMemento->getEndVertexId())->setData(graphMemento->getDataBefore());
		}
	};

	/// <summary> Trieda predstavuje akciu odstran z grafu danu hranu. </summary>
	ref class ActionGraphRemoveEdge : public ActionGraphEdge
	{
	public:
		/// <summary> Vytvori akciu odstran z grafu danu hranu. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphRemoveEdge(ControlsHolder^ graphControls) :
			ActionGraphEdge(idaGraphREMOVE_EDGE, "Remove edge", true, true, graphControls)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			data::VertexIdType tmpBeginVertexId = beginVertexId_;
			bool result = ActionGraphEdge::doFormat() &&
							(GraphControls->GraphPanel->tryGetSelectedEdgeBeginVertexId(tmpBeginVertexId) ||
								data::DataRoutines::editVertexIdManaged(tmpBeginVertexId, "Remove edge beginning in vertex with id")) &&
							(GraphControls->GraphPanel->tryGetSelectedEdgeEndVertexId(endVertexId_) ||
								data::DataRoutines::editVertexIdManaged(endVertexId_, "Remove edge ending in vertex with id"));
			if (result)
			{
				beginVertexId_ = tmpBeginVertexId;
			}
			return result;
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			GraphEdgeActionMemento* graphMemento = dynamic_cast<GraphEdgeActionMemento*>(memento);
			beginVertexId_ = graphMemento->getBeginVertexId();
			endVertexId_ = graphMemento->getEndVertexId();
			accessEditData() = graphMemento->getDataAfter();
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			structures::GraphEdge* edge = GraphControls->Graph->getEdge(beginVertexId_, endVertexId_);
			accessEditData() = edge->accessData(data::GraphDataEdge::getKey());
			GraphControls->Graph->removeEdge(edge);

			GraphEdgeActionMemento* result = new GraphEdgeActionMemento(ID);
			result->setBeginVertexId(beginVertexId_);
			result->setEndVertexId(endVertexId_);
			result->setDataAfter(accessEditData());
			return result;
		}

		/// <summary> Zvrati akciu. </summary>
		/// <param name = "memento"> Memento povodnej akcie. </param>
		void doUndo(ActionMemento* memento) override
		{
			GraphEdgeActionMemento* graphMemento = dynamic_cast<GraphEdgeActionMemento*>(memento);
			structures::GraphEdge* edge =  GraphControls->Graph->createEdge(graphMemento->getBeginVertexId(), graphMemento->getEndVertexId());
			edge->accessData(data::GraphDataEdge::getKey()) = graphMemento->getDataAfter();
		}
	};


	/// <summary> Trieda predstavuje akciu vypocitaj minimalnu vzdialenost medzi danymi vrcholmi grafu Dijkstrovym algoritmom. </summary>
	ref class ActionGraphDijkstra : public ActionGraphEdge
	{
	public:
		/// <summary> Vytvori akciu vypocitaj minimalnu vzdialenost medzi danymi vrcholmi grafu Dijkstrovym algoritmom. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphDijkstra(ControlsHolder^ graphControls) :
			ActionGraphEdge(idaGraphDIJKSTRA, "Run Dijkstra", false, true, graphControls),
			dijkstra_(nullptr)
		{}

	protected:
		/// <summary> Vrati priznak, ci moze byt akcia povolena. </summary>
		/// <returns> Priznak, ci moze byt akcia povolena. </returns>
		bool canBeEnabled() override
		{
			return GraphControls->Graph != nullptr && !GraphControls->Graph->isEmpty();
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <returns> true, ak sa akciu podarilo naformatovat, false inak. </returns>
		bool doFormat() override
		{
			if (ActionGraphEdge::doFormat() &&
				data::DataRoutines::editVertexIdManaged(beginVertexId_, "Begin vertex id") &&
				data::DataRoutines::editVertexIdManaged(endVertexId_, "End vertex id"))
			{
				if (dijkstra_ != nullptr)
				{
					delete dijkstra_;
				}
				dijkstra_ = new structures::Dijkstra(GraphControls->Graph, data::GraphDataEdge::getKey());
				return true;
			}
			else
			{
				return false;
			}
		}

		/// <summary> Naformatuje akciu. </summary>
		/// <param name = "memento"> Memento, podla ktoreho sa naformatuje. </param>
		void doFormat(ActionMemento* memento) override
		{
			GraphEdgeActionMemento* graphMemento = dynamic_cast<GraphEdgeActionMemento*>(memento);
			beginVertexId_ = graphMemento->getBeginVertexId();
			endVertexId_ = graphMemento->getEndVertexId();

			if (dijkstra_ != nullptr)
			{
				delete dijkstra_;
			}
			dijkstra_ = new structures::Dijkstra(GraphControls->Graph, data::GraphDataEdge::getKey());
		}

		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			dijkstra_->tryCompute(beginVertexId_, endVertexId_);

			GraphEdgeActionMemento* result = new GraphEdgeActionMemento(ID);
			result->setBeginVertexId(beginVertexId_);
			result->setEndVertexId(endVertexId_);

			return result;
		}

		/// <summary> Prezentuje vysledok akcie uzivatelovi. </summary>
		void doPresentResult() override
		{
			structures::LinkedList<structures::GraphEdge*> edgeList;
			dijkstra_->getComputedPath(edgeList);
			std::string path = "";
			if (!edgeList.isEmpty())
			{
				path += std::to_string(edgeList[0]->getBeginVertex()->getId());
				for (structures::GraphEdge* edge : edgeList)
				{
					path += "->";
					path += std::to_string(edge->getEndVertex()->getId());
				}
			}
			data::DataRoutines::showNumber(dijkstra_->getComputedDistance(), "Minimal distance");
			data::DataRoutines::showString(path, "Shortest path");

			ActionGraphEdge::doPresentResult();

			if (dijkstra_ != nullptr)
			{
				delete dijkstra_;
				dijkstra_ = nullptr;
			}
		}

		/// <summary> Prezentuje vysledok akcie, ktora bola zopakovana, uzivatelovi. </summary>
		void doPresentRedoResult() override
		{
			doPresentResult();
		}
	private:
		/// <summary> Smernik na instanciu predstavujucu Dijkstrov algoritmus. </summary>
		structures::Dijkstra *dijkstra_;
	};



	/// <summary> Trieda predstavuje akciu vyprazdni graf. </summary>
	ref class ActionGraphClear : public ActionGraph
	{
	public:
		/// <summary> Vytvori akciu vyprazdni graf. </summary>
		/// <param name = "graphControls"> Ovladanie, do ktoreho patri. </param>
		ActionGraphClear(ControlsHolder^ graphControls) :
			ActionGraph(idaGraphCLEAR, "Clear", false, true, graphControls, nullptr)
		{}

	protected:
		/// <summary> Vykona akciu. </summary>
		/// <returns> Memento vykonanej akcie. </returns>
		ActionMemento* doExecute() override
		{
			GraphControls->Graph->clear();

			return new ActionMemento(ID);
		}
	};

	void ControlsGraph::createActions(Generic::List<Action^>^ actions)
	{
		actions->Add(gcnew ActionGraphCreateVertex(this));
		actions->Add(gcnew ActionGraphRemoveVertex(this));
		actions->Add(gcnew ActionGraphEditVertexData(this));
		actions->Add(gcnew ActionGraphGetSuccessors(this));
		actions->Add(gcnew ActionGraphGetPredecessors(this));

		actions->Add(gcnew ActionGraphCreateEdge(this));
		actions->Add(gcnew ActionGraphEditEdgeData(this));
		actions->Add(gcnew ActionGraphRemoveEdge(this));

		actions->Add(gcnew ActionGraphClear(this));
		actions->Add(gcnew ActionStructureSize(ActionGraph::idaGraphSIZE, this));
		actions->Add(gcnew ActionStructureIsEmpty(ActionGraph::idaGraphIS_EMPTY, this));

		actions->Add(gcnew ActionGraphDijkstra(this));
	}
}