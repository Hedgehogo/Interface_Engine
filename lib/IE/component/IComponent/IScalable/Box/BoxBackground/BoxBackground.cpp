#include "BoxBackground.hpp"

namespace ie {
	BoxBackground::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<INonInteractive::Make>&& background,
		sf::Vector2f offset,
		sf::Vector2f min_size
	) :
		object(std::move(object)), background(std::move(background)), offset(offset), min_size(min_size) {
	}
	
	auto BoxBackground::Make::make(InitInfo init_info) -> BoxBackground* {
		return new BoxBackground{std::move(*this), init_info};
	}
	
	BoxBackground::BoxBackground(Make&& make, InitInfo init_info) :
		Box(make.min_size), background_(make.background->make(init_info)), object_(make.object->make(init_info)), offset_(make.offset) {
	}
	
	auto BoxBackground::set_position(sf::Vector2f position) -> void {
		layout_.set_position(position);
		background_->set_position(position);
		object_->set_position(position);
	}
	
	auto BoxBackground::move(sf::Vector2f offset) -> void {
		layout_.move(offset);
		background_->move(offset);
		object_->move(offset);
	}
	
	auto BoxBackground::set_size(sf::Vector2f size) -> void {
		layout_.set_size(size);
		background_->set_size(size);
		object_->set_size(size);
	}
	
	auto BoxBackground::get_min_size() const -> sf::Vector2f {
		return max(object_->get_min_size() + offset_ * 2.f, background_->get_min_size(), minimum_size_);
	}
	
	auto BoxBackground::get_normal_size() const -> sf::Vector2f {
		return max(object_->get_normal_size() + offset_ * 2.f, background_->get_normal_size());
	}
	
	auto BoxBackground::get_background() -> INonInteractive& {
		return *background_;
	}
	
	auto BoxBackground::get_background() const -> INonInteractive const& {
		return *background_;
	}
	
	auto BoxBackground::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxBackground::get_object() const -> IScalable const& {
		return *object_;
	}
	
	auto BoxBackground::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		background_->resize(size, position);
		object_->resize(size - offset_ * 2.f, position + offset_);
	}
	
	auto BoxBackground::handle_event(Event event) -> bool {
		return object_->handle_event(event);
	}
	
	auto BoxBackground::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxBackground::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxBackground::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxBackground::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("background").except().as<ie::BoxPtr<ie::INonInteractive::Make> >().except(),
		map.get_as<sf::Vector2f>("offset").except().ok_or({}),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({}),
	};
}
