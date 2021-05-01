#include "color_scheme.h"
#include "ui_routines.h"
#include <math.h>

namespace ui
{

	Color ^ ColorScheme::getColor(double value, double minValue, double maxValue)
	{
		if (value <= minValue)
		{
			return colorBounds_[0];
		}

		if (value >= maxValue)
		{
			return colorBounds_[colorBounds_->Length - 1];
		}

		double intervalLength = (maxValue - minValue) / static_cast<double>(colorBounds_->Length - 1);
		double intervalFrac = (value - minValue) / intervalLength;

		double interval;
		double position;

		position = modf(intervalFrac, &interval);

		Color^ colorA = colorBounds_[static_cast<int>(interval)];
		Color^ colorB = colorBounds_[static_cast<int>(interval + 1)];

		int r = static_cast<int>(colorA->R + round((colorB->R - colorA->R) * position));
		int g = static_cast<int>(colorA->G + round((colorB->G - colorA->G) * position));
		int b = static_cast<int>(colorA->B + round((colorB->B - colorA->B) * position));

		return UIRoutines::createRGBColor(r, g, b);
	}

	ColorScheme::ColorScheme(int colorBoundsCount) :
		colorBounds_(gcnew array<Color^>(colorBoundsCount))
	{
		for (int i = 0; i < colorBoundsCount; i++)
		{
			setColorBoundary(i, 0, 0, 0);
		}
	}

	void ColorScheme::setColorBoundary(int index, int R, int G, int B)
	{
		colorBounds_[index] = UIRoutines::createRGBColor(R, G, B);
	}

	ColorSchemeJet ^ ColorSchemeJet::getInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = gcnew ColorSchemeJet();
		}

		return instance_;
	}

	ColorSchemeJet::ColorSchemeJet() :
		ColorScheme(5)
	{
		setColorBoundary(0, 0,   0,   255);
		setColorBoundary(1, 0,   255, 255);
		setColorBoundary(2, 0,   255, 0);
		setColorBoundary(3, 255, 255, 0);
		setColorBoundary(4, 255, 0,   0);
	}

}