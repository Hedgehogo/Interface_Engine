#include "Interface.hpp"

#include <cmath>
#include "IE/modules/yaml-cpp/modules/load_modules.hpp"
#include "IE/window/Window/Window.hpp"

namespace ie {
	Interface::Make::Make(BoxPtr<IScalable::Make>&& object, AnimationManager animation_manager, BoxPtr<InteractionStack>&& interaction_stack) :
		object(std::move(object)), animation_manager(std::move(animation_manager)), interaction_stack(std::move(interaction_stack)) {
	}
	
	Interface* Interface::Make::make(InitInfo init_info) {
		return new Interface{std::move(*this), init_info};
	}
	Interface::Interface(Make&& make, InitInfo init_info) :
		window_(&init_info.window),
		render_target_(&init_info.render_target),
		interaction_stack_(std::move(make.interaction_stack)),
		animation_manager_(std::move(make.animation_manager)),
		object_(make.object->make(
			{
				init_info.window,
				init_info.render_target,
				this->draw_manager_,
				this->update_manager_,
				this->interaction_manager_,
				*this->interaction_stack_,
				this->panel_manager_
			}
		)),
		initialized_(true),
		active_(true) {
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
	}
	
	Interface::Interface(BoxPtr<IScalable>&& object, AnimationManager animation_manager, BoxPtr<InteractionStack>&& interaction_stack) :
		render_target_(nullptr),
		interaction_stack_(interaction_stack),
		animation_manager_(std::move(animation_manager)),
		object_(std::move(object)),
		initialized_(false), active_(true) {
	}
	
	Interface::Interface(const std::string& file_path, AnimationManager animation_manager, BoxPtr<InteractionStack>&& interaction_stack) :
		Interface(BoxPtr{ie::load_from_yaml<ie::IScalable>(file_path)}, animation_manager, std::move(interaction_stack)) {
	}
	
	Interface::Interface(sf::RenderWindow& window, BoxPtr<IScalable>&& object, AnimationManager animation_manager, BoxPtr<InteractionStack>&& interaction_stack) :
		Interface(std::move(object), animation_manager, std::move(interaction_stack)) {
		init(window);
	}
	
	Interface::Interface(sf::RenderWindow& window, const std::string& file_path, AnimationManager animation_manager, BoxPtr<InteractionStack>&& interaction_stack) :
		Interface(window, BoxPtr{ie::load_from_yaml<ie::IScalable>(file_path)}, animation_manager, std::move(interaction_stack)) {
	}
	
	Interface::Interface(sf::RenderWindow& window, BoxPtr<IScalable::Make>&& object, AnimationManager animation_manager, BoxPtr<InteractionStack>&& interaction_stack) :
		window_(&window),
		render_target_(&window),
		interaction_stack_(std::move(interaction_stack)),
		animation_manager_(std::move(animation_manager)),
		object_(object->make(
			{
				window,
				window,
				this->draw_manager_,
				this->update_manager_,
				this->interaction_manager_,
				*this->interaction_stack_,
				this->panel_manager_
			}
		)),
		initialized_(true),
		active_(true) {
	}
	
	bool Interface::is_in_window(sf::Vector2f position) {
		return position.x > 0 && position.x < static_cast<float>(render_target_->getSize().x) && position.y > 0 && position.y < static_cast<float>(render_target_->getSize().y);
	}
	
	void Interface::init(InitInfo init_info) {
		if(!initialized_) {
			this->window_ = &init_info.window;
			this->render_target_ = &init_info.render_target;
			init_info.draw_manager.add(*this);
			init_info.update_manager.add(*this);
			InitInfo new_init_info{init_info.window, init_info.render_target, this->draw_manager_, this->update_manager_, this->interaction_manager_, *this->interaction_stack_, this->panel_manager_};
			object_->init(new_init_info);
			initialized_ = true;
		}
	}
	
	void Interface::init(sf::RenderWindow& window) {
		if(!initialized_) {
			this->window_ = &window;
			this->render_target_ = &window;
			InitInfo init_info{window, window, draw_manager_, update_manager_, interaction_manager_, *interaction_stack_, panel_manager_};
			object_->init(init_info);
			sf::Vector2f size(max(static_cast<sf::Vector2f>(static_cast<sf::RenderWindow&>(window).getSize()), object_->get_min_size()));
			resize(size, sf::Vector2f(0, 0));
			initialized_ = true;
		}
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
	
	InteractionStack& Interface::get_interaction_stack() {
		return *interaction_stack_;
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
	
	Interface* Interface::copy() {
		Interface* interface{new Interface{*this}};
		interface->init(*window_);
		return interface;
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
	
	bool DecodePointer<Interface>::decode_pointer(const YAML::Node& node, Interface*& interface) {
		interface = new Interface{
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["animation-manager"], AnimationManager{}),
			BoxPtr{conv_def_ptr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
		return true;
	}
	
	Interface make_interface(const std::filesystem::path& file_path, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{file_path}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			load_modules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(file_path.string())};
		
		return Interface{
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["animation-manager"], AnimationManager{}),
			BoxPtr{conv_def_ptr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
	}
	
	Interface make_interface(sf::RenderWindow& window, const std::filesystem::path& file_path, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{file_path}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			load_modules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(file_path.string())};
		
		return Interface{
			window,
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["animation-manager"], AnimationManager{}),
			BoxPtr{conv_def_ptr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
	}
	
	Interface* make_prt_interface(sf::RenderWindow& window, const std::filesystem::path& file_path, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{file_path}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			load_modules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(file_path.string())};
		
		return new Interface{
			window,
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["animation-manager"], AnimationManager{}),
			BoxPtr{conv_def_ptr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
	}
}