/**
 * @file TFTDisplay.h
 */

#ifndef TFT_DISPLAY_H
#define TFT_DISPLAY_H

#include <IDisplay.h>

class TFTDisplay : public IDisplay {
public:
	void initialize() final;
	void update(float channel1Power, float channel2Power) final;

protected:
	enum class Color {
		Black,
		White,
	};

	struct Point {
		unsigned x;
		unsigned y;
	};

	virtual void initializeDriver() = 0;
	[[nodiscard]] virtual unsigned getWidth() const = 0;
	[[nodiscard]] virtual unsigned getHeight() const = 0;
	[[nodiscard]] virtual unsigned getTextWidth() const = 0;
	[[nodiscard]] virtual unsigned getTextHeight() const = 0;
	virtual void clearScreen(Color color) = 0;
	virtual void drawText(Point topLeft, Color color, const char *string) = 0;

private:
	static constexpr Color CLEAR_COLOR{Color::Black};
	static constexpr Color TEXT_COLOR{Color::White};

	struct Layout {
		Point wire1Text;
		Point wire2Text;
	};

	void determineLayout();

	char m_text_staging[128];
	Layout m_layout;
};

#endif // TFT_DISPLAY_H
