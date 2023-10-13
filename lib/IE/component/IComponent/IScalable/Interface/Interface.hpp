#pragma once

#include <filesystem>

#include "../IScalable.hpp"
#include "IE/panel/IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/interaction/InteractionManager/InteractionManager.hpp"
#include "IE/interaction/InteractionStack/InteractionStack.hpp"
#include "IE/interaction/IAction/WheelAction/WheelAction.hpp"

namespace ie {
	class Interface : public virtual IScalable, public virtual IDrawable, public virtual IUpdatable {
	protected:
		bool isInWindow(sf::Vector2f position);
	
	public:
		struct Make : public virtual IScalable::Make {
			BoxPtr<IScalable::Make> object;
			AnimationManager animationManager = AnimationManager{{}};
			BoxPtr<InteractionStack> interactionStack = makeBoxPtr<InteractionStack>();
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				AnimationManager animationManager = AnimationManager{{}},
				BoxPtr<InteractionStack>&& interactionStack = makeBoxPtr<InteractionStack>()
			);
			
			Interface* make(InitInfo initInfo) override;
		};
		
		Interface(Make&& make, InitInfo initInfo);
		
		explicit Interface(
			BoxPtr<IScalable>&& object,
			AnimationManager animationManager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interactionStack = makeBoxPtr<InteractionStack>()
		);
		
		explicit Interface(
			const std::string& filePath,
			AnimationManager animationManager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interactionStack = makeBoxPtr<InteractionStack>()
		);
		
		explicit Interface(
			sf::RenderWindow& window,
			BoxPtr<IScalable>&& object,
			AnimationManager animationManager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interactionStack = makeBoxPtr<InteractionStack>()
		);
		
		explicit Interface(
			sf::RenderWindow& window,
			const std::string& filePath,
			AnimationManager animationManager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interactionStack = makeBoxPtr<InteractionStack>()
		);
		
		explicit Interface(
			sf::RenderWindow& window,
			BoxPtr<IScalable::Make>&& object,
			AnimationManager animationManager = AnimationManager{{}},
			BoxPtr<InteractionStack>&& interactionStack = makeBoxPtr<InteractionStack>()
		);
		
		void init(InitInfo initInfo) override;
		
		void init(sf::RenderWindow& window);
		
		[[nodiscard]] sf::RenderTarget& getRenderTarget();
		
		[[nodiscard]] DrawManager& getDrawManager();
		
		[[nodiscard]] UpdateManager& getUpdateManager();
		
		[[nodiscard]] InteractionManager& getInteractionManager();
		
		[[nodiscard]] InteractionStack& getInteractionStack();
		
		[[nodiscard]] PanelManager& getPanelManager();
		
		[[nodiscard]] IScalable& getObject();
		
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
	
	protected:
		sf::RenderWindow* window;
		sf::RenderTarget* renderTarget;
		DrawManager drawManager;
		UpdateManager updateManager;
		InteractionManager interactionManager;
		BoxPtr<InteractionStack> interactionStack;
		PanelManager panelManager;
		AnimationManager animationManager;
		BoxPtr<IScalable> object;
		sf::Vector2f mousePosition;
		bool initialized;
		bool active;
	};
	
	template<>
	struct DecodePointer<Interface> {
		static bool decodePointer(const YAML::Node& node, Interface*& interface);
	};
	
	Interface makeInterface(const std::filesystem::path& filePath, int argc = 0, char* argv[] = {});
	
	Interface makeInterface(sf::RenderWindow& window, const std::filesystem::path& filePath, int argc = 0, char* argv[] = {});
	
	Interface* makePrtInterface(sf::RenderWindow& window, const std::filesystem::path& filePath, int argc = 0, char* argv[] = {});
}