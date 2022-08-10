#pragma once
#include "../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

#include "../interaction/interactionManager/interactionManager.h"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/fullColor/fullColor.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/bar/bar.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/sprite/sprite.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/caption/caption.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/capsule/capsule.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/roundedRectangle/roundedRectangle.hpp"
#include "../iObject/iUnscalable/iScalable/layer/border/layerWithBorderHorizontal.hpp"
#include "../iObject/iUnscalable/iScalable/layer/border/layerWithBorderVertical.hpp"
#include "../iObject/iUnscalable/iScalable/layer/border/layerWithBorder.hpp"
#include "../iObject/iUnscalable/iScalable/layer/constRatio/layerWithConstRatio.hpp"
#include "../iObject/iUnscalable/iScalable/layer/constBezel/layerWithConstBezel.hpp"
#include "../iObject/iUnscalable/iScalable/layer/constCenter/layerWithConstCenter.hpp"
#include "../iObject/iUnscalable/iScalable/layer/constBorder/layerWithConstBorder.hpp"
#include "../iObject/iUnscalable/iScalable/layer/panel/layerWithPanel.hpp"
#include "../iObject/iUnscalable/iScalable/layer/alternativeObject/layerWithAlternativeObject.hpp"
#include "../iObject/iUnscalable/iScalable/layer/renderTexture/layerWithRenderTexture.hpp"
#include "../iObject/iUnscalable/iScalable/layer/movableBorder/layerWithMovableBorder.hpp"
#include "../iObject/iUnscalable/iScalable/layer/background/layerWithBackground.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/slider/const/constSlider.h"
#include "../iObject/iUnscalable/iScalable/interactive/simple/slider/slider/slider.h"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/button.h"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/buttonWithIndex/buttonWithIndex.h"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/buttonWIthPanel/buttonWithPanel.h"
#include "../iObject/iUnscalable/iScalable/interactive/simple/switch/switch.h"
#include "../iObject/iUnscalable/interactive/text/text.h"
#include "../iObject/iUnscalable/interactive/text/textBlock/simple/textBlock.h"
#include "../iObject/iUnscalable/interactive/text/textBlock/interactive/interactiveTextBlock.h"
#include "../iObject/iUnscalable/interactive/text/textBlock/object/objectTextBlock.h"
#include "../iObject/iUnscalable/interactive/text/line/underline/underline.h"
#include "../iObject/iUnscalable/interactive/text/line/strikeThrough/strikeThrough.h"
#include "../iObject/iUnscalable/iScalable/interface/interface.h"
#include "../debug/debugLayer.h"

namespace ui {
	void yamlBuilderInit();
	
	class YamlBuilderInitializer {
	public:
		YamlBuilderInitializer();
	};
	//static YamlBuilderInitializer _YamlBuilderInitializer;
}
