#pragma once

#include <SFML/Window.hpp>
#include "_test/_imageEqual/_imageEqual.hpp"
#include <IE/IDrawable/DrawManager/DrawManager.hpp>
#include <IE/IUpdatable/UpdateManager/UpdateManager.hpp>
#include <IE/Interaction/InteractionManager/InteractionManager.hpp>
#include <IE/Interaction/InteractionStack/InteractionStack.hpp>
#include <IE/Panel/IPanelManager/PanelManager/PanelManager.hpp>
#include <IE/IComponent/InitInfo/InitInfo.hpp>

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
	
	bool renderEqual(std::filesystem::path path);
	
	bool renderEqualWithSave(std::filesystem::path path);
};