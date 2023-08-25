#include "Init.hpp"
#include "../../modules/appendix/yaml-cpp/yamlBuilder/shortcut/shortcut.hpp"
#include "../SizingAndPositioning/ISizing/Functions/determineSizing/determineSizing.hpp"
#include "../SizingAndPositioning/ISizing2/Functions/determineSizing2/determineSizing2.hpp"
#include "../SizingAndPositioning/IPositioning/Functions/determinePositioning/determinePositioning.hpp"
#include "../SizingAndPositioning/IPositioning2/Functions/determinePositioning2/determinePositioning2.hpp"
#include "modules/appendix/yaml-cpp/modules/loadModules.hpp"
#include "config.h"

#ifdef IE_ImageMagick_FOUND
	#define MAGICKCORE_QUANTUM_DEPTH 16
	#define MAGICKCORE_HDRI_ENABLE MAGICKCORE_HDRI_ENABLE_OBSOLETE_IN_H
	#include <Magick++.h>
#endif

namespace ui {
	void yamlBuilderInitSfloat() {
		inherit<ISfloat, Sfloat>({"Float"});
		inherit<ISfloat, ISCoefficientValue>();
		addBase<SCoefficientValue, Sfloat, ISCoefficientValue>(std::vector<std::string>{"SCoefficientValue"});
		
		inherit<Sfloat, SRfloat>({"RFloat"});
		inherit<SRfloat, SCRfloat>({"CRFloat"});
		inherit<Sfloat, SConvertToFloat<int>>({"CIntToFloat"});
		
		inherit<ISVector2, SVec2f>({"Vec2F"});
		inherit<ISVector2, SRVec2f>({"RVec2F"});
	}
	
	void yamlBuilderInitSint(){
		inherit<ISint, Sint>({"Int"});
		
		inherit<Sint, SRint>({"RInt"});
		inherit<SRint, SCRint>({"CRFloat"});
		inherit<ISint, SConvertToInt<float>>({"CFloatToInt"});
		
		inherit<ISVector2, SVec2i>({"Vec2I"});
		inherit<ISVector2, SRVec2i>({"RVec2I"});
	}
	
	void init(int argc, char *argv[], std::filesystem::path modulesList) {
#ifdef IE_ImageMagick_FOUND
		Magick::InitializeMagick("");
#endif
		yamlBuilderInit();
		loadModules(argc, argv, modulesList);
	}
	
	void yamlBuilderInit() {
		yamlBuilderInitSint();
		yamlBuilderInitSfloat();
		
		inherit<ISizing, ConstSizing>();
		inherit<ISizing, RelativeNormalSizing>();
		inherit<ISizing, RelativeParentSizing>();
		inherit<ISizing, ParentCoefficientSizing>();
		inherit<ISizing, TargetCoefficientSizing>();
		inherit<ISizing, SmartSizing>();
		
		inherit<ISizing2, Sizing2>();
		inherit<ISizing2, ConstRatioSizing2>();
		
		inherit<IPositioning, InternalPositioning>({"InternalPos"});
		inherit<IPositioning, InternalTargetPositioning>({"InternalTargetPos"});
		inherit<IPositioning, MatchPositioning>({"MatchPos"});
		inherit<IPositioning, MatchTargetPositioning>({"MatchTargetPos"});
		inherit<IPositioning, MatchSidesPositioning>({"MatchSidesPos"});
		
		inherit<IPositioning2, Positioning2>({"Pos2"});
		inherit<IPositioning2, InternalPositioning2>({"InternalPos2"});
		
		inherit<BaseLine, Underline>();
		inherit<BaseLine, StrikeThrough>();
		
		inherit<BaseTextBlock, TextBlock>();
		inherit<BaseTextBlock, InteractiveTextBlock>();
		inherit<BaseTextBlock, ObjectTextBlock>();
		
		inherit<BaseResizer, Resizer>();
		
		inherit<KeyEvent, OpenUrlEvent>({"OpenUrlE"});
		inherit<KeyEvent, CloseWindowEvent>({"CloseWindowE"});
		inherit<KeyEvent, SwitchTabsEvent>({"SwitchTabsE"});
		inherit<KeyEvent, WhileSwitchTabsEvent>({"WhileSwitchTabsE"});
		inherit<KeyEvent, SwitcherEvent>({"SwitcherE", });
		inherit<KeyEvent, SetSintEvent>({"SetSIntE"});
		inherit<KeyEvent, SetSfloatEvent>({"SetSFloatE"});
		
		inherit<TextEvent, TextCopyEvent>({"TextCopyE"});
		inherit<TextEvent, TextSelectionEvent>({"TextSelectionE"});
		
		inherit<IBaseInteraction, OneKeyInteraction>({"OneKeyI"});
		inherit<IBaseInteraction, KeysInteraction>({"KeysI"});
		inherit<IBaseInteraction, EmptyInteraction>({"EmptyI"});
		
		inherit<IHidePanelInteraction, DontHidePanelInteraction>({"DontHidePI"});
		inherit<IHidePanelInteraction, ClickHidePanelInteraction>({"ClickHidePI"});
		inherit<IHidePanelInteraction, PointingHidePanelInteraction>({"PointingHidePI"});
		inherit<IPanelInteraction, IHidePanelInteraction>();
		inherit<IDisplayPanelInteraction, ClickDisplayPanelInteraction>({"ClickDisplayPI"});
		inherit<IDisplayPanelInteraction, PointingDisplayPanelInteraction>({"PointingDisplayPI"});
		inherit<IPanelInteraction, IDisplayPanelInteraction>();
		inherit<IMovePanelInteraction, CoefficientMovePanelInteraction>({"CoefficientMovePI"});
		inherit<IMovePanelInteraction, DontMovePanelInteraction>({"DontMovePI"});
		inherit<IMovePanelInteraction, SideMovePanelInteraction>({"SideMovePI"});
		inherit<IPanelInteraction, IMovePanelInteraction>();
		
		inherit<TextInteraction, TextKeysInteraction>({"TextKeysI"});
		inherit<TextInteraction, TextHotkeyInteraction>({"TextHotkeyI"});
		inherit<TextInteraction, TextEmptyInteraction>({"TextEmptyI"});
		
		inherit<ISbool, SConvertFloatToBoolEquals>({"ConvertFloatToBoolEquals", "CFloatToBoolE"});
		inherit<ISbool, SConvertFloatToBoolGreater>({"ConvertFloatToBoolGreater", "CFloatToBoolG"});
		inherit<ISbool, SConvertFloatToBoolGreaterOrEquals>({"ConvertFloatToBoolGreaterOrEquals", "CFloatToBoolGOE"});
		inherit<ISbool, SConvertFloatToBoolLess>({"ConvertFloatToBoolLess", "CFloatToBoolL"});
		inherit<ISbool, SConvertFloatToBoolLessOrEquals>({"ConvertFloatToBoolLessOrEquals", "CFloatToBoolLOE"});
		
		inherit<IAnimatorUnit, Animation>();
		inherit<IAnimatorUnit, Prerequisite>();
		inherit<IAnimatorUnit, AnimatorUnitMatchFloat>({"AUnitMatchF"});
		inherit<IChangeVariable, ChangeVariableByStraightLine>({"CVByStraightLine", "CVByStraightL"});
		inherit<IChangeVariable, ChangeVariableByBrokenLine>({"CVByBrokenLine", "CVByBrokenL"});
		inherit<IChangeVariable, ChangeVariableBySteppedLine>({"CVBySteppedLine", "CVBySteppedL"});
		inherit<IChangeVariable, ChangeVariableBySinusoid>({"CVBySinusoid", "CVBySin"});
		inherit<IChangeVariable, ChangeVariableByCurve>({"CVByCurve"});
		
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
		inherit<Box, BoxDebug>();
		inherit<Box, BoxBackground>();
		inherit<Box, BoxAlternative>();
		inherit<Box, BoxBorder>();
		inherit<Box, BoxBorderVertical>();
		inherit<Box, BoxBorderHorizontal>();
		inherit<Box, BoxConstBorder>();
		inherit<Box, BoxConstBezel>();
		inherit<Box, BoxConstRatio>();
		inherit<Box, BoxConstRatioCenter>();
		inherit<Box, BoxMovableBorder>();
		inherit<Box, BoxPanel>();
		inherit<Box, BoxRenderTexture>();
		inherit<Box, BoxShader>();
		inherit<Box, BoxSwitchTabs>();
		inherit<Box, BoxMakePermeable>();
		inherit<Box, BoxScroll>();
		inherit<Box, BoxSwitch>();
		inherit<Box, BoxTabs>();
		inherit<Box, BoxSwitcherTabs>();
		inherit<Box, BoxConstCenter>();
		addBase<BoxUninteractive, IUninteractive, Box>();
		inherit<IScalable, Box>();
		inherit<BaseSlider, Slider>();
		inherit<BaseSlider, ConstSlider>();
		inherit<IScalable, BaseSlider>();
		inherit<IScalable, ButtonPanel>();
		inherit<IScalable, Button>();
		inherit<IScalable, Switcher>();
		inherit<IUnscalable, IScalable>();
		inherit<IUnscalable, Text>();
		inherit<IComponent, IUnscalable>();
		inherit<BasePanel, ConstPanel>();
		inherit<BasePanel, Panel>();
		inherit<IComponent, BasePanel>();
		
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