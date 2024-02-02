#pragma once

#include <SFML/Window.hpp>
#include "_test/_image_equal/image_equal.hpp"
#include <IE/component/IDrawable/DrawManager/DrawManager.hpp>
#include <IE/component/IUpdatable/UpdateManager/UpdateManager.hpp>
#include <IE/interaction/InteractionManager/InteractionManager.hpp>
#include <IE/interaction/InteractionStack/InteractionStack.hpp>
#include <IE/panel/IPanelManager/PanelManager/PanelManager.hpp>
#include <IE/component/IComponent/InitInfo/InitInfo.hpp>

struct InitInfoData {
	sf::RenderWindow window{};
	sf::RenderTexture render_target{};
	ie::DynBuffer dyn_buffer{};
	ie::DrawManager draw_manager{};
	ie::UpdateManager update_manager{};
	ie::InteractionManager interaction_manager{};
	ie::PanelManager panel_manager{};
	
	InitInfoData(sf::Vector2u size = {1, 1});
	
	ie::InitInfo make_init_info();
	
	void render_save(std::filesystem::path path);
	
	bool render_equal(std::filesystem::path path, float precision = 0);
	
	bool render_equal_with_save(std::filesystem::path path, float precision = 0);
};