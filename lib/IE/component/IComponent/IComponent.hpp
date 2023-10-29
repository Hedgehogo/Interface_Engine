#pragma once

#include "IE/component/IDrawable/DrawManager/DrawManager.hpp"
#include "IE/component/IUpdatable/UpdateManager/UpdateManager.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "IE/animation/AnimationManager/AnimationManager.hpp"
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
			virtual IComponent* make(InitInfo init_info) = 0;
			
			virtual ~Make() = default;
		};
		
		virtual ~IComponent() = default;
		
		virtual void init(InitInfo init_info) = 0;
		
		virtual void set_position(sf::Vector2f position);
		
		virtual void move(sf::Vector2f position);
		
		virtual void set_size(sf::Vector2f size);
		
		virtual sf::Vector2f get_area_position() const = 0;
		
		virtual sf::Vector2f get_position() const;
		
		virtual sf::Vector2f get_area_size() const = 0;
		
		virtual sf::Vector2f get_size() const;
		
		virtual sf::Vector2f get_min_size() const = 0;
		
		virtual sf::Vector2f get_normal_size() const = 0;
		
		virtual bool in_area(sf::Vector2f point_position);
		
		virtual bool in(sf::Vector2f point_position);
		
		virtual void resize(sf::Vector2f size, sf::Vector2f position) = 0;
		
		virtual bool update_interactions(sf::Vector2f mouse_position) = 0;
		
		virtual IComponent* copy() = 0;
		
		static void draw_debug(sf::Vector2f position, sf::Vector2f size, sf::RenderTarget& render_target, size_t hue);
		
		virtual void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset);
	};
}