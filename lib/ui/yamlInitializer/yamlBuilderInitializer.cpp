#include "yamlBuilderInitializer.hpp"

namespace ui {
	void yamlBuilderInit() {
		YamlBuilder<Sizing>::add("ConstSizing", ConstSizing::createFromYaml, {"CS"});
		YamlBuilder<Sizing>::add("RelativeNormalSizing", RelativeNormalSizing::createFromYaml, {"RNormalSizing", "RNS"});
		YamlBuilder<Sizing>::add("RelativeParentSizing", RelativeParentSizing::createFromYaml, {"RParentSizing", "RPS"});
		YamlBuilder<Sizing>::add("ParentCoefficientSizing", ParentCoefficientSizing::createFromYaml, {"ParentCSizing", "PCS"});
		YamlBuilder<Sizing>::add("TargetCoefficientSizing", TargetCoefficientSizing::createFromYaml, {"TargetCSizing", "TCS"});
		YamlBuilder<Sizing>::add("SmartSizing", SmartSizing::createFromYaml, {"SS"});
		
		YamlBuilder<BaseSizing2>::add("Sizing2", Sizing2::createFromYaml, {"S2"});
		YamlBuilder<BaseSizing2>::add("ConstRatioSizing2", ConstRatioSizing2::createFromYaml, {"CRatioS2", "CRS2"});
		
		YamlBuilder<Positioning>::add("InternalPositioning", InternalPositioning::createFromYaml, {"IPos", "IP"});
		YamlBuilder<Positioning>::add("InternalTargetPositioning", InternalTargetPositioning::createFromYaml, {"ITargetPos", "ITP"});
		YamlBuilder<Positioning>::add("MatchPositioning", MatchPositioning::createFromYaml, {"MPos", "MP"});
		YamlBuilder<Positioning>::add("MatchTargetPositioning", MatchTargetPositioning::createFromYaml, {"MTargetPos", "MTP"});
		YamlBuilder<Positioning>::add("MatchSidesPositioning", MatchSidesPositioning::createFromYaml, {"MSidesPos", "MSP"});
		
		YamlBuilder<BasePositioning2>::add("Positioning2", Positioning2::createFromYaml, {"Pos2", "P2"});
		YamlBuilder<BasePositioning2>::add("InternalPositioning2", InternalPositioning2::createFromYaml, {"InternalPos2", "IP2"});
		
		YamlBuilder<HidePanelInteraction>::add("ClickHidePanelInteraction", ClickHidePanelInteraction::createFromYaml, {"ClickHidePI", "ClickHPI", "CHPI"});
		YamlBuilder<HidePanelInteraction>::add("PointingHidePanelInteraction", PointingHidePanelInteraction::createFromYaml, {"PointingHidePI", "PointingHPI", "PHPI"});
		YamlBuilder<DisplayPanelInteraction>::add("ClickDisplayPanelInteraction", ClickDisplayPanelInteraction::createFromYaml, {"ClickDisplayPI", "ClickDPI", "CDPI"});
		YamlBuilder<DisplayPanelInteraction>::add("PointingDisplayPanelInteraction", PointingDisplayPanelInteraction::createFromYaml, {"PointingDisplayPI", "PointingDPI", "PDPI"});
		YamlBuilder<MovePanelInteraction>::add("CoefficientMovePanelInteraction", CoefficientMovePanelInteraction::createFromYaml, {"CoefficientMovePI", "CoefficientMPI", "CMPI"});
		YamlBuilder<MovePanelInteraction>::add("DontMovePanelInteraction", DontMovePanelInteraction::createFromYaml, {"DontMovePI", "DontMPI", "DMPI"});
		YamlBuilder<MovePanelInteraction>::add("SideMovePanelInteraction", SideMovePanelInteraction::createFromYaml, {"SideMovePI", "SideMPI", "SMPI"});
		
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
		YamlBuilder<Layer>::add("LayerWithShader", LayerWithShader::createFromYaml, {"LWS"});
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<Layer>::build);
		YamlBuilder<BaseSlider>::add("Slider", Slider::createFromYaml);
		YamlBuilder<BaseSlider>::add("ConstSlider", ConstSlider::createFromYaml);
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<BaseSlider>::build);
		YamlBuilder<IScalable>::add("ButtonWithPanel", ButtonWithPanel::createFromYaml, {"ButtonWPanel"});
        YamlBuilder<IScalable>::add("Button", Button::createFromYaml);
		YamlBuilder<IScalable>::add("Switch", Switch::createFromYaml);
		YamlBuilder<IUnscalable>::addSubtype(YamlBuilder<IScalable>::build);
		YamlBuilder<BasePanel>::add("ConstPanel", ConstPanel::createFromYaml);
		YamlBuilder<BasePanel>::add("Panel", Panel::createFromYaml);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<BasePanel>::build);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<IUnscalable>::build);
	}
	
	YamlBuilderInitializer::YamlBuilderInitializer() {
		yamlBuilderInit();
	}
}