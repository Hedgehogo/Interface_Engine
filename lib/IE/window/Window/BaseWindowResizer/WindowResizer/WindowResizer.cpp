#include "WindowResizer.hpp"

#include "../../Window.hpp"

namespace ie {
	WindowResizer::WindowResizer(int internal_border_size, int external_border_size, Key key) : internal_border_size(internal_border_size), external_border_size(external_border_size), key(key){
	}
	
	void swap_borders(int*& current_border, int& border, int& border2, int& grip, int& size){
		if (size < 0 && std::abs(size) > std::abs(grip)) {
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
	
	void check_min_size(int& size, float& min_size, int*& current_border, int& border, int& border2){
		if (size < min_size){
			if (current_border == &border){
				border = border2 - min_size;
			} else {
				border2 = border + min_size;
			}
		}
	}
	
	void WindowResizer::set_size() {
		sf::Vector2i size{borders.right - borders.left, borders.down - borders.up};
		
		swap_borders(current_border.y, borders.up, borders.down, grip.y, size.y);
		swap_borders(current_border.x, borders.left, borders.right, grip.x, size.x);
		
		sf::Vector2f min_size{window->get_min_size()};
		
		check_min_size(size.y, min_size.y, current_border.y, borders.up, borders.down);
		check_min_size(size.x, min_size.x, current_border.x, borders.left, borders.right);
		
		window->get_window().setPosition({borders.left, borders.up});
		window->set_size({static_cast<unsigned>(borders.right - borders.left), static_cast<unsigned>(borders.down - borders.up)});
	}
	
	void WindowResizer::set_borders() {
		sf::Vector2i window_position{window->get_window().getPosition()};
		sf::Vector2u window_size{window->get_window().getSize()};
		borders = {
			window_position.y,
			window_position.y + static_cast<int>(window_size.y),
			window_position.x,
			window_position.x + static_cast<int>(window_size.x)
		};
	}
	
	void WindowResizer::get_current_border(int& grip, int*& current_border, int& border, int& border2, int& window_size, int& mouse_position) {
		if(mouse_position <= internal_border_size && mouse_position >= -external_border_size) {
			current_border = &border;
			grip = mouse_position;
		} else if(window_size - internal_border_size <= mouse_position && window_size + external_border_size >= mouse_position) {
			current_border = &border2;
			grip = mouse_position - window_size;
		} else {
			current_border = nullptr;
			grip = 0;
		}
	};
	
	bool WindowResizer::update(sf::Vector2i mouse_position) {
		if(KeyHandler::is_key_pressed(key)) {
			if(current_border.x || current_border.y) {
				auto global_mouse_position = mouse_position + window->get_window().getPosition();
				if(current_border.y)
					(*current_border.y) = global_mouse_position.y - grip.y;
				if(current_border.x)
					(*current_border.x) = global_mouse_position.x - grip.x;
				
				set_size();
				return true;
				
			} else if (!old_key_pressed) {
				sf::Vector2i window_size{window->get_window().getSize()};
				set_borders();
				
				if(mouse_position.x >= -external_border_size && mouse_position.y >= -external_border_size && mouse_position.x <= window_size.x + external_border_size && mouse_position.y <= window_size.y + external_border_size) {
					get_current_border(grip.y, current_border.y, borders.up, borders.down, window_size.y, mouse_position.y);
					get_current_border(grip.x, current_border.x, borders.left, borders.right, window_size.x, mouse_position.x);
				}
				old_key_pressed = true;
				return current_border.x || current_border.y;
			}
		} else {
			current_border = {};
			old_key_pressed = false;
		}
		return false;
	}
}