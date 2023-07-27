#pragma once

#include "../onlyDrawable.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/determine/determine.hpp"

namespace ui {
	class Sprite : public OnlyDrawable {
	public:
		Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f minSize = {});
		
		Sprite(sf::Texture& texture, sf::Vector2f minSize = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
	
	protected:
		Sprite(sf::Sprite sprite, sf::Vector2f minSize);
	
	public:
		Sprite* copy() override;
	
	protected:
		sf::Sprite sprite;
		sf::Vector2f minimumSize;
	};
	
	template<>
	struct DecodePointer<Sprite> {
		static bool decodePointer(const YAML::Node& node, Sprite*& sprite);
	};
	
	template<>
	bool determine<Sprite>(const YAML::Node& node);
}
