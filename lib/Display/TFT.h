/**
 * @file TFT.h
 */

#ifndef TFT_H
#define TFT_H

/**
 * A color used for drawing on a TFT display.
 *
 * In general, these colors do not correspond to specific RGB values. The TFT
 * driver decides what they translate to.
 */
enum class TFTColor {
	Black,
	White,
};

/**
 * The position of a pixel on a TFT display, given in Cartesian coordinates.
 *
 * The coordinates are non-negative integers. The top-left of the screen is the
 * origin, and the bottom-right is <tt>(W,H)</tt> where @c W and @c H are the
 * width and height of the screen given by @ref TFTDriver::getScreenWidth and
 * @ref TFTDriver::getScreenHeight, respectively.
 */
struct TFTPoint {
	unsigned x;
	unsigned y;

	bool operator==(const TFTPoint &other) const {
		return (x == other.x) && (y == other.y);
	}
};

#endif // TFT_H
