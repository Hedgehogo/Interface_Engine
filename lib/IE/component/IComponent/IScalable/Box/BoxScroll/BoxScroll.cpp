#include "BoxScroll.hpp"

namespace ie {
	BoxScroll::Make::Make(BoxPtr<IComponent::Make>&& object, MakeDyn<SRVec2F> normal_object_position, sf::Vector2f min_size) :
		object(std::move(object)), normal_object_position(std::move(normal_object_position)), min_size(min_size) {
	}
	
	BoxScroll* BoxScroll::Make::make(InitInfo init_info) {
		return new BoxScroll{std::move(*this), init_info};
	}
	
	BoxScroll::BoxScroll(Make&& make, InitInfo init_info) :
		BoxWithView(make.min_size, init_info),
		object_(make.object->make(init_info.copy(this->draw_manager_))),
		normal_object_position_(
			make.normal_object_position.make(init_info.dyn_buffer),
			[&](sf::Vector2f value) {
				this->object_->set_position(get_new_object_position(value));
			}
		) {
		normal_object_position_.get().get_x().set_bounds(0, 1);
		normal_object_position_.get().get_y().set_bounds(0, 1);
	}
	
	void BoxScroll::init(InitInfo init_info) {
		BoxWithView::init(init_info);
		object_->init(init_info.copy(this->draw_manager_));
	}
	
	sf::Vector2f BoxScroll::get_min_size() const {
		return max(minimum_size_, object_->get_min_size());
	}
	
	sf::Vector2f BoxScroll::get_normal_size() const {
		return object_->get_normal_size();
	}
	
	sf::Vector2f BoxScroll::get_new_object_position(sf::Vector2f normal_object_position) {
		sf::Vector2f max_offset{object_->get_size() - layout_.size};
		sf::Vector2f offset{max_offset * normal_object_position};
		return layout_.position - offset;
	}
	
	void BoxScroll::resize(sf::Vector2f size, sf::Vector2f position) {
		BoxWithView::resize(size, position);
		
		object_->set_size(size);
		
		sf::Vector2f object_size{object_->get_size()};
		if(object_size.x == size.x && object_size.y == size.y)
			return object_->set_position(position);
		object_->set_position(get_new_object_position(normal_object_position_.get().get()));
	}
	
	bool BoxScroll::update_interactions(sf::Vector2f mouse_position) {
		return object_->update_interactions(mouse_position);
	}
	
	BoxScroll* BoxScroll::copy() {
		return nullptr;
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxScroll>::decode_pointer(const YAML::Node& node, BoxScroll*& box_scroll) {
		box_scroll = new BoxScroll{
			node["object"].as<BoxPtr<IComponent> >(),
			Buffer::get<SRVec2f>(node["normal-object-position"]),
			(node["min-size"] ? node["min-size"].as<sf::Vector2f>() : sf::Vector2f{0, 0})
		};
		return true;

	}
	*/
}