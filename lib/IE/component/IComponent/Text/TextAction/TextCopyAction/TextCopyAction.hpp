#pragma once

#include "IE/trigger/IAction/IBasicActivityAction/IBasicActivityAction.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	class Text;
	
	template<typename T>
	class BasicTextCopyAction;
	
	namespace make_system {
		template<typename T>
		struct BasicTextCopyAction : public IBasicActivityAction<Text&> {
			bp::BoxPtr<T> clipboard;
			
			BasicTextCopyAction(bp::BoxPtr<T>&& clipboard = bp::BoxPtr<T>{});
			
			auto make(BasicActionInitInfo<Text&> init_info) -> ie::BasicTextCopyAction<T>*;
		};
	}
	
	template<typename T>
	class BasicTextCopyAction : public IBasicActivityAction<Text&> {
	public:
		using Make = make_system::BasicTextCopyAction<T>;
		
		BasicTextCopyAction(Make&& make, BasicActionInitInfo<Text&> init_info);
		
		auto update(bool active) -> void override;
	
	protected:
		Text* text_;
		bp::BoxPtr<T> clipboard_;
	};
	
	using TextCopyAction = BasicTextCopyAction<sf::Clipboard>;
	
	/// @brief Trait to work with the clipboard.
	///
	/// Must contain functions:
	/// @code
	/// static auto set_string(T& clipboard, sf::String str) -> void;
	/// static auto get_string(T& clipboard) -> sf::String;
	/// @endcode
	///
	/// @tparam T Clipboard type.
	template<typename T>
	struct ProcessClipboard {
	};
	
	template<>
	struct ProcessClipboard<sf::Clipboard> {
		static auto set_string(sf::Clipboard& clipboard, sf::String const& str) -> void;
		
		static auto get_string(sf::Clipboard& clipboard) -> sf::String;
	};
}

template<typename T>
struct ieml::Decode<char, ie::make_system::BasicTextCopyAction<T>> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::make_system::BasicTextCopyAction<T>>;
};

#include "TextCopyAction.inl"