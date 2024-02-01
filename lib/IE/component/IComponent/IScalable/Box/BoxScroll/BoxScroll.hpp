#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISValue/SVec2/SVec2.hpp"
#include "../BoxView/BoxView.hpp"

namespace ie {
	class BoxScroll : public BoxWithView {
	protected:
		sf::Vector2f get_new_object_position(sf::Vector2f normal_object_position);
	
	public:
		struct Make : public virtual Box::Make {
			BoxPtr<IComponent::Make> object;
			MakeDyn<SRVec2F> normal_object_position;
			sf::Vector2f min_size;
			
			Make(BoxPtr<IComponent::Make>&& object, MakeDyn<SRVec2F> normal_object_position, sf::Vector2f min_size = {});
			
			BoxScroll* make(InitInfo init_info) override;
		};
		
		BoxScroll(Make&& make, InitInfo init_info);
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
	protected:
		BoxPtr<IComponent> object_;
		SReader<SRVec2F> normal_object_position_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxScroll::Make> {
	static orl::Option<ie::BoxScroll::Make> decode(ieml::Node const& node);
};
