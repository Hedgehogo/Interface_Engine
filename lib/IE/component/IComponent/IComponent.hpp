#pragma once

#include "IE/event/EventHandler/EventHandler.hpp"
#include "IE/component/IDrawable/DrawManager/DrawManager.hpp"
#include "IE/component/IUpdatable/UpdateManager/UpdateManager.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "IE/initialization/make/make.hpp"
#include "IE/utils/reduce/reduce.hpp"
#include "IE/utils/vector/vector.hpp"
#include "IE/utils/vector2/vector2.hpp"
#include "InitInfo/InitInfo.hpp"

namespace ie {
	using namespace bp;
	
	class Panel;
	
	class PanelManager;
	
	class IPanelManager;
	
	class IComponent {
	public:
		struct Make {
			virtual auto make(InitInfo init_info) -> IComponent* = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~IComponent() = default;
		
		virtual auto set_position(sf::Vector2f position) -> void;
		
		virtual auto move(sf::Vector2f offset) -> void;
		
		virtual auto set_size(sf::Vector2f size) -> void;
		
		virtual auto get_area_position() const -> sf::Vector2f = 0;
		
		virtual auto get_position() const -> sf::Vector2f;
		
		virtual auto get_area_size() const -> sf::Vector2f = 0;
		
		virtual auto get_size() const -> sf::Vector2f;
		
		virtual auto get_min_size() const -> sf::Vector2f = 0;
		
		virtual auto get_normal_size() const -> sf::Vector2f = 0;
		
		virtual auto in_area(sf::Vector2f point_position) const -> bool;
		
		virtual auto in(sf::Vector2f point_position) const -> bool;
		
		virtual auto resize(sf::Vector2f size, sf::Vector2f position) -> void = 0;
		
		virtual auto handle_event(Event event) -> bool = 0;
		
		static auto draw_debug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render_target, size_t hue) -> void;
		
		virtual auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void;
	};
}