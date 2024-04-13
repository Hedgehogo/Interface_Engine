#pragma once

#include <filesystem>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IE/event/Event/Event.hpp"
#include "IE/event/EventHandler/EventHandler.hpp"
#include "IE/component/IComponent/IScalable/Interface/Interface.hpp"
#include "BaseWindowResizer/WindowResizer/WindowResizer.hpp"

namespace ie {
	auto get_window_resizer() -> BaseWindowResizer*;
	
	class Window {
	public:
		/*old_yaml
		Window(Interface&& interface, sf::WindowHandle handle, sf::ContextSettings&& settings = sf::ContextSettings());
		
		Window(fs::path interface, sf::WindowHandle handle, sf::ContextSettings&& settings = sf::ContextSettings());
		*/
		
		Window(
			Interface::Make&& make,
			sf::String&& title,
			sf::VideoMode&& mode = {1, 1},
			sf::ContextSettings&& settings = sf::ContextSettings{}
		);
		
		auto create(sf::VideoMode mode, sf::String const& title, sf::Uint32, sf::ContextSettings const& settings) -> void;
		
		virtual auto create(sf::VideoMode mode, sf::String const& title, sf::ContextSettings const& settings = sf::ContextSettings()) -> void;
		
		auto set_position(sf::Vector2i const& position) -> void;
		
		auto set_size(sf::Vector2u const& size) -> void;
		
		virtual auto re_calculate_min_size() -> void;
		
		virtual auto update(std::vector<Event>&& events) -> void;
		
		auto get_interface() -> Interface&;
		
		auto get_window() -> sf::RenderWindow&;
		
		auto get_min_size() const -> sf::Vector2u;
		
		auto events() -> std::vector<Event>;
		
	protected:
		sf::RenderWindow window_;
		DynBuffer dyn_buffer_;
		EventHandler event_handler_;
		Interface interface_;
		BoxPtr<BaseWindowResizer> resizer_;
		sf::Vector2u min_size_;
	};
	
	auto make_window(
		fs::path file_path,
		sf::String&& title,
		sf::VideoMode&& mode = {1, 1},
		sf::ContextSettings&& settings = sf::ContextSettings{}
	) -> Window;
}