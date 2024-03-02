#include <gtest/gtest.h>
#include <IE/sizing-positioning/IPositioning2/Positioning2/Positioning2.hpp>

TEST(SizingAndPositioning, Positioning2) {
	sf::RenderTexture render_texture;
	
	ie::Positioning2 internal_positioning2{
		{{0.5, 0.5}, {0.5, 0.5}},
		{render_texture}
	};
	
	ASSERT_EQ(
		internal_positioning2.find_position({12, 17}, {27, 31}, {16, 19}),
		(sf::Vector2f{18, 23.5})
	);
}