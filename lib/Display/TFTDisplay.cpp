#include <TFTDisplay.h>
#include <math.h>
#include <stdio.h>

TFTDisplay::TFTDisplay(TFTDriver &driver) : m_driver{driver} {}

void TFTDisplay::initialize() {
	m_driver.initialize();
	// The screen is not cleared upon initialization; it displays the
	// (potentially uninitialized) framebuffer. We clear the entire screen once
	// now, and subsequent display updates will overwrite previous text
	// (in effect, clearing it).
	m_driver.clearScreen(CLEAR_COLOR);
	determineLayout();
}

void TFTDisplay::determineLayout() {
	// Wire 1 text will be on the first line
	m_layout.wire1Text.x = 0;
	m_layout.wire1Text.y = 0;

	// Wire 2 text will be on the second line
	m_layout.wire2Text.x = 0;
	m_layout.wire2Text.y = m_driver.getTextHeight();
}

void TFTDisplay::update(float channel1Power, float channel2Power) {
	// NOTE: The extra two spaces at the end are for clearing a previous longer
	// message. The channel power is represented in 1 to 3 digits, so in the worst
	// case there are two leftover characters from the previous update.

	snprintf(
		m_text_staging, sizeof(m_text_staging), "Wire 1: %d%%  ",
		static_cast<int>(round(channel1Power * 100.f))
	);
	m_driver.drawText(
		m_layout.wire1Text, /*textColor=*/TEXT_COLOR, /*bgColor=*/CLEAR_COLOR,
		m_text_staging
	);

	snprintf(
		m_text_staging, sizeof(m_text_staging), "Wire 2: %d%%  ",
		static_cast<int>(round(channel2Power * 100.f))
	);
	m_driver.drawText(
		m_layout.wire2Text, /*textColor=*/TEXT_COLOR, /*bgColor=*/CLEAR_COLOR,
		m_text_staging
	);
}
