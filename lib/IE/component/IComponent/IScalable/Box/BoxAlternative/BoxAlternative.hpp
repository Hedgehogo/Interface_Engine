#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxAlternative : public Box, public virtual IScalableTwoObjects {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> top_object;
			BoxPtr<IScalable::Make> bottom_object;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& top_object, BoxPtr<IScalable::Make>&& bottom_object, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxAlternative* override;
		};
		
		BoxAlternative(Make&& make, InitInfo init_info);
		
		auto handle_event(Event event) -> bool override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
	protected:
		BoxPtr<IScalable> bottom_object_;
		BoxPtr<IScalable> top_object_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxAlternative::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxAlternative::Make>;
};
