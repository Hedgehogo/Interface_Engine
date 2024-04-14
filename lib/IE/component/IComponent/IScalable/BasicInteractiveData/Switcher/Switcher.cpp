#include "Switcher.hpp"
#include "IE/interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "SwitherAction/SwitcherAction.hpp"

namespace ie {
	Switcher::Make::Make(
		BoxPtr<IScalable::Make>&& inactive_background,
		BoxPtr<IScalable::Make>&& active_background,
		MakeDyn<ISMBool> value,
		Key key
	) :
		inactive_background(std::move(inactive_background)),
		active_background(std::move(active_background)),
		value(std::move(value)),
		key(key) {
	}
	
	auto Switcher::Make::make(InitInfo init_info) -> Switcher* {
		return new Switcher{std::move(*this), init_info};
	}
	
	Switcher::Switcher(Make&& make, InitInfo init_info) :
		Switcher(
			std::move(make.inactive_background),
			std::move(make.active_background),
			make.value.make({init_info.dyn_buffer, init_info.update_manager}),
			make.key,
			init_info
		) {
	}
	
	Switcher::Switcher(
		BoxPtr<IScalable::Make> inactive_background,
		BoxPtr<IScalable::Make> active_background,
		ISMBool& value,
		Key key,
		InitInfo init_info
	) :
		interactive_(make_box_ptr<OneKeyInteraction::Make>(make_box_ptr<SwitcherAction::Make>(value), key), init_info, {}),
		inactive_background_(inactive_background->make(init_info.copy(inactive_draw_manager_))),
		active_background_(active_background->make(init_info.copy(active_draw_manager_))),
		active_(value) {
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
	}
	
	auto Switcher::set_position(sf::Vector2f position) -> void {
		layout_.set_position(position);
		inactive_background_->set_position(position);
		active_background_->set_position(position);
	}
	
	auto Switcher::move(sf::Vector2f offset) -> void {
		layout_.move(offset);
		inactive_background_->move(offset);
		active_background_->move(offset);
	}
	
	auto Switcher::set_size(sf::Vector2f size) -> void {
		layout_.set_size(size);
		inactive_background_->set_size(size);
		active_background_->set_size(size);
	}
	
	auto Switcher::get_min_size() const -> sf::Vector2f {
		return max(active_background_->get_min_size(), inactive_background_->get_min_size());
	}
	
	auto Switcher::get_normal_size() const -> sf::Vector2f {
		return max(active_background_->get_normal_size(), inactive_background_->get_normal_size());
	}
	
	auto Switcher::draw() -> void {
		if(active_.get()) {
			active_draw_manager_.draw();
		} else {
			inactive_draw_manager_.draw();
		}
	}
	
	auto Switcher::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		active_background_->resize(size, position);
		inactive_background_->resize(size, position);
	}
	
	auto Switcher::update() -> void {
		interactive_.update();
	}
	
	auto Switcher::handle_event(Event event) -> bool {
		auto updated{
			active_.get() ?
			active_background_->handle_event(event) :
			inactive_background_->handle_event(event)
		};
		interactive_.handle_event();
		return updated;
	}
	
	auto Switcher::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		if(active_.get()) {
			active_background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		} else {
			inactive_background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		}
	}
	
	auto Switcher::layout_get_data() -> LayoutData& {
		return layout_;
	}
	
	auto Switcher::layout_get_data() const -> LayoutData const& {
		return layout_;
	}
}

auto ieml::Decode<char, ie::Switcher::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Switcher::Make> {
	auto map{node.get_map_view().except()};
	return ie::Switcher::Make{
		map.at("inactive-background").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("active-background").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("value").except().as<ie::MakeDyn<ie::ISMBool> >().except(),
		map.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
	};
}