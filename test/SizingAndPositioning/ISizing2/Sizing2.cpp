#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing2/Sizing2/Sizing2.hpp>

TEST(SizingAndPositioning, Sizing2) {
	sf::RenderTexture render_texture;
	
	ie::Sizing2 sizing2{
		{sf::Vector2f{13, 19}},
		{render_texture, sf::Vector2f{17, 29}}
	};
	
	ASSERT_EQ(sizing2.find_size({5, 7}), (sf::Vector2f{13, 19}));
	ASSERT_EQ(sizing2.get_parent_size({23, 29}), (sf::Vector2f{}));
}