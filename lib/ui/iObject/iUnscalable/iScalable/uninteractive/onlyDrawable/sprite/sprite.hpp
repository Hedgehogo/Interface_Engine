#pragma once
#include "../onlyDrawable.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	class Sprite : public OnlyDrawable {
	protected:
		sf::Sprite sprite;
		sf::Vector2f minimumSize;
	
	public:
		Sprite(sf::Texture &texture, sf::IntRect rect, sf::Vector2f minSize = {});
		
		Sprite(sf::Texture &texture, sf::Vector2f minSize = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() override;
		
		sf::Vector2f getAreaSize() override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
	protected:
		Sprite(sf::Sprite sprite, sf::Vector2f minSize);
		
	public:
		Sprite* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, Sprite *&sprite);
}
