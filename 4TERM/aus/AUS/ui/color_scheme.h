#pragma once

using namespace System::Drawing;

namespace ui
{

	public ref class ColorScheme abstract
	{
	public:
		Color^ getColor(double value, double minValue, double maxValue);
	protected:
		ColorScheme(int colorBoundsCount);

		void setColorBoundary(int index, int R, int G, int B);
	private:
		array<Color^>^ colorBounds_;
	};

	public ref class ColorSchemeJet : public ColorScheme
	{
	public:
		static ColorSchemeJet^ getInstance();
	protected:
		ColorSchemeJet();
	private:
		static ColorSchemeJet^ instance_ = nullptr;
	};

}