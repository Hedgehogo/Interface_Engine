#pragma once

#include <IE/IComponent/iLayout/ILayout.hpp>
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"

template<typename T = ui::IUninteractive::Make>
class TestObject : public ui::IUninteractive {
public:
	struct Make : public ui::IUninteractive::Make {
		std::shared_ptr<T> object;
		
		Make(std::shared_ptr<T> object);
		
		TestObject* make(ui::InitInfo initInfo) override;
	};
	
	TestObject(Make&& make, ui::InitInfo initInfo);
	
	void init(ui::InitInfo initInfo) override;
	
	void resize(sf::Vector2f size, sf::Vector2f position) override;
	
	sf::Vector2f getMinSize() const override;
	
	sf::Vector2f getNormalSize() const override;
	
	TestObject* copy() override;

protected:
	std::shared_ptr<T> object;
};

#include "TestObject.inl"
