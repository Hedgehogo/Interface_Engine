#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/shared/SReader/SReader.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"
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
			
			auto make(InitInfo init_info) -> BoxTabs* override;
		};
		
		BoxTabs(Make&& make, InitInfo init_info);
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f offset) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto draw() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto get_array_size() const -> size_t override;
		
		auto get_object_at(size_t index) -> IScalable& override;
		
		auto get_object_at(size_t index) const -> IScalable const& override;
		
	protected:
		std::vector<DrawManager> draw_managers_;
		std::vector<BoxPtr<IScalable> > objects_;
		ISRSize& value_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxTabs::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxTabs::Make>;
};
