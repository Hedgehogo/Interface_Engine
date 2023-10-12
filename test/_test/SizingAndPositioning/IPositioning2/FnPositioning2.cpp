#include <gtest/gtest.h>
#include "IE/sizing-positioning/IPositioning2/FnPositioning2/FnPositioning2.hpp"

TEST(SizingAndPositioning, FnPositioning2) {
	sf::RenderTexture renderTexture;
	
	ie::FnPositioning2 fnPositioning2{
		{
			[](sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f) {
				return sf::Vector2f{15, 20};
			}
		},
		{renderTexture}
	};
	
	ASSERT_EQ(
		fnPositioning2.findPosition({12, 17}, {27, 31}, {16, 19}),
		(sf::Vector2f{15, 20})
	);
}