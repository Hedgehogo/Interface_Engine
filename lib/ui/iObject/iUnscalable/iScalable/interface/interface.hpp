#pragma once

#include "../iScalable.hpp"
#include "../../../panel/manager/general/panelManager.hpp"
#include "../../../../interaction/interactionManager/interactionManager.hpp"
#include "../../../../interaction/interactionStack/interactionStack.hpp"
#include "../../../../interaction/event/wheel/wheelEvent.hpp"

namespace ui {
	class Interface : public IScalable, public IDrawable, public IUpdatable {
	protected:
		sf::RenderTarget* renderTarget;
		DrawManager drawManager;
		UpdateManager updateManager;
		InteractionManager interactionManager;
		InteractionStack* interactionStack;
		PanelManager panelManager;
		AnimationManager animationManager;
		IScalable* object;
		sf::Vector2f mousePosition;
		bool initialized;
		bool active;
		
		void init(InitInfo initInfo) override;
		
		bool isInWindow(sf::Vector2f position);
	
	public:
		void init(sf::RenderTarget& renderTarget);
		
		explicit Interface(IScalable* object, AnimationManager animationManager = AnimationManager{{}}, InteractionStack* interactionStack = new InteractionStack{});
		
		explicit Interface(const std::string& filePath, AnimationManager animationManager = AnimationManager{{}}, InteractionStack* interactionStack = new InteractionStack{});
		
		explicit Interface(sf::RenderTarget& renderTarget, IScalable* object, AnimationManager animationManager = AnimationManager{{}}, InteractionStack* interactionStack = new InteractionStack{});
		
		explicit Interface(sf::RenderTarget& renderTarget, const std::string& filePath, AnimationManager animationManager = AnimationManager{{}}, InteractionStack* interactionStack = new InteractionStack{});
		
		~Interface() override;
		
		[[nodiscard]] sf::RenderTarget* getRenderTarget();
		
		[[nodiscard]] DrawManager* getDrawManager();
		
		[[nodiscard]] UpdateManager* getUpdateManager();
		
		[[nodiscard]] InteractionManager* getInteractionManager();
		
		[[nodiscard]] InteractionStack* getInteractionStack();
		
		[[nodiscard]] PanelManager* getPanelManager();
		
		[[nodiscard]] IScalable* getObject();
		
		void setRenderWindowSize(sf::RenderWindow& window);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getAreaPosition() const override;
		
		sf::Vector2f getAreaSize() const override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
	
	protected:
		void updateCluster(sf::Vector2f mousePosition);
	
	public:
		void update() override;
		
		void update(sf::Vector2f mousePosition, bool active);
		
		Interface* copy() override;
		
		void drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue = 0, uint hueOffset = 36) override;
	};
	
	
	template<>
	struct DecodePointer<Interface> {
		static bool decodePointer(const YAML::Node& node, Interface*& interface);
	};
	
	Interface makeInterface(sf::RenderTarget& renderTarget, const std::string& filePath);
	
	Interface* makePrtInterface(sf::RenderTarget& renderTarget, const std::string& filePath);
}
