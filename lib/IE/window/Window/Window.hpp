#pragma once

#include <filesystem>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IE/component/IComponent/IScalable/Interface/Interface.hpp"
#include "BaseWindowResizer/WindowResizer/WindowResizer.hpp"

namespace ie {
	BaseWindowResizer* get_window_resizer();
	
	class Window {
	protected:
		void construction();
		
	public:
		explicit Window(Interface&& interface);
		
		Window(Interface&& interface, const sf::String& title, const sf::VideoMode& mode = {1, 1}, const sf::ContextSettings& settings = sf::ContextSettings());
		
		Window(Interface&& interface, const sf::String& title, const sf::ContextSettings& settings);
		
		Window(Interface&& interface, sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
		
		/*old_yaml
		explicit Window(const std::filesystem::path& interface);
		
		Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode = {1, 1}, const sf::ContextSettings& settings = sf::ContextSettings());
		
		Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings);
		
		Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
		*/
		
		Window(Interface::Make&& make, sf::String&& title, sf::VideoMode&& mode = {1, 1}, sf::ContextSettings&& settings = sf::ContextSettings{});
		
		void create(sf::VideoMode mode, const sf::String& title, sf::Uint32, const sf::ContextSettings& settings);
		
		virtual void create(sf::VideoMode mode, const sf::String& title, const sf::ContextSettings& settings = sf::ContextSettings());
		
		void set_size(const sf::Vector2u& size);
		
		virtual void re_calculate_min_size();
		
		virtual void update();
		
		Interface& get_interface();
		
		sf::RenderWindow& get_window();
		
		sf::Vector2u get_min_size() const;
	
	protected:
		sf::RenderWindow window_;
		Interface interface_;
		BoxPtr<BaseWindowResizer> resizer_;
		sf::Vector2u min_size_;
	};
}