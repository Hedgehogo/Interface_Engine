#pragma once

#include <filesystem>

#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/sprite/sprite.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/capsule/capsule.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/roundedRectangle/roundedRectangle.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/video/videoConvert.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/video/videoFromFile/videoFromFile.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/caption/caption.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/bar/bar.hpp"
#include "../iObject/iUnscalable/iScalable/box/border/boxWithBorderHorizontal.hpp"
#include "../iObject/iUnscalable/iScalable/box/border/boxWithBorderVertical.hpp"
#include "../iObject/iUnscalable/iScalable/box/border/boxWithBorder.hpp"
#include "../iObject/iUnscalable/iScalable/box/constRatio/boxWithConstRatio.hpp"
#include "../iObject/iUnscalable/iScalable/box/constBezel/boxWithConstBezel.hpp"
#include "../iObject/iUnscalable/iScalable/box/constRatioCenter/boxWithConstRatioCenter.hpp"
#include "../iObject/iUnscalable/iScalable/box/constBorder/boxWithConstBorder.hpp"
#include "../iObject/iUnscalable/iScalable/box/panel/boxWithPanel.hpp"
#include "../iObject/iUnscalable/iScalable/box/alternativeObject/boxWithAlternativeObject.hpp"
#include "../iObject/iUnscalable/iScalable/box/movableBorder/boxWithMovableBorder.hpp"
#include "../iObject/iUnscalable/iScalable/box/background/boxWithBackground.hpp"
#include "../iObject/iUnscalable/iScalable/box/shader/boxWithShader.hpp"
#include "../iObject/iUnscalable/iScalable/box/uninteractive/boxUninteractive.hpp"
#include "../iObject/iUnscalable/iScalable/box/makePermeable/boxMakePermeable.hpp"
#include "../iObject/iUnscalable/iScalable/box/scroll/boxScroll.hpp"
#include "../iObject/iUnscalable/iScalable/box/switcher/boxSwitcher.hpp"
#include "../iObject/iUnscalable/iScalable/box/tabs/boxWithTabs.hpp"
#include "ui/iObject/iUnscalable/iScalable/box/switcherTabs/boxSwitcherTabs.hpp"
#include "ui/iObject/iUnscalable/iScalable/box/constCenter/boxWithConstCenter.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/slider/const/constSlider.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/slider/slider/slider.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/general/button.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/buttonWithPanel/buttonWithPanel.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/switch/switcher.hpp"
#include "../iObject/iUnscalable/interactive/text/text.hpp"
#include "../iObject/iUnscalable/interactive/text/textBlock/interactive/interactiveTextBlock.hpp"
#include "../iObject/iUnscalable/interactive/text/textBlock/object/objectTextBlock.hpp"
#include "../iObject/iUnscalable/interactive/text/line/underline/underline.hpp"
#include "../iObject/iUnscalable/interactive/text/line/strikeThrough/strikeThrough.hpp"
#include "../iObject/iUnscalable/interactive/text/interaction/hotKeys/textHotkeyInteraction.hpp"
#include "../iObject/iUnscalable/iScalable/interface/interface.hpp"
#include "../iObject/iUnscalable/iScalable/box/changeableObjects/event/changeObjects/changeObjectEvent.hpp"
#include "../iObject/iUnscalable/iScalable/box/changeableObjects/event/whileChangingObjects/whileChangingObjectsEvent.hpp"
#include "../sizingAndPositioning/sizing/const/constSizing.hpp"
#include "../sizingAndPositioning/sizing/relative/normal/relativeNormalSizing.hpp"
#include "../sizingAndPositioning/sizing/relative/parent/relativeParentSizing.hpp"
#include "../sizingAndPositioning/sizing/coefficient/parent/parentCoefficientSizing.hpp"
#include "../sizingAndPositioning/sizing/coefficient/target/targetCoefficientSizing.hpp"
#include "../sizingAndPositioning/sizing/smart/smartSizing.hpp"
#include "../sizingAndPositioning/sizing/lambda/lambdaSizing.hpp"
#include "../interaction/iInteraction/empty/emptyInteraction.hpp"
#include "../interaction/iInteraction/mouse/lambda/mouseLambdaInteraction.hpp"
#include "../interaction/event/key/openUrl/openUrlEvent.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/switch/event/switcherEvent.hpp"
#include "modules/appendix/yaml-cpp/shared/value/event/set/setSValueEvent.hpp"
#include "../../modules/appendix/yaml-cpp/shared/value/converts/toBool/equals/sConvertToBoolEquals.hpp"
#include "../../modules/appendix/yaml-cpp/shared/value/converts/toBool/greater/sConvertToBoolGreater.hpp"
#include "../../modules/appendix/yaml-cpp/shared/value/converts/toBool/less/sConvertToBoolLess.hpp"
#include "../../modules/appendix/yaml-cpp/shared/value/converts/toBool/lessOrEquals/sConvertToBoolLessOrEquals.hpp"
#include "../../modules/appendix/yaml-cpp/shared/value/converts/toBool/greaterOrEquals/sConvertToBoolGreaterOrEquals.hpp"
#include "../../modules/appendix/yaml-cpp/shared/value/converts/range/general/sConvertRange.hpp"
#include "../animation/animator/unit/animation/animation.hpp"
#include "../animation/animator/unit/prerequisite/prerequisite.hpp"
#include "../animation/animator/unit/match/animatorUnitMatch.hpp"
#include "../animation/animator/unit/prerequisite/velves/withISbool/valveWithISbool.hpp"
#include "../animation/changeVariable/straightLine/changeVariableByStraightLine.hpp"
#include "../animation/changeVariable/brokenLine/changeVariableByBrokenLine.hpp"
#include "../animation/changeVariable/steppedLine/changeVariableBySteppedLine.hpp"
#include "../animation/changeVariable/sinusoid/changeVariableBySinusoid.hpp"
#include "../animation/changeVariable/curve/changeVariableByCurve.hpp"
#include "../debug/boxDebug.hpp"

namespace ui {
	void init(std::filesystem::path modulesList = {}, int argc = 0, char *argv[] = {});
	
	void yamlBuilderInit();
}