#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISRanged/ISRanged.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxTabs : public Box, public virtual IScalableObjectsArray, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			MakeDyn<ISRSize> value;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, MakeDyn<ISRSize> value, sf::Vector2f min_size = {});
			
			BoxTabs* make(InitInfo init_info) override;
		};
		
		BoxTabs(Make&& make, InitInfo init_info);
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		size_t get_array_size() const override;
		
		IScalable& get_object_at(size_t index) override;
		
		const IScalable& get_object_at(size_t index) const override;
		
	protected:
		std::vector<DrawManager> draw_managers_;
		std::vector<BoxPtr<IScalable> > objects_;
		ISRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxTabs::Make> {
	static orl::Option<ie::BoxTabs::Make> decode(ieml::Node const& node);
};
