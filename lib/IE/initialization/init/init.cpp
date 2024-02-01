#include "init.hpp"
#include "IE/sizing-positioning/ISizing/Functions/determine_sizing/determine_sizing.hpp"
#include "IE/sizing-positioning/ISizing2/Functions/determine_sizing2/determine_sizing2.hpp"
#include "IE/sizing-positioning/IPositioning/Functions/determine_positioning/determine_positioning.hpp"
#include "IE/sizing-positioning/IPositioning2/Functions/determine_positioning2/determine_positioning2.hpp"
#include "IE/modules/yaml-cpp/modules/load_modules.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "IE/utils/meta/is_contains_v/is_contains_v.hpp"
#include "config.h"

#ifdef IE_ImageMagick_FOUND
#define MAGICKCORE_QUANTUM_DEPTH 16
#define MAGICKCORE_HDRI_ENABLE MAGICKCORE_HDRI_ENABLE_OBSOLETE_IN_H
#include <Magick++.h>
#endif

namespace ie {
	void init(int argc, char* argv[], std::filesystem::path modules_list) {
#ifdef IE_ImageMagick_FOUND
		Magick::InitializeMagick("");
#endif
		ieml_rttb_init();
		load_modules(argc, argv, modules_list);
	}
	
	template<typename T>
	void ieml_rttb_init_shared(char first, std::string name) {
		add_type<ISValue<T>, SValue<T> >();
		add_type_make<ISValue<T>, SValue<T> >(name);
		if constexpr(meta::is_contains_v<T, size_t, int, float>) {
			add_type<ISVec2<T>, SVec2<T> >();
			add_type_make<ISVec2<T>, SVec2<T> >(std::string("Vec2") + std::string(1, first));
			add_type<ISVec2<T>, SRVec2<T> >();
			add_type_make<ISVec2<T>, SRVec2<T> >(std::string("RVec2") + std::string(1, first));
			add_type<ISValue<sf::Vector2<T> >, ISVec2<T> >();
			add_type_make<ISValue<sf::Vector2<T> >, ISVec2<T> >();
			add_type<SValue<T>, SRanged<T> >();
			add_type_make<SValue<T>, SRanged<T> >(std::string("R") + name);
			add_type<ISRanged<T>, SRanged<T> >();
			add_type_make<ISRanged<T>, SRanged<T> >();
			add_type<ISValue<T>, ISRanged<T> >();
			add_type_make<ISValue<T>, ISRanged<T> >();
			
			add_bool_determine_make<SRVec2<T> >();
			add_bool_determine_make<SRanged<T> >();
		}
	}
	
	void ieml_rttb_init() {
		[[maybe_unused]] static bool once{[]() {
			ieml_rttb_init_shared<bool>('B', "Bool");
			ieml_rttb_init_shared<size_t>('U', "USize");
			ieml_rttb_init_shared<int>('I', "Int");
			ieml_rttb_init_shared<float>('F', "Float");
			
			//add_type<ISbool, SConvertFloatToBoolEquals>("ConvertFloatToBoolEquals", "CFloatToBoolE");
			//add_type<ISbool, SConvertFloatToBoolGreater>("ConvertFloatToBoolGreater", "CFloatToBoolG");
			//add_type<ISbool, SConvertFloatToBoolGreaterOrEquals>("ConvertFloatToBoolGreaterOrEquals", "CFloatToBoolGOE");
			//add_type<ISbool, SConvertFloatToBoolLess>("ConvertFloatToBoolLess", "CFloatToBoolL");
			//add_type<ISbool, SConvertFloatToBoolLessOrEquals>("ConvertFloatToBoolLessOrEquals", "CFloatToBoolLOE");
			
			//add_type_named<IAnimatorUnit, Animation>();
			//add_type_named<IAnimatorUnit, Prerequisite>();
			//add_type_named<IAnimatorUnit, AnimatorUnitMatchFloat>("AUnitMatchF");
			//add_type_named<IChangeVariable, ChangeVariableByStraightLine>("CVByStraightLine", "CVByStraightL");
			//add_type_named<IChangeVariable, ChangeVariableByBrokenLine>("CVByBrokenLine", "CVByBrokenL");
			//add_type_named<IChangeVariable, ChangeVariableBySteppedLine>("CVBySteppedLine", "CVBySteppedL");
			//add_type_named<IChangeVariable, ChangeVariableBySinusoid>("CVBySinusoid", "CVBySin");
			//add_type_named<IChangeVariable, ChangeVariableByCurve>("CVByCurve");
			
			add_type_make_named<ISizing, ConstSizing>();
			add_type_make_named<ISizing, RelativeNormalSizing>();
			add_type_make_named<ISizing, RelativeParentSizing>();
			add_type_make_named<ISizing, ParentCoefficientSizing>();
			add_type_make_named<ISizing, TargetCoefficientSizing>();
			add_type_make_named<ISizing, SmartSizing>();
			
			add_type_make_named<ISizing2, Sizing2>("Sizing2");
			add_type_make_named<ISizing2, ConstRatioSizing2>("ConstRatioSizing2");
			
			add_type_named<IPositioning, InternalPositioning>("InternalPos");
			add_type_named<IPositioning, InternalTargetPositioning>("InternalTargetPos");
			add_type_named<IPositioning, MatchPositioning>("MatchPos");
			add_type_named<IPositioning, MatchTargetPositioning>("MatchTargetPos");
			add_type_named<IPositioning, MatchSidesPositioning>("MatchSidesPos");
			
			add_type_named<IPositioning2, Positioning2>("Pos2");
			add_type_named<IPositioning2, InternalPositioning2>("InternalPos2");
			
			add_type_make_named<BaseLine, Underline>();
			add_type_make_named<BaseLine, StrikeThrough>();
			
			add_type_make_named<BaseTextBlock, TextBlock>();
			add_type_make_named<BaseTextBlock, InteractiveTextBlock>();
			add_type_make_named<BaseTextBlock, ObjectTextBlock>();
			
			add_type_make_named<BaseResizer, Resizer>();
			
			add_type_make_named<KeyAction, OpenUrlAction>("OpenUrlA");
			add_type_make_named<KeyAction, CloseWindowAction>("CloseWindowA");
			add_type_make_named<KeyAction, SwitcherAction>("SwitcherA");
			//add_type_make_named<KeyAction, SetSIntAction>("SetSIntA");
			//add_type_make_named<KeyAction, SetSFloatAction>("SetSFloatA");
			
			add_type_make_named<BasicKeyAction<Text&>, TextCopyAction>("TextCopyA");
			add_type_make_named<BasicKeyAction<Text&>, TextSelectionAction>("TextSelectionA");
			
			add_type_make_named<BaseSwitchTabsAction, SwitchTabsAction>("SwitchTabsA");
			add_type_make_named<BaseSwitchTabsAction, WhileSwitchTabsAction>("WhileSwitchTabsA");
			
			add_type_make_named<IBaseInteraction, OneKeyInteraction>("OneKeyI");
			add_type_make_named<IBaseInteraction, KeysInteraction>("KeysI");
			add_type_make_named<IBaseInteraction, EmptyInteraction>("EmptyI");
			
			add_type_make_named<IHidePanelInteraction, DontHidePanelInteraction>("DontHidePI");
			add_type_make_named<IHidePanelInteraction, ClickHidePanelInteraction>("ClickHidePI");
			add_type_make_named<IHidePanelInteraction, PointingHidePanelInteraction>("PointingHidePI");
			add_type_make<IPanelInteraction, IHidePanelInteraction>();
			add_type_make_named<IDisplayPanelInteraction, ClickDisplayPanelInteraction>("ClickDisplayPI");
			add_type_make_named<IDisplayPanelInteraction, PointingDisplayPanelInteraction>("PointingDisplayPI");
			add_type_make<IPanelInteraction, IDisplayPanelInteraction>();
			add_type_make_named<IMovePanelInteraction, CoefficientMovePanelInteraction>("CoefficientMovePI");
			add_type_make_named<IMovePanelInteraction, DontMovePanelInteraction>("DontMovePI");
			add_type_make_named<IMovePanelInteraction, SideMovePanelInteraction>("SideMovePI");
			add_type_make<IPanelInteraction, IMovePanelInteraction>();
			
			add_type_make<IBasicInteraction<Text&>, BasicKeysInteraction<Text&> >("TextKeysInteraction", "TextKeysI");
			//add_type_make<IBasicInteraction<Text&>, BasicHotkeyInteraction<Text&> >("TextHotkeyInteraction", "TextHotkeyI");
			add_type_make<IBasicInteraction<Text&>, BasicEmptyInteraction<Text&> >("TextEmptyInteraction", "TextEmptyI");
			
			add_fn_make<OnlyDrawable>(video_convert, "Video");
			//add_fn<Box>(switcher_tabs_decode_pointer, "SwitcherTabs", "SwitcherT");
			
			add_type_make_named<IUninteractive, Empty>();
			add_type_make_named<IUninteractive, FullColor>();
			add_type_make_named<IUninteractive, RoundedRectangle>();
			add_type_make_named<IUninteractive, Capsule>();
			add_type_make_named<IUninteractive, Sprite>();
			add_type_make_named<IUninteractive, Bar>();
			add_type_make_named<IUninteractive, Caption>();
			add_type_make_named<IUninteractive, BoxUninteractive>();
			add_type_make<IScalable, IUninteractive>();
			add_type_make_named<Box, BoxDebug>();
			add_type_make_named<Box, BoxBackground>();
			add_type_make_named<Box, BoxAlternative>();
			add_type_make_named<Box, BoxBorder>();
			add_type_make_named<Box, BoxBorderVertical>();
			add_type_make_named<Box, BoxBorderHorizontal>();
			add_type_make_named<Box, BoxConstBorder>();
			add_type_make_named<Box, BoxConstBezel>();
			add_type_make_named<Box, BoxConstRatio>();
			add_type_make_named<Box, BoxConstRatioCenter>();
			add_type_make_named<Box, BoxMovableBorder>();
			add_type_make_named<Box, BoxPanel>();
			add_type_make_named<Box, BoxRenderTexture>();
			add_type_make_named<Box, BoxShader>();
			add_type_make_named<Box, BoxSwitchTabs>();
			add_type_make_named<Box, BoxMakePermeable>();
			add_type_make_named<Box, BoxScroll>();
			add_type_make_named<Box, BoxSwitch>();
			add_type_make_named<Box, BoxTabs>();
			add_type_make_named<Box, BoxSwitcherTabs>();
			add_type_make_named<Box, BoxConstCenter>();
			add_type_make_named<Box, BoxUninteractive>();
			add_type_make<IScalable, Box>();
			add_type_make_named<IScalable, Slider>();
			add_type_make_named<IScalable, ConstSlider>();
			add_type_make_named<IScalable, ButtonPanel>();
			add_type_make_named<IScalable, Button>();
			add_type_make_named<IScalable, Switcher>();
			add_type_make<IComponent, IScalable>();
			add_type_make_named<IComponent, Text>();
			
			add_type_make_named<BasePanel, ConstPanel>();
			add_type_make_named<BasePanel, Panel>();
			
			add_bool_determine_make<SBool>();
			add_bool_determine_make<FullColor>();
			add_bool_determine_make<RoundedRectangle>();
			add_bool_determine_make<Sprite>();
			//add_determine_make<TextBlock>();
			add_determine_make<ISizing>(determine_sizing);
			add_determine_make<ISizing2>(determine_sizing2);
			add_determine<IPositioning>(determine_positioning);
			add_determine_make<IPositioning2>(determine_positioning2);
			add_bool_determine_make<OpenUrlAction>(determine_url);
			add_bool_determine_make<KeysInteraction>(determine_url);
			//add_bool_determine_make<BasicKeysInteraction<Text&> >(determine_url);
			return true;
		}()};
	}
	
	/*
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
	 */
}