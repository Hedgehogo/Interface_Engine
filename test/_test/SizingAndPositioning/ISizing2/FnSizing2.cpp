#include <gtest/gtest.h>
#include "IE/sizing-positioning/ISizing2/FnSizing2/FnSizing2.hpp"

TEST(SizingAndPositioning, FnSizing2) {
	sf::RenderTexture render_texture;
	
	ie::FnSizing2 fn_sizing2{
		{
			[](sf::Vector2f, sf::Vector2f, sf::Vector2f) {
				return sf::Vector2f{13.f, 19.f};
			},
			[](sf::Vector2f) {
				return sf::Vector2f{5.f, 7.f};
			}
		},
		{
			render_texture,
			sf::Vector2f{17, 29}
		}
	};
	
	ASSERT_EQ(fn_sizing2.find_size({5, 7}), (sf::Vector2f{13, 19}));
	ASSERT_EQ(fn_sizing2.get_parent_size({23, 29}), (sf::Vector2f{5, 7}));
}