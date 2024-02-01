#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class Text;
	
	template<typename T>
	class BasicTextCopyAction : public BasicBaseKeyAction<Text&> {
	public:
		struct Make : public BasicBaseKeyAction<Text&>::Make {
			T& clipboard;
			
			Make(T&& clipboard = T{});
			
			BasicTextCopyAction* make(BasicActionInitInfo<Text&> init_info);
		};
		
		BasicTextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		Text* text;
		T& clipboard;
	};
	
	using TextCopyAction = BasicTextCopyAction<sf::Clipboard>;
	
	/// @brief Trait to work with the clipboard.
	///
	/// Must contain functions:
	/// @code
	/// static void set_string(T& clipboard, std::u32string str);
	/// static std::u32string get_string(T& clipboard);
	/// @endcode
	///
	/// @tparam T Clipboard type.
	template<typename T>
	struct ProcessClipboard {
	};
	
	template<>
	struct ProcessClipboard<sf::Clipboard> {
		static void set_string(sf::Clipboard& clipboard, const sf::String& str);
		
		static sf::String get_string(sf::Clipboard& clipboard);
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<TextCopyAction> {
		static bool decode_pointer(const YAML::Node&, TextCopyAction*& text_copy_action);
	};
	*/
}

#include "TextCopyAction.inl"