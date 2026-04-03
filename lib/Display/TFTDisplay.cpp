#include <TFTDisplay.h>
#include <math.h>
#include <stdio.h>

void TFTDisplay::initialize() {
	initializeDriver();
	determineLayout();
	clearScreen(CLEAR_COLOR);
}

void TFTDisplay::determineLayout() {
	// Wire 1 text will be on the first line
	m_layout.wire1Text.x = 0;
	m_layout.wire1Text.y = 0;

	// Wire 2 text will be on the second line
	m_layout.wire2Text.x = 0;
	m_layout.wire2Text.y = getTextHeight();
}

void TFTDisplay::update(float channel1Power, float channel2Power) {
	snprintf(
		m_text_staging, sizeof(m_text_staging), "Wire 1 Power Level: %d%%",
		static_cast<int>(round(channel1Power * 100.f))
	);
	drawText(m_layout.wire1Text, TEXT_COLOR, m_text_staging);

	snprintf(
		m_text_staging, sizeof(m_text_staging), "Wire 2 Power Level: %d%%",
		static_cast<int>(round(channel2Power * 100.f))
	);
	drawText(m_layout.wire2Text, TEXT_COLOR, m_text_staging);
}
