#include <gtest/gtest.h>
#include <IE/IComponent/IUnscalable/IScalable/Box/BoxShader/BoxShader.hpp>
#include <IE/IComponent/IUnscalable/IScalable/IUninteractive/OnlyDrawable/Capsule/Capsule.hpp>
#include <_test/IComponent/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IComponent, BoxShader) {
	InitInfoData data{{100, 100}};
	
	auto shader = new sf::Shader{};
	shader->loadFromFile("test-src/BoxShader.glsl", sf::Shader::Type::Fragment);
	ie::BoxShader boxShader{
		{
			ie::makeBoxPtr<ie::IScalable::Make, ie::Capsule::Make>(sf::Color::Green),
			new sf::Shader{},
			ie::BoxShader::Transmission::Texture
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxShader);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxShader.getMinSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxShader.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxShader.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxShader.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxShader.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxShader.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxShader.updateInteractions({}), true);
	
	boxShader.setSize({5, 11});
	ASSERT_EQ(boxShader.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxShader.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxShader.setPosition({19, 39});
	ASSERT_EQ(boxShader.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxShader.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxShader.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxShader.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxShader.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxShader.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxShader.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxShader.move({10, 5});
	ASSERT_EQ(boxShader.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxShader.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxShader.png"));
}