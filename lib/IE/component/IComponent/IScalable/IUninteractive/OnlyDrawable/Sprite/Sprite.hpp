#pragma once

#include "../OnlyDrawable.hpp"
#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"
#include "IE\modules\yaml-cpp\yaml-builder\determine\determine.hpp"

namespace ie {
	class Sprite : public OnlyDrawable {
	public:
		struct Make : public virtual IUninteractive::Make {
			sf::Texture& texture;
			sf::IntRect rect;
			sf::Vector2f minSize;
			
			Make(sf::Texture& texture, sf::IntRect rect, sf::Vector2f minSize = {});
			
			Make(sf::Texture& texture, sf::Vector2f minSize = {});
			
			Sprite* make(InitInfo initInfo) override;
		};
		
		Sprite(Make&& make, InitInfo initInfo);
		
		Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f minSize = {});
		
		Sprite(sf::Texture& texture, sf::Vector2f minSize = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
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