#include "BoxConstCenter.hpp"

namespace ie {
	BoxConstCenter::Make::Make(BoxPtr<IScalable::Make>&& const_object, BoxPtr<IScalable::Make>&& background, sf::Vector2f const_size, sf::Vector2f min_size) :
		const_object(std::move(const_object)), background(std::move(background)), const_size(const_size), min_size(min_size) {
	}
	
	BoxConstCenter* BoxConstCenter::Make::make(InitInfo init_info) {
		return new BoxConstCenter{std::move(*this), init_info};
	}
	
	BoxConstCenter::BoxConstCenter(Make&& make, InitInfo init_info) :
		Box(make.min_size), const_object(make.const_object->make(init_info)), background(make.background->make(init_info)), const_size(make.const_size) {
	}
	
	BoxConstCenter::BoxConstCenter(BoxPtr<IScalable>&& const_object, BoxPtr<IScalable>&& background, const sf::Vector2f& const_size, const sf::Vector2f& min_size) :
		Box(min_size), const_object(std::move(const_object)), background(std::move(background)), const_size(const_size) {
	}
	
	void BoxConstCenter::init(InitInfo init_info) {
		const_object->init(init_info);
		background->init(init_info);
	}
	
	void BoxConstCenter::set_position(sf::Vector2f position) {
		Box::set_position(position);
		if(resized) {
			const_object->move(const_size);
		} else {
			resized = true;
			const_object->resize(const_size, layout_.position + position);
		}
		const_object->set_position(position + (layout_.size / 2.f) - (const_size / 2.f));
		background->set_position(position);
	}
	
	void BoxConstCenter::move(sf::Vector2f position) {
		Box::move(position);
		if(resized) {
			const_object->move(const_size);
		} else {
			resized = true;
			const_object->resize(const_size, layout_.position + position);
		}
		background->move(position);
	}
	
	void BoxConstCenter::set_size(sf::Vector2f size) {
		Box::set_size(size);
		if(!resized) {
			resized = true;
			const_object->set_size(const_size);
		}
		background->set_size(size);
	}
	
	void BoxConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		if(resized) {
			const_object->set_position(position + (size / 2.f) - (const_size / 2.f));
		} else {
			resized = true;
			const_object->resize(const_size, position + (size / 2.f) - (const_size / 2.f));
		}
		background->resize(size, position);
	}
	
	sf::Vector2f BoxConstCenter::get_min_size() const {
		return max(IComponentTwoObjects::get_min_size(), const_size);
	}
	
	sf::Vector2f BoxConstCenter::get_normal_size() const {
		return max(IComponentTwoObjects::get_normal_size(), const_size);
	}
	
	IScalable& BoxConstCenter::get_first_object() {
		return *const_object;
	}
	
	const IScalable& BoxConstCenter::get_first_object() const {
		return *const_object;
	}
	
	IScalable& BoxConstCenter::get_second_object() {
		return *background;
	}
	
	const IScalable& BoxConstCenter::get_second_object() const {
		return *background;
	}
	
	bool BoxConstCenter::update_interactions(sf::Vector2f) {
		return background->in(layout_.position) ? background->update_interactions(layout_.position) : const_object->update_interactions(layout_.position);
	}
	
	BoxConstCenter* BoxConstCenter::copy() {
		return new BoxConstCenter{*this};
	}
	
	bool DecodePointer<BoxConstCenter>::decode_pointer(const YAML::Node& node, BoxConstCenter*& box_with_const_center) {
		box_with_const_center = new BoxConstCenter{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["background"].as<BoxPtr<IScalable> >(),
			node["const-size"].as<sf::Vector2f>(),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}