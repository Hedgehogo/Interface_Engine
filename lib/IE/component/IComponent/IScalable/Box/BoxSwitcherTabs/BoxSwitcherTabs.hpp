#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISRanged/ISRanged.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"
#include "../../BasicInteractiveData/BasicInteractiveData.hpp"

namespace ie {
	class BoxSwitcherTabs : public Box, public virtual IScalableObjectsArray, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			MakeDyn<ISRSize> value;
			Key key;
			bool is_horizontal;
			sf::Vector2f min_size = {};
			
			Make(
				std::vector<BoxPtr<IScalable::Make> >&& objects,
				MakeDyn<ISRSize> value,
				Key key = Key::MouseLeft,
				bool is_horizontal = true,
				sf::Vector2f min_size = {}
			);
			
			BoxSwitcherTabs* make(InitInfo init_info) override;
		};
		
		BoxSwitcherTabs(Make&& make, InitInfo init_info);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		size_t get_array_size() const override;
		
		IScalable& get_object_at(size_t index) override;
		
		const IScalable& get_object_at(size_t index) const override;
		
		int get_tab(sf::Vector2f position);
		
	protected:
		BasicInteractiveData<BoxSwitcherTabs&> interactive_;
		std::vector<BoxPtr<IScalable> > objects_;
		bool is_horizontal_;
		ISRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxSwitcherTabs::Make> {
	static orl::Option<ie::BoxSwitcherTabs::Make> decode(ieml::Node const& node);
};
