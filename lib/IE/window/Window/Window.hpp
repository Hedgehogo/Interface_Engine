#pragma once

#include <filesystem>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IE/component/IComponent/IScalable/Interface/Interface.hpp"
#include "BaseWindowResizer/WindowResizer/WindowResizer.hpp"

namespace ie {
	auto get_window_resizer() -> BaseWindowResizer*;
	
	class Window {
	public:
		/*old_yaml
		explicit Window(Interface&& interface);
		
		Window(
			Interface&& interface,
			const sf::String& title,
			const sf::VideoMode& mode = {1, 1},
			const sf::ContextSettings& settings = sf::ContextSettings()
		);
		
		Window(Interface&& interface, const sf::String& title, const sf::ContextSettings& settings);
		
		Window(Interface&& interface, sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
		
		explicit Window(const std::filesystem::path& interface);
		
		Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode = {1, 1}, const sf::ContextSettings& settings = sf::ContextSettings());
		
		Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings);
		
		Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
		*/
		
		Window(
			Interface::Make&& make,
			sf::String&& title,
			sf::VideoMode&& mode = {1, 1},
			sf::ContextSettings&& settings = sf::ContextSettings{}
		);
		
		auto create(sf::VideoMode mode, sf::String const& title, sf::Uint32, sf::ContextSettings const& settings) -> void;
		
		virtual auto create(sf::VideoMode mode, sf::String const& title, sf::ContextSettings const& settings = sf::ContextSettings()) -> void;
		
		auto set_size(sf::Vector2u const& size) -> void;
		
		virtual auto re_calculate_min_size() -> void;
		
		virtual auto update() -> void;
		
		auto get_interface() -> Interface&;
		
		auto get_window() -> sf::RenderWindow&;
		
		auto get_min_size() const -> sf::Vector2u;
		
		auto handle_event(sf::Event event) -> void;
	
	protected:
		sf::RenderWindow window_;
		DynBuffer dyn_buffer_;
		KeyHandler key_handler_;
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