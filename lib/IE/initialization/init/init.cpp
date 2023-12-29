#include "init.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/shortcut/shortcut.hpp"
#include "IE/sizing-positioning/ISizing/Functions/determine_sizing/determine_sizing.hpp"
#include "IE/sizing-positioning/ISizing2/Functions/determine_sizing2/determine_sizing2.hpp"
#include "IE/sizing-positioning/IPositioning/Functions/determine_positioning/determine_positioning.hpp"
#include "IE/sizing-positioning/IPositioning2/Functions/determine_positioning2/determine_positioning2.hpp"
#include "IE/modules/yaml-cpp/modules/load_modules.hpp"
#include "config.h"

#ifdef IE_ImageMagick_FOUND
	#define MAGICKCORE_QUANTUM_DEPTH 16
	#define MAGICKCORE_HDRI_ENABLE MAGICKCORE_HDRI_ENABLE_OBSOLETE_IN_H
	#include <Magick++.h>
#endif

namespace ie {
	void yaml_builder_init_sfloat() {
		inherit<ISfloat, Sfloat>({"Float"});
		inherit<ISfloat, ISCoefficientValue>();
		add_base<SCoefficientValue, Sfloat, ISCoefficientValue>(std::vector<std::string>{"SCoefficientValue"});
		
		inherit<Sfloat, SRfloat>({"RFloat"});
		inherit<SRfloat, SCRfloat>({"CRFloat"});
		inherit<Sfloat, SConvertToFloat<int>>({"CIntToFloat"});
		
		inherit<ISVector2, SVec2f>({"Vec2F"});
		inherit<ISVector2, SRVec2f>({"RVec2F"});
	}
	
	void yaml_builder_init_sint(){
		inherit<ISint, Sint>({"Int"});
		
		inherit<Sint, SRint>({"RInt"});
		inherit<SRint, SCRint>({"CRFloat"});
		inherit<ISint, SConvertToInt<float> >({"CFloatToInt"});
		
		inherit<ISVector2, SVec2i>({"Vec2I"});
		inherit<ISVector2, SRVec2i>({"RVec2I"});
	}
	
	void init(int argc, char *argv[], std::filesystem::path modules_list) {
#ifdef IE_ImageMagick_FOUND
		Magick::InitializeMagick("");
#endif
		yaml_builder_init();
		load_modules(argc, argv, modules_list);
	}
	
	void yaml_builder_init() {
		yaml_builder_init_sint();
		yaml_builder_init_sfloat();
		
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
		
		inherit<KeyAction, OpenUrlAction>({"OpenUrlA"});
		inherit<KeyAction, CloseWindowAction>({"CloseWindowA"});
		inherit<KeyAction, SwitcherAction>({"SwitcherA", });
		inherit<KeyAction, SetSIntAction>({"SetSIntA"});
		inherit<KeyAction, SetSFloatAction>({"SetSFloatA"});
		
		inherit<BasicKeyAction<Text&>, TextCopyAction >({"TextCopyA"});
		inherit<BasicKeyAction<Text&>, TextSelectionAction>({"TextSelectionA"});
		
		inherit<BaseSwitchTabsAction, SwitchTabsAction>({"SwitchTabsA"});
		inherit<BaseSwitchTabsAction, WhileSwitchTabsAction>({"WhileSwitchTabsA"});
		
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
		
		inherit<IBasicInteraction<Text&>, BasicKeysInteraction<Text&>>({"TextKeysI"});
		//inherit<IBasicInteraction<Text&>, BasicHotkeyInteraction<Text&>>({"TextHotkeyI"});
		inherit<IBasicInteraction<Text&>, BasicEmptyInteraction<Text&>>({"TextEmptyI"});
		
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
		
		add_func<OnlyDrawable>(video_convert, {"Video"});
		//add_func<Box>(switcher_tabs_decode_pointer, {"SwitcherTabs", "SwitcherT"});
		
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
		add_base<BoxUninteractive, IUninteractive, Box>();
		inherit<IScalable, Box>();
		inherit<BaseSlider, Slider>();
		inherit<BaseSlider, ConstSlider>();
		inherit<IScalable, BaseSlider>();
		inherit<IScalable, ButtonPanel>();
		inherit<IScalable, Button>();
		inherit<IScalable, Switcher>();
		inherit<IComponent, IScalable>();
		inherit<IComponent, Text>();
		
		inherit<BasePanel, ConstPanel>();
		inherit<BasePanel, Panel>();
		
		add_determine<FullColor>();
		add_determine<RoundedRectangle>();
		add_determine<Sprite>();
		add_determine<TextBlock>();
		add_determine<ISizing>(determine_sizing);
		add_determine<ISizing2>(determine_sizing2);
		add_determine<IPositioning>(determine_positioning);
		add_determine<IPositioning2>(determine_positioning2);
		add_determine<OpenUrlAction>(determine_url);
		add_determine<KeysInteraction>(determine_url);
		add_determine<BasicKeysInteraction<Text&>>(determine_url);
	}
}