cmake_minimum_required(VERSION 3.21)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}
        enums/corner/corner.h
        enums/side/side.h
        enums/size/size.h
        enums/enums.h
        interaction/event/button/buttonEvent.h interaction/event/button/buttonEvent.cpp
        interaction/event/button/empty/emptyEvent.cpp interaction/event/button/empty/emptyEvent.h
        interaction/event/button/simple/buttonEventSimple.cpp interaction/event/button/simple/buttonEventSimple.h
        interaction/event/button/lambdaSimple/buttonEvent_LambdaSimple.cpp interaction/event/button/lambdaSimple/buttonEvent_LambdaSimple.h
        interaction/event/button/addInteraction/addInteractionEvent.cpp interaction/event/button/addInteraction/addInteractionEvent.h
        interaction/event/button/addInteraction/blockInteraction/addBlockInteractionEvent.cpp interaction/event/button/addInteraction/blockInteraction/addBlockInteractionEvent.h
        interaction/event/wheel/wheelEvent.cpp interaction/event/wheel/wheelEvent.h
        interaction/event/wheel/simple/wheelEventSimple.cpp interaction/event/wheel/simple/wheelEventSimple.h
        interaction/iInteraction/iInteraction.h
        interaction/iInteraction/empty/emptyInteraction.cpp interaction/iInteraction/empty/emptyInteraction.h
        interaction/iInteraction/lambda/lambdaInteraction.cpp interaction/iInteraction/lambda/lambdaInteraction.h
        interaction/iInteraction/double/doubleInteraction.cpp interaction/iInteraction/double/doubleInteraction.h
        interaction/iInteraction/mouse/mouseInteraction.cpp interaction/iInteraction/mouse/mouseInteraction.h
        interaction/iInteraction/mouse/lambda/mouseLambdaInteraction.cpp interaction/iInteraction/mouse/lambda/mouseLambdaInteraction.h
        interaction/iInteraction/block/iBlockInteraction.cpp interaction/iInteraction/block/iBlockInteraction.h
        interaction/iInteraction/oneButton/oneButtonInteraction.cpp interaction/iInteraction/oneButton/oneButtonInteraction.h
        interaction/iInteraction/block/pressed/pressedInteraction.cpp interaction/iInteraction/block/pressed/pressedInteraction.h
        interaction/interactionManager/interactionManager.cpp interaction/interactionManager/interactionManager.h
        interaction/interactionStack/interactionStack.cpp interaction/interactionStack/interactionStack.h
        iObject/iObject.h iObject/iObject.cpp
        iObject/iFlat/iFlat.h
        iObject/iFlat/range/range.cpp iObject/iFlat/range/range.h
        iObject/iFlat/iDrawn/iDrawn.cpp iObject/iFlat/iDrawn/iDrawn.h
        iObject/iFlat/iLayer/iLayer.cpp iObject/iFlat/iLayer/iLayer.h
        iObject/iFlat/iDrawn/fullColor/fullColor.cpp iObject/iFlat/iDrawn/fullColor/fullColor.h
        iObject/iFlat/iDrawn/rectangle/rectangle.cpp iObject/iFlat/iDrawn/rectangle/rectangle.h
        iObject/iFlat/iDrawn/capsule/capsule.cpp iObject/iFlat/iDrawn/capsule/capsule.h
        iObject/iFlat/iDrawn/caption/caption.cpp iObject/iFlat/iDrawn/caption/caption.h
        iObject/iFlat/iDrawn/sprite/sprite.cpp iObject/iFlat/iDrawn/sprite/sprite.h
        iObject/iFlat/iDrawn/empty/empty.cpp iObject/iFlat/iDrawn/empty/empty.h
        iObject/iFlat/iDrawn/bar/bar.cpp iObject/iFlat/iDrawn/bar/bar.h
        iObject/iFlat/iLayer/layerWithBorder/layerWithBorder.cpp iObject/iFlat/iLayer/layerWithBorder/layerWithBorder.h
        iObject/iFlat/iLayer/layerWithBorder/layerWithBorderHorizontal.cpp iObject/iFlat/iLayer/layerWithBorder/layerWithBorderHorizontal.h
        iObject/iFlat/iLayer/layerWithBorder/layerWithBorderVertical.cpp iObject/iFlat/iLayer/layerWithBorder/layerWithBorderVertical.h
        iObject/iFlat/iLayer/layerWithConstRatio/layerWithConstRatio.cpp iObject/iFlat/iLayer/layerWithConstRatio/layerWithConstRatio.h
        iObject/iFlat/iLayer/layerWithConstBezel/layerWithConstBezel.cpp iObject/iFlat/iLayer/layerWithConstBezel/layerWithConstBezel.h
        iObject/iFlat/iLayer/layerWithConstBorder/layerWithConstBorder.cpp iObject/iFlat/iLayer/layerWithConstBorder/layerWithConstBorder.h
        iObject/iFlat/iLayer/layerWithConstCenter/layerWithConstCenter.cpp iObject/iFlat/iLayer/layerWithConstCenter/layerWithConstCenter.h
        iObject/iFlat/iLayer/layerWithAlternativeObject/layerWithAlternativeObject.cpp iObject/iFlat/iLayer/layerWithAlternativeObject/layerWithAlternativeObject.h
        iObject/iFlat/iInteractive/iInteractive.cpp iObject/iFlat/iInteractive/iInteractive.h
        iObject/iFlat/iInteractive/simple/interactiveSimple.cpp iObject/iFlat/iInteractive/simple/interactiveSimple.h
        iObject/iFlat/iInteractive/simple/button/button.cpp iObject/iFlat/iInteractive/simple/button/button.h
        iObject/iFlat/iInteractive/simple/button/buttonWithIndex/buttonWithIndex.cpp iObject/iFlat/iInteractive/simple/button/buttonWithIndex/buttonWithIndex.h
        iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/buttonWithPanel.cpp iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/buttonWithPanel.h
        iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/interaction/displayPanelInteraction.h
        iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/interaction/pointingDisplayPanelInteraction/pointingDisplayPanelInteraction.h iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/interaction/pointingDisplayPanelInteraction/pointingDisplayPanelInteraction.cpp
        iObject/iFlat/iInteractive/simple/slider/baseSlider.cpp iObject/iFlat/iInteractive/simple/slider/baseSlider.h
        iObject/iFlat/iInteractive/simple/slider/slider/slider.cpp iObject/iFlat/iInteractive/simple/slider/slider/slider.h
        iObject/iFlat/iInteractive/simple/slider/const/constSlider.cpp iObject/iFlat/iInteractive/simple/slider/const/constSlider.h
        iObject/iFlat/iInteractive/simple/slider/interaction/slideEvent/sliderEvent.cpp iObject/iFlat/iInteractive/simple/slider/interaction/slideEvent/sliderEvent.h
        iObject/iFlat/iInteractive/simple/slider/interaction/wheelEvent/sliderWheelEvent.cpp iObject/iFlat/iInteractive/simple/slider/interaction/wheelEvent/sliderWheelEvent.h
        iObject/iFlat/iInteractive/simple/slider/interaction/interaction/sliderInteraction.cpp iObject/iFlat/iInteractive/simple/slider/interaction/interaction/sliderInteraction.h
        iObject/iFlat/iInteractive/text/text.cpp iObject/iFlat/iInteractive/text/text.h
        iObject/iFlat/iInteractive/text/textBlock/baseTextBlock.cpp iObject/iFlat/iInteractive/text/textBlock/baseTextBlock.h
        iObject/iFlat/iInteractive/text/textBlock/simple/textBlock.cpp iObject/iFlat/iInteractive/text/textBlock/simple/textBlock.h
        iObject/panel/panel.cpp iObject/panel/panel.h
        iObject/panel/interaction/panelInteraction.cpp iObject/panel/interaction/panelInteraction.h
        iObject/panel/interaction/hidePanelInteraction.h
        iObject/panel/interaction/pointingHidePanelInteraction/pointingHidePanelInteraction.cpp iObject/panel/interaction/pointingHidePanelInteraction/pointingHidePanelInteraction.h
        iObject/panel/panelStack/panelStack.cpp iObject/panel/panelStack/panelStack.h
        iObject/iFlat/interface/interface.cpp iObject/iFlat/interface/interface.h
        UI.h
        iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/interaction/displayPanelInteraction.h
        iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/interaction/pointingDisplayPanelInteraction/pointingDisplayPanelInteraction.h
       	iObject/iFlat/iInteractive/simple/button/buttonWIthPanel/interaction/pointingDisplayPanelInteraction/pointingDisplayPanelInteraction.cpp
       	iObject/panel/interaction/panelInteraction.cpp iObject/panel/interaction/panelInteraction.h iObject/panel/interaction/hidePanelInteraction.h
       	iObject/panel/interaction/pointingHidePanelInteraction/pointingHidePanelInteraction.cpp iObject/panel/interaction/pointingHidePanelInteraction/pointingHidePanelInteraction.h
       	iObject/iFlat/iInteractive/text/character/baseCharacter.cpp iObject/iFlat/iInteractive/text/character/baseCharacter.h
       	iObject/iFlat/iInteractive/text/character/simple/character.cpp iObject/iFlat/iInteractive/text/character/simple/character.h
       	iObject/iFlat/iInteractive/text/textBlock/interactive/interactiveTextBlock.cpp iObject/iFlat/iInteractive/text/textBlock/interactive/interactiveTextBlock.h
       	iObject/iFlat/iInteractive/text/textVariables.h)

set(SFML_DIR "\\home\\andrewkoro105\\SFML-2.5.1\\lib\\cmake\\SFML")

set(CMAKE_MODULE_PATH "${cmaKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system)

add_executable(${PROJECT_NAME}_ex main.cpp)

target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})
