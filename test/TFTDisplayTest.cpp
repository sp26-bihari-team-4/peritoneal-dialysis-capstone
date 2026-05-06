#include <TFTDisplay.h>
#include <TFTDriver.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::StrEq;

class MockTFTDriver : public TFTDriver {
public:
	MOCK_METHOD(void, initialize, (), (override));
	MOCK_METHOD(unsigned, getScreenWidth, (), (override, const));
	MOCK_METHOD(unsigned, getScreenHeight, (), (override, const));
	MOCK_METHOD(unsigned, getTextWidth, (), (override, const));
	MOCK_METHOD(unsigned, getTextHeight, (), (override, const));
	MOCK_METHOD(void, clearScreen, (TFTColor color), (override));
	MOCK_METHOD(
		void, drawText,
		(TFTPoint topLeft, TFTColor textColor, TFTColor bgColor,
		 const char *string),
		(override)
	);
};

class TFTDisplayTest : public testing::Test {
protected:
	unsigned int TEXT_HEIGHT = 8;
	TFTPoint line1{0, 0};
	TFTPoint line2{0, TEXT_HEIGHT};
	MockTFTDriver driver;
	TFTDisplay display{driver};

	TFTDisplayTest() {
		EXPECT_CALL(driver, initialize());
		EXPECT_CALL(driver, clearScreen(TFTColor::Black));
		EXPECT_CALL(driver, getTextHeight()).WillOnce(Return(TEXT_HEIGHT));
		// Call initialize before each test so display can store the text height
		display.initialize();
	}
};

TEST_F(TFTDisplayTest, DisplaysZeros) {
	EXPECT_CALL(
		driver,
		drawText(line1, TFTColor::White, TFTColor::Black, StrEq("Wire 1: 0%  "))
	);
	EXPECT_CALL(
		driver,
		drawText(line2, TFTColor::White, TFTColor::Black, StrEq("Wire 2: 0%  "))
	);

	display.update(0, 0);
}

TEST_F(TFTDisplayTest, DisplaysHundreds) {
	EXPECT_CALL(
		driver,
		drawText(line1, TFTColor::White, TFTColor::Black, StrEq("Wire 1: 100%  "))
	);
	EXPECT_CALL(
		driver,
		drawText(line2, TFTColor::White, TFTColor::Black, StrEq("Wire 2: 100%  "))
	);

	display.update(1, 1);
}

TEST_F(TFTDisplayTest, DisplaysMixedValues) {
	EXPECT_CALL(
		driver,
		drawText(line1, TFTColor::White, TFTColor::Black, StrEq("Wire 1: 25%  "))
	);
	EXPECT_CALL(
		driver,
		drawText(line2, TFTColor::White, TFTColor::Black, StrEq("Wire 2: 75%  "))
	);

	display.update(0.25, 0.75);
}

TEST_F(TFTDisplayTest, RoundsToTheNearestPercent) {
	EXPECT_CALL(
		driver,
		drawText(line1, TFTColor::White, TFTColor::Black, StrEq("Wire 1: 44%  "))
	);
	EXPECT_CALL(
		driver,
		drawText(line2, TFTColor::White, TFTColor::Black, StrEq("Wire 2: 56%  "))
	);

	display.update(0.4444, 0.5555);
}
