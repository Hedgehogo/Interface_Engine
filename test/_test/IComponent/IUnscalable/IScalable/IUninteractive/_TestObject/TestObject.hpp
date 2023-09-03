#pragma once

#include <IE/IComponent/ILayout/ILayout.hpp>
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"

template<typename T = ie::IUninteractive::Make>
class TestObject : public ie::IUninteractive {
public:
	struct Make : public ie::IUninteractive::Make {
		std::shared_ptr<T> object;
		
		Make(std::shared_ptr<T> object);
		
		TestObject* make(ie::InitInfo initInfo) override;
	};
	
	TestObject(Make&& make, ie::InitInfo initInfo);
	
	void init(ie::InitInfo initInfo) override;
	
	void resize(sf::Vector2f size, sf::Vector2f position) override;
	
	sf::Vector2f getMinSize() const override;
	
	sf::Vector2f getNormalSize() const override;
	
	TestObject* copy() override;

protected:
	std::shared_ptr<T> object;
};

#include "TestObject.inl"