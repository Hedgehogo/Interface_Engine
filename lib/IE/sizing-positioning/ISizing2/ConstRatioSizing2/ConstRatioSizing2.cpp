#include "ConstRatioSizing2.hpp"
#include "IE/sizing-positioning/ISizing/Functions/make_size_make/make_size_make.hpp"

namespace ie {
	ConstRatioSizing2::Make::Make(BoxPtr<ISizing::Make>&& sizing, float ratio, bool horizontal) :
		sizing(std::move(sizing)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float ratio, bool horizontal, bool relative_parent) :
		sizing(make_size_make(relative_parent)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float const_size, float ratio, bool horizontal) :
		sizing(new ConstSizing::Make{const_size}), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float coefficient, float addition, float ratio, bool horizontal, bool relative_target) :
		sizing(make_size_make(coefficient, addition, relative_target)), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2::Make::Make(float target_coefficient, float parent_coefficient, float addition, float ratio, bool horizontal) :
		sizing(new SmartSizing::Make{target_coefficient, parent_coefficient, addition}), ratio(ratio), horizontal(horizontal) {
	}
	
	ConstRatioSizing2* ConstRatioSizing2::Make::make(Sizing2InitInfo init_info) {
		return new ConstRatioSizing2{std::move(*this), init_info};
	}
	
	ConstRatioSizing2::ConstRatioSizing2(Make&& make, Sizing2InitInfo init_info) :
		render_target_(&init_info.render_target),
		sizing_(make.sizing->make((make.horizontal ? init_info.normal_size.x : init_info.normal_size.y))),
		ratio_(make.ratio),
		horizontal_(make.horizontal) {
	}
	
	sf::Vector2f ConstRatioSizing2::find_size(sf::Vector2f parent_size) {
		sf::Vector2f target_size{static_cast<sf::Vector2f>(render_target_->getSize())};
		float size = (horizontal_ ? sizing_->find_size(parent_size.x, target_size.x) : sizing_->find_size(parent_size.y, target_size.y));
		return (horizontal_ ? sf::Vector2f{size, size / ratio_} : sf::Vector2f{size * ratio_, size});
	}
	
	sf::Vector2f ConstRatioSizing2::get_parent_size(sf::Vector2f object_size) {
		float size = (horizontal_ ? sizing_->get_parent_size(object_size.x) : sizing_->get_parent_size(object_size.y));
		return (horizontal_ ? sf::Vector2f{size, size / ratio_} : sf::Vector2f{size * ratio_, size});
	}
}

orl::Option<ie::ConstRatioSizing2::Make> ieml::Decode<char, ie::ConstRatioSizing2::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	auto ratio{map.get_as<float>("ratio").ok_or(1.)};
	auto horizontal{map.get_as<bool>("horizontal").ok_or(true)};
	if(auto relative_parent{map.at("relative-parent")}) {
		return {{ratio, horizontal, relative_parent.ok().as<bool>().except()}};
	}
	if(auto const_size{map.at("const-size")}) {
		return {{const_size.ok().as<float>().except(), ratio, horizontal}};
	}
	auto target_coefficient{map.at("target-coefficient")};
	auto parent_coefficient{map.at("parent-coefficient")};
	if(target_coefficient.is_ok() && parent_coefficient.is_ok()) {
		return ie::ConstRatioSizing2::Make{
			target_coefficient.ok().as<float>().except(),
			parent_coefficient.ok().as<float>().except(),
			map.get_as<float>("addition").ok_or(0.),
			ratio,
			horizontal
		};
	}
	if(target_coefficient.is_ok() || parent_coefficient.is_ok()) {
		auto relative_target{target_coefficient.is_ok()};
		auto& coefficient{relative_target ? target_coefficient.ok() : parent_coefficient.ok()};
		return ie::ConstRatioSizing2::Make{
			coefficient.as<float>().except(),
			map.get_as<float>("addition").ok_or(0.),
			ratio,
			horizontal,
			relative_target
		};
	}
	return ie::ConstRatioSizing2::Make{
		map.at("sizing").except().as<ie::BoxPtr<ie::ISizing::Make> >().move_except(),
		ratio,
		horizontal
	};
}
