#include "BoxMovableBorder.hpp"
#include "IE/interaction/IAction/BasicKeyAction/BasicAddInteractionAction/BasicAddBlockInteractionAction/BasicAddBlockInteractionAction.hpp"
#include <algorithm>

namespace ie {
	BoxMovableBorder::Make::Make(
		BoxPtr<IScalable::Make>&& first_object,
		BoxPtr<IScalable::Make>&& second_object,
		bool is_horizontal_border,
		MakeDyn<ISMRFloat> border_value,
		int border_interaction_size,
		Key key,
		sf::Vector2f min_size
	) :
		first_object(std::move(first_object)),
		second_object(std::move(second_object)),
		is_horizontal_border(is_horizontal_border),
		border_value(std::move(border_value)),
		border_interaction_size(border_interaction_size),
		key(key),
		min_size(min_size) {
	}
	
	auto BoxMovableBorder::Make::make(InitInfo init_info) -> BoxMovableBorder* {
		return new BoxMovableBorder{std::move(*this), init_info};
	}
	
	BoxMovableBorder::BoxMovableBorder(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		interactive_(make_box_ptr<BasicOneKeyInteraction<BoxMovableBorder&>::Make>(
			make_box_ptr<BasicAddBlockInteractionAction<BoxMovableBorder&>::Make>(
				make_box_ptr<BasicOneKeyInteraction<BoxMovableBorder&>::Make, BasicPressedInteraction<BoxMovableBorder&>::Make>(
					make_box_ptr<MovableBorderAction::Make>(), make.key
				)
			), make.key
		), init_info, *this),
		first_object_(make.first_object->make(init_info)),
		second_object_(make.second_object->make(init_info)),
		border_value_(
			DynBuffer::get(std::move(make.border_value), SInitInfo{init_info}),
			[this](const float&) {
				this->resize(layout_.size, layout_.position);
			}
		),
		border_value_now_(border_value_.get().get()),
		border_interaction_size_(make.border_interaction_size),
		is_horizontal_border_(make.is_horizontal_border) {
		init_info.update_manager.add(*this);
	}
	
	auto BoxMovableBorder::get_border_value() -> float {
		return border_value_.get().get();
	}
	
	auto BoxMovableBorder::set_border_value(float border_value) -> void {
		this->border_value_.get().set(border_value);
	}
	
	auto BoxMovableBorder::get_border_value_now() -> float {
		return this->border_value_now_;
	}
	
	auto BoxMovableBorder::get_border_interaction_size() -> int {
		return this->border_interaction_size_;
	}
	
	auto BoxMovableBorder::set_border_interaction_size(int size) -> void {
		this->border_interaction_size_ = size;
	}
	
	auto BoxMovableBorder::is_in_border(sf::Vector2f point_position) -> bool {
		if(
			point_position.x < layout_.position.x ||
			point_position.x > layout_.position.x + layout_.size.x ||
			point_position.y < layout_.position.y ||
			point_position.y > layout_.position.y + layout_.size.y
			) {
			return false;
		}
		if(this->is_horizontal_border_) {
			int border_position = layout_.size.x * border_value_now_ + layout_.position.x;
			return point_position.x > border_position - border_interaction_size_ && point_position.x < border_position + border_interaction_size_;
		}
		int border_position = layout_.size.y * border_value_now_ + layout_.position.y;
		return point_position.y > border_position - border_interaction_size_ && point_position.y < border_position + border_interaction_size_;
	}
	
	auto BoxMovableBorder::get_is_horizontal_border() -> bool {
		return this->is_horizontal_border_;
	}
	
	auto BoxMovableBorder::update() -> void {
		interactive_.update();
	}
	
	auto BoxMovableBorder::update_interactions(sf::Vector2f mouse_position) -> bool {
		if(!this->is_in_border(mouse_position)) {
			if(this->is_horizontal_border_) {
				float split_position = layout_.position.x + layout_.size.x * this->border_value_now_;
				if(split_position > mouse_position.x) {
					return first_object_->update_interactions(mouse_position);
				}
				return second_object_->update_interactions(mouse_position);
			} else {
				float split_position = layout_.position.y + layout_.size.y * this->border_value_now_;
				if(split_position > mouse_position.y) {
					return first_object_->update_interactions(mouse_position);
				}
				return second_object_->update_interactions(mouse_position);
			}
		} else {
			interactive_.update_interactions();
		}
		return true;
	}
	
	auto BoxMovableBorder::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		
		sf::Vector2f first_object_size;
		sf::Vector2f second_object_size;
		
		auto first_object_min_size{first_object_->get_min_size()};
		auto second_object_min_size{second_object_->get_min_size()};
		
		auto second_position = position;
		
		if(this->is_horizontal_border_) {
			auto c{second_object_min_size.x / first_object_min_size.x};
			auto min_size_border{1 - c / (c + 1)};
			
			if(min_size_border > border_value_.get().get()) {
				border_value_now_ = std::max({first_object_min_size.x / size.x, border_value_.get().get()});
			} else {
				auto diff = size.x - get_min_size().x;
				border_value_now_ = std::min({(diff + first_object_min_size.x) / size.x, border_value_.get().get()});
			}
			
			first_object_size = {size.x * border_value_now_, size.y};
			second_object_size = {size.x - first_object_size.x, size.y};
			second_position.x += first_object_size.x;
		} else {
			auto c{second_object_min_size.y / first_object_min_size.y};
			auto min_size_border{1 - c / (c + 1)};
			
			if(min_size_border > border_value_.get().get()) {
				border_value_now_ = std::max({first_object_min_size.y / size.y, border_value_.get().get()});
			} else {
				auto diff = size.y - get_min_size().y;
				border_value_now_ = std::min({(diff + first_object_min_size.y) / size.y, border_value_.get().get()});
			}
			
			first_object_size = {size.x, size.y * border_value_now_};
			second_object_size = {size.x, size.y - first_object_size.y};
			second_position.y += first_object_size.y;
		}
		first_object_->resize(first_object_size, position);
		second_object_->resize(second_object_size, second_position);
	}
	
	auto BoxMovableBorder::get_min_size() const -> sf::Vector2f {
		auto first_min_size{first_object_->get_min_size()};
		auto second_min_size{second_object_->get_min_size()};
		if(this->is_horizontal_border_) {
			return {first_min_size.x + second_min_size.x, std::max(first_min_size.y, second_min_size.y)};
		}
		return {std::max(first_min_size.x, second_min_size.x), std::max(first_min_size.y + second_min_size.y, this->minimum_size_.y)};
	}
	
	auto BoxMovableBorder::get_normal_size() const -> sf::Vector2f {
		auto first_normal_size{first_object_->get_normal_size()};
		auto second_normal_size{second_object_->get_normal_size()};
		if(this->is_horizontal_border_) {
			return {first_normal_size.x + second_normal_size.x, std::max(first_normal_size.y, second_normal_size.y)};
		}
		return {std::max(first_normal_size.x, second_normal_size.x), first_normal_size.y + second_normal_size.y};
	}
	
	auto BoxMovableBorder::get_first_object() -> IScalable& {
		return *first_object_;
	}
	
	auto BoxMovableBorder::get_first_object() const -> IScalable const& {
		return *first_object_;
	}
	
	auto BoxMovableBorder::get_second_object() -> IScalable& {
		return *second_object_;
	}
	
	auto BoxMovableBorder::get_second_object() const -> IScalable const& {
		return *second_object_;
	}
	
	auto BoxMovableBorder::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		IComponent::draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		first_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
		second_object_->draw_debug(render_target, indent + indent_addition, indent_addition, hue + hue_offset, hue_offset);
	}
}

auto ieml::Decode<char, ie::BoxMovableBorder::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxMovableBorder::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxMovableBorder::Make{
		map.at("first-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.at("second-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<bool>("border-horizontal").except().ok_or(false),
		map.at("border-value").except().as<ie::MakeDyn<ie::ISMRFloat> >().except(),
		map.get_as<int>("border-interaction-size").except().ok_or(5),
		map.get_as<ie::Key>("key").except().ok_or(ie::Key::MouseLeft),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
