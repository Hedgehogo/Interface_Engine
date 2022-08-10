#include "yamlBuilderInitializer.h"

namespace ui {
	void yamlBuilderInit() {
		YamlBuilder<Sizing>::add("ConstSizing", ConstSizing::createFromYaml, {"CS"});
		YamlBuilder<Sizing>::add("RelativeNormalSizing", RelativeNormalSizing::createFromYaml, {"RNormalSizing", "RNS"});
		YamlBuilder<Sizing>::add("RelativeParentSizing", RelativeParentSizing::createFromYaml, {"RParentSizing", "RPS"});
		YamlBuilder<Sizing>::add("ParentCoefficientSizing", ParentCoefficientSizing::createFromYaml, {"ParentCSizing", "PCS"});
		YamlBuilder<Sizing>::add("TargetCoefficientSizing", TargetCoefficientSizing::createFromYaml, {"TargetCSizing", "TCS"});
		YamlBuilder<Sizing>::add("SmartSizing", SmartSizing::createFromYaml, {"SS"});
		
		YamlBuilder<BaseSizing2>::add("Sizing2", Sizing2::createFromYaml);
		YamlBuilder<BaseSizing2>::add("ConstRatioSizing2", ConstRatioSizing2::createFromYaml, {"CRatioS2", "CRS2"});
		
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
        YamlBuilder<IScalable>::add("Button", Button::createFromYaml);
		YamlBuilder<IUnscalable>::addSubtype(YamlBuilder<IScalable>::build);
		//YamlBuilder<BasePanel>::add("ConstPanel", ConstPanel::createFromYaml);
		//YamlBuilder<BasePanel>::add("Panel", Panel::createFromYaml);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<BasePanel>::build);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<IUnscalable>::build);
		
        YamlBuilder<HidePanelInteraction>::add("ClickHidePanelInteraction", ClickHidePanelInteraction::createFromYaml, {"ClickHidePI", "ClickHPI", "CHPI"});
        YamlBuilder<HidePanelInteraction>::add("PointingHidePanelInteraction", PointingHidePanelInteraction::createFromYaml, {"PointingHidePI", "PointingHPI", "PHPI"});
        YamlBuilder<DisplayPanelInteraction>::add("ClickDisplayPanelInteraction", ClickDisplayPanelInteraction::createFromYaml, {"ClickDisplayPI", "ClickDPI", "CDPI"});
        YamlBuilder<DisplayPanelInteraction>::add("PointingDisplayPanelInteraction", PointingDisplayPanelInteraction::createFromYaml, {"PointingDisplayPI", "PointingDPI", "PDPI"});
        YamlBuilder<MovePanelInteraction>::add("CoefficientMovePanelInteraction", CoefficientMovePanelInteraction::createFromYaml, {"CoefficientMovePI", "CoefficientMPI", "CMPI"});
        YamlBuilder<MovePanelInteraction>::add("DontMovePanelInteraction", DontMovePanelInteraction::createFromYaml, {"DontMovePI", "DontMPI", "DMPI"});
        YamlBuilder<MovePanelInteraction>::add("SideMovePanelInteraction", SideMovePanelInteraction::createFromYaml, {"SideMovePI", "SideMPI", "SMPI"});
	}
	
	YamlBuilderInitializer::YamlBuilderInitializer() {
		yamlBuilderInit();
	}
}