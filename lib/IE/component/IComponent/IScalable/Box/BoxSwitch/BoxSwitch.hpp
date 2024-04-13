#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISReadable.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableTwoObjects/IScalableTwoObjects.hpp"

namespace ie {
	class BoxSwitch : public Box, public virtual IScalableTwoObjects, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableTwoObjects::Make {
			BoxPtr<IScalable::Make> inactive_object;
			BoxPtr<IScalable::Make> active_object;
			MakeDyn<ISBool> value;
			sf::Vector2f min_size = {};
			
			Make(BoxPtr<IScalable::Make>&& inactive_object, BoxPtr<IScalable::Make>&& active_object, MakeDyn<ISBool> value, const sf::Vector2f& min_size = {});
			
			auto make(InitInfo init_info) -> BoxSwitch* override;
		};
		
		BoxSwitch(Make&& make, InitInfo init_info);
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f position) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto draw() -> void override;
		
		auto update_interactions(Event event) -> bool override;
		
		auto get_first_object() -> IScalable& override;
		
		auto get_first_object() const -> IScalable const& override;
		
		auto get_second_object() -> IScalable& override;
		
		auto get_second_object() const -> IScalable const& override;
		
	protected:
		DrawManager inactive_draw_manager_;
		DrawManager active_draw_manager_;
		BoxPtr<IScalable> inactive_object_;
		BoxPtr<IScalable> active_object_;
		ISBool& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxSwitch::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxSwitch::Make>;
};
