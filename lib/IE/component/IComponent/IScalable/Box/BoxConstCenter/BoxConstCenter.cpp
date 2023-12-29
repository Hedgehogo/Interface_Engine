#include "BoxConstCenter.hpp"

namespace ie {
	BoxConstCenter::Make::Make(BoxPtr<IScalable::Make>&& const_object, BoxPtr<IScalable::Make>&& background, sf::Vector2f const_size, sf::Vector2f min_size) :
		const_object(std::move(const_object)), background(std::move(background)), const_size(const_size), min_size(min_size) {
	}
	
	BoxConstCenter* BoxConstCenter::Make::make(InitInfo init_info) {
		return new BoxConstCenter{std::move(*this), init_info};
	}
	
	BoxConstCenter::BoxConstCenter(Make&& make, InitInfo init_info) :
		Box(make.min_size), const_object_(make.const_object->make(init_info)), background_(make.background->make(init_info)), const_size_(make.const_size) {
	}
	
	BoxConstCenter::BoxConstCenter(BoxPtr<IScalable>&& const_object, BoxPtr<IScalable>&& background, const sf::Vector2f& const_size, const sf::Vector2f& min_size) :
		Box(min_size), const_object_(std::move(const_object)), background_(std::move(background)), const_size_(const_size) {
	}
	
	void BoxConstCenter::init(InitInfo init_info) {
		const_object_->init(init_info);
		background_->init(init_info);
	}
	
	void BoxConstCenter::set_position(sf::Vector2f position) {
		Box::set_position(position);
		if(resized_) {
			const_object_->move(const_size_);
		} else {
			resized_ = true;
			const_object_->resize(const_size_, layout_.position + position);
		}
		const_object_->set_position(position + (layout_.size / 2.f) - (const_size_ / 2.f));
		background_->set_position(position);
	}
	
	void BoxConstCenter::move(sf::Vector2f position) {
		Box::move(position);
		if(resized_) {
			const_object_->move(const_size_);
		} else {
			resized_ = true;
			const_object_->resize(const_size_, layout_.position + position);
		}
		background_->move(position);
	}
	
	void BoxConstCenter::set_size(sf::Vector2f size) {
		Box::set_size(size);
		if(!resized_) {
			resized_ = true;
			const_object_->set_size(const_size_);
		}
		background_->set_size(size);
	}
	
	void BoxConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		if(resized_) {
			const_object_->set_position(position + (size / 2.f) - (const_size_ / 2.f));
		} else {
			resized_ = true;
			const_object_->resize(const_size_, position + (size / 2.f) - (const_size_ / 2.f));
		}
		background_->resize(size, position);
	}
	
	sf::Vector2f BoxConstCenter::get_min_size() const {
		return max(IComponentTwoObjects::get_min_size(), const_size_);
	}
	
	sf::Vector2f BoxConstCenter::get_normal_size() const {
		return max(IComponentTwoObjects::get_normal_size(), const_size_);
	}
	
	IScalable& BoxConstCenter::get_first_object() {
		return *const_object_;
	}
	
	const IScalable& BoxConstCenter::get_first_object() const {
		return *const_object_;
	}
	
	IScalable& BoxConstCenter::get_second_object() {
		return *background_;
	}
	
	const IScalable& BoxConstCenter::get_second_object() const {
		return *background_;
	}
	
	bool BoxConstCenter::update_interactions(sf::Vector2f) {
		return background_->in(layout_.position) ? background_->update_interactions(layout_.position) : const_object_->update_interactions(layout_.position);
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