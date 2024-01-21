#include "Sizing2.hpp"
#include "IE/sizing-positioning/ISizing/Functions/make_size_make/make_size_make.hpp"

namespace ie {
	Sizing2::Make::Make(BoxPtr<ISizing::Make>&& horizontal, BoxPtr<ISizing::Make>&& vertical) :
		horizontal(std::move(horizontal)), vertical(std::move(vertical)) {
	}
	
	Sizing2::Make::Make(bool relative_parent) :
		horizontal(make_size_make(relative_parent)), vertical(make_size_make(relative_parent)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f const_size) :
		horizontal(make_size_make(const_size.x)), vertical(make_size_make(const_size.y)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f coefficient, sf::Vector2f addition, bool relative_target) :
		horizontal(make_size_make(coefficient.x, addition.x, relative_target)),
		vertical(make_size_make(coefficient.y, addition.y, relative_target)) {
	}
	
	Sizing2::Make::Make(sf::Vector2f target_coefficient, sf::Vector2f parent_coefficient, sf::Vector2f addition) :
		horizontal(make_size_make(target_coefficient.x, parent_coefficient.x, addition.x)),
		vertical(make_size_make(target_coefficient.y, parent_coefficient.y, addition.y)) {
	}
	
	Sizing2* Sizing2::Make::make(Sizing2InitInfo init_info) {
		return new Sizing2{std::move(*this), init_info};
	}
	
	Sizing2::Sizing2(Make&& make, Sizing2InitInfo init_info) :
		horizontal_(make.horizontal->make(init_info.normal_size.x)),
		vertical_(make.vertical->make(init_info.normal_size.y)),
		render_target_(&init_info.render_target) {
	}
	
	Sizing2::Sizing2(BoxPtr<ISizing>&& horizontal, BoxPtr<ISizing>&& vertical) :
		horizontal_(std::move(horizontal)), vertical_(std::move(vertical)), render_target_(nullptr) {
	}
	
	Sizing2::Sizing2(bool relative_parent) :
		horizontal_(BoxPtr{make_size_make(relative_parent)}->make(0)),
		vertical_(BoxPtr{make_size_make(relative_parent)}->make(0)),
		render_target_(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f const_size) :
		horizontal_(BoxPtr{make_size_make(const_size.x)}->make(0)),
		vertical_(BoxPtr{make_size_make(const_size.y)}->make(0)),
		render_target_(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relative_target) :
		horizontal_(BoxPtr{make_size_make(coefficient.x, addition.x, relative_target)}->make(0)),
		vertical_(BoxPtr{make_size_make(coefficient.y, addition.y, relative_target)}->make(0)),
		render_target_(nullptr) {
	}
	
	Sizing2::Sizing2(sf::Vector2f target_coefficient, sf::Vector2f parent_coefficient, sf::Vector2f addition) :
		horizontal_(BoxPtr{make_size_make(target_coefficient.x, parent_coefficient.x, addition.x)}->make(0)),
		vertical_(BoxPtr{make_size_make(target_coefficient.y, parent_coefficient.y, addition.y)}->make(0)),
		render_target_(nullptr) {
	}
	
	void Sizing2::init(sf::RenderTarget& render_target, sf::Vector2f normal_size) {
		this->render_target_ = &render_target;
		horizontal_->init(normal_size.x);
		vertical_->init(normal_size.y);
	}
	
	sf::Vector2f Sizing2::find_size(sf::Vector2f parent_size) {
		sf::Vector2f target_size{render_target_->getSize()};
		return {horizontal_->find_size(parent_size.x, target_size.x), vertical_->find_size(parent_size.y, target_size.y)};
	}
	
	sf::Vector2f Sizing2::get_parent_size(sf::Vector2f object_size) {
		return {horizontal_->get_parent_size(object_size.x), vertical_->get_parent_size(object_size.y)};
	}
	
	Sizing2* Sizing2::copy() {
		return new Sizing2{*this};
	}
}

orl::Option<ie::Sizing2::Make> ieml::Decode<char, ie::Sizing2::Make>::decode(ieml::Node const& node) {
	auto& clear_node{node.get_clear()};
	if(auto result{clear_node.as<sf::Vector2f>()}) {
		return {{result.ok()}};
	}
	auto map{clear_node.get_map_view().except()};
	if(auto relative{map.at("relative-parent")}) {
		return {{relative.ok().as<bool>().except()}};
	}
	if(auto const_size{map.at("const-size")}) {
		return {{const_size.ok().as<sf::Vector2f>().except()}};
	}
	auto target_coefficient{map.at("target-coefficient")};
	auto parent_coefficient{map.at("parent-coefficient")};
	if(target_coefficient.is_ok() || parent_coefficient.is_ok()) {
		auto relative_target{target_coefficient.is_ok()};
		auto& coefficient{relative_target ? target_coefficient.ok() : parent_coefficient.ok()};
		return ie::Sizing2::Make{
			coefficient.as<sf::Vector2f>().except(),
			map.get_as<sf::Vector2f>("addition").ok_or({}),
			relative_target
		};
	}
	if(target_coefficient.is_ok() && parent_coefficient.is_ok()) {
		return ie::Sizing2::Make{
			target_coefficient.ok().as<sf::Vector2f>().except(),
			parent_coefficient.ok().as<sf::Vector2f>().except(),
			map.get_as<sf::Vector2f>("addition").ok_or({})
		};
	}
	return ie::Sizing2::Make{
		map.at("horizontal").except().as<ie::BoxPtr<ie::ISizing::Make> >().move_except(),
		map.at("vertical").except().as<ie::BoxPtr<ie::ISizing::Make> >().move_except(),
	};
}
