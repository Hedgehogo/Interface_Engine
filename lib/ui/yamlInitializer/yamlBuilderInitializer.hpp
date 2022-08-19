#pragma once
#include "../../yaml/yamlWithSfml/yamlBuilder/yamlBuilder.hpp"

#include "../interaction/interactionManager/interactionManager.h"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/fullColor/fullColor.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/bar/bar.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/sprite/sprite.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/caption/caption.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/capsule/capsule.hpp"
#include "../iObject/iUnscalable/iScalable/uninteractive/onlyDrawable/roundedRectangle/roundedRectangle.hpp"
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
#include "../iObject/iUnscalable/iScalable/layer/shader/layerWithShader.hpp"
#include "../iObject/iUnscalable/iScalable/layer/layerWithUnInteractive/layerWithUnInteractive.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/slider/const/constSlider.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/slider/slider/slider.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/baseButton.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/general/button.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/button/buttonWIthPanel/buttonWithPanel.hpp"
#include "../iObject/iUnscalable/iScalable/interactive/simple/switch/switch.hpp"
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
