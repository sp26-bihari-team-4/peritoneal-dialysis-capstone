/**
 * @file AdafruitDisplay.h
 */

#ifndef ADAFRUIT_DISPLAY_H
#define ADAFRUIT_DISPLAY_H

#include <Adafruit_ST7735.h>
#include <TFTDisplay.h>
#include <stdint.h>

class AdafruitDisplay : public TFTDisplay {
public:
	AdafruitDisplay(int csPin, int dcPin);

protected:
	void initializeDriver() override;
	[[nodiscard]] unsigned getWidth() const override;
	[[nodiscard]] unsigned getHeight() const override;
	[[nodiscard]] unsigned getTextWidth() const override;
	[[nodiscard]] unsigned getTextHeight() const override;
	void clearScreen(Color color) override;
	void drawText(Point topLeft, Color color, const char *string) override;

private:
	// The display accepts 16-bit colors in the 565 format (5 bits red, 6 bits
	// blue, 5 bits green).
	using Color565 = uint16_t;

	// According to
	// <https://adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x.html#a39eb4a8a2c9fa4ab7d58ceffd19535d5>,
	// the default text size is 6x8.
	static constexpr unsigned DEFAULT_TEXT_WIDTH{6};
	static constexpr unsigned DEFAULT_TEXT_HEIGHT{8};

	/**
	 * Converts an abstract color to the representation used by the Adafruit
	 * ST7735 library.
	 */
	static Color565 encodeColor(Color color);

	Adafruit_ST7735 m_driver;
};

#endif // ADAFRUIT_DISPLAY_H
