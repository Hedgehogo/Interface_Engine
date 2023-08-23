#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/IPositioning2/LambdaPositioning2/LambdaPositioning2.hpp>

TEST(SizingAndPositioning, LambdaPositioning2) {
	sf::RenderTexture renderTexture;
	
	ui::LambdaPositioning2 lambdaPositioning2{
		{
			[](sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f) {
				return sf::Vector2f{15, 20};
			}
		},
		{renderTexture}
	};
	
	ASSERT_EQ(
		lambdaPositioning2.findPosition({12, 17}, {27, 31}, {16, 19}),
		(sf::Vector2f{15, 20})
	);
}