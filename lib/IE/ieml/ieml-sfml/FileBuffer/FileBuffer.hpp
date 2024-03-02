#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	template<typename T>
	struct LoadFromFile {
		static auto load(T& object, std::string name) -> void;
	};
	
	template<typename T>
	class FileBuffer {
	public:
		FileBuffer() = default;
		
		static auto get(const std::string& name) -> T&;
		
		static auto set_object(std::string const& name, std::string const& file_path) -> void;
		
		static auto add_alias(std::string const& name, std::string const& alias) -> void;
	
	protected:
		static absl::flat_hash_map<std::string, T> objects_;
		static absl::flat_hash_map<std::string, T*> aliases_;
	};

#ifdef IE_ImageMagick_FOUND
	/*old_yaml
	template<>
	struct LoadFromFile<std::vector<sf::Texture> > {
		static auto load(std::vector<sf::Texture>& object, std::string name) -> void;
	};
	*/
#endif
}

namespace tnl {
	template<>
	struct TypeName<sf::Texture> {
		constexpr static auto type_name = tnl::StringView{"Texture"};
	};
	
	template<>
	struct TypeName<sf::Font> {
		constexpr static auto type_name = tnl::StringView{"Font"};
	};
}

namespace ieml {
	template<>
	struct Decode<char, sf::Texture&> {
		static auto decode(ieml::Node const& node) -> orl::Option<sf::Texture&>;
	};
	
	template<>
	struct Decode<char, sf::Font&> {
		static auto decode(ieml::Node const& node) -> orl::Option<sf::Font&>;
	};
	
#ifdef IE_ImageMagick_FOUND
	/*old_yaml
	template<>
	struct Decode<char, std::vector<sf::Texture>&> {
		static auto decode(ieml::Node const& node) -> orl::Option<std::vector<sf::Texture>&>;
	};
	*/
#endif
}

#include "FileBuffer.inl"
