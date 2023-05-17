#pragma once

#include <filesystem>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../iObject/iUnscalable/iScalable/interface/interface.hpp"
#include "resizer/general/windowResizer.hpp"

namespace ui {
	IWindowResizer* getWindowResizer();
	
	class Window : public sf::RenderWindow{
	protected:
		Interface interface;
		sf::Vector2f minSize;
		
		IWindowResizer* resizer;
		
		void construction();
		
	public:
		explicit Window(const Interface& interface);
		
		Window(const Interface& interface, const sf::String& title, const sf::VideoMode& mode = {1, 1}, const sf::ContextSettings& settings = sf::ContextSettings());
		
		Window(const Interface& interface, const sf::String& title, const sf::ContextSettings& settings);
		
		Window(const Interface& interface, sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
		
		explicit Window(const std::filesystem::path& interface);
		
		Window(const std::filesystem::path& interface, const sf::String& title, const sf::VideoMode& mode = {1, 1}, const sf::ContextSettings& settings = sf::ContextSettings());
		
		Window(const std::filesystem::path& interface, const sf::String& title, const sf::ContextSettings& settings);
		
		Window(const std::filesystem::path& interface, sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
		
		void create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings = sf::ContextSettings());
		
		virtual void create(sf::VideoMode mode, const sf::String& title, const sf::ContextSettings& settings = sf::ContextSettings());
		
		void setSize(const sf::Vector2u& size);
		
		virtual void reCreateMinSize();
		
		virtual void update();
		
		Interface& getInterface();
		
		const sf::Vector2f& getMinSize();
	};
}