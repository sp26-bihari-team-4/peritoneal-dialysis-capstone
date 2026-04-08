/**
 * @file TFTDriver.h
 */

#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H

#include <TFT.h>

/**
 * A low-level interface to a TFT display.
 */
class TFTDriver {
public:
	/**
	 * Initializes the display.
	 *
	 * The display must be initialized before any other functions are called.
	 */
	virtual void initialize() = 0;

	/**
	 * Returns the width, in pixels, of the screen.
	 */
	[[nodiscard]] virtual unsigned getScreenWidth() const = 0;

	/**
	 * Returns the height, in pixels, of the screen.
	 */
	[[nodiscard]] virtual unsigned getScreenHeight() const = 0;

	/**
	 * Returns the width, in pixels, of one character.
	 */
	[[nodiscard]] virtual unsigned getTextWidth() const = 0;

	/**
	 * Returns the height, in pixels, of one character.
	 */
	[[nodiscard]] virtual unsigned getTextHeight() const = 0;

	/**
	 * Assigns one color to all pixels on the screen, clearing any previously
	 * drawn text.
	 *
	 * @param color The color to assign.
	 */
	virtual void clearScreen(TFTColor color) = 0;

	/**
	 * Draws monospace text.
	 *
	 * If the text goes off the right edge of the screen, it is wrapped to the
	 * next line.
	 *
	 * @param topLeft The top-left position of the first character.
	 * @param color The text color.
	 * @param string The NUL-terminated ASCII string to draw.
	 */
	virtual void
	drawText(TFTPoint topLeft, TFTColor color, const char *string) = 0;
};

#endif // TFT_DRIVER_H
