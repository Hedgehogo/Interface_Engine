#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxSwitchTabs : public Box, public virtual IScalableObjectsArray, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PSValue<size_t> value;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSValue<size_t> value, sf::Vector2f min_size = {});
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, size_t index = 0, sf::Vector2f min_size = {});
			
			BoxSwitchTabs* make(InitInfo init_info) override;
		};
		
		BoxSwitchTabs(Make&& make, InitInfo init_info);
		
		BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, PSValue<size_t> value, sf::Vector2f min_size = {});
		
		BoxSwitchTabs(std::vector<BoxPtr<IScalable> >&& objects, size_t index = 0, sf::Vector2f min_size = {});
		
		BoxSwitchTabs(const BoxSwitchTabs& other);
		
		void init(InitInfo init_info) override;
		
		void set_value(PSValue<size_t> index);
		
		PSValue<size_t> get_value();
		
		void set_index(size_t index);
		
		size_t get_index();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		size_t get_array_size() const override;
		
		IScalable& get_object_at(size_t index) override;
		
		const IScalable& get_object_at(size_t index) const override;
		
		BoxSwitchTabs* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		std::vector<DrawManager> draw_managers_;
		std::vector<BoxPtr<IScalable> > objects_;
		PSValue<size_t> value_;
	};
	
	template<>
	struct DecodePointer<BoxSwitchTabs> {
		static bool decode_pointer(const YAML::Node& node, BoxSwitchTabs*& box_with_changeable_objects);
	};
}
