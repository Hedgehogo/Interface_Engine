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
	
	ConstRatioSizing2::ConstRatioSizing2(BoxPtr<ISizing>&& sizing, float ratio, bool horizontal) : sizing_(std::move(sizing)), ratio_(ratio), horizontal_(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float ratio, bool horizontal, bool relative_parent) :
		sizing_(BoxPtr{make_size_make(relative_parent)}->make(0)), ratio_(ratio), horizontal_(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float const_size, float ratio, bool horizontal) :
		sizing_(new ConstSizing{const_size}), ratio_(ratio), horizontal_(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float coefficient, float addition, float ratio, bool horizontal, bool relative_target) :
		sizing_(BoxPtr{make_size_make(coefficient, addition, relative_target)}->make(0)), ratio_(ratio), horizontal_(horizontal) {
	}
	
	ConstRatioSizing2::ConstRatioSizing2(float target_coefficient, float parent_coefficient, float addition, float ratio, bool horizontal) :
		sizing_(new SmartSizing{target_coefficient, parent_coefficient, addition}), ratio_(ratio), horizontal_(horizontal) {
	}
	
	void ConstRatioSizing2::init(sf::RenderTarget& render_target, sf::Vector2f normal_size) {
		this->render_target_ = &render_target;
		sizing_->init((horizontal_ ? normal_size.x : normal_size.y));
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
	
	ConstRatioSizing2* ConstRatioSizing2::copy() {
		return new ConstRatioSizing2{*this};
	}
	
	bool DecodePointer<ConstRatioSizing2>::decode_pointer(const YAML::Node& node, ConstRatioSizing2*& const_ratio_sizing2) {
		float ratio{conv_def(node["ratio"], 1.f)};
		bool horizontal{conv_bool_def(node["direction"], "horizontal", "vertical", true)};
		
		if(node["sizing"]) {
			const_ratio_sizing2 = new ConstRatioSizing2{
				node["sizing"].as<BoxPtr<ISizing> >(),
				ratio,
				horizontal
			};
		} else if(node["relative"]) {
			const_ratio_sizing2 = new ConstRatioSizing2{
				ratio,
				horizontal,
				convert_bool(node["relative"], "parent", "normal")
			};
		} else if(node["const-size"]) {
			const_ratio_sizing2 = new ConstRatioSizing2{
				node["const-size"].as<float>(),
				ratio,
				horizontal
			};
		} else if(node["coefficient"]) {
			const_ratio_sizing2 = new ConstRatioSizing2{
				node["coefficient"].as<float>(),
				conv_def(node["addition"], 0.f),
				ratio,
				horizontal,
				conv_bool_def(node["relative"], "target", "parent")
			};
		} else if(node["target-coefficient"] && node["parent-coefficient"]) {
			const_ratio_sizing2 = new ConstRatioSizing2{
				node["target-coefficient"].as<float>(),
				node["parent-coefficient"].as<float>(),
				conv_def(node["addition"], 0.f),
				ratio,
				horizontal
			};
		} else {
			throw YAML::BadConversion{node.Mark()};
		}
		return true;
	}
}