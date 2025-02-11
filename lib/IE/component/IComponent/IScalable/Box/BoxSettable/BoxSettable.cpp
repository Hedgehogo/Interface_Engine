#include "BoxSettable.hpp"
#include "IE/ieml/Indexed/Indexed.hpp"

namespace ie {
	BoxSettable::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		object(std::move(object)), min_size(min_size) {
	}
	
	auto BoxSettable::Make::make(InitInfo init_info) -> BoxSettable* {
		return new BoxSettable{std::move(*this), init_info};
	}
	
	BoxSettable::BoxSettable(Make&& make, InitInfo init_info) :
		BoxSettable(std::move(make.object), make.min_size, init_info) {
	}
	
	BoxSettable::BoxSettable(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size, InitInfo init_info) :
		Box(min_size),
		window_(&init_info.window),
		render_target_(&init_info.render_target),
		dyn_buffer_(&init_info.dyn_buffer),
		text_style_buffer_(init_info.text_style_buffer),
		event_handler_(&init_info.event_handler),
		panel_manager_interceptor_(init_info.panel_manager),
		object_(object->make(
			{
				init_info.window,
				init_info.render_target,
				init_info.dyn_buffer,
				init_info.text_style_buffer,
				init_info.event_handler,
				draw_manager_,
				update_manager_,
				trigger_manager_,
				panel_manager_interceptor_
			}
		)) {
		init_info.draw_manager.add(*this);
		init_info.update_manager.add(*this);
	}
	
	auto BoxSettable::set_object(BoxPtr<IScalable::Make>&& new_object) -> void {
		draw_manager_.clear();
		update_manager_.clear();
		trigger_manager_.clear();
		panel_manager_interceptor_.clear();
		InitInfo init_info{
			*window_,
			*render_target_,
			*dyn_buffer_,
			text_style_buffer_,
			*event_handler_,
			draw_manager_,
			update_manager_,
			trigger_manager_,
			panel_manager_interceptor_,
		};
		object_ = BoxPtr<IScalable>{new_object->make(init_info)};
	}
	
	auto BoxSettable::draw() -> void {
		this->draw_manager_.draw();
	}
	
	auto BoxSettable::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		object_->resize(size, position);
	}
	
	auto BoxSettable::update() -> void {
		this->update_manager_.update();
	}
	
	auto BoxSettable::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxSettable::get_object() const -> IScalable const& {
		return *object_;
	}
}