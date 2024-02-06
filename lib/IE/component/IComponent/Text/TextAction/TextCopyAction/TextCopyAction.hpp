#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class Text;
	
	template<typename T>
	class BasicTextCopyAction;
	
	namespace make_system{
		template<typename T>
		struct BasicTextCopyAction : public BasicBaseKeyAction<Text&>::Make {
			bp::BoxPtr<T> clipboard;
			
			BasicTextCopyAction(bp::BoxPtr<T>&& clipboard = bp::BoxPtr<T>{});
			
			ie::BasicTextCopyAction<T>* make(BasicActionInitInfo<Text&> init_info);
		};
	}
	
	template<typename T>
	class BasicTextCopyAction : public BasicBaseKeyAction<Text&> {
	public:
		using Make = make_system::BasicTextCopyAction<T>;
		
		BasicTextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
	protected:
		void start_pressed() override;
		
		void stop_pressed() override;
		
		void while_pressed() override;
		
		void while_not_pressed() override;
		
		Text* text;
		bp::BoxPtr<T> clipboard;
	};
	
	using TextCopyAction = BasicTextCopyAction<sf::Clipboard>;
	
	/// @brief Trait to work with the clipboard.
	///
	/// Must contain functions:
	/// @code
	/// static void set_string(T& clipboard, sf::String str);
	/// static sf::String get_string(T& clipboard);
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
}

template<typename T>
struct ieml::Decode<char, ie::make_system::BasicTextCopyAction<T>> {
	static orl::Option<ie::make_system::BasicTextCopyAction<T>> decode(ieml::Node const& node);
};

#include "TextCopyAction.inl"