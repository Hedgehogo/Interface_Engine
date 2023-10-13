#pragma once

#include <SFML/Window.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"
#include <IE/component/IDrawable/DrawManager/DrawManager.hpp>
#include <IE/component/IUpdatable/UpdateManager/UpdateManager.hpp>
#include <IE/interaction/InteractionManager/InteractionManager.hpp>
#include <IE/interaction/InteractionStack/InteractionStack.hpp>
#include <IE/panel/IPanelManager/PanelManager/PanelManager.hpp>
#include <IE/component/IComponent/InitInfo/InitInfo.hpp>

struct InitInfoData {
	sf::RenderWindow window{};
	sf::RenderTexture renderTarget{};
	ie::DrawManager drawManager{};
	ie::UpdateManager updateManager{};
	ie::InteractionManager interactionManager{};
	ie::InteractionStack interactionStack{};
	ie::PanelManager panelManager{};
	
	InitInfoData(sf::Vector2u size = {1, 1});
	
	ie::InitInfo makeInitInfo();
	
	void renderSave(std::filesystem::path path);
	
	bool renderEqual(std::filesystem::path path, float precision = 0);
	
	bool renderEqualWithSave(std::filesystem::path path, float precision = 0);
};