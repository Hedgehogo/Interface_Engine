#pragma once
#include "../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

#include "../interaction/interactionManager/interactionManager.h"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/fullColor/fullColor.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/bar/bar.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/sprite/sprite.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/caption/caption.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/capsule/capsule.hpp"
#include "../iObject/iUnscalable/iScalable/onlyDrawable/roundedRectangle/roundedRectangle.hpp"
#include "../iObject/iUnscalable/iScalable/layer/border/layerWithBorderHorizontal.h"
#include "../iObject/iUnscalable/iScalable/layer/border/layerWithBorderVertical.h"
#include "../iObject/iUnscalable/iScalable/layer/border/layerWithBorder.h"
#include "../iObject/iUnscalable/iScalable/layer/constRatio/layerWithConstRatio.h"
#include "../iObject/iUnscalable/iScalable/layer/constBezel/layerWithConstBezel.h"
#include "../iObject/iUnscalable/iScalable/layer/constCenter/layerWithConstCenter.h"
#include "../iObject/iUnscalable/iScalable/layer/constBorder/layerWithConstBorder.h"
#include "../iObject/iUnscalable/iScalable/layer/panel/layerWithPanel.h"
#include "../iObject/iUnscalable/iScalable/layer/alternativeObject/layerWithAlternativeObject.h"
#include "../iObject/iUnscalable/iScalable/layer/renderTexture/layerWithRenderTexture.h"
#include "../iObject/iUnscalable/iScalable/layer/movableBorder/layerWithMovableBorder.h"
#include "../iObject/iUnscalable/iScalable/layer/background/layerWithBackground.h"
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
