#include "yamlBuilderInitializer.hpp"

namespace ui {
	void yamlBuilderInit() {
		YamlBuilder<Sizing>::add(createPointer<ConstSizing>, "ConstSizing", {"CS"});
		YamlBuilder<Sizing>::add(createPointer<RelativeNormalSizing>, "RelativeNormalSizing", {"RNormalSizing", "RNS"});
		YamlBuilder<Sizing>::add(createPointer<RelativeParentSizing>, "RelativeParentSizing", {"RParentSizing", "RPS"});
		YamlBuilder<Sizing>::add(createPointer<ParentCoefficientSizing>, "ParentCoefficientSizing", {"ParentCSizing", "PCS"});
		YamlBuilder<Sizing>::add(createPointer<TargetCoefficientSizing>, "TargetCoefficientSizing", {"TargetCSizing", "TCS"});
		YamlBuilder<Sizing>::add(createPointer<SmartSizing>, "SmartSizing", {"SS"});
		
		YamlBuilder<BaseSizing2>::add(createPointer<Sizing2>, "Sizing2", {"S2"});
		YamlBuilder<BaseSizing2>::add(createPointer<ConstRatioSizing2>, "ConstRatioSizing2", {"CRatioS2", "CRS2"});
		
		YamlBuilder<Positioning>::add(createPointer<InternalPositioning>, "InternalPositioning", {"IPos", "IP"});
		YamlBuilder<Positioning>::add(createPointer<InternalTargetPositioning>, "InternalTargetPositioning", {"ITargetPos", "ITP"});
		YamlBuilder<Positioning>::add(createPointer<MatchPositioning>, "MatchPositioning", {"MPos", "MP"});
		YamlBuilder<Positioning>::add(createPointer<MatchTargetPositioning>, "MatchTargetPositioning", {"MTargetPos", "MTP"});
		YamlBuilder<Positioning>::add(createPointer<MatchSidesPositioning>, "MatchSidesPositioning", {"MSidesPos", "MSP"});
		
		YamlBuilder<BasePositioning2>::add(createPointer<Positioning2>, "Positioning2", {"Pos2", "P2"});
		YamlBuilder<BasePositioning2>::add(createPointer<InternalPositioning2>, "InternalPositioning2", {"InternalPos2", "IP2"});
		
		YamlBuilder<BaseLine>::add(createPointer<Underline>, "Underline", {"U"});
		YamlBuilder<BaseLine>::add(createPointer<StrikeThrough>, "StrikeThrough", {"ST"});
		YamlBuilder<BaseTextBlock>::add(createPointer<TextBlock>, "TextBlock", {"TB"});
		YamlBuilder<BaseTextBlock>::add(createPointer<InteractiveTextBlock>, "InteractiveTextBlock", {"ITB"});
		YamlBuilder<BaseTextBlock>::add(createPointer<ObjectTextBlock>, "ObjectTextBlock", {"OTB"});
		YamlBuilder<BaseResizer>::add(createPointer<Resizer>, "Resizer", {"R"});

        YamlBuilder<TextEvent>::add(createPointer<TextCopyEvent>, "TextCopyEvent", {"TCE"});
        YamlBuilder<TextEvent>::add(createPointer<TextSelectionEvent>, "TextSelectionEvent", {"TSE"});
		YamlBuilder<ButtonEvent>::addSubtype(YamlBuilder<TextEvent>::build);
		YamlBuilder<ButtonEvent>::add( createPointer<ChangeObjectEvent>, "ChangeObjectEvent", { "COE", "ChangeObjectE"});
		YamlBuilder<ButtonEvent>::add( createPointer<WhileChangingObjectsEvent>, "WhileChangingObjectsEvent", { "WhileChangingO", "WCO"});

		YamlBuilder<HidePanelInteraction>::add(createPointer<DontHidePanelInteraction>, "DontHidePanelInteraction", {"DontHidePI", "DontHPI", "DHPI"});
		YamlBuilder<HidePanelInteraction>::add(createPointer<ClickHidePanelInteraction>, "ClickHidePanelInteraction", {"ClickHidePI", "ClickHPI", "CHPI"});
		YamlBuilder<HidePanelInteraction>::add(createPointer<PointingHidePanelInteraction>, "PointingHidePanelInteraction", {"PointingHidePI", "PointingHPI", "PHPI"});
		YamlBuilder<BasePanelInteraction>::addSubtype(YamlBuilder<HidePanelInteraction>::build);
		YamlBuilder<DisplayPanelInteraction>::add(createPointer<ClickDisplayPanelInteraction>, "ClickDisplayPanelInteraction", {"ClickDisplayPI", "ClickDPI", "CDPI"});
		YamlBuilder<DisplayPanelInteraction>::add(createPointer<PointingDisplayPanelInteraction>, "PointingDisplayPanelInteraction", {"PointingDisplayPI", "PointingDPI", "PDPI"});
		YamlBuilder<BasePanelInteraction>::addSubtype(YamlBuilder<DisplayPanelInteraction>::build);
		YamlBuilder<MovePanelInteraction>::add(createPointer<CoefficientMovePanelInteraction>, "CoefficientMovePanelInteraction", {"CoefficientMovePI", "CoefficientMPI", "CMPI"});
		YamlBuilder<MovePanelInteraction>::add(createPointer<DontMovePanelInteraction>, "DontMovePanelInteraction", {"DontMovePI", "DontMPI", "DMPI"});
		YamlBuilder<MovePanelInteraction>::add(createPointer<SideMovePanelInteraction>, "SideMovePanelInteraction", {"SideMovePI", "SideMPI", "SMPI"});
		YamlBuilder<BasePanelInteraction>::addSubtype(YamlBuilder<MovePanelInteraction>::build);
		YamlBuilder<IInteraction>::addSubtype(YamlBuilder<BasePanelInteraction>::build);
		YamlBuilder<TextInteraction>::add(createPointer<TextButtonsInteraction>, "TextButtonsInteraction", {"TBI"});
		YamlBuilder<TextInteraction>::add(createPointer<TextHotkeyInteraction>, "TextHotkeyInteraction", {"THI"});
		YamlBuilder<TextInteraction>::add(createPointer<TextEmptyInteraction>, "TextEmptyInteraction", {"TEI"});
		YamlBuilder<IInteraction>::addSubtype(YamlBuilder<TextInteraction>::build);
		YamlBuilder<IInteraction>::add(createPointer<ButtonsInteraction>, "ButtonsInteraction", {"BI"});
		YamlBuilder<IInteraction>::add(createPointer<OneButtonInteraction>, "OneButtonInteraction", {"OBI"});
		YamlBuilder<IInteraction>::add(createPointer<HotkeyInteraction>, "HotkeyInteraction", {"HI"});
		YamlBuilder<IInteraction>::add(createPointer<EmptyInteraction>, "EmptyInteraction", {"EI"});

		YamlBuilder<OnlyDrawable>::add(createPointer<Empty>, "Empty");
		YamlBuilder<OnlyDrawable>::add(createPointer<FullColor>, "FullColor");
		YamlBuilder<OnlyDrawable>::add(createPointer<RoundedRectangle>, "RoundedRectangle");
		YamlBuilder<OnlyDrawable>::add(createPointer<Capsule>, "Capsule");
		YamlBuilder<OnlyDrawable>::add(createPointer<Sprite>, "Sprite");
		YamlBuilder<IUninteractive>::addSubtype(YamlBuilder<OnlyDrawable>::build);
		YamlBuilder<IUninteractive>::add(createPointer<Bar>, "Bar");
		YamlBuilder<IUninteractive>::add(createPointer<Caption>, "Caption");
		YamlBuilder<IUninteractive>::add(createPointer<UninteractiveLayer>, "LayerWithUnInteractive", {"LWUnInteractive", "LWUI"});
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<IUninteractive>::build);
		YamlBuilder<Layer>::add(createPointer<LayerWithBackground>, "LayerWithBackground", {"LayerWBackground", "LWBa"});
		YamlBuilder<Layer>::add(createPointer<LayerWithAlternativeObject>, "LayerWithAlternativeObject", {"LayerWAObject", "LWAO"});
		YamlBuilder<Layer>::add(createPointer<LayerWithBorder>, "LayerWithBorder", {"LayerWBorder", "LWB"});
		YamlBuilder<Layer>::add(createPointer<LayerWithBorderVertical>, "LayerWithBorderVertical", {"LayerWBorderV", "LWBV"});
		YamlBuilder<Layer>::add(createPointer<LayerWithBorderHorizontal>, "LayerWithBorderHorizontal", {"LayerWBorderH", "LWBH"});
		YamlBuilder<Layer>::add(createPointer<LayerWithConstBorder>, "LayerWithConstBorder", {"LayerWCBorder", "LWCB"});
		YamlBuilder<Layer>::add(createPointer<LayerWithConstBezel>, "LayerWithConstBezel", {"LayerWCBezel", "LWCBe"});
		YamlBuilder<Layer>::add(createPointer<LayerWithConstRatio>, "LayerWithConstRatio", {"LayerWCRatio", "LWCR"});
		YamlBuilder<Layer>::add(createPointer<LayerWithConstCenter>, "LayerWithConstCenter", {"LayerWCCenter", "LWCC"});
		YamlBuilder<Layer>::add(createPointer<LayerWithMovableBorder>, "LayerWithMovableBorder", {"LayerWMBorder", "LWMB"});
		YamlBuilder<Layer>::add(createPointer<LayerWithPanel>, "LayerWithPanel", {"LayerWPanel", "LWP"});
		YamlBuilder<Layer>::add(createPointer<LayerWithRenderTexture>, "LayerWithRenderTexture", {"LayerWRTexture", "LWRT"});
        YamlBuilder<Layer>::add(createPointer<LayerWithShader>, "LayerWithShader", {"LWS"});
        YamlBuilder<Layer>::add(createPointer<UninteractiveLayer>, "UninteractiveLayer", {"UninteractiveL", "UL"});
		YamlBuilder<Layer>::add(createPointer<MakePermeable>, "MakePermeable", {"MakePerm", "MP"});
		YamlBuilder<Layer>::add(createPointer<LayerWithChangeableObjects>, "LayerWithChangeableObjects", {"LWChangeableObjects", "LWCO"});
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<Layer>::build);
		YamlBuilder<BaseSlider>::add(createPointer<Slider>, "Slider");
		YamlBuilder<BaseSlider>::add(createPointer<ConstSlider>, "ConstSlider");
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<BaseSlider>::build);
		YamlBuilder<IScalable>::add(createPointer<ButtonWithPanel>, "ButtonWithPanel", {"ButtonWPanel"});
		YamlBuilder<IScalable>::add(createPointer<Button>, "Button");
		YamlBuilder<IScalable>::add(createPointer<Switch>, "Switch");
		YamlBuilder<IUnscalable>::addSubtype(YamlBuilder<IScalable>::build);
		YamlBuilder<IScalable>::add(createPointer<Text>, "Text", {});
        YamlBuilder<BasePanel>::add(createPointer<ConstPanel>, "ConstPanel");
		YamlBuilder<BasePanel>::add(createPointer<Panel>, "Panel");
		YamlBuilder<IObject>::addSubtype(YamlBuilder<BasePanel>::build);
		YamlBuilder<IObject>::addSubtype(YamlBuilder<IUnscalable>::build);
	}
	
	YamlBuilderInitializer::YamlBuilderInitializer() {
		yamlBuilderInit();
	}
}