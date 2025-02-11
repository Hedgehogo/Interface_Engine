#pragma once

#include <SFML/Window.hpp>
#include "_image_equal/image_equal.hpp"
#include <IE/shared/DynBuffer/DynBuffer.hpp>
#include <IE/event/EventHandler/EventHandler.hpp>
#include <IE/component/IDrawable/DrawManager/DrawManager.hpp>
#include <IE/component/IUpdatable/UpdateManager/UpdateManager.hpp>
#include <IE/trigger/TriggerManager/TriggerManager.hpp>
#include <IE/panel/IPanelManager/PanelManager/PanelManager.hpp>
#include <IE/component/IComponent/InitInfo/InitInfo.hpp>

struct InitInfoData {
	sf::RenderWindow window{};
	sf::RenderTexture render_target{};
	ie::DynBuffer dyn_buffer{};
	ie::EventHandler event_handler{};
	ie::DrawManager draw_manager{};
	ie::UpdateManager update_manager{};
	ie::TriggerManager trigger_manager{};
	ie::PanelManager panel_manager{};
	
	InitInfoData(sf::Vector2u size = {1, 1});
	
	ie::InitInfo make_init_info();
	
	void render_save(std::filesystem::path path);
	
	bool render_equal(std::filesystem::path path, float precision = 0);
	
	bool render_equal_with_save(std::filesystem::path path, float precision = 0);
};