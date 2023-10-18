#pragma once

#include "../BoxRenderTexture/BoxRenderTexture.hpp"
#include "IE/modules/yaml-cpp/shared/ISVector2/SVector2/SVector2.hpp"

namespace ie {
	class BoxShader : public BoxRenderTexture {
	public:
		enum Transmission {
			None = 0,
			Texture = 1 << 0,
			MousePosition = 1 << 1,
			Size = 1 << 2,
			AspectRatio = 1 << 3,
			Time = 1 << 4,
		};
		
		struct Make : public BoxRenderTexture::Make {
			sf::Shader* shader;
			uint transmission;
			std::map<std::string, PISfloat> values_f = {};
			std::map<std::string, PISint> values_i = {};
			std::map<std::string, PISbool> values_b = {};
			std::map<std::string, PISValue<sf::Color>> values_c = {};
			std::map<std::string, PSRVec2f> values_v = {};
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				sf::Shader* shader,
				uint transmission,
				std::map<std::string, PISfloat> values_f = {},
				std::map<std::string, PISint> values_i = {},
				std::map<std::string, PISbool> values_b = {},
				std::map<std::string, PISValue<sf::Color>> values_c = {},
				std::map<std::string, PSRVec2f> values_v = {},
				bool optimize = true,
				sf::Vector2f min_size = {}
			);
			
			BoxShader* make(InitInfo init_info) override;
		};
		
		BoxShader(Make&& make, InitInfo init_info);
		
		BoxShader(
			BoxPtr<IScalable>&& object, sf::Shader* shader, uint transmission,
			std::map<std::string, PISfloat> values_f = {},
			std::map<std::string, PISint> values_i = {},
			std::map<std::string, PISbool> values_b = {},
			std::map<std::string, PISValue<sf::Color>> values_c = {},
			std::map<std::string, PSRVec2f> values_v = {},
			bool optimize = true, sf::Vector2f min_size = {}
		);
		
		~BoxShader();
		
		void set_uniform(std::string name, float var);
		
		void set_uniform(std::string name, int var);
		
		void set_uniform(std::string name, bool var);
		
		void set_uniform(std::string name, sf::Color var);
		
		void set_uniform(std::string name, sf::Vector2f var);
		
		void set_size(sf::Vector2f size) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		BoxShader* copy() override;
	
	protected:
		sf::Shader* shader;
		uint transmission;
		
		sf::Clock clock;
	};
	
	template<>
	struct DecodePointer<BoxShader> {
		static bool decode_pointer(const YAML::Node& node, BoxShader*& box_with_shader);
	};
}