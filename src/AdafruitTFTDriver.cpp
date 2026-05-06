#include <AdafruitTFTDriver.h>
#include <stdint.h>

// Instantiate Adafruit driver using hardware SPI.
AdafruitTFTDriver::AdafruitTFTDriver(int csPin, int dcPin)
		: m_gfx{
				static_cast<int8_t>(csPin), static_cast<int8_t>(dcPin), /*rst=*/-1
			} {}

void AdafruitTFTDriver::initialize() {
	m_gfx.initR(DISPLAY_REVISION);
	m_gfx.setTextSize(TEXT_SCALE);
	m_gfx.setRotation(SCREEN_ORIENTATION);
}

unsigned AdafruitTFTDriver::getScreenWidth() const {
	return m_gfx.width();
}

unsigned AdafruitTFTDriver::getScreenHeight() const {
	return m_gfx.height();
}

unsigned AdafruitTFTDriver::getTextWidth() const {
	return TEXT_SCALE * DEFAULT_TEXT_WIDTH;
}

unsigned AdafruitTFTDriver::getTextHeight() const {
	return TEXT_SCALE * DEFAULT_TEXT_HEIGHT;
}

void AdafruitTFTDriver::clearScreen(TFTColor color) {
	m_gfx.fillScreen(encodeColor(color));
}

void AdafruitTFTDriver::drawText(
	TFTPoint topLeft, TFTColor textColor, TFTColor bgColor, const char *string
) {
	m_gfx.setCursor(
		static_cast<int16_t>(topLeft.x), static_cast<int16_t>(topLeft.y)
	);
	m_gfx.setTextColor(encodeColor(textColor), encodeColor(bgColor));
	m_gfx.print(string);
}

AdafruitTFTDriver::Color565 AdafruitTFTDriver::encodeColor(TFTColor color) {
	switch (color) {
	case TFTColor::Black:
		return 0;
	case TFTColor::White:
		return UINT16_MAX;
	default:
		// There are no other colors.
		__builtin_unreachable();
	}
}
