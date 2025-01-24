#include "BoxRenderTexture.hpp"

namespace ie {
	BoxRenderTexture::Make::Make(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f min_size) :
		object(std::move(object)), optimize(optimize), min_size(min_size) {
	}
	
	auto BoxRenderTexture::Make::make(InitInfo init_info) -> BoxRenderTexture* {
		return new BoxRenderTexture{std::move(*this), init_info};
	}
	
	BoxRenderTexture::BoxRenderTexture(Make&& make, InitInfo init_info) :
		BoxRenderTexture(std::move(make.object), make.optimize, make.min_size, init_info) {
	}
	
	BoxRenderTexture::BoxRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f min_size, InitInfo init_info) :
		Box(min_size),
		sprite_(render_texture_.getTexture()),
		object_(object->make(init_info.copy(render_texture_).copy(draw_manager_))),
		trigger_manager_(&init_info.trigger_manager),
		render_target_(&init_info.render_target),
		optimize_(optimize),
		active_(true) {
		init_info.draw_manager.add(*this);
	}
	
	auto BoxRenderTexture::draw() -> void {
		if(!optimize_ || active_ || trigger_manager_->is_blocked()) {
			render_texture_.clear(sf::Color(0, 0, 0, 0));
			draw_manager_.draw();
			render_texture_.display();
			active_ = false;
		}
		render_target_->draw(sprite_);
	}
	
	auto BoxRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		IComponentObject::resize(size, position);
		auto start{sf::Vector2f{std::floor(position.x), std::ceil(position.y)}};
		auto end{sf::Vector2f{std::floor(position.x + size.x), std::ceil(position.y + size.y)}};
		auto texture_size{sf::Vector2i{end - start}};
		
		view_.reset({start, end - start});
		
		render_texture_.create(texture_size.x, texture_size.y);
		render_texture_.setView(view_);
		
		sprite_.setTexture(render_texture_.getTexture());
		sprite_.setTextureRect({{0, 0}, texture_size});
		sprite_.setPosition(start);
		
		active_ = true;
	}
	
	auto BoxRenderTexture::handle_event(Event event) -> bool {
		if(object_->handle_event(event)) {
			active_ = true;
			return true;
		}
		return false;
	}
	
	auto BoxRenderTexture::get_min_size() const -> sf::Vector2f {
		return max(object_->get_min_size(), minimum_size_, sf::Vector2f{1, 1});
	}
	
	auto BoxRenderTexture::get_normal_size() const -> sf::Vector2f {
		return max(object_->get_normal_size(), minimum_size_, sf::Vector2f{1, 1});
	}
	
	auto BoxRenderTexture::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxRenderTexture::get_object() const -> IScalable const& {
		return *object_;
	}
	
	auto BoxRenderTexture::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxRenderTexture::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxRenderTexture::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxRenderTexture::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<bool>("optimize").except().ok_or(true),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
