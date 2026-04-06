/**
 * @file TFTDisplay.h
 */

#ifndef TFT_DISPLAY_H
#define TFT_DISPLAY_H

#include <IDisplay.h>
#include <TFT.h>
#include <TFTDriver.h>

class TFTDisplay : public IDisplay {
public:
	explicit TFTDisplay(TFTDriver &driver);

	void initialize() final;
	void update(float channel1Power, float channel2Power) final;

private:
	static constexpr TFTColor CLEAR_COLOR{TFTColor::Black};
	static constexpr TFTColor TEXT_COLOR{TFTColor::White};

	struct Layout {
		TFTPoint wire1Text;
		TFTPoint wire2Text;
	};

	void determineLayout();

	TFTDriver &m_driver;
	char m_text_staging[128];
	Layout m_layout;
};

#endif // TFT_DISPLAY_H
