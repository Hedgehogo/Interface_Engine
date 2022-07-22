cmake_minimum_required(VERSION 3.21)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}
        enums/corner/corner.h
        enums/side/side.h
        enums/size/size.h
        enums/location/location.h
        enums/location2/location2.cpp enums/location2/location2.h
        enums/enums.h
        sizingAndPositioning/sizing/sizing.cpp sizingAndPositioning/sizing/sizing.h
        sizingAndPositioning/sizing/const/constSizing.cpp sizingAndPositioning/sizing/const/constSizing.h
        sizingAndPositioning/sizing/relative/parent/relativeParentSizing.cpp sizingAndPositioning/sizing/relative/parent/relativeParentSizing.h
        sizingAndPositioning/sizing/relative/normal/relativeNormalSizing.cpp sizingAndPositioning/sizing/relative/normal/relativeNormalSizing.h
        sizingAndPositioning/sizing/coefficient/parent/parentCoefficientSizing.cpp sizingAndPositioning/sizing/coefficient/parent/parentCoefficientSizing.h
        sizingAndPositioning/sizing/coefficient/target/targetCoefficientSizing.cpp sizingAndPositioning/sizing/coefficient/target/targetCoefficientSizing.h
        sizingAndPositioning/sizing/smart/smartSizing.cpp sizingAndPositioning/sizing/smart/smartSizing.h
        sizingAndPositioning/sizing/lambda/lambdaSizing.cpp sizingAndPositioning/sizing/lambda/lambdaSizing.h
        sizingAndPositioning/sizing2/baseSizing2.cpp sizingAndPositioning/sizing2/baseSizing2.h
        sizingAndPositioning/sizing2/general/sizing2.cpp sizingAndPositioning/sizing2/general/sizing2.h
        sizingAndPositioning/sizing2/lambda/lambdaSizing2.cpp sizingAndPositioning/sizing2/lambda/lambdaSizing2.h
        sizingAndPositioning/sizing2/constRatio/constRatioSizing2.cpp sizingAndPositioning/sizing2/constRatio/constRatioSizing2.h
        sizingAndPositioning/positioning/positioning.cpp sizingAndPositioning/positioning/positioning.h
        sizingAndPositioning/positioning/internal/internalPositioning.cpp sizingAndPositioning/positioning/internal/internalPositioning.h
        sizingAndPositioning/positioning/internal/target/internalTargetPositioning.cpp sizingAndPositioning/positioning/internal/target/internalTargetPositioning.h
        sizingAndPositioning/positioning/match/matchPositioning.cpp sizingAndPositioning/positioning/match/matchPositioning.h
        sizingAndPositioning/positioning/match/sides/matchSidesPositioning.cpp sizingAndPositioning/positioning/match/sides/matchSidesPositioning.h
        sizingAndPositioning/positioning/match/target/matchTargetPositioning.cpp sizingAndPositioning/positioning/match/target/matchTargetPositioning.h
        sizingAndPositioning/positioning/lambda/lambdaPositioning.cpp sizingAndPositioning/positioning/lambda/lambdaPositioning.h
        sizingAndPositioning/positioning2/basePositioning2.cpp sizingAndPositioning/positioning2/basePositioning2.h
        sizingAndPositioning/positioning2/general/positioning2.cpp sizingAndPositioning/positioning2/general/positioning2.h
        sizingAndPositioning/positioning2/lambda/lambdaPositioning2.cpp sizingAndPositioning/positioning2/lambda/lambdaPositioning2.h
        sizingAndPositioning/sizingAndPositioning.h
        interaction/event/button/buttonEvent.cpp interaction/event/button/buttonEvent.h
        interaction/event/button/empty/emptyEvent.cpp interaction/event/button/empty/emptyEvent.h
        interaction/event/button/simple/buttonEventSimple.cpp interaction/event/button/simple/buttonEventSimple.h
        interaction/event/button/lambdaSimple/buttonEvent_LambdaSimple.cpp interaction/event/button/lambdaSimple/buttonEvent_LambdaSimple.h
        interaction/event/button/addInteraction/addInteractionEvent.cpp interaction/event/button/addInteraction/addInteractionEvent.h
        interaction/event/button/addInteraction/blockInteraction/addBlockInteractionEvent.cpp interaction/event/button/addInteraction/blockInteraction/addBlockInteractionEvent.h
        interaction/event/wheel/wheelEvent.cpp interaction/event/wheel/wheelEvent.h
        interaction/event/wheel/simple/wheelEventSimple.cpp interaction/event/wheel/simple/wheelEventSimple.h
        interaction/iInteraction/iInteraction.cpp interaction/iInteraction/iInteraction.h
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
        iObject/iObject.cpp iObject/iObject.h
        iObject/iUnscalable/iUnscalable.h
        iObject/layout/layout.cpp iObject/layout/layout.h
        iObject/layout/object/layoutWithObject.cpp iObject/layout/object/layoutWithObject.h
        iObject/layout/twoObjects/layoutWithTwoObjects.cpp iObject/layout/twoObjects/layoutWithTwoObjects.h
        iObject/layout/objectsArray/layoutWithObjectsArray.cpp iObject/layout/objectsArray/layoutWithObjectsArray.h
        iObject/layout/background/layoutWithBackground.cpp iObject/layout/background/layoutWithBackground.h
        iObject/iUnscalable/iScalable/iScalable.h
        iObject/iUnscalable/iScalable/iDrawable/iDrawable.cpp iObject/iUnscalable/iScalable/iDrawable/iDrawable.h
        iObject/iUnscalable/iScalable/iLayer/iLayer.cpp iObject/iUnscalable/iScalable/iLayer/iLayer.h
        iObject/iUnscalable/iScalable/iDrawable/fullColor/fullColor.cpp iObject/iUnscalable/iScalable/iDrawable/fullColor/fullColor.h
        iObject/iUnscalable/iScalable/iDrawable/roundedRectangle/roundedRectangle.cpp iObject/iUnscalable/iScalable/iDrawable/roundedRectangle/roundedRectangle.h
        iObject/iUnscalable/iScalable/iDrawable/capsule/capsule.cpp iObject/iUnscalable/iScalable/iDrawable/capsule/capsule.h
        iObject/iUnscalable/iScalable/iDrawable/caption/caption.cpp iObject/iUnscalable/iScalable/iDrawable/caption/caption.h
        iObject/iUnscalable/iScalable/iDrawable/sprite/sprite.cpp iObject/iUnscalable/iScalable/iDrawable/sprite/sprite.h
        iObject/iUnscalable/iScalable/iDrawable/empty/empty.cpp iObject/iUnscalable/iScalable/iDrawable/empty/empty.h
        iObject/iUnscalable/iScalable/iDrawable/bar/bar.cpp iObject/iUnscalable/iScalable/iDrawable/bar/bar.h
        iObject/iUnscalable/iScalable/iLayer/border/layerWithBorder.cpp iObject/iUnscalable/iScalable/iLayer/border/layerWithBorder.h
        iObject/iUnscalable/iScalable/iLayer/border/layerWithBorderHorizontal.cpp iObject/iUnscalable/iScalable/iLayer/border/layerWithBorderHorizontal.h
        iObject/iUnscalable/iScalable/iLayer/border/layerWithBorderVertical.cpp iObject/iUnscalable/iScalable/iLayer/border/layerWithBorderVertical.h
        iObject/iUnscalable/iScalable/iLayer/constRatio/layerWithConstRatio.cpp iObject/iUnscalable/iScalable/iLayer/constRatio/layerWithConstRatio.h
        iObject/iUnscalable/iScalable/iLayer/constBezel/layerWithConstBezel.cpp iObject/iUnscalable/iScalable/iLayer/constBezel/layerWithConstBezel.h
        iObject/iUnscalable/iScalable/iLayer/constBorder/layerWithConstBorder.cpp iObject/iUnscalable/iScalable/iLayer/constBorder/layerWithConstBorder.h
        iObject/iUnscalable/iScalable/iLayer/constCenter/layerWithConstCenter.cpp iObject/iUnscalable/iScalable/iLayer/constCenter/layerWithConstCenter.h
        iObject/iUnscalable/iScalable/iLayer/panel/layerWithPanel.cpp iObject/iUnscalable/iScalable/iLayer/panel/layerWithPanel.h
        iObject/iUnscalable/iScalable/iLayer/alternativeObject/layerWithAlternativeObject.cpp iObject/iUnscalable/iScalable/iLayer/alternativeObject/layerWithAlternativeObject.h
        iObject/iUnscalable/iScalable/iLayer/movableBorder/layerWithMovableBorder.cpp iObject/iUnscalable/iScalable/iLayer/movableBorder/layerWithMovableBorder.h
        iObject/iUnscalable/iScalable/iLayer/movableBorder/interaction/event/movableBorderEvent.cpp iObject/iUnscalable/iScalable/iLayer/movableBorder/interaction/event/movableBorderEvent.h
        iObject/iUnscalable/iScalable/iLayer/renderTexture/layerWithRenderTexture.cpp iObject/iUnscalable/iScalable/iLayer/renderTexture/layerWithRenderTexture.h
        iObject/iUnscalable/iScalable/iLayer/background/layerWithBackground.cpp
        iObject/iUnscalable/iScalable/iLayer/background/layerWithBackground.h
        debug/debugLayer.cpp debug/debugLayer.h
        iObject/iUnscalable/iInteractive/iInteractive.cpp iObject/iUnscalable/iInteractive/iInteractive.h
        iObject/iUnscalable/iScalable/interactive/simple/interactiveSimple.cpp iObject/iUnscalable/iScalable/interactive/simple/interactiveSimple.h
        iObject/iUnscalable/iScalable/interactive/simple/button/button.cpp iObject/iUnscalable/iScalable/interactive/simple/button/button.h
        iObject/iUnscalable/iScalable/interactive/simple/button/buttonWithIndex/buttonWithIndex.cpp iObject/iUnscalable/iScalable/interactive/simple/button/buttonWithIndex/buttonWithIndex.h
        iObject/iUnscalable/iScalable/interactive/simple/button/buttonWIthPanel/buttonWithPanel.cpp iObject/iUnscalable/iScalable/interactive/simple/button/buttonWIthPanel/buttonWithPanel.h
        iObject/iUnscalable/iScalable/interactive/simple/slider/baseSlider.cpp iObject/iUnscalable/iScalable/interactive/simple/slider/baseSlider.h
        iObject/iUnscalable/iScalable/interactive/simple/slider/slider/slider.cpp iObject/iUnscalable/iScalable/interactive/simple/slider/slider/slider.h
        iObject/iUnscalable/iScalable/interactive/simple/slider/const/constSlider.cpp iObject/iUnscalable/iScalable/interactive/simple/slider/const/constSlider.h
        iObject/iUnscalable/iScalable/interactive/simple/slider/interaction/slideEvent/sliderEvent.cpp iObject/iUnscalable/iScalable/interactive/simple/slider/interaction/slideEvent/sliderEvent.h
        iObject/iUnscalable/iScalable/interactive/simple/slider/interaction/wheelEvent/sliderWheelEvent.cpp iObject/iUnscalable/iScalable/interactive/simple/slider/interaction/wheelEvent/sliderWheelEvent.h
        iObject/iUnscalable/iScalable/interactive/simple/slider/interaction/interaction/sliderInteraction.cpp iObject/iUnscalable/iScalable/interactive/simple/slider/interaction/interaction/sliderInteraction.h
        iObject/iUnscalable/iInteractive/text/text.cpp iObject/iUnscalable/iInteractive/text/text.h
        iObject/iUnscalable/iInteractive/text/textVariables.h
        iObject/iUnscalable/iInteractive/text/character/baseCharacter.cpp iObject/iUnscalable/iInteractive/text/character/baseCharacter.h
        iObject/iUnscalable/iInteractive/text/character/simple/character.cpp iObject/iUnscalable/iInteractive/text/character/simple/character.h
        iObject/iUnscalable/iInteractive/text/character/object/objectCharacter.cpp
        iObject/iUnscalable/iInteractive/text/character/object/objectCharacter.h
        iObject/iUnscalable/iInteractive/text/textBlock/baseTextBlock.cpp iObject/iUnscalable/iInteractive/text/textBlock/baseTextBlock.h
        iObject/iUnscalable/iInteractive/text/textBlock/simple/textBlock.cpp iObject/iUnscalable/iInteractive/text/textBlock/simple/textBlock.h
        iObject/iUnscalable/iInteractive/text/textBlock/interactive/interactiveTextBlock.cpp iObject/iUnscalable/iInteractive/text/textBlock/interactive/interactiveTextBlock.h
        iObject/iUnscalable/iInteractive/text/textBlock/object/objectTextBlock.cpp
        iObject/iUnscalable/iInteractive/text/textBlock/object/objectTextBlock.h
        iObject/panel/panel/basePanel.cpp iObject/panel/panel/basePanel.h
        iObject/panel/panel/const/constPanel.cpp iObject/panel/panel/const/constPanel.h
        iObject/panel/panel/general/panel.cpp iObject/panel/panel/general/panel.h
        iObject/panel/panel/interaction/basePanelInteraction.cpp iObject/panel/panel/interaction/basePanelInteraction.h
        iObject/panel/panel/interaction/general/panelInteraction.cpp iObject/panel/panel/interaction/general/panelInteraction.h
        iObject/panel/panel/interaction/click/clickPanelInteraction.cpp iObject/panel/panel/interaction/click/clickPanelInteraction.h
        iObject/panel/panel/interaction/click/event/panelEvent.cpp iObject/panel/panel/interaction/click/event/panelEvent.h
        iObject/panel/panel/interaction/display/displayPanelInteraction.cpp iObject/panel/panel/interaction/display/displayPanelInteraction.h
        iObject/panel/panel/interaction/display/pointing/pointingDisplayPanelInteraction.h iObject/panel/panel/interaction/display/pointing/pointingDisplayPanelInteraction.cpp
        iObject/panel/panel/interaction/display/click/event/displayPanelEvent.cpp iObject/panel/panel/interaction/display/click/event/displayPanelEvent.h
        iObject/panel/panel/interaction/display/click/clickDisplayPanelInteraction.cpp iObject/panel/panel/interaction/display/click/clickDisplayPanelInteraction.h
        iObject/panel/panel/interaction/hide/hidePanelInteraction.cpp iObject/panel/panel/interaction/hide/hidePanelInteraction.h
        iObject/panel/panel/interaction/hide/pointing/pointingHidePanelInteraction.cpp iObject/panel/panel/interaction/hide/pointing/pointingHidePanelInteraction.h
        iObject/panel/panel/interaction/hide/click/clickHidePanelInteraction.cpp iObject/panel/panel/interaction/hide/click/clickHidePanelInteraction.h
        iObject/panel/panel/interaction/hide/click/event/hidePanelEvent.cpp iObject/panel/panel/interaction/hide/click/event/hidePanelEvent.h
        iObject/panel/panel/interaction/move/movePanelInteraction.cpp iObject/panel/panel/interaction/move/movePanelInteraction.h
        iObject/panel/panel/interaction/move/coefficient/coefficientMovePanelInteraction.cpp iObject/panel/panel/interaction/move/coefficient/coefficientMovePanelInteraction.h
        iObject/panel/panel/interaction/move/dont/dontMovePanelInteraction.cpp iObject/panel/panel/interaction/move/dont/dontMovePanelInteraction.h
        iObject/panel/panel/interaction/move/side/sideMovePanelInteraction.cpp iObject/panel/panel/interaction/move/side/sideMovePanelInteraction.h
        iObject/panel/panelManager/panelManager.cpp iObject/panel/panelManager/panelManager.h
        iObject/iUnscalable/iScalable/interface/interface.cpp iObject/iUnscalable/iScalable/interface/interface.h
        UI.h
        )


set(SFML_PATH_1 "E:\\SFML-2.5.1\\lib\\cmake\\SFML")
set(SFML_PATH_2 "C:\\SFML-2.5.1-clion\\lib\\cmake\\SFML")
set(SFML_PATH_3 "\\home\\andrewkoro105\\SFML-2.5.1\\lib\\cmake\\SFML")

if(EXISTS ${SFML_PATH_1} OR EXISTS ${SFML_PATH_2})
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

if(EXISTS ${SFML_PATH_1})
    set(SFML_DIR ${SFML_PATH_1})
elseif(EXISTS ${SFML_PATH_2})
    set(SFML_DIR ${SFML_PATH_2})
else()
    set(SFML_DIR ${SFML_PATH_3})
endif()

set(CMAKE_MODULE_PATH "${cmaKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-system)

#[[set_target_properties(Interface_Engine PROPERTIES PUBLIC_HEADER "UI.h")

export(TARGETS Interface_Engine FILE Interface_Engine-config.cmake)

install(TARGETS Interface_Engine ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/public_headers")]]

add_executable(${PROJECT_NAME}_ex main.cpp)

#find_library(`Yes_Science` Interface_Engine)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
