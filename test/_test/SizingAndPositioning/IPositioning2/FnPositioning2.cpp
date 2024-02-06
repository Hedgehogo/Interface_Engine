#include <gtest/gtest.h>
#include "IE/sizing-positioning/IPositioning2/FnPositioning2/FnPositioning2.hpp"

TEST(SizingAndPositioning, FnPositioning2) {
	sf::RenderTexture render_texture;
	
	ie::FnPositioning2 fn_positioning2{
		{
			[](sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f) {
				return sf::Vector2f{15, 20};
			}
		},
		{render_texture}
	};
	
	ASSERT_EQ(
		fn_positioning2.find_position({12, 17}, {27, 31}, {16, 19}),
		(sf::Vector2f{15, 20})
	);
}