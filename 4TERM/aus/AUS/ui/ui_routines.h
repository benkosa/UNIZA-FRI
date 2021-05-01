#pragma once

#include "../structures/ds_structure_types.h"
#include "../structures/structure.h"
#include "../data/data_types.h"
#include <string>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace ui {

	/// <summary> 
	/// Kniznicna trieda obsahujuca rutinne metody pre pracu s rozhranim.
	/// </summary>
	class UIRoutines
	{
	public:
		static void layoutControlToCenter(Control^ control, Drawing::Rectangle^ rect, int offsetLeft, int offsetTop);
		static void layoutControlFillRect(Control^ control,	Drawing::Rectangle^ rect, int offsetLeft, int offsetTop);

		static std::string convertStructureADTToStr(const structures::StructureADT adt);
		static std::string convertStructureADSToStr(const structures::StructureADS ads);
		static std::string convertIntToStr(int i);
		static std::string convertStringtoStr(String^ str);

		static String^ convertMemoryToString(const void* ptr, const int bytes);

		static Color createRGBColor(int r, int g, int b);

		static void showMessage(String^ caption, String^ message);
		static bool confirmDialog(String^ caption, String^ message);
	private:
		/// <summary> Sukromny konstruktor znemoznuje vytvorenie instancie kniznicnej triedy. </summary>
		UIRoutines();
	};

}