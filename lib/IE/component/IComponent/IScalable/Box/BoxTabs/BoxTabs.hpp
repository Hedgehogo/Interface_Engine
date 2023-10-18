#pragma once

#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"

namespace ie {
	class BoxTabs : public Box, public virtual IScalableObjectsArray, public virtual IDrawable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PISint value;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PISint value, sf::Vector2f min_size = {});
			
			BoxTabs* make(InitInfo init_info) override;
		};
		
		BoxTabs(Make&& make, InitInfo init_info);
		
		BoxTabs(std::vector<BoxPtr<IScalable> >&& objects, PISint value, sf::Vector2f min_size = {});
		
		BoxTabs(const BoxTabs& other);
		
		void init(InitInfo init_info) override;
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void draw() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		std::size_t get_array_size() const override;
		
		IScalable& get_object_at(std::size_t index) override;
		
		const IScalable& get_object_at(std::size_t index) const override;
		
		BoxTabs* copy() override;
	
	protected:
		std::vector<DrawManager> draw_managers;
		std::vector<BoxPtr<IScalable> > objects;
		PISint value;
	};
	
	template<>
	struct DecodePointer<BoxTabs> {
		static bool decode_pointer(const YAML::Node& node, BoxTabs*& box_with_tabs);
	};
}
