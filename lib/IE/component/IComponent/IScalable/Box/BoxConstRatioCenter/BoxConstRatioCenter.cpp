#include "BoxConstRatioCenter.hpp"

namespace ie {
	BoxConstRatioCenter::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<INonInteractive::Make>&& background,
		float aspect_ratio,
		sf::Vector2f min_size
	) :
		object(std::move(object)),
		first_object(new Empty::Make),
		second_object(new Empty::Make),
		background(std::move(background)),
		aspect_ratio(aspect_ratio),
		min_size(min_size) {
	}
	
	BoxConstRatioCenter::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		BoxPtr<INonInteractive::Make>&& background,
		float aspect_ratio,
		sf::Vector2f min_size
	) :
		object(std::move(object)),
		first_object(std::move(first_object)),
		second_object(std::move(second_object)),
		background(std::move(background)),
		aspect_ratio(aspect_ratio),
		min_size(min_size) {
	}
	
	BoxConstRatioCenter* BoxConstRatioCenter::Make::make(InitInfo init_info) {
		return new BoxConstRatioCenter{std::move(*this), init_info};
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		background_(make.background->make(init_info)),
		object_(make.object->make(init_info)),
		first_object_(make.first_object->make(init_info.copy(first_draw_manager_))),
		second_object_(make.second_object->make(init_info.copy(second_draw_manager_))),
		aspect_ratio_(make.aspect_ratio) {
		init_info.draw_manager.add(*this);
	}
	
	void BoxConstRatioCenter::set_aspect_ratio(float aspect_ratio) {
		this->aspect_ratio_ = aspect_ratio;
		this->set_position(layout_.position);
	}
	
	void BoxConstRatioCenter::set_position(sf::Vector2f position) {
		BoxConstRatioCenter::move(position - layout_.position);
	}
	
	void BoxConstRatioCenter::move(sf::Vector2f position) {
		layout_.move(position);
		object_->move(position);
		background_->move(position);
		first_object_->move(position);
		second_object_->move(position);
	}
	
	void BoxConstRatioCenter::set_size(sf::Vector2f size) {
		resize(size, layout_.position);
	}
	
	void BoxConstRatioCenter::draw() {
		if(render_first_) {
			first_draw_manager_.draw();
		}
		if(render_second_) {
			second_draw_manager_.draw();
		}
	}
	
	void BoxConstRatioCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		
		sf::Vector2f first_min_size{first_object_->get_min_size()};
		sf::Vector2f second_min_size{second_object_->get_min_size()};
		sf::Vector2f second_position{position};
		sf::Vector2f objects_size{size};
		
		background_->resize(size, position);
		float size_aspect_ratio = size.x / size.y;
		if(size_aspect_ratio > aspect_ratio_) {
			size.x = size.y * aspect_ratio_;
			objects_size.x = (layout_.size.x - size.x) / 2.0f;
			second_position.x += objects_size.x + size.x;
		} else {
			size.y = size.x / aspect_ratio_;
			objects_size.y = (layout_.size.y - size.y) / 2.0f;
			second_position.y += objects_size.y + size.y;
		}
		render_first_ = first_min_size.x < objects_size.x && first_min_size.y < objects_size.y;
		render_second_ = second_min_size.x < objects_size.x && second_min_size.y < objects_size.y;
		
		object_->resize(size, position + (layout_.size - size) / 2.0f);
		
		if(render_first_)
			first_object_->resize(objects_size, position);
		if(render_second_)
			second_object_->resize(objects_size, second_position);
	}
	
	bool BoxConstRatioCenter::update_interactions(sf::Vector2f mouse_position) {
		if(object_->in_area(mouse_position)) {
			return object_->update_interactions(mouse_position);
		}
		if(render_first_ && first_object_->in_area(mouse_position)) {
			return first_object_->update_interactions(mouse_position);
		}
		if(render_second_ && second_object_->in_area(mouse_position)) {
			return second_object_->update_interactions(mouse_position);
		}
		return background_->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstRatioCenter::get_min_size() const {
		sf::Vector2f object_min_size{object_->get_min_size()};
		object_min_size = sf::Vector2f{std::max(object_min_size.x, object_min_size.y * aspect_ratio_),
									   std::max(object_min_size.y, object_min_size.x / aspect_ratio_)};
		return max(object_min_size, background_->get_min_size(), minimum_size_);
	}
	
	sf::Vector2f BoxConstRatioCenter::get_normal_size() const {
		sf::Vector2f object_normal_size{object_->get_normal_size()};
		object_normal_size = sf::Vector2f{std::max(object_normal_size.x, object_normal_size.y * aspect_ratio_),
										  std::max(object_normal_size.y, object_normal_size.x / aspect_ratio_)};
		return max(object_normal_size, background_->get_normal_size());
	}
	
	INonInteractive& BoxConstRatioCenter::get_background() {
		return *background_;
	}
	
	const INonInteractive& BoxConstRatioCenter::get_background() const {
		return *background_;
	}
	
	IScalable& BoxConstRatioCenter::get_object() {
		return *object_;
	}
	
	const IScalable& BoxConstRatioCenter::get_object() const {
		return *object_;
	}
	
	IScalable& BoxConstRatioCenter::get_first_object() {
		return *first_object_;
	}
	
	const IScalable& BoxConstRatioCenter::get_first_object() const {
		return *first_object_;
	}
	
	IScalable& BoxConstRatioCenter::get_second_object() {
		return *second_object_;
	}
	
	const IScalable& BoxConstRatioCenter::get_second_object() const {
		return *second_object_;
	}
	
	void BoxConstRatioCenter::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		first_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}

orl::Option<ie::BoxConstRatioCenter::Make> ieml::Decode<char, ie::BoxConstRatioCenter::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxConstRatioCenter::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<ie::BoxPtr<ie::IScalable::Make> >("first-object").except().ok_or_else([] {
			return ie::make_box_ptr<ie::IScalable::Make, ie::Empty::Make>();
		}),
		map.get_as<ie::BoxPtr<ie::IScalable::Make> >("second-object").except().ok_or_else([] {
			return ie::make_box_ptr<ie::IScalable::Make, ie::Empty::Make>();
		}),
		map.get_as<ie::BoxPtr<ie::INonInteractive::Make> >("background").except().ok_or_else([] {
			return ie::make_box_ptr<ie::INonInteractive::Make, ie::Empty::Make>();
		}),
		map.at("aspect-ratio").except().as<float>().except(),
		map.at("min-size").except().as<sf::Vector2f>().except(),
	};
}
