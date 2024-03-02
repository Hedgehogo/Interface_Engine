#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxSwitchTabs : public Box, public virtual IScalableObjectsArray, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			MakeDyn<ISMRSize> value;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, MakeDyn<ISMRSize> value, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxSwitchTabs* override;
		};
		
		BoxSwitchTabs(Make&& make, InitInfo init_info);
		
		auto get_value() -> ISMRSize&;
		
		auto set_index(size_t index) -> void;
		
		auto get_index() -> size_t;
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto get_array_size() const -> size_t override;
		
		auto get_object_at(size_t index) -> IScalable& override;
		
		auto get_object_at(size_t index) const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		std::vector<DrawManager> draw_managers_;
		std::vector<BoxPtr<IScalable> > objects_;
		ISMRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxSwitchTabs::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxSwitchTabs::Make>;
};
