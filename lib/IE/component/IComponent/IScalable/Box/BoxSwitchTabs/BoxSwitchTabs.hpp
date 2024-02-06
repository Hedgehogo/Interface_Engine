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
			
			BoxSwitchTabs* make(InitInfo init_info) override;
		};
		
		BoxSwitchTabs(Make&& make, InitInfo init_info);
		
		ISMRSize& get_value();
		
		void set_index(size_t index);
		
		size_t get_index();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		size_t get_array_size() const override;
		
		IScalable& get_object_at(size_t index) override;
		
		const IScalable& get_object_at(size_t index) const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		std::vector<DrawManager> draw_managers_;
		std::vector<BoxPtr<IScalable> > objects_;
		ISMRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxSwitchTabs::Make> {
	static orl::Option<ie::BoxSwitchTabs::Make> decode(ieml::Node const& node);
};
