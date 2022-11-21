#include "yamlBuilderInitializer.hpp"
#include "../../modules/appendix/yaml-cpp/yamlBuilder/shortcut/shortcut.hpp"

namespace ui {
	void yamlBuilderInit() {
		inherit<Sizing, ConstSizing>({"CS"});
		inherit<Sizing, RelativeNormalSizing>({"RNormalSizing", "RNS"});
		inherit<Sizing, RelativeParentSizing>({"RParentSizing", "RPS"});
		inherit<Sizing, ParentCoefficientSizing>({"ParentCSizing", "PCS"});
		inherit<Sizing, TargetCoefficientSizing>({"TargetCSizing", "TCS"});
		inherit<Sizing, SmartSizing>({"SS"});
		
		inherit<BaseSizing2, Sizing2>({"S2"});
		inherit<BaseSizing2, ConstRatioSizing2>({"CRatioS2", "CRS2"});
		
		inherit<Positioning, InternalPositioning>({"IPos", "IP"});
		inherit<Positioning, InternalTargetPositioning>({"ITargetPos", "ITP"});
		inherit<Positioning, MatchPositioning>({"MPos", "MP"});
		inherit<Positioning, MatchTargetPositioning>({"MTargetPos", "MTP"});
		inherit<Positioning, MatchSidesPositioning>({"MSidesPos", "MSP"});
		
		inherit<BasePositioning2, Positioning2>({"Pos2", "P2"});
		inherit<BasePositioning2, InternalPositioning2>({"InternalPos2", "IP2"});
		
		inherit<BaseLine, Underline>({"U"});
		inherit<BaseLine, StrikeThrough>({"ST"});
		
		inherit<BaseTextBlock, TextBlock>({"TB"});
		inherit<BaseTextBlock, InteractiveTextBlock>({"ITB"});
		inherit<BaseTextBlock, ObjectTextBlock>({"OTB"});
		
		inherit<BaseResizer, Resizer>({"R"});
		
        inherit<TextEvent, TextCopyEvent>({"TCE"});
        inherit<TextEvent, TextSelectionEvent>({"TSE"});
        inherit<TextEvent, TextAddBlockInteractionEvent>({"TABIE"});
		inherit<KeyEvent, TextEvent>();
		inherit<KeyEvent, ChangeObjectEvent>({"COE", "ChangeObjectE"});
		inherit<KeyEvent, WhileChangingObjectsEvent>({"WhileChangingOE", "WCO"});
		inherit<KeyEvent, OpenUrlEvent>({"UrlE", "Url", "OUE"});

		inherit<HidePanelInteraction, DontHidePanelInteraction>({"DontHidePI", "DontHPI", "DHPI"});
		inherit<HidePanelInteraction, ClickHidePanelInteraction>({"ClickHidePI", "ClickHPI", "CHPI"});
		inherit<HidePanelInteraction, PointingHidePanelInteraction>({"PointingHidePI", "PointingHPI", "PHPI"});
		inherit<BasePanelInteraction, HidePanelInteraction>();
		inherit<DisplayPanelInteraction, ClickDisplayPanelInteraction>({"ClickDisplayPI", "ClickDPI", "CDPI"});
		inherit<DisplayPanelInteraction, PointingDisplayPanelInteraction>({"PointingDisplayPI", "PointingDPI", "PDPI"});
		inherit<BasePanelInteraction, DisplayPanelInteraction>();
		inherit<MovePanelInteraction, CoefficientMovePanelInteraction>({"CoefficientMovePI", "CoefficientMPI", "CMPI"});
		inherit<MovePanelInteraction, DontMovePanelInteraction>({"DontMovePI", "DontMPI", "DMPI"});
		inherit<MovePanelInteraction, SideMovePanelInteraction>({"SideMovePI", "SideMPI", "SMPI"});
		inherit<BasePanelInteraction, MovePanelInteraction>();
		inherit<IInteraction, BasePanelInteraction>();
		inherit<TextInteraction, TextKeysInteraction>({"TKI"});
		inherit<TextInteraction, TextHotkeyInteraction>({"THI"});
		inherit<TextInteraction, TextEmptyInteraction>({"TEI"});
		inherit<IInteraction, TextInteraction>();
		inherit<IInteraction, KeysInteraction>({"KI"});
		inherit<IInteraction, OneKeyInteraction>({"OKI"});
		inherit<IInteraction, HotkeyInteraction>({"HI"});
		inherit<IInteraction, EmptyInteraction>({"EI"});
		
		inherit<OnlyDrawable, Empty>();
		inherit<OnlyDrawable, FullColor>();
		inherit<OnlyDrawable, RoundedRectangle>();
		inherit<OnlyDrawable, Capsule>();
		inherit<OnlyDrawable, Sprite>();
		inherit<IUninteractive, OnlyDrawable>();
		inherit<IUninteractive, Bar>();
		inherit<IUninteractive, Caption>();
		inherit<IScalable, IUninteractive>();
		inherit<Layer, DebugLayer>({"Debug", "DL"});
		inherit<Layer, LayerWithBackground>({"LayerWBackground", "LWBa"});
		inherit<Layer, LayerWithAlternativeObject>({"LayerWAObject", "LWAO"});
		inherit<Layer, LayerWithBorder>({"LayerWBorder", "LWB"});
		inherit<Layer, LayerWithBorderVertical>({"LayerWBorderV", "LWBV"});
		inherit<Layer, LayerWithBorderHorizontal>({"LayerWBorderH", "LWBH"});
		inherit<Layer, LayerWithConstBorder>({"LayerWCBorder", "LWCB"});
		inherit<Layer, LayerWithConstBezel>({"LayerWCBezel", "LWCBe"});
		inherit<Layer, LayerWithConstRatio>({"LayerWCRatio", "LWCR"});
		inherit<Layer, LayerWithConstCenter>({"LayerWCCenter", "LWCC"});
		inherit<Layer, LayerWithMovableBorder>({"LayerWMBorder", "LWMB"});
		inherit<Layer, LayerWithPanel>({"LayerWPanel", "LWP"});
		inherit<Layer, LayerWithRenderTexture>({"LayerWRTexture", "LWRT"});
        inherit<Layer, LayerWithShader>({"LWS"});
		inherit<Layer, MakePermeable>({"MakePerm", "MP"});
		inherit<Layer, LayerWithChangeableObjects>({"LWChangeableObjects", "LWCO"});
		addBase<UninteractiveLayer, IUninteractive, Layer>({"UninteractiveL", "UL"});
		inherit<IScalable, Layer>();
		inherit<BaseSlider, Slider>();
		inherit<BaseSlider, ConstSlider>();
		inherit<IScalable, BaseSlider>();
		inherit<IScalable, ButtonWithPanel>({"ButtonWPanel"});
		inherit<IScalable, Button>();
		inherit<IScalable, Switch>();
		inherit<IUnscalable, IScalable>();
		inherit<IScalable, Text>();
        inherit<BasePanel, ConstPanel>();
		inherit<BasePanel, Panel>();
		inherit<IObject, BasePanel>();
		inherit<IObject, IUnscalable>();
		
		addDetermine<FullColor>();
		addDetermine<RoundedRectangle>();
		addDetermine<Sprite>();
		addDetermine<TextBlock>();
		addDetermine<OpenUrlEvent>(determineUrl);
		addDetermine<KeysInteraction>(determineUrl);
		addDetermine<TextKeysInteraction>(determineUrl);
	}
}