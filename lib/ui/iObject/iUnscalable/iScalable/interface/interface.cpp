#include "interface.hpp"

#include <cmath>
#include "modules/appendix/yaml-cpp/modules/loadModules.hpp"
#include "ui/window/window.hpp"

namespace ui {
	void Interface::init(InitInfo initInfo) {
		if(!initialized) {
			this->window = &initInfo.window;
			this->renderTarget = &initInfo.renderTarget;
			initInfo.drawManager.add(*this);
			initInfo.updateManager.add(*this);
			InitInfo newInitInfo{initInfo.window, initInfo.renderTarget, this->drawManager, this->updateManager, this->interactionManager, *this->interactionStack, this->panelManager};
			object->init(newInitInfo);
			initialized = true;
		}
	}
	
	void Interface::init(Window& window) {
		if(!initialized) {
			this->window = &window;
			this->renderTarget = &window;
			InitInfo initInfo{window, window, drawManager, updateManager, interactionManager, *interactionStack, panelManager};
			object->init(initInfo);
			sf::Vector2f size(max(static_cast<sf::Vector2f>(window.getSize()), object->getMinSize()));
			resize(size, sf::Vector2f(0, 0));
			initialized = true;
		}
	}
	
	Interface::Interface(IScalable* object, AnimationManager animationManager, InteractionStack* interactionStack) :
		object(object), animationManager(std::move(animationManager)), interactionStack(interactionStack), renderTarget(nullptr), interactionManager(), panelManager(), initialized(false), active(true) {
	}
	
	Interface::Interface(const std::string& filePath, AnimationManager animationManager, InteractionStack* interactionStack) :
		Interface(ui::loadFromYaml<ui::IScalable>(filePath), animationManager, interactionStack) {
	}
	
	Interface::Interface(Window& window, IScalable* object, AnimationManager animationManager, InteractionStack* interactionStack) :
		Interface(object, animationManager, interactionStack) {
		init(window);
	}
	
	Interface::Interface(Window& window, const std::string& filePath, AnimationManager animationManager, InteractionStack* interactionStack) :
		Interface(window, ui::loadFromYaml<ui::IScalable>(filePath), animationManager, interactionStack) {
	}
	
	Interface::~Interface() {
		delete object;
	}
	
	bool Interface::isInWindow(sf::Vector2f position) {
		return position.x > 0 && position.x < static_cast<float>(renderTarget->getSize().x) && position.y > 0 && position.y < static_cast<float>(renderTarget->getSize().y);
	}
	
	void Interface::draw() {
		drawManager.draw();
		panelManager.draw();
	}
	
	void Interface::resize(sf::Vector2f size, sf::Vector2f position) {
		object->resize(size, position);
	}
	
	sf::Vector2f Interface::getAreaPosition() const {
		return object->getAreaPosition();
	}
	
	sf::Vector2f Interface::getAreaSize() const {
		return object->getAreaSize();
	}
	
	sf::Vector2f Interface::getMinSize() const {
		return object->getMinSize();
	}
	
	sf::Vector2f Interface::getNormalSize() const {
		return object->getNormalSize();
	}
	
	void Interface::updateCluster(sf::Vector2f mousePosition) {
		interactionManager.update(sf::Vector2i(mousePosition));
	}
	
	void Interface::update() {
		animationManager.update();
		panelManager.update();
		updateManager.update();
		updateCluster(mousePosition);
		active = false;
	}
	
	void Interface::update(sf::Vector2f mousePosition, bool active) {
		if(active) {
			this->updateInteractions(mousePosition);
		} else {
			this->mousePosition = mousePosition;
		}
		this->update();
	}
	
	bool Interface::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		this->mousePosition = mousePosition;
		if(isInWindow(mousePosition) && !interactionManager.isBlocked()) {
			if(!panelManager.updateInteractions(mousePosition, true)) {
				object->updateInteractions(mousePosition);
			}
		}
		return true;
	}
	
	Interface* Interface::copy() {
		Interface* interface{new Interface{object->copy(), *animationManager.copy(), interactionStack}};
		interface->init(*window);
		return interface;
	}
	
	void Interface::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	sf::RenderTarget* Interface::getRenderTarget() {
		return renderTarget;
	}
	
	DrawManager* Interface::getDrawManager() {
		return &drawManager;
	}
	
	UpdateManager* Interface::getUpdateManager() {
		return &updateManager;
	}
	
	InteractionManager* Interface::getInteractionManager() {
		return &interactionManager;
	}
	
	InteractionStack* Interface::getInteractionStack() {
		return interactionStack;
	}
	
	PanelManager* Interface::getPanelManager() {
		return &panelManager;
	}
	
	IScalable* Interface::getObject() {
		return object;
	}
	
	void Interface::setRenderWindowSize(sf::RenderWindow& window) {
		auto newWindowSize{ui::max(getNormalSize(), sf::Vector2f(window.getSize()))};
		sf::Vector2u windowSize = {static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
		window.setSize(windowSize);
		setSize(sf::Vector2f(windowSize));
	}
	
	
	bool DecodePointer<Interface>::decodePointer(const YAML::Node& node, Interface*& interface) {
		interface = new Interface{
			node["object"].as<IScalable*>(),
			convDef(node["animation-manager"], AnimationManager{}),
			convDef(node["interaction-stack"], new InteractionStack{})
		};
		return true;
	}
	
	Interface makeInterface(const std::filesystem::path& filePath, int argc, char *argv[]) {
		if(auto modules =  std::filesystem::path{filePath}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			loadModules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(filePath.string())};
		
		return Interface{
			node["object"].as<IScalable*>(),
			convDef(node["animation-manager"], AnimationManager{}),
			convDef(node["interaction-stack"], new InteractionStack{})
		};
	}
	
	Interface makeInterface(Window& window, const std::filesystem::path& filePath, int argc, char *argv[]) {
		if(auto modules =  std::filesystem::path{filePath}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			loadModules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(filePath.string())};
		
		return Interface{
			window,
			node["object"].as<IScalable*>(),
			convDef(node["animation-manager"], AnimationManager{}),
			convDef(node["interaction-stack"], new InteractionStack{})
		};
	}
	
	Interface* makePrtInterface(Window& window, const std::filesystem::path& filePath, int argc, char *argv[]) {
		if(auto modules =  std::filesystem::path{filePath}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			loadModules(argc, argv, modules);
		 
		YAML::Node node{YAML::LoadFile(filePath.string())};
		
		return new Interface{
			window,
			node["object"].as<IScalable*>(),
			convDef(node["animation-manager"], AnimationManager{}),
			convDef(node["interaction-stack"], new InteractionStack{})
		};
	}
}
