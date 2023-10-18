#include "BoxSettable.hpp"

namespace ie {
	BoxSettable::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		object(std::move(object)), min_size(min_size) {
	}
	
	BoxSettable* BoxSettable::Make::make(InitInfo init_info) {
		return new BoxSettable{std::move(*this), init_info};
	}
	
	BoxSettable::BoxSettable(Make&& make, InitInfo init_info) :
		BoxSettable(std::move(make.object), make.min_size, init_info) {
	}
	
	BoxSettable::BoxSettable(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size, InitInfo init_info) :
		Box(min_size),
		window(&init_info.window),
		render_target(&init_info.render_target),
		interaction_stack(&init_info.interaction_stack),
		panel_manager_interceptor(init_info.panel_manager),
		object(object->make(
			{
				init_info.window,
				init_info.render_target,
				draw_manager,
				update_manager,
				interaction_manager,
				init_info.interaction_stack,
				panel_manager_interceptor
			}
		)) {
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
	}
	
	BoxSettable::BoxSettable(BoxPtr<IScalable>&& object, sf::Vector2f min_size) : Box(min_size), object(std::move(object)) {
	}
	
	void BoxSettable::init(InitInfo init_info) {
		draw_manager.add(this->draw_manager);
		update_manager.add(this->update_manager);
		
		this->panel_manager_interceptor.init(init_info.panel_manager);
		
		this->window = &init_info.window;
		this->render_target = &init_info.render_target;
		this->interaction_stack = &init_info.interaction_stack;
	}
	
	void BoxSettable::set_object(BoxPtr<IScalable>&& new_object) {
		draw_manager.clear();
		update_manager.clear();
		interaction_manager.clear();
		panel_manager_interceptor.clear();
		InitInfo init_info{*window, *render_target, draw_manager, update_manager, interaction_manager, *interaction_stack, panel_manager_interceptor};
		new_object->init(init_info);
		object = new_object;
	}
	
	void BoxSettable::set_object(BoxPtr<IScalable::Make>&& new_object) {
		draw_manager.clear();
		update_manager.clear();
		interaction_manager.clear();
		panel_manager_interceptor.clear();
		InitInfo init_info{*window, *render_target, draw_manager, update_manager, interaction_manager, *interaction_stack, panel_manager_interceptor};
		object = BoxPtr{new_object->make(init_info)};
	}
	
	void BoxSettable::draw() {
		this->draw_manager.draw();
	}
	
	void BoxSettable::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		object->resize(size, position);
	}
	
	void BoxSettable::update() {
		this->update_manager.update();
	}
	
	IScalable& BoxSettable::get_object() {
		return *object;
	}
	
	const IScalable& BoxSettable::get_object() const {
		return *object;
	}
	
	BoxSettable* BoxSettable::copy() {
		return new BoxSettable{*this};
	}
}