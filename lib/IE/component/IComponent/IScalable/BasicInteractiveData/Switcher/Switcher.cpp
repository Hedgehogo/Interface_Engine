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
	
	Switcher* Switcher::Make::make(InitInfo init_info) {
		return new Switcher{std::move(*this), init_info};
	}
	
	Switcher::Switcher(Make&& make, InitInfo init_info) :
		Switcher(
			std::move(make.inactive_background),
			std::move(make.active_background),
			make.value.make(init_info.dyn_buffer),
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
	
	void Switcher::set_position(sf::Vector2f position) {
		layout_.set_position(position);
		inactive_background_->set_position(position);
		active_background_->set_position(position);
	}
	
	void Switcher::move(sf::Vector2f position) {
		layout_.move(position);
		inactive_background_->move(position);
		active_background_->move(position);
	}
	
	void Switcher::set_size(sf::Vector2f size) {
		layout_.set_size(size);
		inactive_background_->set_size(size);
		active_background_->set_size(size);
	}
	
	sf::Vector2f Switcher::get_min_size() const {
		return max(active_background_->get_min_size(), inactive_background_->get_min_size());
	}
	
	sf::Vector2f Switcher::get_normal_size() const {
		return max(active_background_->get_normal_size(), inactive_background_->get_normal_size());
	}
	
	void Switcher::draw() {
		if(active_.get()) {
			active_draw_manager_.draw();
		} else {
			inactive_draw_manager_.draw();
		}
	}
	
	void Switcher::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		active_background_->resize(size, position);
		inactive_background_->resize(size, position);
	}
	
	void Switcher::update() {
		interactive_.update();
	}
	
	bool Switcher::update_interactions(sf::Vector2f mouse_position) {
		bool background_update;
		if(active_.get()) {
			background_update = active_background_->update_interactions(mouse_position);
		} else {
			background_update = inactive_background_->update_interactions(mouse_position);
		}
		interactive_.update_interactions();
		return background_update;
	}
	
	void Switcher::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		if(active_.get()) {
			active_background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		} else {
			inactive_background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		}
	}
	
	LayoutData& Switcher::layout_get_data() {
		return layout_;
	}
	
	const LayoutData& Switcher::layout_get_data() const {
		return layout_;
	}
}

orl::Option<ie::Switcher::Make> ieml::Decode<char, ie::Switcher::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::Switcher::Make{
		map.at("inactive-background").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("active-background").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("value").except().as<ie::MakeDyn<ie::ISMBool> >().move_except(),
		map.get_as<ie::Key>("key").ok_or(ie::Key::MouseLeft),
	};
}