#pragma once

#include "IE/component/IComponent/IComponentLayout/IComponentLayout.hpp"
#include "IE/component/IComponent/IScalable/INonInteractive/INonInteractive.hpp"

template<typename T = ie::INonInteractive::Make>
class TestObject : public ie::INonInteractive {
public:
	struct Make : public ie::INonInteractive::Make {
		std::shared_ptr<T> object;
		
		Make(std::shared_ptr<T> object);
		
		TestObject* make(ie::InitInfo init_info) override;
	};
	
	TestObject(Make&& make, ie::InitInfo init_info);
	
	void init(ie::InitInfo init_info) override;
	
	void resize(sf::Vector2f size, sf::Vector2f position) override;
	
	sf::Vector2f get_min_size() const override;
	
	sf::Vector2f get_normal_size() const override;
	
	TestObject* copy() override;

protected:
	std::shared_ptr<T> object;
};

#include "TestObject.inl"