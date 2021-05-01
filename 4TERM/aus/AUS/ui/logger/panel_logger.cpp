#include "panel_logger.h"
#include "ui_logger.h"

using namespace System;
using namespace System::Windows::Forms;

namespace ui {

	PanelLogger::PanelLogger(void)
	{
		InitializeComponent();

		imagesLog->Images->Add(gcnew Bitmap("images/error.png"));
		imagesLog->Images->Add(gcnew Bitmap("images/warning.png"));
		imagesLog->Images->Add(gcnew Bitmap("images/hint.png"));
		imagesLog->Images->Add(gcnew Bitmap("images/debug.png"));

		log::Logger::getInstance()->registerProvider(this);
	}

	PanelLogger ^ PanelLogger::createAndIntegrateLogger(Panel^ owner)
	{
		PanelLogger ^ result = gcnew PanelLogger();
		owner->Controls->Add(result);
		result->Dock = DockStyle::Fill;
		return result;
	}

	void PanelLogger::log(log::LogType lt, System::String ^ message)
	{
		ListViewItem^ item = gcnew ListViewItem(convertLogTypeToString(lt), convertLogTypeToImageIndex(lt));
		lviewLogger->Items->Insert(0, item);
		item->SubItems->Add(message);
		item->Selected = true;
		item->Focused = true;
	}

	PanelLogger::~PanelLogger()
	{
		log::Logger::getInstance()->unregisterProvider(this);

		if (components)
		{
			delete components;
		}
	}

	String^ PanelLogger::convertLogTypeToString(const log::LogType lt)
	{
		switch (lt)
		{
			case log::LogType::ltERROR:
				return "Error";
			case log::LogType::ltWARNING:
				return "Warning";
			case log::LogType::ltHINT:
				return "Hint";
			case log::LogType::ltWAIT:
				return "Wait";
			case log::LogType::ltDEBUG:
				return "Debug";
			default:
				return "Unknown";
		}
	}

	int PanelLogger::convertLogTypeToImageIndex(const log::LogType lt)
	{
		switch (lt)
		{
			case log::LogType::ltERROR:
				return LOG_IMAGE_ERROR;
			case log::LogType::ltWARNING:
				return LOG_IMAGE_WARNING;
			case log::LogType::ltHINT:
				return LOG_IMAGE_HINT;
			case log::LogType::ltWAIT:
				return LOG_IMAGE_WAIT;
			case log::LogType::ltDEBUG:
				return LOG_IMAGE_DEBUG;
			default:
				return LOG_IMAGE_NONE;
		}
	}

}
