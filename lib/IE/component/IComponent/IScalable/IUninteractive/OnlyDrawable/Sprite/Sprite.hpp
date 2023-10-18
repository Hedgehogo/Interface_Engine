#pragma once

#include "../OnlyDrawable.hpp"
#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/determine/determine.hpp"

namespace ie {
	class Sprite : public OnlyDrawable {
	public:
		struct Make : public virtual IUninteractive::Make {
			sf::Texture& texture;
			sf::IntRect rect;
			sf::Vector2f min_size;
			
			Make(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size = {});
			
			Make(sf::Texture& texture, sf::Vector2f min_size = {});
			
			Sprite* make(InitInfo init_info) override;
		};
		
		Sprite(Make&& make, InitInfo init_info);
		
		Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size = {});
		
		Sprite(sf::Texture& texture, sf::Vector2f min_size = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		Sprite* copy() override;
	
	protected:
		sf::Sprite sprite;
		sf::Vector2f minimum_size;
	};
	
	template<>
	struct DecodePointer<Sprite> {
		static bool decode_pointer(const YAML::Node& node, Sprite*& sprite);
	};
	
	template<>
	bool determine<Sprite>(const YAML::Node& node);
}