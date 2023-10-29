#pragma once

#include "../OnlyDrawable.hpp"
#include "../../IUninteractiveLayout/IUninteractiveLayout.hpp"

namespace ie {
	class RoundedRectangle : public OnlyDrawable, public virtual IUninteractiveLayout {
	public:
		struct Make : public virtual IUninteractiveLayout::Make {
			sf::Color color;
			float radius;
			
			Make(sf::Color color, float radius);
			
			RoundedRectangle* make(InitInfo init_info) override;
		};
		
		RoundedRectangle(Make&& make, InitInfo init_info);
		
		RoundedRectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		RoundedRectangle* copy() override;
	
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout_;
		sf::RectangleShape horizontal_rectangle;
		sf::RectangleShape vertical_rectangle;
		sf::CircleShape circle;
		float radius;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<RoundedRectangle> {
		static bool decode_pointer(const YAML::Node& node, RoundedRectangle*& rounded_rectangle);
	};
	*/
	/*old_yaml_determine
	template<>
	bool determine<RoundedRectangle>(const YAML::Node& node);
	*/
}
