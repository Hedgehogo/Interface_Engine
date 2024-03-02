#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISVec2/ISVec2.hpp"
#include "../BoxView/BoxView.hpp"

namespace ie {
	class BoxScroll : public BoxView {
	public:
		struct Make : public virtual Box::Make {
			BoxPtr<IComponent::Make> object;
			MakeDyn<ISRVec2F> normal_object_position;
			sf::Vector2f min_size;
			
			Make(BoxPtr<IComponent::Make>&& object, MakeDyn<ISRVec2F> normal_object_position, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxScroll* override;
		};
		
		BoxScroll(Make&& make, InitInfo init_info);
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
	protected:
		auto get_new_object_position(sf::Vector2f normal_object_position) -> sf::Vector2f;
		
		BoxPtr<IComponent> object_;
		SReader<ISRVec2F> normal_object_position_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxScroll::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxScroll::Make>;
};
