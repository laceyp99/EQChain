#pragma once

#include <JuceHeader.h>

namespace juce
{
	class FilmStripSlider
	{
	public:
		FilmStripSlider(Image* _knobStrip);
		void drawFrame(Graphics& g, int x, int y, int width, int height, Slider& slider);

	private:
		Image* knobStrip;
		int frameCount;
		int frameSize;
		bool isVerticalStrip;
	};
}
