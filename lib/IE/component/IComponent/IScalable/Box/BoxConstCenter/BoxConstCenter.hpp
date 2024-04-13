#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxConstCenter : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> const_object;
			BoxPtr<IScalable::Make> background;
			sf::Vector2f const_size;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& const_object, BoxPtr<IScalable::Make>&& background, sf::Vector2f const_size, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxConstCenter* override;
		};
		
		BoxConstCenter(Make&& make, InitInfo init_info);
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f position) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
		auto update_interactions(Event event) -> bool override;
		
	protected:
		BoxPtr<IScalable> const_object_;
		BoxPtr<IScalable> background_;
		sf::Vector2f const_size_;
		bool resized_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxConstCenter::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxConstCenter::Make>;
};
