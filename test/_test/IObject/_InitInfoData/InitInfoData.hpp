#pragma once

#include <SFML/Window.hpp>
#include <_test/_imageEqual.hpp>
#include <ui/drawable/manager/drawManager.hpp>
#include <ui/updatable/manager/updateManager.hpp>
#include <ui/interaction/manager/interactionManager.hpp>
#include <ui/interaction/interactionStack/interactionStack.hpp>
#include <ui/iObject/panel/manager/general/panelManager.hpp>
#include <ui/iObject/initInfo/initInfo.hpp>

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
