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
		window_(&init_info.window),
		render_target_(&init_info.render_target),
		interaction_stack_(&init_info.interaction_stack),
		panel_manager_interceptor_(init_info.panel_manager),
		object_(object->make(
			{
				init_info.window,
				init_info.render_target,
				draw_manager_,
				update_manager_,
				interaction_manager_,
				init_info.interaction_stack,
				panel_manager_interceptor_
			}
		)) {
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
	}
	
	BoxSettable::BoxSettable(BoxPtr<IScalable>&& object, sf::Vector2f min_size) : Box(min_size), object_(std::move(object)) {
	}
	
	void BoxSettable::init(InitInfo init_info) {
		draw_manager_.add(this->draw_manager_);
		update_manager_.add(this->update_manager_);
		
		this->panel_manager_interceptor_.init(init_info.panel_manager);
		
		this->window_ = &init_info.window;
		this->render_target_ = &init_info.render_target;
		this->interaction_stack_ = &init_info.interaction_stack;
	}
	
	void BoxSettable::set_object(BoxPtr<IScalable>&& new_object) {
		draw_manager_.clear();
		update_manager_.clear();
		interaction_manager_.clear();
		panel_manager_interceptor_.clear();
		InitInfo init_info{*window_, *render_target_, draw_manager_, update_manager_, interaction_manager_, *interaction_stack_, panel_manager_interceptor_};
		new_object->init(init_info);
		object_ = new_object;
	}
	
	void BoxSettable::set_object(BoxPtr<IScalable::Make>&& new_object) {
		draw_manager_.clear();
		update_manager_.clear();
		interaction_manager_.clear();
		panel_manager_interceptor_.clear();
		InitInfo init_info{*window_, *render_target_, draw_manager_, update_manager_, interaction_manager_, *interaction_stack_, panel_manager_interceptor_};
		object_ = BoxPtr{new_object->make(init_info)};
	}
	
	void BoxSettable::draw() {
		this->draw_manager_.draw();
	}
	
	void BoxSettable::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		object_->resize(size, position);
	}
	
	void BoxSettable::update() {
		this->update_manager_.update();
	}
	
	IScalable& BoxSettable::get_object() {
		return *object_;
	}
	
	const IScalable& BoxSettable::get_object() const {
		return *object_;
	}
	
	BoxSettable* BoxSettable::copy() {
		return new BoxSettable{*this};
	}
}