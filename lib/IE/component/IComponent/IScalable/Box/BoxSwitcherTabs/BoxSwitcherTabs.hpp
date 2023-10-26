#pragma once

#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"
#include "../../BasicInteractiveData/BasicInteractiveData.hpp"

namespace ie {
	class BoxSwitcherTabs : public Box, public virtual IScalableObjectsArray, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			PSint value;
			Key key;
			bool is_horizontal;
			sf::Vector2f min_size = {};
			
			Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSint value, Key key = Key::MouseLeft, bool is_horizontal = true, sf::Vector2f min_size = {});
			
			BoxSwitcherTabs* make(InitInfo init_info) override;
		};
		
		BoxSwitcherTabs(Make&& make, InitInfo init_info);
		
		BoxSwitcherTabs(std::vector<BoxPtr<IScalable> >&& objects, PSint value, Key key, bool is_horizontal, sf::Vector2f min_size = {});
		
		void init(InitInfo init_info) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		size_t get_array_size() const override;
		
		IScalable& get_object_at(size_t index) override;
		
		const IScalable& get_object_at(size_t index) const override;
		
		int get_tab(sf::Vector2f position);
		
		BoxSwitcherTabs* copy() override;
	
	protected:
		BasicInteractiveData<BoxSwitcherTabs&> interactive_;
		std::vector<BoxPtr<IScalable> > objects_;
		bool is_horizontal_;
		PSint value_;
	};
	
	template<>
	struct DecodePointer<BoxSwitcherTabs> {
		static bool decode_pointer(const YAML::Node& node, BoxSwitcherTabs*& switcher_tabs);
	};
}