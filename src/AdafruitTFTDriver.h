/**
 * @file AdafruitTFTDriver.h
 */

#ifndef ADAFRUIT_TFT_DRIVER_H
#define ADAFRUIT_TFT_DRIVER_H

#include <Adafruit_ST7735.h>
#include <TFTDriver.h>
#include <stdint.h>

class AdafruitTFTDriver : public TFTDriver {
public:
	AdafruitTFTDriver(int csPin, int dcPin);

	void initialize() override;
	[[nodiscard]] unsigned getScreenWidth() const override;
	[[nodiscard]] unsigned getScreenHeight() const override;
	[[nodiscard]] unsigned getTextWidth() const override;
	[[nodiscard]] unsigned getTextHeight() const override;
	void clearScreen(TFTColor color) override;
	void drawText(
		TFTPoint topLeft, TFTColor textColor, TFTColor bgColor, const char *string
	) override;

private:
	// The display accepts 16-bit colors in the 565 format (5 bits red, 6 bits
	// green, 5 bits blue).
	using Color565 = uint16_t;

	// <https://learn.adafruit.com/adafruit-mini-tft-0-dot-96-inch-180x60-breakout/wiring-test>
	static constexpr uint8_t DISPLAY_REVISION{INITR_MINI160x80_PLUGIN};

	// The magnification level for text.
	static constexpr unsigned TEXT_SCALE{2};

	// The value used for the Adafruit GFX 'setRotation' call. By default, the
	// display uses a portrait oritentation. A value of 1 corresponds to a
	// landscape orientation.
	static constexpr unsigned SCREEN_ORIENTATION{1};

	// According to
	// <https://adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x.html#a39eb4a8a2c9fa4ab7d58ceffd19535d5>,
	// the default text size is 6x8.
	static constexpr unsigned DEFAULT_TEXT_WIDTH{6};
	static constexpr unsigned DEFAULT_TEXT_HEIGHT{8};

	/**
	 * Converts an abstract color to the representation used by the Adafruit
	 * ST7735 library.
	 */
	static Color565 encodeColor(TFTColor color);

	Adafruit_ST7735 m_gfx;
};

#endif // ADAFRUIT_TFT_DRIVER_H
