#include "graph_data.h"


#pragma region GraphDataVertex

const data::GraphDataVertex data::GraphDataVertex::classKey_;

data::GraphDataVertex * data::GraphDataVertex::getData(structures::GraphVertex * vertex)
{
	return dynamic_cast<GraphDataVertex*>(&vertex->accessData(&classKey_));
}

const data::GraphDataVertex * data::GraphDataVertex::getKey()
{
	return &classKey_;
}

data::GraphDataVertex::GraphDataVertex() :
	GraphData(),
	label_("")
{
}

data::GraphDataVertex::GraphDataVertex(const GraphDataVertex & other) :
	GraphData(other),
	label_(other.label_)
{
}

structures::GraphData & data::GraphDataVertex::operator=(const GraphData & other)
{
	return *this = dynamic_cast<const GraphDataVertex&>(other);
}

structures::GraphData * data::GraphDataVertex::clone() const
{ 
	return new GraphDataVertex(*this); 
}

const structures::GraphData * data::GraphDataVertex::getClassKey() const
{
	return &classKey_;
}

data::GraphDataVertex & data::GraphDataVertex::operator=(const GraphDataVertex & other)
{
	if (this != &other)
	{
		label_ = other.label_;
	}
	return *this;
}

void data::GraphDataVertex::reset()
{ 
	label_.clear();
}

bool data::GraphDataVertex::edit()
{ 
	return data::DataRoutines::editString(label_, "Edit vertex data"); 
}

System::String ^ data::GraphDataVertex::toString() const
{
	return gcnew System::String(label_.c_str()); 
}

#pragma endregion


#pragma region GraphDataEdge

const data::GraphDataEdge data::GraphDataEdge::classKey_;

data::GraphDataEdge * data::GraphDataEdge::getData(structures::GraphEdge * edge)
{
	return dynamic_cast<GraphDataEdge*>(&edge->accessData(&classKey_));
}

const data::GraphDataEdge * data::GraphDataEdge::getKey()
{
	return &classKey_;
}

data::GraphDataEdge::GraphDataEdge() :
	GraphDataLength(),
	selected_(false)
{
}

data::GraphDataEdge::GraphDataEdge(const GraphDataEdge & other) :
	GraphDataLength(other),
	selected_(other.selected_)
{
}

structures::GraphDataLength & data::GraphDataEdge::operator=(const GraphDataLength & other)
{
	return *this = dynamic_cast<const GraphDataEdge&>(other);
}

structures::GraphData * data::GraphDataEdge::clone() const
{ 
	return new GraphDataEdge(*this); 
}

const structures::GraphData * data::GraphDataEdge::getClassKey() const
{
	return &classKey_;
}

data::GraphDataEdge & data::GraphDataEdge::operator=(const GraphDataEdge & other)
{
	if (this != &other)
	{
		GraphDataLength::operator=(other);

		selected_ = other.selected_;
	}
	return *this;
}

void data::GraphDataEdge::reset()
{ 
	setLength(0); 
}

bool data::GraphDataEdge::edit()
{
	double length = getLength();
	if (data::DataRoutines::editNumber(length, "Edit edge length"))
	{
		setLength(length);
		return true;
	}
	return false;
}

bool & data::GraphDataEdge::selected() 
{ 
	return selected_; 
}

bool data::GraphDataEdge::selected() const
{
	return selected_; 
}

System::String ^ data::GraphDataEdge::toString() const
{ 
	return gcnew System::String(Convert::ToString(getLength()));
}

#pragma endregion