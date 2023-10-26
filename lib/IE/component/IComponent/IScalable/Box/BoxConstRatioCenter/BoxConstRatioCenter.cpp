#include "BoxConstRatioCenter.hpp"

namespace ie {
	BoxConstRatioCenter::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, float aspect_ratio, sf::Vector2f min_size) :
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
		BoxPtr<IUninteractive::Make>&& background,
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
		background(make.background->make(init_info)),
		object(make.object->make(init_info)),
		first_object(make.first_object->make(init_info.copy(first_draw_manager))),
		second_object(make.second_object->make(init_info.copy(second_draw_manager))),
		aspect_ratio(make.aspect_ratio) {
		init_info.draw_manager.add(*this);
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(
		BoxPtr<IScalable>&& object,
		BoxPtr<IUninteractive>&& background,
		float aspect_ratio,
		sf::Vector2f min_size
	) : Box(min_size), background(std::move(background)), object(std::move(object)), first_object(new Empty), second_object(new Empty), aspect_ratio(aspect_ratio) {
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(
		BoxPtr<IScalable>&& object,
		BoxPtr<IScalable>&& first_object,
		BoxPtr<IScalable>&& second_object,
		BoxPtr<IUninteractive>&& background,
		float aspect_ratio,
		sf::Vector2f min_size
	) : Box(min_size), background(std::move(background)), object(std::move(object)), first_object(std::move(first_object)), second_object(std::move(second_object)), aspect_ratio(aspect_ratio) {
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(const BoxConstRatioCenter& other) :
		Box(other), background(other.background), object(other.object), first_object(other.first_object), second_object(other.second_object), aspect_ratio(other.aspect_ratio) {
	}
	
	void BoxConstRatioCenter::init(InitInfo init_info) {
		background->init(init_info);
		object->init(init_info);
		init_info.draw_manager.add(*this);
		first_object->init(init_info.copy(this->first_draw_manager));
		second_object->init(init_info.copy(this->second_draw_manager));
	}
	
	void BoxConstRatioCenter::set_aspect_ratio(float aspect_ratio) {
		this->aspect_ratio = aspect_ratio;
		this->set_position(layout_.position);
	}
	
	void BoxConstRatioCenter::set_position(sf::Vector2f position) {
		BoxConstRatioCenter::move(position - layout_.position);
	}
	
	void BoxConstRatioCenter::move(sf::Vector2f position) {
		layout_.move(position);
		object->move(position);
		background->move(position);
		first_object->move(position);
		second_object->move(position);
	}
	
	void BoxConstRatioCenter::set_size(sf::Vector2f size) {
		resize(size, layout_.position);
	}
	
	void BoxConstRatioCenter::draw() {
		if(render_first) {
			first_draw_manager.draw();
		}
		if(render_second) {
			second_draw_manager.draw();
		}
	}
	
	void BoxConstRatioCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		
		sf::Vector2f first_min_size{first_object->get_min_size()};
		sf::Vector2f second_min_size{second_object->get_min_size()};
		sf::Vector2f second_position{position};
		sf::Vector2f objects_size{size};
		
		background->resize(size, position);
		float size_aspect_ratio = size.x / size.y;
		if(size_aspect_ratio > aspect_ratio) {
			size.x = size.y * aspect_ratio;
			objects_size.x = (layout_.size.x - size.x) / 2.0f;
			second_position.x += objects_size.x + size.x;
		} else {
			size.y = size.x / aspect_ratio;
			objects_size.y = (layout_.size.y - size.y) / 2.0f;
			second_position.y += objects_size.y + size.y;
		}
		render_first = first_min_size.x < objects_size.x && first_min_size.y < objects_size.y;
		render_second = second_min_size.x < objects_size.x && second_min_size.y < objects_size.y;
		
		object->resize(size, position + (layout_.size - size) / 2.0f);
		
		if(render_first)
			first_object->resize(objects_size, position);
		if(render_second)
			second_object->resize(objects_size, second_position);
	}
	
	bool BoxConstRatioCenter::update_interactions(sf::Vector2f mouse_position) {
		if(object->in_area(mouse_position)) {
			return object->update_interactions(mouse_position);
		}
		if(render_first && first_object->in_area(mouse_position)) {
			return first_object->update_interactions(mouse_position);
		}
		if(render_second && second_object->in_area(mouse_position)) {
			return second_object->update_interactions(mouse_position);
		}
		return background->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstRatioCenter::get_min_size() const {
		sf::Vector2f object_min_size{object->get_min_size()};
		object_min_size = sf::Vector2f{std::max(object_min_size.x, object_min_size.y * aspect_ratio), std::max(object_min_size.y, object_min_size.x / aspect_ratio)};
		return max(object_min_size, background->get_min_size(), minimum_size);
	}
	
	sf::Vector2f BoxConstRatioCenter::get_normal_size() const {
		sf::Vector2f object_normal_size{object->get_normal_size()};
		object_normal_size = sf::Vector2f{std::max(object_normal_size.x, object_normal_size.y * aspect_ratio), std::max(object_normal_size.y, object_normal_size.x / aspect_ratio)};
		return max(object_normal_size, background->get_normal_size());
	}
	
	IUninteractive& BoxConstRatioCenter::get_background() {
		return *background;
	}
	
	const IUninteractive& BoxConstRatioCenter::get_background() const {
		return *background;
	}
	
	IScalable& BoxConstRatioCenter::get_object() {
		return *object;
	}
	
	const IScalable& BoxConstRatioCenter::get_object() const {
		return *object;
	}
	
	IScalable& BoxConstRatioCenter::get_first_object() {
		return *first_object;
	}
	
	const IScalable& BoxConstRatioCenter::get_first_object() const {
		return *first_object;
	}
	
	IScalable& BoxConstRatioCenter::get_second_object() {
		return *second_object;
	}
	
	const IScalable& BoxConstRatioCenter::get_second_object() const {
		return *second_object;
	}
	
	BoxConstRatioCenter* BoxConstRatioCenter::copy() {
		return new BoxConstRatioCenter{*this};
	}
	
	void BoxConstRatioCenter::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		background->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		first_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
	
	bool DecodePointer<BoxConstRatioCenter>::decode_pointer(const YAML::Node& node, BoxConstRatioCenter*& box_with_const_ratio_center) {
		box_with_const_ratio_center = new BoxConstRatioCenter{
			node["object"].as<BoxPtr<IScalable> >(),
			BoxPtr{conv_def_ptr<IScalable, Empty>(node["first-object"])},
			BoxPtr{conv_def_ptr<IScalable, Empty>(node["second-object"])},
			BoxPtr{conv_def_ptr<IUninteractive, Empty>(node["background"])},
			node["aspect-ratio"].as<float>(),
			node["min-size"].as<sf::Vector2f>(),
		};
		return true;
	}
}
