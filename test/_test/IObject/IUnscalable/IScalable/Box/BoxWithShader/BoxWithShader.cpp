#include <gtest/gtest.h>
#include <ui/iObject/iUnscalable/iScalable/box/shader/boxWithShader.hpp>
#include <ui/iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/capsule/capsule.hpp>
#include <_test/IObject/_InitInfoData/InitInfoData.hpp>
#include <_test/_imageEqual.hpp>

TEST(IObject, BoxWithShader) {
	InitInfoData data{{100, 100}};
	
	auto shader = new sf::Shader{};
	shader->loadFromFile("test-src/BoxWithShader.glsl", sf::Shader::Type::Fragment);
	ui::BoxWithShader boxWithShader{
		{
			ui::makeBoxPtr<ui::IScalable::Make, ui::Capsule::Make>(sf::Color::Green),
			new sf::Shader{},
			ui::BoxWithShader::Transmission::texture
		},
		data.makeInitInfo()
	};
	data.interactionManager.update({});
	
	ASSERT_EQ(data.drawManager.size(), 1);
	ASSERT_EQ(&data.drawManager.get(0), &boxWithShader);
	ASSERT_EQ(data.updateManager.size(), 0);
	ASSERT_EQ(data.interactionManager.size(), 0);
	ASSERT_EQ(data.panelManager.size(), 0);
	
	ASSERT_EQ(boxWithShader.getMinSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxWithShader.getNormalSize(), (sf::Vector2f{1, 1}));
	ASSERT_EQ(boxWithShader.getSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithShader.getAreaSize(), sf::Vector2f{});
	ASSERT_EQ(boxWithShader.getPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithShader.getAreaPosition(), sf::Vector2f{});
	ASSERT_EQ(boxWithShader.updateInteractions({}), true);
	
	boxWithShader.setSize({5, 11});
	ASSERT_EQ(boxWithShader.getSize(), (sf::Vector2f{5, 11}));
	ASSERT_EQ(boxWithShader.getAreaSize(), (sf::Vector2f{5, 11}));
	
	boxWithShader.setPosition({19, 39});
	ASSERT_EQ(boxWithShader.getPosition(), (sf::Vector2f{19, 39}));
	ASSERT_EQ(boxWithShader.getAreaPosition(), (sf::Vector2f{19, 39}));
	
	boxWithShader.resize({7, 13}, {23, 41});
	ASSERT_EQ(boxWithShader.getSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithShader.getAreaSize(), (sf::Vector2f{7, 13}));
	ASSERT_EQ(boxWithShader.getPosition(), (sf::Vector2f{23, 41}));
	ASSERT_EQ(boxWithShader.getAreaPosition(), (sf::Vector2f{23, 41}));
	
	boxWithShader.move({10, 5});
	ASSERT_EQ(boxWithShader.getPosition(), (sf::Vector2f{33, 46}));
	ASSERT_EQ(boxWithShader.getAreaPosition(), (sf::Vector2f{33, 46}));
	
	data.drawManager.draw();
	ASSERT_TRUE(data.renderEqualWithSave("test-src/BoxWithShader.png"));
}