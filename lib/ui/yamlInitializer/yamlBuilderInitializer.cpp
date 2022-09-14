#include "yamlBuilderInitializer.hpp"

namespace ui {
	void yamlBuilderInit() {
		YamlBuilder<Sizing>::add(ConstSizing::createFromYaml, "ConstSizing", {"CS"});
		YamlBuilder<Sizing>::add(RelativeNormalSizing::createFromYaml, "RelativeNormalSizing", {"RNormalSizing", "RNS"});
		YamlBuilder<Sizing>::add(RelativeParentSizing::createFromYaml, "RelativeParentSizing", {"RParentSizing", "RPS"});
		YamlBuilder<Sizing>::add(ParentCoefficientSizing::createFromYaml, "ParentCoefficientSizing", {"ParentCSizing", "PCS"});
		YamlBuilder<Sizing>::add(TargetCoefficientSizing::createFromYaml, "TargetCoefficientSizing", {"TargetCSizing", "TCS"});
		YamlBuilder<Sizing>::add(SmartSizing::createFromYaml, "SmartSizing", {"SS"});
		
		YamlBuilder<BaseSizing2>::add(Sizing2::createFromYaml, "Sizing2", {"S2"});
		YamlBuilder<BaseSizing2>::add(ConstRatioSizing2::createFromYaml, "ConstRatioSizing2", {"CRatioS2", "CRS2"});
		
		YamlBuilder<Positioning>::add(InternalPositioning::createFromYaml, "InternalPositioning", {"IPos", "IP"});
		YamlBuilder<Positioning>::add(InternalTargetPositioning::createFromYaml, "InternalTargetPositioning", {"ITargetPos", "ITP"});
		YamlBuilder<Positioning>::add(MatchPositioning::createFromYaml, "MatchPositioning", {"MPos", "MP"});
		YamlBuilder<Positioning>::add(MatchTargetPositioning::createFromYaml, "MatchTargetPositioning", {"MTargetPos", "MTP"});
		YamlBuilder<Positioning>::add(MatchSidesPositioning::createFromYaml, "MatchSidesPositioning", {"MSidesPos", "MSP"});
		
		YamlBuilder<BasePositioning2>::add(Positioning2::createFromYaml, "Positioning2", {"Pos2", "P2"});
		YamlBuilder<BasePositioning2>::add(InternalPositioning2::createFromYaml, "InternalPositioning2", {"InternalPos2", "IP2"});
		
		YamlBuilder<HidePanelInteraction>::add(DontHidePanelInteraction::createFromYaml, "DontHidePanelInteraction", {"DontHidePI", "DontHPI", "DHPI"});
		YamlBuilder<HidePanelInteraction>::add(ClickHidePanelInteraction::createFromYaml, "ClickHidePanelInteraction", {"ClickHidePI", "ClickHPI", "CHPI"});
		YamlBuilder<HidePanelInteraction>::add(PointingHidePanelInteraction::createFromYaml, "PointingHidePanelInteraction", {"PointingHidePI", "PointingHPI", "PHPI"});
		YamlBuilder<BasePanelInteraction>::addSubtype(YamlBuilder<HidePanelInteraction>::build);
		YamlBuilder<DisplayPanelInteraction>::add(ClickDisplayPanelInteraction::createFromYaml, "ClickDisplayPanelInteraction", {"ClickDisplayPI", "ClickDPI", "CDPI"});
		YamlBuilder<DisplayPanelInteraction>::add(PointingDisplayPanelInteraction::createFromYaml, "PointingDisplayPanelInteraction", {"PointingDisplayPI", "PointingDPI", "PDPI"});
		YamlBuilder<BasePanelInteraction>::addSubtype(YamlBuilder<DisplayPanelInteraction>::build);
		YamlBuilder<MovePanelInteraction>::add(CoefficientMovePanelInteraction::createFromYaml, "CoefficientMovePanelInteraction", {"CoefficientMovePI", "CoefficientMPI", "CMPI"});
		YamlBuilder<MovePanelInteraction>::add(DontMovePanelInteraction::createFromYaml, "DontMovePanelInteraction", {"DontMovePI", "DontMPI", "DMPI"});
		YamlBuilder<MovePanelInteraction>::add(SideMovePanelInteraction::createFromYaml, "SideMovePanelInteraction", {"SideMovePI", "SideMPI", "SMPI"});
		YamlBuilder<BasePanelInteraction>::addSubtype(YamlBuilder<MovePanelInteraction>::build);
		YamlBuilder<IInteraction>::addSubtype(YamlBuilder<BasePanelInteraction>::build);

        YamlBuilder<BaseLine>::add(Underline::createFromYaml, "Underline", {"U"});
        YamlBuilder<BaseLine>::add(StrikeThrough::createFromYaml, "StrikeThrough", {"ST"});
        YamlBuilder<BaseTextBlock>::add(TextBlock::createFromYaml, "TextBlock", {"TB"});
        YamlBuilder<BaseTextBlock>::add(InteractiveTextBlock::createFromYaml, "InteractiveTextBlock", {"ITB"});
        YamlBuilder<BaseTextBlock>::add(ObjectTextBlock::createFromYaml, "ObjectTextBlock", {"OTB"});
        YamlBuilder<BaseResizer>::add(Resizer::createFromYaml, "Resizer", {"R"});
		
		YamlBuilder<OnlyDrawable>::add(Empty::createFromYaml, "Empty");
		YamlBuilder<OnlyDrawable>::add(FullColor::createFromYaml, "FullColor");
		YamlBuilder<OnlyDrawable>::add(RoundedRectangle::createFromYaml, "RoundedRectangle");
		YamlBuilder<OnlyDrawable>::add(Capsule::createFromYaml, "Capsule");
		YamlBuilder<OnlyDrawable>::add(Sprite::createFromYaml, "Sprite");
		YamlBuilder<IUninteractive>::addSubtype(YamlBuilder<OnlyDrawable>::build);
		YamlBuilder<IUninteractive>::add(Bar::createFromYaml, "Bar");
		YamlBuilder<IUninteractive>::add(Caption::createFromYaml, "Caption");
		YamlBuilder<IUninteractive>::add(UninteractiveLayer::createFromYaml, "LayerWithUnInteractive", {"LWUnInteractive", "LWUI"});
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<IUninteractive>::build);
		YamlBuilder<Layer>::add(LayerWithBackground::createFromYaml, "LayerWithBackground", {"LayerWBackground", "LWBa"});
		YamlBuilder<Layer>::add(LayerWithAlternativeObject::createFromYaml, "LayerWithAlternativeObject", {"LayerWAObject", "LWAO"});
		YamlBuilder<Layer>::add(LayerWithBorder::createFromYaml, "LayerWithBorder", {"LayerWBorder", "LWB"});
		YamlBuilder<Layer>::add(LayerWithBorderVertical::createFromYaml, "LayerWithBorderVertical", {"LayerWBorderV", "LWBV"});
		YamlBuilder<Layer>::add(LayerWithBorderHorizontal::createFromYaml, "LayerWithBorderHorizontal", {"LayerWBorderH", "LWBH"});
		YamlBuilder<Layer>::add(LayerWithConstBorder::createFromYaml, "LayerWithConstBorder", {"LayerWCBorder", "LWCB"});
		YamlBuilder<Layer>::add(LayerWithConstBezel::createFromYaml, "LayerWithConstBezel", {"LayerWCBezel", "LWCBe"});
		YamlBuilder<Layer>::add(LayerWithConstRatio::createFromYaml, "LayerWithConstRatio", {"LayerWCRatio", "LWCR"});
		YamlBuilder<Layer>::add(LayerWithConstCenter::createFromYaml, "LayerWithConstCenter", {"LayerWCCenter", "LWCC"});
		YamlBuilder<Layer>::add(LayerWithMovableBorder::createFromYaml, "LayerWithMovableBorder", {"LayerWMBorder", "LWMB"});
		YamlBuilder<Layer>::add(LayerWithPanel::createFromYaml, "LayerWithPanel", {"LayerWPanel", "LWP"});
		YamlBuilder<Layer>::add(LayerWithRenderTexture::createFromYaml, "LayerWithRenderTexture", {"LayerWRTexture", "LWRT"});
        YamlBuilder<Layer>::add(LayerWithShader::createFromYaml, "LayerWithShader", {"LWS"});
        YamlBuilder<Layer>::add(UninteractiveLayer::createFromYaml, "UninteractiveLayer", {"UninteractiveL", "UL"});
		YamlBuilder<Layer>::add(MakePermeable::createFromYaml, "MakePermeable", {"MakePerm", "MP"});
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<Layer>::build);
		YamlBuilder<BaseSlider>::add(Slider::createFromYaml, "Slider");
		YamlBuilder<BaseSlider>::add(ConstSlider::createFromYaml, "ConstSlider");
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<BaseSlider>::build);
		YamlBuilder<IScalable>::add(ButtonWithPanel::createFromYaml, "ButtonWithPanel", {"ButtonWPanel"});
		YamlBuilder<IScalable>::add(Button::createFromYaml, "Button");
		YamlBuilder<IScalable>::add(Switch::createFromYaml, "Switch");
		YamlBuilder<IUnscalable>::addSubtype(YamlBuilder<IScalable>::build);
		YamlBuilder<IScalable>::add(Text::createFromYaml, "Text", {});
        YamlBuilder<BasePanel>::add(ConstPanel::createFromYaml, "ConstPanel");
		YamlBuilder<BasePanel>::add(Panel::createFromYaml, "Panel");
		YamlBuilder<IObject>::addSubtype(YamlBuilder<BasePanel>::build);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<IUnscalable>::build);
	}
	
	YamlBuilderInitializer::YamlBuilderInitializer() {
		yamlBuilderInit();
	}
}