#include "InteractiveTextBlock.hpp"

#include <utility>

namespace ie {
	InteractiveTextBlock::Make::Make(
		BoxPtr<IBaseTrigger::Make>&& trigger,
		sf::String const& text,
		Indexed<TextStyle>&& text_style
	) :
		TextBlock::Make(text, std::move(text_style)),
		trigger(std::move(trigger)) {
	}
	
	auto InteractiveTextBlock::Make::make(TextBockInitInfo init_info) -> InteractiveTextBlock* {
		return new InteractiveTextBlock{std::move(*this), init_info};
	}
	
	InteractiveTextBlock::InteractiveTextBlock(
		Make&& make,
		TextBockInitInfo init_info
	) :
		TextBlock(
			TextBlock::Make{
				make.text,
				std::move(make.text_stile)
			},
			init_info
		),
		trigger_manager_(&init_info.text_trigger_manager),
		trigger_(make.trigger->make({static_cast<InitInfo>(init_info), {}})) {
	}
	
	auto InteractiveTextBlock::update() -> void {
		trigger_->update();
	}
	
	auto InteractiveTextBlock::handle_event(Event event) -> bool {
		return trigger_->handle_event(event);
	}
	
	auto InteractiveTextBlock::in(sf::Vector2f point_position) -> bool {
		for(auto& character: text_characters_) {
			if(character->in(point_position)) {
				return true;
			}
		}
		return false;
	}
}

auto ieml::Decode<char, ie::InteractiveTextBlock::Make>::decode(ieml::Node const& node) -> orl::Option<ie::InteractiveTextBlock::Make> {
	auto map{node.get_map_view().except()};
	return ie::InteractiveTextBlock::Make{
		map.at("trigger").except().as<bp::BoxPtr<ie::IBaseTrigger::Make> >().except(),
		map.at("text").except().as<sf::String>().except(),
		map.at("text_style").except().as<ie::Indexed<ie::TextStyle> >().except()
	};
}
