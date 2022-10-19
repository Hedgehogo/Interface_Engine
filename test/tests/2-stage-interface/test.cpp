#include "../../createTestProgram/createTestProgram.hpp"
#include "../../testsObjects/testObject/testObject.hpp"
#include "../../testsObjects/testPanel/testPanel.hpp"

TEST(Interface, draw) {
	auto testObject = new TestObject;
	auto testPanel = new TestPanel{};
	auto testInterface = new ui::Interface{testObject};


	testInterface->getPanelManager()->displayPanel(testPanel);

    Program testProgram{
		testInterface,
        {1, 1}
    };

	ASSERT_GT(testObject->getProcessed().draw, 0);

	ASSERT_GT(testPanel->getProcessed().draw, 0);

	ASSERT_GT(testPanel->getProcessed().draw, testObject->getProcessed().draw);
}

TEST(Interface, init) {
	auto testObject = new TestObject;
	auto testPanel = new TestPanel{};
	auto testInterface = new ui::Interface{testObject};


	testInterface->getPanelManager()->displayPanel(testPanel);

	Program testProgram{
		testInterface,
		{1, 1}
	};

	ASSERT_GT(testObject->getProcessed().init.time, 0);

	ASSERT_EQ(testInterface->getRenderTarget(), testObject->getProcessed().init.renderTarget);
	ASSERT_EQ(testInterface->getDrawManager(), testObject->getProcessed().init.drawManager);
	ASSERT_EQ(testInterface->getUpdateManager(), testObject->getProcessed().init.updateManager);
	ASSERT_EQ(testInterface->getInteractionStack(), testObject->getProcessed().init.interactionStack);
	ASSERT_EQ(testInterface->getInteractionManager(), testObject->getProcessed().init.interactionManager);
	ASSERT_EQ(testInterface->getPanelManager(), testObject->getProcessed().init.panelManager);
}

TEST(Interface, resize) {
    auto fullColor = new ui::FullColor{sf::Color::Red};
    ui::Interface interface{fullColor};
    interface.resize({10, 10}, {5, 5});

    ASSERT_TRUE((fullColor->getSize() == sf::Vector2f{10, 10}));
    ASSERT_TRUE((fullColor->getPosition() == sf::Vector2f{5, 5}));
}

TEST(Interface, setSize) {
    auto fullColor = new ui::FullColor{sf::Color::Red};
    ui::Interface interface{fullColor};
    interface.setSize({10, 10});

    ASSERT_TRUE((fullColor->getSize() == sf::Vector2f{10, 10}));
	ASSERT_TRUE((interface.getSize() == sf::Vector2f{10, 10}));
}

TEST(Interface, setPosition) {
    auto fullColor = new ui::FullColor{sf::Color::Red};
    ui::Interface interface{fullColor};
    interface.setPosition({5, 5});

    ASSERT_TRUE((fullColor->getPosition() == sf::Vector2f{5, 5}));
	ASSERT_TRUE((interface.getPosition() == sf::Vector2f{5, 5}));
}

TEST(Interface, move) {
	auto fullColor = new ui::FullColor{sf::Color::Red};
	ui::Interface interface{fullColor};
	interface.setPosition({5, 5});

	ASSERT_TRUE((fullColor->getPosition() == sf::Vector2f{5, 5}));
	ASSERT_TRUE((interface.getPosition() == sf::Vector2f{5, 5}));
}


TEST(Interface, minSize) {
	ui::Interface interface{new TestObject{{10, 10}}};
	ASSERT_TRUE((interface.getMinSize() == sf::Vector2f{ 10, 10 }));
}

TEST(Interface, normalSize) {
	ui::Interface interface{new TestObject{{10, 10}, {20, 20}}};
	ASSERT_TRUE((interface.getNormalSize() == sf::Vector2f{20, 20}));
}

TEST(Interface, copy) {
	auto testObject = new TestObject;

	Program testProgram{
		new ui::Interface{
			testObject
		},
		{1, 1}
	};

	ui::Interface interfaceCopy = *testProgram.interface->copy();

	ASSERT_GT(testObject->getProcessed().copy, 0);

	ASSERT_EQ(interfaceCopy.getNormalSize(), testProgram.interface->getNormalSize());
	ASSERT_EQ(interfaceCopy.getAreaPosition(), testProgram.interface->getAreaPosition());
	ASSERT_EQ(interfaceCopy.getAreaSize(), testProgram.interface->getAreaSize());
	ASSERT_EQ(interfaceCopy.getMinSize(), testProgram.interface->getMinSize());
	ASSERT_EQ(interfaceCopy.getPosition(), testProgram.interface->getPosition());
	ASSERT_EQ(interfaceCopy.getSize(), testProgram.interface->getSize());
	ASSERT_EQ(interfaceCopy.getRenderTarget(), testProgram.interface->getRenderTarget());
	ASSERT_EQ(interfaceCopy.getInteractionStack(), testProgram.interface->getInteractionStack());
}
