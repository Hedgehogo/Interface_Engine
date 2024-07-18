#include "init.hpp"
#include "IE/sizing-positioning/ISizing/Functions/determine_sizing/determine_sizing.hpp"
#include "IE/sizing-positioning/ISizing2/Functions/determine_sizing2/determine_sizing2.hpp"
#include "IE/sizing-positioning/IPositioning/Functions/determine_positioning/determine_positioning.hpp"
#include "IE/sizing-positioning/IPositioning2/Functions/determine_positioning2/determine_positioning2.hpp"
#include "IE/modules/load_modules.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "IE/utils/meta/is_contains_v/is_contains_v.hpp"

namespace ie {
	auto init(int argc, char* argv[], std::filesystem::path modules_list) -> void {
		ieml_rttb_init();
		load_modules(argc, argv, modules_list);
	}
	
	template<typename T>
	auto ieml_rttb_init_shared(std::string first, std::string name) -> void {
		add_type_with_make<ISMutable<T>, SMutable<T> >(std::string("M") + name);
		add_type_with_make<ISReadable<T>, ISMutable<T> >();
		add_type_with_make<ISReadable<T>, SReadable<T> >(name);
		add_names<ISReadable<T> >(std::string("I") + name);
		add_names<typename ISReadable<T>::Make >(std::string("I") + name);
		
		add_type_make<KeyAction, SetSValueAction<T> >(std::string("Set") + name + std::string("Action"));
		add_type_make<KeyAction, AddSValueAction<T> >(std::string("Add") + name + std::string("Action"));
		add_type_with_make<SReadable<bool>, SEqual<T> >(std::string("(=)") + name);
		add_type_with_make<SReadable<bool>, SNotEqual<T> >(std::string("(!=)") + name);
		
		if constexpr(meta::is_contains_v<T, size_t, int, float>) {
			add_type_with_make<SString, SToString<T> >(std::string("ToString") + first);
			add_type_with_make<SReadable<bool>, SEqual<sf::Vector2<T> > >(std::string("(=)Vec2") + first);
			add_type_with_make<SReadable<bool>, SNotEqual<sf::Vector2<T> > >(std::string("(!=)Vec2") + first);
			add_type_with_make<SReadable<bool>, SLess<T> >(std::string("(<)") + name);
			add_type_with_make<SReadable<bool>, SGreater<T> >(std::string("(>)") + name);
			add_type_with_make<SReadable<bool>, SLessOrEqual<T> >(std::string("(<=)") + name);
			add_type_with_make<SReadable<bool>, SGreaterOrEqual<T> >(std::string("(>=)") + name);
			add_type_with_make<SRanged<T>, SRAnyOf<T> >("RAnyOf");
			add_type_with_make<SRanged<T>, SRBezierCurve<T> >("RBezierCurve");
			add_type_with_make<SRanged<T>, SRSin<T> >("RSin");
			add_type_with_make<SRanged<T>, SRCos<T> >("RCos");
			add_type_with_make<SRanged<T>, SLerp<T> >("Lerp");
			add_type_with_make<SRanged<T>, SRLerp<T> >("RLerp");
			add_type_with_make<SRanged<T>, SRFloor<T> >("RFloor");
			add_type_with_make<SRanged<T>, SRCeil<T> >("RCeil");
			add_type_with_make<SRanged<T>, SRRound<T> >("RRound");
			add_type_with_make<SReadable<T>, SFloor<T> >("Floor");
			add_type_with_make<SReadable<T>, SCeil<T> >("Ceil");
			add_type_with_make<SReadable<T>, SRound<T> >("Round");
			add_type_with_make<ISMVec2<T>, SMVec2<T> >(std::string("MVec2") + first);
			add_type_with_make<ISMRVec2<T>, SMRVec2<T> >(std::string("MRVec2") + first);
			add_type_with_make<ISMutable<sf::Vector2<T> >, ISMVec2<T> >(
				std::string("IMutable(Vec2") + first + std::string(")")
			);
			add_type_with_make<ISMutable<T>, SMRanged<T> >(std::string("MR") + name);
			add_type_with_make<ISMRanged<T>, SMRanged<T> >();
			add_type_with_make<ISMutable<T>, ISMRanged<T> >(std::string("IMR") + name);
			add_type_with_make<ISVec2<T>, SVec2<T> >(std::string("Vec2") + first);
			add_type_with_make<ISRVec2<T>, ISMRVec2<T> >(std::string("IMRVec2") + first);
			add_type_with_make<ISRVec2<T>, SRVec2<T> >(std::string("RVec2") + first);
			add_type_with_make<ISVec2<T>, ISMVec2<T> >(std::string("IMVec2") + first);
			add_type_with_make<ISReadable<sf::Vector2<T> >, ISVec2<T> >(std::string("IVec2") + first);
			add_type_with_make<ISReadable<T>, SRanged<T> >(std::string("R") + name);
			add_type_with_make<ISRanged<T>, SRanged<T> >(std::string("R") + name);
			add_type_with_make<ISRanged<T>, ISMRanged<T> >(std::string("IMR") + name);
			add_type_with_make<ISReadable<T>, ISRanged<T> >(std::string("IR") + name);
			
			add_bool_determine_make<SMRVec2<T> >();
			add_bool_determine_make<SMRanged<T> >();
		}
	}
	
	auto ieml_rttb_init() -> void {
		[[maybe_unused]] static bool once{[]() {
			ieml_rttb_init_shared<bool>("B", "Bool");
			ieml_rttb_init_shared<size_t>("S", "Size");
			ieml_rttb_init_shared<int>("I", "Int");
			ieml_rttb_init_shared<float>("F", "Float");
			add_type_with_make<SRFloat, STime>("Time");
			add_type_with_make<ISInt, SCastF2I>("CastF");
			add_type_with_make<ISSize, SCastF2S>("CastF");
			add_type_with_make<ISFloat, SCastI2F>("CastI");
			add_type_with_make<ISSize, SCastF2S>("CastI");
			add_type_with_make<ISFloat, SCastS2F>("CastS");
			add_type_with_make<ISInt, SCastS2I>("CastS");
			add_type_with_make<ISRInt, SRCastF2I>("RCastF");
			add_type_with_make<ISRSize, SRCastF2S>("RCastF");
			add_type_with_make<ISRFloat, SRCastI2F>("RCastI");
			add_type_with_make<ISRSize, SRCastF2S>("RCastI");
			add_type_with_make<ISRFloat, SRCastS2F>("RCastS");
			add_type_with_make<ISRInt, SRCastS2I>("RCastS");
			add_type_with_make<ISMString, SMString>("MString");
			add_type_with_make<ISString, SString>("String");
			add_type_with_make<ISString, ISMString>("IMString");
			add_names<ISString::Make>("IString");
			add_type_with_make<SReadable<bool>, SEqualS >(std::string("(=)String"));
			add_type_with_make<SReadable<bool>, SNotEqualS >(std::string("(!=)String"));
			
			add_type_make_named<ISizing, ConstSizing>();
			add_type_make_named<ISizing, RelativeNormalSizing>();
			add_type_make_named<ISizing, RelativeParentSizing>();
			add_type_make_named<ISizing, ParentCoefficientSizing>();
			add_type_make_named<ISizing, TargetCoefficientSizing>();
			add_type_make_named<ISizing, SmartSizing>();
			add_names<ISizing::Make>("ISizing");
			
			add_type_make_named<ISizing2, Sizing2>();
			add_type_make_named<ISizing2, ConstRatioSizing2>();
			add_names<ISizing2::Make>("ISizing2");
			
			add_type_named<IPositioning, InternalPositioning>("InternalPos");
			add_type_named<IPositioning, InternalTargetPositioning>("InternalTargetPos");
			add_type_named<IPositioning, MatchPositioning>("MatchPos");
			add_type_named<IPositioning, MatchTargetPositioning>("MatchTargetPos");
			add_type_named<IPositioning, MatchSidesPositioning>("MatchSidesPos");
			add_names<IPositioning>("IPos");
			
			add_type_named<IPositioning2, Positioning2>("Pos2");
			add_type_named<IPositioning2, InternalPositioning2>("InternalPos2");
			add_names<IPositioning>("IPos2");
			
			add_type_make_named<BaseLine, Underline>();
			add_type_make_named<BaseLine, StrikeThrough>();
			add_names<BaseLine::Make>("BaseLine");
			
			add_type_make_named<BaseTextBlock, TextBlock>();
			add_type_make_named<BaseTextBlock, InteractiveTextBlock>();
			add_type_make_named<BaseTextBlock, ObjectTextBlock>();
			add_names<BaseTextBlock::Make>("BaseTextBlock");
			
			add_type_make_named<BaseTextResizer, TextResizer>();
			add_names<BaseTextResizer::Make>("BaseTextResizer");
			
			add_type_make<KeyAction, OpenUrlAction>("OpenUrlAction", "OpenUrlA");
			add_type_make<KeyAction, CloseWindowAction>("CloseWindowAction", "CloseWindowA");
			add_type_make<KeyAction, SwitcherAction>("SwitcherAction", "SwitcherA");
			//add_type_make_named<KeyAction, SetSIntAction>("SetSIntA");
			//add_type_make_named<KeyAction, SetSFloatAction>("SetSFloatA");
			add_names<KeyAction::Make>("KeyAction");
			
			add_type_make_named<BasicKeyAction<Text&>, TextCopyAction>("TextCopyA");
			add_type_make_named<BasicKeyAction<Text&>, TextSelectionAction>("TextSelectionA");
			add_names<BasicKeyAction<Text&>::Make>("TextKeyAction");
			
			add_type_make_named<BaseSwitchTabsAction, SwitchTabsAction>("SwitchTabsA");
			add_type_make_named<BaseSwitchTabsAction, WhileSwitchTabsAction>("WhileSwitchTabsA");
			add_names<BaseSwitchTabsAction::Make>("BaseSwitchTabsAction");
			
			add_type_make_named<IBaseInteraction, HotkeyInteraction>("HotkeyI");
			add_type_make_named<IBaseInteraction, OneKeyInteraction>("OneKeyI");
			add_type_make_named<IBaseInteraction, KeysInteraction>("KeysI");
			add_type_make_named<IBaseInteraction, EmptyInteraction>("EmptyI");
			add_names<IBaseInteraction::Make>("IBaseInteraction");
			
			add_type_make_named<IHidePanelInteraction, DontHidePanelInteraction>("DontHidePI");
			add_type_make_named<IHidePanelInteraction, ClickHidePanelInteraction>("ClickHidePI");
			add_type_make_named<IHidePanelInteraction, PointingHidePanelInteraction>("PointingHidePI");
			add_type_make_named<IPanelInteraction, IHidePanelInteraction>("IHidePI");
			add_type_make_named<IDisplayPanelInteraction, ClickDisplayPanelInteraction>("ClickDisplayPI");
			add_type_make_named<IDisplayPanelInteraction, PointingDisplayPanelInteraction>("PointingDisplayPI");
			add_type_make_named<IPanelInteraction, IDisplayPanelInteraction>("IDisplayPI");
			add_type_make_named<IMovePanelInteraction, CoefficientMovePanelInteraction>("CoefficientMovePI");
			add_type_make_named<IMovePanelInteraction, DontMovePanelInteraction>("DontMovePI");
			add_type_make_named<IMovePanelInteraction, SideMovePanelInteraction>("SideMovePI");
			add_type_make_named<IPanelInteraction, IMovePanelInteraction>("IMovePI");
			add_names<IPanelInteraction::Make>("IPanelInteraction");
			
			add_type_make<IBasicInteraction<Text&>, BasicKeysInteraction<Text&> >("TextKeysInteraction", "TextKeysI");
			add_type_make<IBasicInteraction<Text&>, BasicHotkeyInteraction<Text&> >("TextHotkeyInteraction", "TextHotkeyI");
			add_type_make<IBasicInteraction<Text&>, BasicEmptyInteraction<Text&> >("TextEmptyInteraction", "TextEmptyI");
			add_names<IBasicInteraction<Text&>::Make>("ITextInteraction");
			
			add_fn_make<OnlyDrawable>(video_convert, "Video");
			//add_fn<Box>(switcher_tabs_decode_pointer, "SwitcherTabs", "SwitcherT");
			add_type_make_named<INonInteractive, Empty>();
			add_type_make_named<INonInteractive, FullColor>();
			add_type_make_named<INonInteractive, RoundedRectangle>();
			add_type_make_named<INonInteractive, Capsule>();
			add_type_make_named<INonInteractive, Sprite>();
			add_type_make_named<INonInteractive, Bar>();
			add_type_make<INonInteractive, Caption>("Caption");
			add_type_make<INonInteractive, EditCaption>("EditCaption");
			add_type_make_named<INonInteractive, BoxUninteractive>();
			add_type_make_named<IScalable, INonInteractive>();
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
			add_type_make<Box, BoxMovableBorder>("BoxMovableBorder");
			add_type_make<Box, MovableBorder>("MovableBorder");
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
			add_type_make_named<IScalable, Box>();
			add_type_make_named<IScalable, Slider>();
			add_type_make_named<IScalable, ConstSlider>();
			add_type_make_named<IScalable, ButtonPanel>();
			add_type_make_named<IScalable, Button>();
			add_type_make_named<IScalable, Switcher>();
			add_type_make_named<IScalableV, IScalable>();
			add_type_make_named<IScalableH, IScalable>();
			add_type_make_named<IComponent, IScalableV>();
			add_type_make_named<IComponent, IScalableH>();
			add_type_make_named<IComponent, Text>();
			add_names<BoxModulesLoader::LibsOneType>("LibsOneType");
			add_names<BoxModulesLoader::LibType>("LibType");
			add_names<BoxModulesLoader::Make>("BoxModulesLoader");
			add_names<IComponent::Make>("IComponent");
			
			add_type_make_named<BasePanel, ConstPanel>();
			add_type_make_named<BasePanel, Panel>();
			add_names<BasePanel::Make>("BasePanel");
			
			add_bool_determine_make<SMString>();
			add_bool_determine_make<TextBlock>();
			add_bool_determine_make<SMBool>();
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