#include "WindowResizer.hpp"

#include "../../Window.hpp"

namespace ie {
	WindowResizer::WindowResizer(int internal_border_size, int external_border_size, Key key) :
		internal_border_size_(internal_border_size), external_border_size_(external_border_size), key_(key) {
	}
	
	auto WindowResizer::update(std::vector<Event> const& events, EventHandler& event_handler) -> bool {
		orl::Option<event_system::Touch> maybe_touch;
		for(auto const& event: events) {
			for(auto const touch_pressed: event.touch_pressed(event_handler.get_key(key_))) {
				maybe_touch = touch_pressed;
			}
		}
		
		return maybe_touch.map([this](auto touch) {
			auto set_size_fn{
				[this]{
					auto swap_borders_fn{
						[](int*& current_border, int& border, int& border2, int& grip, int& size) {
							if(size < 0 && std::abs(size) > std::abs(grip)) {
								std::swap(border, border2);
								grip = -grip;
								size = -size;
								if(current_border == &border) {
									current_border = &border2;
								} else {
									current_border = &border;
								}
							}
						}
					};
					auto check_min_size_fn {
						[](int size, float min_size, int*& current_border, int& border, int& border2) {
							if(size < min_size) {
								if(current_border == &border) {
									border = border2 - min_size;
								} else {
									border2 = border + min_size;
								}
							}
						}
					};
					
					auto size{sf::Vector2i{borders_.right - borders_.left, borders_.down - borders_.up}};
					auto const min_size{sf::Vector2f{window_->get_min_size()}};

					for(auto& current_border : current_borders_.x) {
						swap_borders_fn(current_border, borders_.left, borders_.right, grip_.x, size.x);
						check_min_size_fn(size.x, min_size.x, current_border, borders_.left, borders_.right);
					}
					for(auto& current_border : current_borders_.y){
						swap_borders_fn(current_border, borders_.up, borders_.down, grip_.y, size.y);
						check_min_size_fn(size.y, min_size.y, current_border, borders_.up, borders_.down);
					}
					
					window_->set_position({borders_.left, borders_.up});
					window_->set_size({static_cast<unsigned>(borders_.right - borders_.left), static_cast<unsigned>(borders_.down - borders_.up)});
				}
			};
			
			auto set_borders_fn {
				[this]() {
					auto const window_position{window_->get_window().getPosition()};
					auto const window_size{window_->get_window().getSize()};
					borders_ = {
						window_position.y,
						window_position.y + static_cast<int>(window_size.y),
						window_position.x,
						window_position.x + static_cast<int>(window_size.x)
					};
				}
			};
			
			auto get_current_border_fn {
				[this](int& grip, orl::Option<int*>& current_border, int& border, int& border2, int window_size, int touch_position) {
					if(touch_position <= internal_border_size_ && touch_position >= -external_border_size_) {
						current_border = &border;
						grip = touch_position;
					} else if(window_size - internal_border_size_ <= touch_position && window_size + external_border_size_ >= touch_position) {
						current_border = &border2;
						grip = touch_position - window_size;
					} else {
						current_border = {};
						grip = 0;
					}
				}
			};
			
			if(current_borders_.x.is_some() || current_borders_.y.is_some()) {
				auto const global_touch_position = touch.position + window_->get_window().getPosition();
				
				for(auto& current_border : current_borders_.x) {
					(*current_border) = global_touch_position.x - grip_.x;
				}
				for(auto& current_border : current_borders_.y) {
					(*current_border) = global_touch_position.y - grip_.y;
				}
				
				set_size_fn();
				return true;
			} else if(!old_key_pressed_) {
				set_borders_fn();
				old_key_pressed_ = true;
				auto const window_size{sf::Vector2i{window_->get_window().getSize()}};
				
				get_current_border_fn(grip_.y, current_borders_.y, borders_.up,   borders_.down,  window_size.y, touch.position.y);
				get_current_border_fn(grip_.x, current_borders_.x, borders_.left, borders_.right, window_size.x, touch.position.x);
				
				return current_borders_.x.is_some() || current_borders_.y.is_some();
			}
			return false;
		}).some_or_else([this] {
			current_borders_ = {nullptr, nullptr};
			old_key_pressed_ = false;
			return false;
		});
	}
}