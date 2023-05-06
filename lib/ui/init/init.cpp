#include "init.hpp"
#include "../../modules/appendix/yaml-cpp/yamlBuilder/shortcut/shortcut.hpp"
#include "../sizingAndPositioning/sizing/determine/determineSizing.hpp"
#include "../sizingAndPositioning/sizing2/determine/determineSizing2.hpp"
#include "../sizingAndPositioning/positioning/determine/determinePositioning.hpp"
#include "../sizingAndPositioning/positioning2/determine/determinePositioning2.hpp"
#include "modules/appendix/yaml-cpp/modules/loadCModules/loadCModules.hpp"
#define MAGICKCORE_QUANTUM_DEPTH 16
# define MAGICKCORE_HDRI_ENABLE MAGICKCORE_HDRI_ENABLE_OBSOLETE_IN_H

#include <Magick++.h>

namespace ui {
	void sfloatBuilderInit(){
		inherit<ISfloat, Sfloat>({"Sfloat"});
		inherit<ISfloat, ISCoefficientValue>({"ISCoefficientValue"});
		addBase<SCoefficientValue, Sfloat, ISCoefficientValue>(std::vector<std::string>{"SCoefficientValue"});
		
		inherit<Sfloat, SRfloat>({"SRfloat"});
		inherit<SRfloat, SCRfloat>({"SCRfloat", "SCRf"});
		inherit<Sfloat, SConvertToFloat<int>>({"SConvertIntToFloat", "SConvertIToF", "SCIToF", "SCITF"});
		
		inherit<ISVector2, SVec2f>({"SVec2f"});
		inherit<ISVector2, SRVec2f>({"SRVec2f"});
	}
	
	void sintBuilderInit(){
		inherit<ISint, Sint>({"Sint"});
		
		inherit<Sint, SRint>({"SRint"});
		inherit<SRint, SCRint>({"SCRfloat", "SCRf"});
		inherit<ISint, SConvertToInt<float>>({"SConvertFloatToInt", "SConvertFToI", "SCFToI", "SCFTI"});
		
		inherit<ISVector2, SVec2i>({"SVec2i"});
		inherit<ISVector2, SRVec2i>({"SRVec2i"});
	}
	
	void init(std::filesystem::path modulesList, int argc, char *argv[]) {
		Magick::InitializeMagick("");
		yamlBuilderInit();
		loadCModules(modulesList, argc, argv);
	}
	
	void yamlBuilderInit() {
		sintBuilderInit();
		sfloatBuilderInit();
		
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
		inherit<KeyEvent, SwitcherEvent>({"SwitcherEvent", "Switcher", "SE"});
		inherit<KeyEvent, SetSintEvent>({"SSintE", "SSiE"});
		inherit<KeyEvent, SetSfloatEvent>({"SSfloatE", "SSfE"});
		
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
		
		inherit<ISbool, SConvertFloatToBoolEquals>({"ConvertFloatToBoolEquals", "SCFTBE"});
		inherit<ISbool, SConvertFloatToBoolEquals>({"ConvertFloatToBoolEquals", "SCFTBE"});
		inherit<ISbool, SConvertFloatToBoolGreater>({"ConvertFloatToBoolGreater", "SCFTBG"});
		inherit<ISbool, SConvertFloatToBoolGreaterOrEquals>({"ConvertFloatToBoolGreaterOrEquals", "SCFTBGOE", "SCFTBGE"});
		inherit<ISbool, SConvertFloatToBoolLess>({"ConvertFloatToBoolLess", "SCFTBL"});
		inherit<ISbool, SConvertFloatToBoolLessOrEquals>({"ConvertFloatToBoolLessOrEquals", "SCFTBLOE", "SCFTBLE"});
		
		inherit<IAnimatorUnit, Animation>({"A"});
		inherit<IAnimatorUnit, Prerequisite>({"P"});
		inherit<IAnimatorUnit, AnimatorUnitMatchFloat>({"M", "Mf", "AUMf", "AUM"});
		inherit<IChangeVariable, ChangeVariableByStraightLine>({"CVByStraightLine", "CVByStraightL", "CVBSL"});
		inherit<IChangeVariable, ChangeVariableByBrokenLine>({"CVByBrokenLine", "CVByBrokenL", "CVBBL"});
		inherit<IChangeVariable, ChangeVariableBySteppedLine>({"CVBySteppedLine", "CVBySteppedL", "CVBStepL"});
		inherit<IChangeVariable, ChangeVariableBySinusoid>({"CVBySinusoid", "CVBySin", "CVBS"});
		inherit<IChangeVariable, ChangeVariableByCurve>({"CVByCurve", "CVBCurve", "CVBC"});
		inherit<IValve, ValveWithISbool>({"VWISbool", "VIWISB"});
		
		addFunc<OnlyDrawable>(videoConvert, {"Video"});
		//addFunc<Box>(switcherTabsDecodePointer, {"SwitcherTabs", "SwitcherT"});
		
		inherit<OnlyDrawable, Empty>();
		inherit<OnlyDrawable, FullColor>();
		inherit<OnlyDrawable, RoundedRectangle>();
		inherit<OnlyDrawable, Capsule>();
		inherit<OnlyDrawable, Sprite>();
		inherit<IUninteractive, OnlyDrawable>();
		inherit<IUninteractive, Bar>();
		inherit<IUninteractive, Caption>();
		inherit<IScalable, IUninteractive>();
		inherit<Box, BoxDebug>({"BDebug", "BD"});
		inherit<Box, BoxWithBackground>({"BoxWBackground", "BWBa"});
		inherit<Box, BoxWithAlternativeObject>({"BoxWAObject", "BWAO"});
		inherit<Box, BoxWithBorder>({"BoxWBorder", "BWB"});
		inherit<Box, BoxWithBorderVertical>({"BoxWBorderV", "BWBV"});
		inherit<Box, BoxWithBorderHorizontal>({"BoxWBorderH", "BWBH"});
		inherit<Box, BoxWithConstBorder>({"BoxWCBorder", "BWCB"});
		inherit<Box, BoxWithConstBezel>({"BoxWCBezel", "BWCBe"});
		inherit<Box, BoxWithConstRatio>({"BoxWCRatio", "BWCR"});
		inherit<Box, BoxWithConstRatioCenter>({"BoxWCCenter", "BWCRC"});
		inherit<Box, BoxWithMovableBorder>({"BoxWMBorder", "BWMB"});
		inherit<Box, BoxWithPanel>({"BoxWPanel", "BWP"});
		inherit<Box, BoxWithRenderTexture>({"BoxWRTexture", "BWRT"});
		inherit<Box, BoxWithShader>({"BWS"});
		inherit<Box, BoxWithChangeableObjects>({"BWChangeableObjects", "BWCO"});
		inherit<Box, BoxMakePermeable>({"BMakePerm", "BMP"});
		inherit<Box, BoxScroll>({"BScroll", "BSc"});
		inherit<Box, BoxSwitcher>({"BSwitcher", "BSw"});
		inherit<Box, BoxWithTabs>({"BWTabs", "BWT"});
		inherit<Box, BoxSwitcherTabs>({"BSwitcherTabs"});
		addBase<BoxUninteractive, IUninteractive, Box>(std::vector<std::string>{"BUninteractive", "BU"});
		inherit<IScalable, Box>();
		inherit<BaseSlider, Slider>();
		inherit<BaseSlider, ConstSlider>();
		inherit<IScalable, BaseSlider>();
		inherit<IScalable, ButtonWithPanel>({"ButtonWPanel"});
		inherit<IScalable, Button>();
		inherit<IScalable, Switcher>();
		inherit<IUnscalable, IScalable>();
		inherit<Interactive, Text>();
		inherit<IUnscalable, Interactive>();
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