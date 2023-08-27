#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/IPositioning2/Positioning2/Positioning2.hpp>

TEST(SizingAndPositioning, Positioning2) {
	sf::RenderTexture renderTexture;
	
	ie::Positioning2 internalPositioning2{
		{{0.5, 0.5}, {0.5, 0.5}},
		{renderTexture}
	};
	
	ASSERT_EQ(
		internalPositioning2.findPosition({12, 17}, {27, 31}, {16, 19}),
		(sf::Vector2f{18, 23.5})
	);
}