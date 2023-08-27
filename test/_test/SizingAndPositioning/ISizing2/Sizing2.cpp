#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing2/Sizing2/Sizing2.hpp>

TEST(SizingAndPositioning, Sizing2) {
	sf::RenderTexture renderTexture;
	
	ie::Sizing2 sizing2{
		{sf::Vector2f{13, 19}},
		{renderTexture, sf::Vector2f{17, 29}}
	};
	
	ASSERT_EQ(sizing2.findSize({5, 7}), (sf::Vector2f{13, 19}));
	ASSERT_EQ(sizing2.getParentSize({23, 29}), (sf::Vector2f{}));
}