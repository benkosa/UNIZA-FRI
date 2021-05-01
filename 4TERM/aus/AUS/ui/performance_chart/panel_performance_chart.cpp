#include "panel_performance_chart.h"
#include "performance.h"
#include "../ui_routines.h"
#include <vector>

namespace ui
{

	PanelPerformanceChart::PanelPerformanceChart(void):
		colors_(gcnew array<Color^>(12)),
		structure_(nullptr)
	{
		InitializeComponent();

		colors_[0] = UIRoutines::createRGBColor(0xCC, 0x00, 0x00);
		colors_[1] = UIRoutines::createRGBColor(0xCC, 0x00, 0x33);
		colors_[2] = UIRoutines::createRGBColor(0xCC, 0x00, 0x66);
		colors_[3] = UIRoutines::createRGBColor(0xCC, 0x00, 0x99);
		colors_[4] = UIRoutines::createRGBColor(0xCC, 0x00, 0xCC);
		colors_[5] = UIRoutines::createRGBColor(0xCC, 0x00, 0xFF);
		
		colors_[6] = UIRoutines::createRGBColor(0xFF, 0x00, 0x00);
		colors_[7] = UIRoutines::createRGBColor(0xFF, 0x00, 0xCC);
		colors_[8] = UIRoutines::createRGBColor(0xFF, 0x00, 0x99);
		colors_[9] = UIRoutines::createRGBColor(0xFF, 0x00, 0x66);
		colors_[10] = UIRoutines::createRGBColor(0xFF, 0x00, 0x33);
		colors_[11] = UIRoutines::createRGBColor(0xFF, 0x00, 0x00);
	}

	void PanelPerformanceChart::presentStructure(structures::Structure * structure, structures::StructureADT adt)
	{
		chartPerformance->Series->Clear();

		StructurePerformanceHolder* operations = dynamic_cast<StructurePerformanceHolder*>(StructuresPerformanceHolder::getInstance()->getStructureInfoHolder(structure));

		if (operations != nullptr)
		{
			StructurePerformanceHolder::InfoMap* infoMap = operations->getStructureInfoMap();

			for (StructurePerformanceHolder::InfoMapPair infoMapPair : *infoMap)
			{
				std::string caption = StructuresPerformanceHolder::getInstance()->infoCaption(adt, infoMapPair.second->getID());

				Series^ series = getSeries(adt, infoMapPair.second->getID(), gcnew String(caption.c_str()));

				for (StructureInfo* structureInfo : *infoMapPair.second->getInfoVector())
				{
					PerformanceInfo* performanceInfo = dynamic_cast<PerformanceInfo*>(structureInfo);
					series->Points->AddXY(static_cast<int>(performanceInfo->getSize()), performanceInfo->complexity());
				}
			}

			structure_ = structure;
		}
	}

	void PanelPerformanceChart::actionPerformed(PerformanceInfo* performanceInfo)
	{
		presentStructure(performanceInfo->getStructure(), performanceInfo->getADT());
	}

	PanelPerformanceChart::~PanelPerformanceChart()
	{
		if (components)
		{
			delete components;
		}
	}

	Series ^ PanelPerformanceChart::getSeries(structures::StructureADT adt, int operationID, String^ caption)
	{
		Series^ result = gcnew Series();

		result->Name = caption;
		result->Color = Color(colors_[operationID % 12]);
		result->IsVisibleInLegend = true;
		result->IsXValueIndexed = true;
		result->ChartType = adt == structures::StructureADT::adtVECTOR || adt == structures::StructureADT::adtARRAY ? SeriesChartType::FastPoint : SeriesChartType::FastLine;

		chartPerformance->Series->Add(result);

		return result;
	}

}
