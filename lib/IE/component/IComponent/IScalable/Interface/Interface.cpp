#include "Interface.hpp"

#include <cmath>
#include <IEML/parser.hpp>
#include "IE/modules/load_modules.hpp"
#include "../Box/BoxModulesLoader/BoxModulesLoader.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"

namespace ie {
	Interface::Make::Make(BoxPtr<IScalable::Make>&& object) :
		object(std::move(object)) {
	}
	
	auto Interface::Make::make(InitInfo init_info) -> Interface* {
		return new Interface{std::move(*this), init_info};
	}
	
	Interface::Interface(Make&& make, InitInfo init_info) :
		window_(&init_info.window),
		render_target_(&init_info.render_target),
		object_(make.object->make(
			{
				init_info.window,
				init_info.render_target,
				init_info.dyn_buffer,
				init_info.text_style_buffer,
				init_info.event_handler,
				this->draw_manager_,
				this->update_manager_,
				this->interaction_manager_,
				this->panel_manager_
			}
		)),
		active_(true) {
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
	}
	
	Interface::Interface(
		sf::RenderWindow& window,
		DynBuffer& dyn_buffer,
		absl::flat_hash_set<bp::BoxPtr<Indexed<TextStyle> > >& text_style_buffer,
		EventHandler& event_handler,
		BoxPtr<IScalable::Make>&& object
	) :
		window_(&window),
		render_target_(&window),
		object_(object->make(
			{
				window,
				window,
				dyn_buffer,
				text_style_buffer,
				event_handler,
				this->draw_manager_,
				this->update_manager_,
				this->interaction_manager_,
				this->panel_manager_
			}
		)),
		active_(true) {
	}
	
	auto Interface::is_in_window(sf::Vector2f position) -> bool {
		return
			position.x > 0 && position.x < static_cast<float>(render_target_->getSize().x) &&
			position.y > 0 && position.y < static_cast<float>(render_target_->getSize().y);
	}
	
	auto Interface::get_render_target() -> sf::RenderTarget& {
		return *render_target_;
	}
	
	auto Interface::get_draw_manager() -> DrawManager& {
		return draw_manager_;
	}
	
	auto Interface::get_update_manager() -> UpdateManager& {
		return update_manager_;
	}
	
	auto Interface::get_interaction_manager() -> InteractionManager& {
		return interaction_manager_;
	}
	
	auto Interface::get_panel_manager() -> PanelManager& {
		return panel_manager_;
	}
	
	auto Interface::get_object() -> IScalable& {
		return *object_;
	}
	
	auto Interface::draw() -> void {
		draw_manager_.draw();
		panel_manager_.draw();
	}
	
	auto Interface::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		object_->resize(size, position);
	}
	
	auto Interface::get_area_position() const -> sf::Vector2f {
		return object_->get_area_position();
	}
	
	auto Interface::get_area_size() const -> sf::Vector2f {
		return object_->get_area_size();
	}
	
	auto Interface::get_min_size() const -> sf::Vector2f {
		return object_->get_min_size();
	}
	
	auto Interface::get_normal_size() const -> sf::Vector2f {
		return object_->get_normal_size();
	}
	
	auto Interface::update() -> void {
		panel_manager_.update();
		update_manager_.update();
		active_ = false;
	}
	
	auto Interface::update(std::vector<Event> const& events, bool active) -> void {
		if(active) {
			for(auto& event: events) {
				this->handle_event(event);
			}
		}
		this->update();
	}
	
	auto Interface::handle_event(Event event) -> bool {
		active_ = true;
		for(auto pointer: event.pointer()) {
			if(pointer.id == std::numeric_limits<size_t>::max()) {
				mouse_position_ = sf::Vector2f{pointer.position};
			}
		}
		if(is_in_window(mouse_position_)) {
			if(!interaction_manager_.handle_event(event) && !panel_manager_.handle_event(event, true)) {
				object_->handle_event(event);
			}
		}
		return true;
	}
	
	auto Interface::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
	
	auto Interface::set_render_window_size(sf::RenderWindow& window) -> void {
		auto new_window_size{ie::max(get_normal_size(), sf::Vector2f(window.getSize()))};
		auto window_size{sf::Vector2u{sf::Vector2f{std::ceil(new_window_size.x), std::ceil(new_window_size.y)}}};
		window.setSize(window_size);
		set_size(sf::Vector2f(window_size));
	}
	
	auto make_interface(std::filesystem::path file_path, int argc, char* argv[]) -> Interface::Make {
		auto node{ieml::from_file(file_path)};
		auto object{bp::make_box_ptr<BoxModulesLoader::Make>(node.as<BoxModulesLoader::Make>().except())};
		return Interface::Make{std::move(object)};
	}
	
	auto make_interface(
		sf::RenderWindow& window,
		DynBuffer& dyn_buffer,
		absl::flat_hash_set<bp::BoxPtr<Indexed<TextStyle> > >& text_style_buffer,
		EventHandler& event_handler,
		std::filesystem::path file_path,
		int argc,
		char* argv[]
	) -> Interface {
		auto node{ieml::from_file(file_path)};
		auto object{bp::make_box_ptr<BoxModulesLoader::Make>(node.as<BoxModulesLoader::Make>().except())};
		return Interface{window, dyn_buffer, text_style_buffer, event_handler, std::move(object)};
	}
}

auto ieml::Decode<char, ie::Interface::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Interface::Make> {
	auto map{node.get_map_view().except()};
	return {{map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except()}};
}
