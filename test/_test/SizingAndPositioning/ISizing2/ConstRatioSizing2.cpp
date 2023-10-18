#include <gtest/gtest.h>
#include <IE/sizing-positioning/ISizing2/ConstRatioSizing2/ConstRatioSizing2.hpp>

TEST(SizingAndPositioning, ConstRatioSizing2) {
	sf::RenderTexture render_texture;
	
	ie::ConstRatioSizing2 const_ratio_sizing2{
		{13.f, 1.f},
		{render_texture, sf::Vector2f{17, 29}}
	};
	
	ASSERT_EQ(const_ratio_sizing2.find_size({5, 7}), (sf::Vector2f{13, 13}));
	ASSERT_EQ(const_ratio_sizing2.get_parent_size({23, 29}), (sf::Vector2f{}));
}