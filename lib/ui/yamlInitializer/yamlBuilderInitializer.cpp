#include "yamlBuilderInitializer.hpp"
#include "../../modules/appendix/yaml-cpp/yamlBuilder/shortcut/shortcut.hpp"
#include "../sizingAndPositioning/sizing/determine/determineSizing.hpp"
#include "../sizingAndPositioning/sizing2/determine/determineSizing2.hpp"
#include "../sizingAndPositioning/positioning/determine/determinePositioning.hpp"
#include "../sizingAndPositioning/positioning2/determine/determinePositioning2.hpp"

namespace ui {
	void yamlBuilderInit() {
		inherit<ISizing, ConstSizing>({"CS"});
		inherit<ISizing, RelativeNormalSizing>({"RNormalSizing", "RNS"});
		inherit<ISizing, RelativeParentSizing>({"RParentSizing", "RPS"});
		inherit<ISizing, ParentCoefficientSizing>({"ParentCSizing", "PCS"});
		inherit<ISizing, TargetCoefficientSizing>({"TargetCSizing", "TCS"});
		inherit<ISizing, SmartSizing>({"SS"});
		
		inherit<ISizing2, Sizing2>({"S2"});
		inherit<ISizing2, ConstRatioSizing2>({"CRatioS2", "CRS2"});
		
		inherit<IPositioning, InternalPositioning>({"IPos", "IP"});
		inherit<IPositioning, InternalTargetPositioning>({"ITargetPos", "ITP"});
		inherit<IPositioning, MatchPositioning>({"MPos", "MP"});
		inherit<IPositioning, MatchTargetPositioning>({"MTargetPos", "MTP"});
		inherit<IPositioning, MatchSidesPositioning>({"MSidesPos", "MSP"});
		
		inherit<IPositioning2, Positioning2>({"Pos2", "P2"});
		inherit<IPositioning2, InternalPositioning2>({"InternalPos2", "IP2"});
		
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

		inherit<IAnimatorUnit, Animation>({"Animation", "A"});
		inherit<IAnimationVariable, SharedAnimationVariable<float>>({"SharedAV", "SAV"});
		inherit<IChangeVariable, ChangeVariableByStraightLine>({"CVByStraightLine", "CVBSL"});
		inherit<IConvertToUse<float>, ConvertToUseCoefficient<float>>({"CTUCoefficientf", "CTUCf"});
		inherit<IConvertToUse<float>, ConvertToUseCoefficientWithRange<float>>({"CTUCoefficientWithRangef", "CTUCWRf"});

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
		inherit<Layer, ScrollLayer>({"ScrollL", "SL"});
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
		addDetermine<ISizing>(determineSizing);
		addDetermine<ISizing2>(determineSizing2);
		addDetermine<IPositioning>(determinePositioning);
		addDetermine<IPositioning2>(determinePositioning2);
		addDetermine<OpenUrlEvent>(determineUrl);
		addDetermine<KeysInteraction>(determineUrl);
		addDetermine<TextKeysInteraction>(determineUrl);
	}
}