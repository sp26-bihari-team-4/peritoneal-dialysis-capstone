/**
 * @file TFTDriver.h
 */

#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

#include <TFT.h>

class TFTDriver {
public:
	virtual void initialize() = 0;
	[[nodiscard]] virtual unsigned getScreenWidth() const = 0;
	[[nodiscard]] virtual unsigned getScreenHeight() const = 0;
	[[nodiscard]] virtual unsigned getTextWidth() const = 0;
	[[nodiscard]] virtual unsigned getTextHeight() const = 0;
	virtual void clearScreen(TFTColor color) = 0;

	virtual void
	drawText(TFTPoint topLeft, TFTColor color, const char *string) = 0;
};

#endif // TFT_DRIVER_H
