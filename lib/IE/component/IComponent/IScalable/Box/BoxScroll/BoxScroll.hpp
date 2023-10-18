#pragma once

#include "../BoxView/BoxView.hpp"
#include "IE/modules/yaml-cpp/shared/ISVector2/SVector2/SVector2.hpp"

namespace ie {
	class BoxScroll : public BoxWithView {
	protected:
		sf::Vector2f get_new_object_position(sf::Vector2f normal_object_position);
	
	public:
		struct Make : public virtual Box::Make {
			BoxPtr<IComponent::Make> object;
			PSRVec2f normal_object_position;
			sf::Vector2f min_size;
			
			Make(BoxPtr<IComponent::Make>&& object, PSRVec2f normal_object_position, sf::Vector2f min_size = {});
			
			BoxScroll* make(InitInfo init_info) override;
		};
		
		BoxScroll(Make&& make, InitInfo init_info);
		
		BoxScroll(BoxPtr<IComponent>&& object, const PSRVec2f& normal_object_position, const sf::Vector2f& min_size = {});
		
		void init(InitInfo init_info) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		BoxScroll* copy() override;
	
	protected:
		BoxPtr<IComponent> object;
		PSRVec2f normal_object_position;
	};
	
	template<>
	struct DecodePointer<BoxScroll> {
		static bool decode_pointer(const YAML::Node& node, BoxScroll*& box_scroll);
	};
}