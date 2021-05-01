#include "panel_controls.h"

namespace ui{

	PanelControls::PanelControls(void):
		panelPresent_(nullptr),
		panelPerformance_(gcnew PanelPerformanceChart()),
		panelActionHistory_(gcnew PanelActionHistory())
	{
		InitializeComponent();

		pnlPerformance->Controls->Add(panelPerformance_);
		panelPerformance_->Dock = DockStyle::Fill;

		pnlHistory->Controls->Add(panelActionHistory_);
		panelActionHistory_->Dock = DockStyle::Fill;
	}

	void PanelControls::showPresentPanel(bool value)
	{
		lblNoVisualization->Visible = !value;
		if (panelPresent_ != nullptr)
		{
			panelPresent_->Visible = value;
		}
	}

	inline PanelControls::~PanelControls()
	{
		if (components)
		{
			delete components;
		}
	}

}