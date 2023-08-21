#include "Interface.hpp"

#include <cmath>
#include "modules/appendix/yaml-cpp/modules/loadModules.hpp"
#include "IE/Window/Window.hpp"

namespace ui {
	Interface::Make::Make(BoxPtr<IScalable::Make>&& object, AnimationManager animationManager, BoxPtr<InteractionStack>&& interactionStack) :
		object(std::move(object)), animationManager(std::move(animationManager)), interactionStack(std::move(interactionStack)) {
	}
	
	Interface* Interface::Make::make(InitInfo initInfo) {
		return new Interface{std::move(*this), initInfo};
	}
	Interface::Interface(Make&& make, InitInfo initInfo) :
		window(&initInfo.window),
		renderTarget(&initInfo.renderTarget),
		interactionStack(std::move(make.interactionStack)),
		animationManager(std::move(make.animationManager)),
		object(make.object->make(
			{
				initInfo.window,
				initInfo.renderTarget,
				this->drawManager,
				this->updateManager,
				this->interactionManager,
				*this->interactionStack,
				this->panelManager
			}
		)),
		initialized(true),
		active(true) {
		initInfo.drawManager.add(*this);
		initInfo.updateManager.add(*this);
	}
	
	Interface::Interface(BoxPtr<IScalable>&& object, AnimationManager animationManager, BoxPtr<InteractionStack>&& interactionStack) :
		renderTarget(nullptr),
		interactionStack(interactionStack),
		animationManager(std::move(animationManager)),
		object(std::move(object)),
		initialized(false), active(true) {
	}
	
	Interface::Interface(const std::string& filePath, AnimationManager animationManager, BoxPtr<InteractionStack>&& interactionStack) :
		Interface(BoxPtr{ui::loadFromYaml<ui::IScalable>(filePath)}, animationManager, std::move(interactionStack)) {
	}
	
	Interface::Interface(sf::RenderWindow& window, BoxPtr<IScalable>&& object, AnimationManager animationManager, BoxPtr<InteractionStack>&& interactionStack) :
		Interface(std::move(object), animationManager, std::move(interactionStack)) {
		init(window);
	}
	
	Interface::Interface(sf::RenderWindow& window, const std::string& filePath, AnimationManager animationManager, BoxPtr<InteractionStack>&& interactionStack) :
		Interface(window, BoxPtr{ui::loadFromYaml<ui::IScalable>(filePath)}, animationManager, std::move(interactionStack)) {
	}
	
	Interface::Interface(sf::RenderWindow& window, BoxPtr<IScalable::Make>&& object, AnimationManager animationManager, BoxPtr<InteractionStack>&& interactionStack) :
		window(&window),
		renderTarget(&window),
		interactionStack(std::move(interactionStack)),
		animationManager(std::move(animationManager)),
		object(object->make(
			{
				window,
				window,
				this->drawManager,
				this->updateManager,
				this->interactionManager,
				*this->interactionStack,
				this->panelManager
			}
		)),
		initialized(true),
		active(true) {
	}
	
	bool Interface::isInWindow(sf::Vector2f position) {
		return position.x > 0 && position.x < static_cast<float>(renderTarget->getSize().x) && position.y > 0 && position.y < static_cast<float>(renderTarget->getSize().y);
	}
	
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
	
	void Interface::init(sf::RenderWindow& window) {
		if(!initialized) {
			this->window = &window;
			this->renderTarget = &window;
			InitInfo initInfo{window, window, drawManager, updateManager, interactionManager, *interactionStack, panelManager};
			object->init(initInfo);
			sf::Vector2f size(max(static_cast<sf::Vector2f>(static_cast<sf::RenderWindow&>(window).getSize()), object->getMinSize()));
			resize(size, sf::Vector2f(0, 0));
			initialized = true;
		}
	}
	
	sf::RenderTarget& Interface::getRenderTarget() {
		return *renderTarget;
	}
	
	DrawManager& Interface::getDrawManager() {
		return drawManager;
	}
	
	UpdateManager& Interface::getUpdateManager() {
		return updateManager;
	}
	
	InteractionManager& Interface::getInteractionManager() {
		return interactionManager;
	}
	
	InteractionStack& Interface::getInteractionStack() {
		return *interactionStack;
	}
	
	PanelManager& Interface::getPanelManager() {
		return panelManager;
	}
	
	IScalable& Interface::getObject() {
		return *object;
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
		Interface* interface{new Interface{*this}};
		interface->init(*window);
		return interface;
	}
	
	void Interface::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	void Interface::setRenderWindowSize(sf::RenderWindow& window) {
		auto newWindowSize{ui::max(getNormalSize(), sf::Vector2f(window.getSize()))};
		sf::Vector2u windowSize = {static_cast<unsigned>(std::ceil(newWindowSize.x)), static_cast<unsigned>(std::ceil(newWindowSize.y))};
		window.setSize(windowSize);
		setSize(sf::Vector2f(windowSize));
	}
	
	bool DecodePointer<Interface>::decodePointer(const YAML::Node& node, Interface*& interface) {
		interface = new Interface{
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["animation-manager"], AnimationManager{}),
			BoxPtr{convDefPtr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
		return true;
	}
	
	Interface makeInterface(const std::filesystem::path& filePath, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{filePath}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			loadModules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(filePath.string())};
		
		return Interface{
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["animation-manager"], AnimationManager{}),
			BoxPtr{convDefPtr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
	}
	
	Interface makeInterface(sf::RenderWindow& window, const std::filesystem::path& filePath, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{filePath}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			loadModules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(filePath.string())};
		
		return Interface{
			window,
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["animation-manager"], AnimationManager{}),
			BoxPtr{convDefPtr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
	}
	
	Interface* makePrtInterface(sf::RenderWindow& window, const std::filesystem::path& filePath, int argc, char* argv[]) {
		if(auto modules = std::filesystem::path{filePath}.replace_filename("modules.yaml"); std::filesystem::exists(modules))
			loadModules(argc, argv, modules);
		
		YAML::Node node{YAML::LoadFile(filePath.string())};
		
		return new Interface{
			window,
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["animation-manager"], AnimationManager{}),
			BoxPtr{convDefPtr<InteractionStack, InteractionStack>(node["interaction-stack"])}
		};
	}
}
