#include "BoxSwitcherTabs.hpp"

#include "../BoxSwitch/BoxSwitch.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include "IE/interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"
#include "IE/modules/yaml-cpp/shared/value/converts/toBool/equals/sConvertToBoolEquals.hpp"
#include "IE/component/IComponent/IScalable/Box/BoxSwitcherTabs/SwitcherTabsAction/SwitcherTabsAction.hpp"

namespace ie {
	BoxSwitcherTabs::Make::Make(std::vector<BoxPtr<IScalable::Make> >&& objects, PSint value, Key key, bool isHorizontal, sf::Vector2f minSize) :
		objects(std::move(objects)), value(std::move(value)), key(key), isHorizontal(isHorizontal), minSize(minSize) {
	}
	
	BoxSwitcherTabs* BoxSwitcherTabs::Make::make(InitInfo initInfo) {
		return new BoxSwitcherTabs{std::move(*this), initInfo};
	}
	
	BoxSwitcherTabs::BoxSwitcherTabs(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		interactive(makeBoxPtr<BasicOneKeyInteraction<BoxSwitcherTabs&>::Make>(
			makeBoxPtr<SwitcherTabsAction::Make>(make.value), make.key
		), initInfo, *this),
		objects(mapMake(std::move(make.objects), initInfo)),
		isHorizontal(make.isHorizontal),
		value(make.value) {
		initInfo.updateManager.add(*this);
	}
	
	BoxSwitcherTabs::BoxSwitcherTabs(std::vector<BoxPtr<IScalable> >&& objects, PSint value, Key key, bool isHorizontal, sf::Vector2f minSize) :
		Box(minSize), interactive(makeBoxPtr<BasicOneKeyInteraction<BoxSwitcherTabs&> >(makeBoxPtr<SwitcherTabsAction>(value), key)),
		objects(std::move(objects)), isHorizontal(isHorizontal), value(value) {
	}
	
	void BoxSwitcherTabs::init(InitInfo initInfo) {
		interactive.init(initInfo, *this);
		for(auto& object: objects) {
			object->init(initInfo);
		}
		initInfo.updateManager.add(*this);
	}
	
	void BoxSwitcherTabs::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
		if(isHorizontal) {
			sf::Vector2f objectSize{size.x / objects.size(), size.y};
			float positionX = position.x;
			for(const auto& object: objects) {
				object->resize(objectSize, {positionX, position.y});
				positionX += objectSize.x;
			}
		} else {
			sf::Vector2f objectSize{size.x, size.y / objects.size()};
			float positionY = position.y;
			for(const auto& object: objects) {
				object->resize(objectSize, {position.x, positionY});
				positionY += objectSize.y;
			}
		}
	}
	
	void BoxSwitcherTabs::update() {
		interactive.update();
	}
	
	bool BoxSwitcherTabs::updateInteractions(sf::Vector2f) {
		interactive.updateInteractions();
		return true;
	}
	
	std::size_t BoxSwitcherTabs::getArraySize() const {
		return objects.size();
	}
	
	IScalable& BoxSwitcherTabs::getObjectAt(std::size_t index) {
		return *objects.at(index);
	}
	
	const IScalable& BoxSwitcherTabs::getObjectAt(std::size_t index) const {
		return *objects.at(index);
	}
	
	int BoxSwitcherTabs::getTab(sf::Vector2f position) {
		return static_cast<int>(isHorizontal ? (position.x - layout.position.x) / (layout.size.x / objects.size()) : (position.y - layout.position.y) / (layout.size.y / objects.size()));
	}
	
	BoxSwitcherTabs* BoxSwitcherTabs::copy() {
		return new BoxSwitcherTabs{*this};
	}
	
	bool DecodePointer<BoxSwitcherTabs>::decodePointer(const YAML::Node& node, BoxSwitcherTabs*& switcherTabs) {
		switcherTabs = new BoxSwitcherTabs{
			node["objects"].as<std::vector<BoxPtr<IScalable> > >(),
			Buffer::get<Sint>(node["value"]),
			convDef(node["key"], Key::MouseLeft),
			convBoolDef(node["direction"], "horizontal", "vertical"),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}