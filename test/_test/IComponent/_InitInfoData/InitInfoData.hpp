#pragma once

#include <SFML/Window.hpp>
#include <_test/_imageEqual.hpp>
#include <IE/IDrawable/DrawManager/DrawManager.hpp>
#include <IE/updatable/manager/updateManager.hpp>
#include <IE/Interaction/InteractionManager/InteractionManager.hpp>
#include <IE/Interaction/interactionStack/InteractionStack.hpp>
#include <IE/IComponent/Panel/IPanelManager/PanelManager/PanelManager.hpp>
#include <IE/IComponent/InitInfo/InitInfo.hpp>

struct InitInfoData {
	sf::RenderWindow window{};
	sf::RenderTexture renderTarget{};
	ui::DrawManager drawManager{};
	ui::UpdateManager updateManager{};
	ui::InteractionManager interactionManager{};
	ui::InteractionStack interactionStack{};
	ui::PanelManager panelManager{};
	
	InitInfoData(sf::Vector2u size = {1, 1});
	
	ui::InitInfo makeInitInfo();
	
	void renderSave(std::filesystem::path path);
	
	bool renderEqual(std::filesystem::path path);
	
	bool renderEqualWithSave(std::filesystem::path path);
};
