#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxBorderHorizontal : public Box, public virtual IScalableObjectsArray {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			std::vector<float> bounds;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f min_size = {});
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f min_size = {});
			
			Make(BoxPtr<IScalable::Make>&& first_object, BoxPtr<IScalable::Make>&& second_object, float bound = 0.5f, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> BoxBorderHorizontal* override;
		};
		
		BoxBorderHorizontal(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto get_array_size() const -> size_t override;
		
		auto get_object_at(size_t index) -> IScalable& override;
		
		auto get_object_at(size_t index) const -> IScalable const& override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	
	protected:
		std::vector<BoxPtr<IScalable> > objects_;
		std::vector<float> bounds_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxBorderHorizontal::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxBorderHorizontal::Make>;
};
