#include "Switcher.hpp"
#include "IE/interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "SwitherAction/SwitcherAction.hpp"

namespace ie {
	Switcher::Make::Make(BoxPtr<IScalable::Make>&& inactive_background, BoxPtr<IScalable::Make>&& active_background, PSbool value, Key key) :
		inactive_background(std::move(inactive_background)), active_background(std::move(active_background)), value(value), key(key) {
	}
	
	Switcher::Make::Make(BoxPtr<IScalable::Make>&& inactive_background, BoxPtr<IScalable::Make>&& active_background, Key key, bool start_active) :
		inactive_background(std::move(inactive_background)), active_background(std::move(active_background)), value(std::make_shared<Sbool>(start_active)), key(key) {
	}
	
	Switcher* Switcher::Make::make(InitInfo init_info) {
		return new Switcher{std::move(*this), init_info};
	}
	
	Switcher::Switcher(Make&& make, InitInfo init_info) :
		interactive(make_box_ptr<OneKeyInteraction::Make>(make_box_ptr<SwitcherAction::Make>(make.value), make.key), init_info, {}),
		inactive_background(make.inactive_background->make(init_info.copy(inactive_draw_manager))),
		active_background(make.active_background->make(init_info.copy(active_draw_manager))),
		active(make.value) {
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
	}
	
	Switcher::Switcher(BoxPtr<IScalable>&& inactive_background, BoxPtr<IScalable>&& active_background, PSbool value, Key key) :
		interactive(make_box_ptr<OneKeyInteraction>(make_box_ptr<SwitcherAction>(value), key)),
		inactive_background(std::move(inactive_background)), active_background(std::move(active_background)), active(value) {
	}
	
	Switcher::Switcher(BoxPtr<IScalable>&& inactive_background, BoxPtr<IScalable>&& active_background, Key key, bool start_active) :
		Switcher(std::move(inactive_background), std::move(active_background), std::make_shared<Sbool>(start_active), key) {
	}
	
	void Switcher::init(InitInfo init_info) {
		interactive.init(init_info, {});
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
		inactive_background->init(init_info.copy(inactive_draw_manager));
		active_background->init(init_info.copy(active_draw_manager));
	}
	
	void Switcher::set_position(sf::Vector2f position) {
		layout.set_position(position);
		inactive_background->set_position(position);
		active_background->set_position(position);
	}
	
	void Switcher::move(sf::Vector2f position) {
		layout.move(position);
		inactive_background->move(position);
		active_background->move(position);
	}
	
	void Switcher::set_size(sf::Vector2f size) {
		layout.set_size(size);
		inactive_background->set_size(size);
		active_background->set_size(size);
	}
	
	sf::Vector2f Switcher::get_min_size() const {
		return max(active_background->get_min_size(), inactive_background->get_min_size());
	}
	
	sf::Vector2f Switcher::get_normal_size() const {
		return max(active_background->get_normal_size(), inactive_background->get_normal_size());
	}
	
	void Switcher::draw() {
		if(active->get_value()) {
			active_draw_manager.draw();
		} else {
			inactive_draw_manager.draw();
		}
	}
	
	void Switcher::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		active_background->resize(size, position);
		inactive_background->resize(size, position);
	}
	
	void Switcher::update() {
		interactive.update();
	}
	
	bool Switcher::update_interactions(sf::Vector2f mouse_position) {
		bool background_update;
		if(active->get_value()) {
			background_update = active_background->update_interactions(mouse_position);
		} else {
			background_update = inactive_background->update_interactions(mouse_position);
		}
		interactive.update_interactions();
		return background_update;
	}
	
	Switcher* Switcher::copy() {
		return new Switcher{*this};
	}
	
	void Switcher::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		if(active->get_value()) {
			active_background->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		} else {
			inactive_background->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		}
	}
	
	LayoutData& Switcher::layout_get_data() {
		return layout;
	}
	
	const LayoutData& Switcher::layout_get_data() const {
		return layout;
	}
	
	bool DecodePointer<Switcher>::decode_pointer(const YAML::Node& node, Switcher*& switcher) {
		auto inactive_background{node["inactive-background"].as<BoxPtr<IScalable> >()};
		auto active_background{node["active-background"].as<BoxPtr<IScalable> >()};
		Key key{conv_def<Key>(node["key"], Key::MouseLeft)};
		
		if(node["value"]) {
			switcher = new Switcher{
				std::move(inactive_background),
				std::move(active_background),
				Buffer::get<Sbool>(node["value"]),
				key
			};
		} else if(node["state"]) {
			switcher = new Switcher{
				std::move(inactive_background),
				std::move(active_background),
				key,
				convert_bool(node["state"], "active", "inactive")
			};
		} else {
			switcher = new Switcher{
				std::move(inactive_background),
				std::move(active_background),
				key,
				conv_def(node["start-active"], false)
			};
		}
		return true;
	}
}