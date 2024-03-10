#include "WindowResizer.hpp"

#include "../../Window.hpp"

namespace ie {
	WindowResizer::WindowResizer(int internal_border_size, int external_border_size, Key key) :
		internal_border_size_(internal_border_size), external_border_size_(external_border_size), key_(key) {
	}
	
	bool WindowResizer::update(sf::Vector2i mouse_position) {
		if(KeyHandler{}.is_key_pressed(key_)) {
			if(current_border_.x || current_border_.y) {
				auto global_mouse_position = mouse_position + window_->get_window().getPosition();
				if(current_border_.y) {
					(*current_border_.y) = global_mouse_position.y - grip_.y;
				}
				if(current_border_.x) {
					(*current_border_.x) = global_mouse_position.x - grip_.x;
				}
				
				set_size();
				return true;
			} else if(!old_key_pressed_) {
				auto window_size{sf::Vector2i{window_->get_window().getSize()}};
				set_borders();
				if(
					mouse_position.x >= -external_border_size_ && mouse_position.y >= -external_border_size_ &&
					mouse_position.x <= window_size.x + external_border_size_ && mouse_position.y <= window_size.y + external_border_size_
					) {
					get_current_border(grip_.y, current_border_.y, borders_.up, borders_.down, window_size.y, mouse_position.y);
					get_current_border(grip_.x, current_border_.x, borders_.left, borders_.right, window_size.x, mouse_position.x);
				}
				
				old_key_pressed_ = true;
				return current_border_.x || current_border_.y;
			}
		} else {
			current_border_ = {};
			old_key_pressed_ = false;
		}
		return false;
	}
	
	void swap_borders(int*& current_border, int& border, int& border2, int& grip, int& size) {
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
	
	void check_min_size(int& size, float& min_size, int*& current_border, int& border, int& border2) {
		if(size < min_size) {
			if(current_border == &border) {
				border = border2 - min_size;
			} else {
				border2 = border + min_size;
			}
		}
	}
	
	void WindowResizer::set_size() {
		auto size{sf::Vector2i{borders_.right - borders_.left, borders_.down - borders_.up}};
		
		swap_borders(current_border_.y, borders_.up, borders_.down, grip_.y, size.y);
		swap_borders(current_border_.x, borders_.left, borders_.right, grip_.x, size.x);
		
		auto min_size{sf::Vector2f{window_->get_min_size()}};
		
		check_min_size(size.y, min_size.y, current_border_.y, borders_.up, borders_.down);
		check_min_size(size.x, min_size.x, current_border_.x, borders_.left, borders_.right);
		
		window_->get_window().setPosition({borders_.left, borders_.up});
		window_->set_size({static_cast<unsigned>(borders_.right - borders_.left), static_cast<unsigned>(borders_.down - borders_.up)});
	}
	
	void WindowResizer::set_borders() {
		auto window_position{window_->get_window().getPosition()};
		auto window_size{window_->get_window().getSize()};
		borders_ = {
			window_position.y,
			window_position.y + static_cast<int>(window_size.y),
			window_position.x,
			window_position.x + static_cast<int>(window_size.x)
		};
	}
	
	void WindowResizer::get_current_border(int& grip, int*& current_border, int& border, int& border2, int& window_size, int& mouse_position) {
		if(mouse_position <= internal_border_size_ && mouse_position >= -external_border_size_) {
			current_border = &border;
			grip = mouse_position;
		} else if(window_size - internal_border_size_ <= mouse_position && window_size + external_border_size_ >= mouse_position) {
			current_border = &border2;
			grip = mouse_position - window_size;
		} else {
			current_border = nullptr;
			grip = 0;
		}
	};
}