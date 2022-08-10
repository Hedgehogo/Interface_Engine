#include "yamlBuilderInitializer.h"

namespace ui {
	void yamlBuilderInit() {
		YamlBuilder<OnlyDrawable>::add("Empty", Empty::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("FullColor", FullColor::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("RoundedRectangle", RoundedRectangle::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Capsule", Capsule::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Caption", Caption::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Sprite", Sprite::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Bar", Bar::createFromYaml);
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<OnlyDrawable>::build);
		YamlBuilder<Layer>::add("LayerWithBackground", LayerWithBackground::createFromYaml, {"LayerWBackground", "LWBa"});
		YamlBuilder<Layer>::add("LayerWithAlternativeObject", LayerWithAlternativeObject::createFromYaml, {"LayerWAObject", "LWAO"});
		YamlBuilder<Layer>::add("LayerWithBorder", LayerWithBorder::createFromYaml, {"LayerWBorder", "LWB"});
		YamlBuilder<Layer>::add("LayerWithBorderVertical", LayerWithBorderVertical::createFromYaml, {"LayerWBorderV", "LWBV"});
		YamlBuilder<Layer>::add("LayerWithBorderHorizontal", LayerWithBorderHorizontal::createFromYaml, {"LayerWBorderH", "LWBH"});
		YamlBuilder<Layer>::add("LayerWithConstBorder", LayerWithConstBorder::createFromYaml, {"LayerWCBorder", "LWCB"});
		YamlBuilder<Layer>::add("LayerWithConstBezel", LayerWithConstBezel::createFromYaml, {"LayerWCBezel", "LWCBe"});
		YamlBuilder<Layer>::add("LayerWithConstRatio", LayerWithConstRatio::createFromYaml, {"LayerWCRatio", "LWCR"});
		YamlBuilder<Layer>::add("LayerWithConstCenter", LayerWithConstCenter::createFromYaml, {"LayerWCCenter", "LWCC"});
		YamlBuilder<Layer>::add("LayerWithMovableBorder", LayerWithMovableBorder::createFromYaml, {"LayerWMBorder", "LWMB"});
		YamlBuilder<Layer>::add("LayerWithPanel", LayerWithPanel::createFromYaml, {"LayerWPanel", "LWP"});
		YamlBuilder<Layer>::add("LayerWithRenderTexture", LayerWithRenderTexture::createFromYaml, {"LayerWRTexture", "LWRT"});
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<Layer>::build);
		YamlBuilder<IUnscalable>::addSubtype(YamlBuilder<IScalable>::build);
		//YamlBuilder<BasePanel>::add("ConstPanel", ConstPanel::createFromYaml);
		//YamlBuilder<BasePanel>::add("Panel", Panel::createFromYaml);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<BasePanel>::build);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<IUnscalable>::build);
	}
	
	YamlBuilderInitializer::YamlBuilderInitializer() {
		yamlBuilderInit();
	}
}