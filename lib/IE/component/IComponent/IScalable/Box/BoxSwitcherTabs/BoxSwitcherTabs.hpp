#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
#include "IE/event/EventHandler/KeyHandler/KeyHandler.hpp"
#include "../Box.hpp"
#include "../../IScalableLayout/IScalableObjectsArray/IScalableObjectsArray.hpp"
#include "../../BasicInteractiveData/BasicInteractiveData.hpp"

namespace ie {
	class BoxSwitcherTabs : public Box, public virtual IScalableObjectsArray, public virtual IUpdatable {
	public:
		struct Make : public virtual Box::Make, public virtual IScalableObjectsArray::Make {
			std::vector<BoxPtr<IScalable::Make> > objects;
			MakeDyn<ISMRSize> value;
			Key key;
			bool is_horizontal;
			sf::Vector2f min_size = {};
			
			Make(
				std::vector<BoxPtr<IScalable::Make> >&& objects,
				MakeDyn<ISMRSize> value,
				Key key = Key::MouseLeft,
				bool is_horizontal = true,
				sf::Vector2f min_size = {}
			);
			
			auto make(InitInfo init_info) -> BoxSwitcherTabs* override;
		};
		
		BoxSwitcherTabs(Make&& make, InitInfo init_info);
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto get_array_size() const -> size_t override;
		
		auto get_object_at(size_t index) -> IScalable& override;
		
		auto get_object_at(size_t index) const -> IScalable const& override;
		
		auto get_tab(sf::Vector2f position) -> int;
		
	protected:
		BasicInteractiveData<BoxSwitcherTabs&> interactive_;
		std::vector<BoxPtr<IScalable> > objects_;
		bool is_horizontal_;
		ISMRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxSwitcherTabs::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxSwitcherTabs::Make>;
};
