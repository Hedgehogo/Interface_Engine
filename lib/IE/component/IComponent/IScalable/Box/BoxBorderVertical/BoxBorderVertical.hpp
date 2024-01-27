#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxBorderVertical : public Box, public virtual IScalableObjectsArray {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			std::vector<float> bounds;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, std::vector<float> bounds, sf::Vector2f min_size = {});
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, sf::Vector2f min_size = {});
			
			Make(BoxPtr<IScalable::Make>&& first_object, BoxPtr<IScalable::Make>&& second_object, float bound = 0.5f, sf::Vector2f min_size = {});
			
			BoxBorderVertical* make(InitInfo init_info) override;
		};
		
		BoxBorderVertical(Make&& make, InitInfo init_info);
		
		BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, std::vector<float> bounds, sf::Vector2f min_size = {0, 0});
		
		BoxBorderVertical(std::vector<BoxPtr<IScalable> >&& objects, sf::Vector2f min_size = {0, 0});
		
		BoxBorderVertical(BoxPtr<IScalable>&& first_object, BoxPtr<IScalable>&& second_object, float bound = 0.5f, sf::Vector2f min_size = {0, 0});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		size_t get_array_size() const override;
		
		IScalable& get_object_at(size_t index) override;
		
		const IScalable& get_object_at(size_t index) const override;
		
		BoxBorderVertical* copy() override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	
	protected:
		std::vector<BoxPtr<IScalable> > objects_;
		std::vector<float> bounds_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxBorderVertical::Make> {
	static orl::Option<ie::BoxBorderVertical::Make> decode(ieml::Node const& node);
};
