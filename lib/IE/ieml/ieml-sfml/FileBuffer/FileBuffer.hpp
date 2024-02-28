#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	template<typename T>
	struct LoadFromFile {
		static void load(T& object, std::string name);
	};
	
	template<typename T>
	class FileBuffer {
	public:
		FileBuffer() = default;
		
		static T& get(const std::string& name);
		
		static void set_object(const std::string& name, const std::string& file_path);
		
		static void add_alias(const std::string& name, const std::string& alias);
	
	protected:
		static absl::flat_hash_map<std::string, T> objects_;
		static absl::flat_hash_map<std::string, T*> aliases_;
	};

#ifdef IE_ImageMagick_FOUND
	/*old_yaml
	template<>
	struct LoadFromFile<std::vector<sf::Texture> > {
		static void load(std::vector<sf::Texture>& object, std::string name);
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
		static orl::Option<sf::Texture&> decode(ieml::Node const& node);
	};
	
	template<>
	struct Decode<char, sf::Font&> {
		static orl::Option<sf::Font&> decode(ieml::Node const& node);
	};
	
#ifdef IE_ImageMagick_FOUND
	/*old_yaml
	template<>
	struct Decode<char, std::vector<sf::Texture>&> {
		static orl::Option<std::vector<sf::Texture>&> decode(ieml::Node const& node);
	};
	*/
#endif
}

#include "FileBuffer.inl"
