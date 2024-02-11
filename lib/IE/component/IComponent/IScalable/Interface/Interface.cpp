#include "Interface.hpp"

#include <cmath>
#include <IEML/parser.hpp>
#include "IE/modules/yaml-cpp/modules/load_modules.hpp"

namespace ie {
	Interface::Make::Make(BoxPtr<IScalable::Make>&& object, AnimationManager animation_manager) :
		object(std::move(object)), animation_manager(std::move(animation_manager)) {
	}
	
	Interface* Interface::Make::make(InitInfo init_info) {
		return new Interface{std::move(*this), init_info};
	}
	
	Interface::Interface(Make&& make, InitInfo init_info) :
		window_(&init_info.window),
		render_target_(&init_info.render_target),
		animation_manager_(std::move(make.animation_manager)),
		object_(make.object->make(
			{
				init_info.window,
				init_info.render_target,
				init_info.dyn_buffer,
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
		BoxPtr<IScalable::Make>&& object,
		AnimationManager animation_manager
	) :
		window_(&window),
		render_target_(&window),
		animation_manager_(std::move(animation_manager)),
		object_(object->make(
			{
				window,
				window,
				dyn_buffer,
				this->draw_manager_,
				this->update_manager_,
				this->interaction_manager_,
				this->panel_manager_
			}
		)),
		active_(true) {
	}
	
	bool Interface::is_in_window(sf::Vector2f position) {
		return
			position.x > 0 && position.x < static_cast<float>(render_target_->getSize().x) &&
			position.y > 0 && position.y < static_cast<float>(render_target_->getSize().y);
	}
	
	sf::RenderTarget& Interface::get_render_target() {
		return *render_target_;
	}
	
	DrawManager& Interface::get_draw_manager() {
		return draw_manager_;
	}
	
	UpdateManager& Interface::get_update_manager() {
		return update_manager_;
	}
	
	InteractionManager& Interface::get_interaction_manager() {
		return interaction_manager_;
	}
	
	PanelManager& Interface::get_panel_manager() {
		return panel_manager_;
	}
	
	IScalable& Interface::get_object() {
		return *object_;
	}
	
	void Interface::draw() {
		draw_manager_.draw();
		panel_manager_.draw();
	}
	
	void Interface::resize(sf::Vector2f size, sf::Vector2f position) {
		object_->resize(size, position);
	}
	
	sf::Vector2f Interface::get_area_position() const {
		return object_->get_area_position();
	}
	
	sf::Vector2f Interface::get_area_size() const {
		return object_->get_area_size();
	}
	
	sf::Vector2f Interface::get_min_size() const {
		return object_->get_min_size();
	}
	
	sf::Vector2f Interface::get_normal_size() const {
		return object_->get_normal_size();
	}
	
	void Interface::update_cluster(sf::Vector2f mouse_position) {
		interaction_manager_.update(sf::Vector2i(mouse_position));
	}
	
	void Interface::update() {
		animation_manager_.update();
		panel_manager_.update();
		update_manager_.update();
		update_cluster(mouse_position_);
		active_ = false;
	}
	
	void Interface::update(sf::Vector2f mouse_position, bool active) {
		if(active) {
			this->update_interactions(mouse_position);
		} else {
			this->mouse_position_ = mouse_position;
		}
		this->update();
	}
	
	bool Interface::update_interactions(sf::Vector2f mouse_position) {
		active_ = true;
		this->mouse_position_ = mouse_position;
		if(is_in_window(mouse_position) && !interaction_manager_.is_blocked()) {
			if(!panel_manager_.update_interactions(mouse_position, true)) {
				object_->update_interactions(mouse_position);
			}
		}
		return true;
	}
	
	void Interface::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
	
	void Interface::set_render_window_size(sf::RenderWindow& window) {
		auto new_window_size{ie::max(get_normal_size(), sf::Vector2f(window.getSize()))};
		sf::Vector2u window_size = {static_cast<unsigned>(std::ceil(new_window_size.x)), static_cast<unsigned>(std::ceil(new_window_size.y))};
		window.setSize(window_size);
		set_size(sf::Vector2f(window_size));
	}
	
	Interface::Make make_interface(std::filesystem::path file_path, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{file_path}.replace_filename("modules.ieml"); std::filesystem::exists(modules)) {
			load_modules(argc, argv, modules);
		}
		
		auto node{ieml::from_file(file_path)};
		auto map{node.get_map_view().except()};
		auto object{map.at("object").except().as<BoxPtr<IScalable::Make> >().except()};
		return Interface::Make{std::move(object)};
	}
	
	Interface make_interface(sf::RenderWindow& window, DynBuffer& dyn_buffer, std::filesystem::path file_path, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{file_path}.replace_filename("modules.yaml"); std::filesystem::exists(modules)) {
			load_modules(argc, argv, modules);
		}
		
		auto node{ieml::from_file(file_path)};
		auto map{node.get_map_view().except()};
		auto object{map.at("object").except().as<BoxPtr<IScalable::Make> >().except()};
		return Interface{window, dyn_buffer, std::move(object)};
	}
}

orl::Option<ie::Interface::Make> ieml::Decode<char, ie::Interface::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::Interface::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except()
	};
}
