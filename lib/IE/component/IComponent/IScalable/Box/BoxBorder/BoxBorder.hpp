#pragma once

#include "../Box.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"

namespace ie {
	class BoxBorder : public Box {
	public:
		struct Make : public virtual Box::Make {
			std::vector<std::vector<BoxPtr<IScalable::Make> > > objects;
			std::vector<float> bounds_horizontal;
			std::vector<float> bounds_vertical;
			sf::Vector2f min_size = {};
			
			Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, std::vector<float> bounds_horizontal, std::vector<float> bounds_vertical, sf::Vector2f min_size = {});
			
			Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, sf::Vector2f min_size = {});
			
			BoxBorder* make(InitInfo init_info) override;
		};
		
		BoxBorder(Make&& make, InitInfo init_info);
		
		BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, std::vector<float> bounds_horizontal, std::vector<float> bounds_vertical, sf::Vector2f min_size = {});
		
		BoxBorder(std::vector<std::vector<BoxPtr<IScalable> > >&& objects, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		BoxBorder* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		std::vector<std::vector<BoxPtr<IScalable> > > objects_;
		std::vector<float> bounds_horizontal_;
		std::vector<float> bounds_vertical_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<BoxBorder> {
		static bool decode_pointer(const YAML::Node& node, BoxBorder*& box_with_border);
	};
	*/
}
