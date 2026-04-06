/**
 * @file TFTDisplay.h
 */

#ifndef TFT_DISPLAY_H
#define TFT_DISPLAY_H

#include <IDisplay.h>
#include <TFT.h>
#include <TFTDriver.h>

/**
 * An @ref IDisplay implementation for TFT color displays.
 */
class TFTDisplay : public IDisplay {
public:
	/**
	 * Creates a TFT display for a specific TFT driver.
	 *
	 * @param driver The underlying driver.
	 */
	explicit TFTDisplay(TFTDriver &driver);

	void initialize() override;
	void update(float channel1Power, float channel2Power) override;

private:
	/**
	 * The color used for clearing the screen.
	 */
	static constexpr TFTColor CLEAR_COLOR{TFTColor::Black};

	/**
	 * The default color for drawing text.
	 */
	static constexpr TFTColor TEXT_COLOR{TFTColor::White};

	/**
	 * The positions of UI elements.
	 */
	struct Layout {
		TFTPoint wire1Text; /**< The top-left of the first line of text. */
		TFTPoint wire2Text; /**< The top-left of the second line of text. */
	};

	/**
	 * Pre-computes the positions of UI elements.
	 */
	void determineLayout();

	TFTDriver &m_driver;
	char m_text_staging[128];
	Layout m_layout;
};

#endif // TFT_DISPLAY_H
