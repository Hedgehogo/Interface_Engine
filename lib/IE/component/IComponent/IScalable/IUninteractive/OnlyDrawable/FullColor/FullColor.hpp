#pragma once

#include "../OnlyDrawable.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class FullColor : public OnlyDrawable {
	public:
		struct Make : public virtual IUninteractive::Make {
			sf::Color color;
			sf::Vector2f normal_size = {};
			
			Make(sf::Color color, sf::Vector2f normal_size = {0, 0});
			
			FullColor* make(InitInfo init_info) override;
		};
		
		FullColor(Make&& make, InitInfo init_info);
		
		explicit FullColor(sf::Color color, sf::Vector2f normal_size = {0, 0});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		FullColor* copy() override;
	
	protected:
		sf::RectangleShape rectangle;
		sf::Vector2f normal_size;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<FullColor> {
		static bool decode_pointer(const YAML::Node& node, FullColor*& full_color);
	};
	*/
	
	/*old_yaml_determine_impl
	template<>
	bool determine<FullColor>(const YAML::Node& node);
	*/
}
