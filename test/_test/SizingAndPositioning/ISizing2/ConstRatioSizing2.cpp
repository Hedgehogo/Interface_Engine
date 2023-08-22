#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing2/ConstRatioSizing2/ConstRatioSizing2.hpp>

TEST(SizingAndPositioning, ConstRatioSizing2) {
	sf::RenderTexture renderTexture;
	
	ui::ConstRatioSizing2 constRatioSizing2{
		{13.f, 1.f},
		{renderTexture, sf::Vector2f{17, 29}}
	};
	
	ASSERT_EQ(constRatioSizing2.findSize({5, 7}), (sf::Vector2f{13, 13}));
	ASSERT_EQ(constRatioSizing2.getParentSize({23, 29}), (sf::Vector2f{}));
}