#include <gtest/gtest.h>
#include <IE/SizingAndPositioning/ISizing2/LambdaSizing2/LambdaSizing2.hpp>

TEST(SizingAndPositioning, LambdaSizing2) {
	sf::RenderTexture renderTexture;
	
	ie::LambdaSizing2 lambdaSizing2{
		{
			[](sf::Vector2f, sf::Vector2f, sf::Vector2f) {
				return sf::Vector2f{13.f, 19.f};
			},
			[](sf::Vector2f) {
				return sf::Vector2f{5.f, 7.f};
			}
		},
		{
			renderTexture,
			sf::Vector2f{17, 29}
		}
	};
	
	ASSERT_EQ(lambdaSizing2.findSize({5, 7}), (sf::Vector2f{13, 19}));
	ASSERT_EQ(lambdaSizing2.getParentSize({23, 29}), (sf::Vector2f{5, 7}));
}