#include "BoxConstRatio.hpp"

namespace ie {
	BoxConstRatio::Make::Make(
		BoxPtr<IScalable::Make>&& const_object,
		BoxPtr<IScalable::Make>&& second_object,
		BoxPtr<IUninteractive::Make>&& background,
		float aspect_ratio,
		Corner corner,
		sf::Vector2f min_size
	) :
		const_object(std::move(const_object)),
		second_object(std::move(second_object)),
		background(std::move(background)),
		aspect_ratio(aspect_ratio),
		corner(corner),
		min_size(min_size) {
	}
	
	BoxConstRatio* BoxConstRatio::Make::make(InitInfo init_info) {
		return new BoxConstRatio{std::move(*this), init_info};
	}
	
	BoxConstRatio::BoxConstRatio(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		background(make.background->make(init_info)),
		const_object(make.const_object->make(init_info)),
		second_object(make.second_object->make(init_info.copy(second_draw_manager))),
		vertical_side(make.corner == Corner::UpLeft || make.corner == Corner::UpRight),
		horizontal_side(make.corner == Corner::UpLeft || make.corner == Corner::DownLeft),
		render_second(true),
		aspect_ratio(make.aspect_ratio) {
		init_info.draw_manager.add(*this);
	}
	
	BoxConstRatio::BoxConstRatio(
		BoxPtr<IScalable>&& const_object,
		BoxPtr<IScalable>&& second_object,
		BoxPtr<IUninteractive>&& background,
		float aspect_ratio,
		Corner corner,
		sf::Vector2f min_size
	) :
		Box(min_size),
		background(std::move(background)),
		const_object(std::move(const_object)),
		second_object(std::move(second_object)),
		vertical_side(corner == Corner::UpLeft || corner == Corner::UpRight),
		horizontal_side(corner == Corner::UpLeft || corner == Corner::DownLeft),
		render_second(true),
		aspect_ratio(aspect_ratio) {
	}
	
	BoxConstRatio::BoxConstRatio(const BoxConstRatio& other) :
		Box(other), background(other.background), const_object(other.const_object), second_object(other.second_object),
		vertical_side(other.vertical_side), horizontal_side(other.horizontal_side), render_second(other.render_second), aspect_ratio(other.aspect_ratio) {
	}
	
	void BoxConstRatio::init(InitInfo init_info) {
		init_info.draw_manager.add(*this);
		background->init(init_info);
		const_object->init(init_info);
		second_object->init(init_info.copy(second_draw_manager));
	}
	
	Corner BoxConstRatio::get_corner() {
		if(vertical_side) {
			if(horizontal_side) {
				return Corner::UpLeft;
			}
			return Corner::UpRight;
		} else {
			if(horizontal_side) {
				return Corner::DownLeft;
			}
			return Corner::DownRight;
		}
	}
	
	void BoxConstRatio::draw() {
		if(render_second) {
			second_draw_manager.draw();
		}
	}
	
	void BoxConstRatio::set_position(sf::Vector2f position) {
		BoxConstRatio::move(position - layout_.position);
	}
	
	void BoxConstRatio::move(sf::Vector2f position) {
		layout_.move(position);
		background->move(position);
		const_object->move(position);
		second_object->move(position);
	}
	
	void BoxConstRatio::set_size(sf::Vector2f size) {
		resize(size, layout_.position);
	}
	
	void BoxConstRatio::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		
		sf::Vector2f const_size = sf::Vector2f(size.x / size.y > aspect_ratio ? sf::Vector2f{size.y * aspect_ratio, size.y} : sf::Vector2f{size.x, size.x / aspect_ratio});
		sf::Vector2f second_size = sf::Vector2f(size.x / size.y > aspect_ratio ? sf::Vector2f{size.x - const_size.x, size.y} : sf::Vector2f{size.x, size.y - const_size.y});
		
		sf::Vector2f const_position = sf::Vector2f{0, 0};
		sf::Vector2f second_position = sf::Vector2f{0, 0};
		
		sf::Vector2f second_min_size = second_object->get_min_size();
		render_second = second_size.x > second_min_size.x && second_size.y > second_min_size.y;
		if(render_second) {
			if(size.x / size.y > aspect_ratio) {
				if(horizontal_side) {
					second_position.x = const_size.x;
				} else {
					const_position.x = second_size.x;
				}
			} else {
				if(vertical_side) {
					second_position.y = const_size.y;
				} else {
					const_position.y = second_size.y;
				}
			}
		} else {
			const_position = (layout_.size - const_size) / 2.0f;
		}
		
		const_position += position;
		second_position += position;
		
		const_object->resize(const_size, const_position);
		second_object->resize(second_size, second_position);
		background->resize(size, position);
	}
	
	bool BoxConstRatio::update_interactions(sf::Vector2f mouse_position) {
		if(render_second && second_object->in_area(mouse_position)) {
			return second_object->update_interactions(mouse_position);
		}
		if(const_object->in_area(mouse_position)) {
			return const_object->update_interactions(mouse_position);
		}
		return background->update_interactions(mouse_position);
	}
	
	sf::Vector2f BoxConstRatio::get_min_size() const {
		sf::Vector2f const_min_size{const_object->get_min_size()};
		const_min_size = sf::Vector2f{std::max(const_min_size.x, const_min_size.y * aspect_ratio), std::max(const_min_size.y, const_min_size.x / aspect_ratio)};
		return max(const_min_size, background->get_min_size(), minimum_size);
	}
	
	sf::Vector2f BoxConstRatio::get_normal_size() const {
		sf::Vector2f const_normal_size{const_object->get_normal_size()};
		sf::Vector2f second_normal_size{second_object->get_normal_size()};
		//sf::Vector2f normal_size{std::max(const_normal_size.x, const_normal_size.y * aspect_ratio), std::max(const_normal_size.y, const_normal_size.x / aspect_ratio)};
		sf::Vector2f normal_size{const_normal_size.x + second_normal_size.x, std::max(const_normal_size.y, second_normal_size.y)};
		return max(normal_size, background->get_normal_size());
	}
	
	IUninteractive& BoxConstRatio::get_background() {
		return *background;
	}
	
	const IUninteractive& BoxConstRatio::get_background() const {
		return *background;
	}
	
	IScalable& BoxConstRatio::get_first_object() {
		return *const_object;
	}
	
	const IScalable& BoxConstRatio::get_first_object() const {
		return *const_object;
	}
	
	IScalable& BoxConstRatio::get_second_object() {
		return *second_object;
	}
	
	const IScalable& BoxConstRatio::get_second_object() const {
		return *second_object;
	}
	
	BoxConstRatio* BoxConstRatio::copy() {
		return new BoxConstRatio{*this};
	}
	
	void BoxConstRatio::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		const_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
	
	bool DecodePointer<BoxConstRatio>::decode_pointer(const YAML::Node& node, BoxConstRatio*& box_with_const_ratio) {
		box_with_const_ratio = new BoxConstRatio{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["second-object"].as<BoxPtr<IScalable> >(),
			BoxPtr{conv_def_ptr<IUninteractive, Empty>(node["background"])},
			node["aspect-ratio"].as<float>(),
			conv_def(node["corner"], Corner::UpLeft),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}
