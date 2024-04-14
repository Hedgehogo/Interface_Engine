#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"

namespace ie {
	class BoxBorder : public Box {
	public:
		struct Make : public virtual Box::Make {
			std::vector<std::vector<BoxPtr<IScalable::Make> > > objects;
			std::vector<float> bounds_horizontal;
			std::vector<float> bounds_vertical;
			sf::Vector2f min_size = {};
			
			Make(
				std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects,
				std::vector<float> bounds_horizontal,
				std::vector<float> bounds_vertical,
				sf::Vector2f min_size = {}
			);
			
			Make(std::vector<std::vector<BoxPtr<IScalable::Make> > >&& objects, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxBorder* override;
		};
		
		BoxBorder(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		std::vector<std::vector<BoxPtr<IScalable> > > objects_;
		std::vector<float> bounds_horizontal_;
		std::vector<float> bounds_vertical_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxBorder::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxBorder::Make>;
};
