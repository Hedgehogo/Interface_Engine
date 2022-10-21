#include "yamlBuilderInitializer.hpp"

namespace ui {
	template<typename Base, typename Type>
	void addType(std::vector<std::string> aliases = {}) {
		YamlBuilder<Base>::template add<Type>(aliases);
	}
	
	template<typename Base, typename Type>
	void addSubtype() {
		YamlBuilder<Base>::template addSubtype<Type>();
	}
	
	void yamlBuilderInit() {
		addType<Sizing, ConstSizing>({"CS"});
		addType<Sizing, RelativeNormalSizing>({"RNormalSizing", "RNS"});
		addType<Sizing, RelativeParentSizing>({"RParentSizing", "RPS"});
		addType<Sizing, ParentCoefficientSizing>({"ParentCSizing", "PCS"});
		addType<Sizing, TargetCoefficientSizing>({"TargetCSizing", "TCS"});
		addType<Sizing, SmartSizing>({"SS"});
		
		addType<BaseSizing2, Sizing2>({"S2"});
		addType<BaseSizing2, ConstRatioSizing2>({"CRatioS2", "CRS2"});
		
		addType<Positioning, InternalPositioning>({"IPos", "IP"});
		addType<Positioning, InternalTargetPositioning>({"ITargetPos", "ITP"});
		addType<Positioning, MatchPositioning>({"MPos", "MP"});
		addType<Positioning, MatchTargetPositioning>({"MTargetPos", "MTP"});
		addType<Positioning, MatchSidesPositioning>({"MSidesPos", "MSP"});
		
		addType<BasePositioning2, Positioning2>({"Pos2", "P2"});
		addType<BasePositioning2, InternalPositioning2>({"InternalPos2", "IP2"});
		
		addType<BaseLine, Underline>({"U"});
		addType<BaseLine, StrikeThrough>({"ST"});
		
		addType<BaseTextBlock, TextBlock>({"TB"});
		addType<BaseTextBlock, InteractiveTextBlock>({"ITB"});
		addType<BaseTextBlock, ObjectTextBlock>({"OTB"});
		
		addType<BaseResizer, Resizer>({"R"});
		
        addType<TextEvent, TextCopyEvent>({"TCE"});
        addType<TextEvent, TextSelectionEvent>({"TSE"});
		addSubtype<ButtonEvent, TextEvent>();
		addType<ButtonEvent, ChangeObjectEvent>({ "COE", "ChangeObjectE"});
		addType<ButtonEvent, WhileChangingObjectsEvent>({ "WhileChangingO", "WCO"});
		
		addType<HidePanelInteraction, DontHidePanelInteraction>({"DontHidePI", "DontHPI", "DHPI"});
		addType<HidePanelInteraction, ClickHidePanelInteraction>({"ClickHidePI", "ClickHPI", "CHPI"});
		addType<HidePanelInteraction, PointingHidePanelInteraction>({"PointingHidePI", "PointingHPI", "PHPI"});
		addSubtype<BasePanelInteraction, HidePanelInteraction>();
		addType<DisplayPanelInteraction, ClickDisplayPanelInteraction>({"ClickDisplayPI", "ClickDPI", "CDPI"});
		addType<DisplayPanelInteraction, PointingDisplayPanelInteraction>({"PointingDisplayPI", "PointingDPI", "PDPI"});
		addSubtype<BasePanelInteraction, DisplayPanelInteraction>();
		addType<MovePanelInteraction, CoefficientMovePanelInteraction>({"CoefficientMovePI", "CoefficientMPI", "CMPI"});
		addType<MovePanelInteraction, DontMovePanelInteraction>({"DontMovePI", "DontMPI", "DMPI"});
		addType<MovePanelInteraction, SideMovePanelInteraction>({"SideMovePI", "SideMPI", "SMPI"});
		addSubtype<BasePanelInteraction, MovePanelInteraction>();
		addSubtype<IInteraction, BasePanelInteraction>();
		addType<TextInteraction, TextButtonsInteraction>({"TBI"});
		addType<TextInteraction, TextHotkeyInteraction>({"THI"});
		addType<TextInteraction, TextEmptyInteraction>({"TEI"});
		addSubtype<IInteraction, TextInteraction>();
		addType<IInteraction, ButtonsInteraction>({"BI"});
		addType<IInteraction, OneButtonInteraction>({"OBI"});
		addType<IInteraction, HotkeyInteraction>({"HI"});
		addType<IInteraction, EmptyInteraction>({"EI"});
		
		addType<OnlyDrawable, Empty>();
		addType<OnlyDrawable, FullColor>();
		addType<OnlyDrawable, RoundedRectangle>();
		addType<OnlyDrawable, Capsule>();
		addType<OnlyDrawable, Sprite>();
		addSubtype<IUninteractive, OnlyDrawable>();
		addType<IUninteractive, Bar>();
		addType<IUninteractive, Caption>();
		addType<IUninteractive, UninteractiveLayer>({"UninteractiveL", "LWUI"});
		addSubtype<IScalable, IUninteractive>();
		addType<Layer, LayerWithBackground>({"LayerWBackground", "LWBa"});
		addType<Layer, LayerWithAlternativeObject>({"LayerWAObject", "LWAO"});
		addType<Layer, LayerWithBorder>({"LayerWBorder", "LWB"});
		addType<Layer, LayerWithBorderVertical>({"LayerWBorderV", "LWBV"});
		addType<Layer, LayerWithBorderHorizontal>({"LayerWBorderH", "LWBH"});
		addType<Layer, LayerWithConstBorder>({"LayerWCBorder", "LWCB"});
		addType<Layer, LayerWithConstBezel>({"LayerWCBezel", "LWCBe"});
		addType<Layer, LayerWithConstRatio>({"LayerWCRatio", "LWCR"});
		addType<Layer, LayerWithConstCenter>({"LayerWCCenter", "LWCC"});
		addType<Layer, LayerWithMovableBorder>({"LayerWMBorder", "LWMB"});
		addType<Layer, LayerWithPanel>({"LayerWPanel", "LWP"});
		addType<Layer, LayerWithRenderTexture>({"LayerWRTexture", "LWRT"});
        addType<Layer, LayerWithShader>({"LWS"});
        addType<Layer, UninteractiveLayer>({"UninteractiveL", "UL"});
		addType<Layer, MakePermeable>({"MakePerm", "MP"});
		addType<Layer, LayerWithChangeableObjects>({"LWChangeableObjects", "LWCO"});
		addSubtype<IScalable, Layer>();
		addType<BaseSlider, Slider>();
		addType<BaseSlider, ConstSlider>();
		addSubtype<IScalable, BaseSlider>();
		addType<IScalable, ButtonWithPanel>({"ButtonWPanel"});
		addType<IScalable, Button>();
		addType<IScalable, Switch>();
		addSubtype<IUnscalable, IScalable>();
		addType<IScalable, Text>();
        addType<BasePanel, ConstPanel>();
		addType<BasePanel, Panel>();
		addSubtype<IObject, BasePanel>();
		addSubtype<IObject, IUnscalable>();
	}
}