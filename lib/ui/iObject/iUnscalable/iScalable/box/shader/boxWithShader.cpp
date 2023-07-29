#include "boxWithShader.hpp"

namespace ui {
	uint convertTransmissionDef(const YAML::Node& node) {
		uint transmission{};
		if(node) {
			std::map<std::string, BoxWithShader::Transmission> transmissionMap{
				{"size",          BoxWithShader::Transmission::size},
				{"texture",       BoxWithShader::Transmission::texture},
				{"aspectRatio",   BoxWithShader::Transmission::aspectRatio},
				{"mousePosition", BoxWithShader::Transmission::mousePosition},
				{"time",          BoxWithShader::Transmission::time},
			};
			
			if(node.IsScalar()) {
				std::string strTransmission = node.as<std::string>();
				transmission = transmissionMap[strTransmission];
			} else if(node.IsSequence()) {
				std::string strTransmission;
				for(const auto& item: node) {
					strTransmission = item.as<std::string>();
					transmission = static_cast<BoxWithShader::Transmission>(transmission | transmissionMap[strTransmission]);
				}
			}
		}
		return transmission;
	}
	
	BoxWithShader::BoxWithShader(
		BoxPtr<IScalable>&& object, sf::Shader* shader, uint transmission,
		std::map<std::string, PISfloat> valuesF,
		std::map<std::string, PISint> valuesI,
		std::map<std::string, PISbool> valuesB,
		std::map<std::string, PISValue<sf::Color>> valuesC,
		std::map<std::string, PSRVec2f> valuesV,
		bool optimize, sf::Vector2f minSize
	) : BoxWithRenderTexture(std::forward<BoxPtr<IScalable> >(object), optimize, minSize), shader(shader), transmission(transmission) {
		clock.restart();
		
		for(auto& [name, value]: valuesF) {
			value->addSetter([&](float var) {
				setUniform(name, var);
			});
		}
		for(auto& [name, value]: valuesI) {
			value->addSetter([&](int var) {
				setUniform(name, var);
			});
		}
		for(auto& [name, value]: valuesB) {
			value->addSetter([&](bool var) {
				setUniform(name, var);
			});
		}
		for(auto& [name, value]: valuesC) {
			value->addSetter([&](sf::Color var) {
				setUniform(name, var);
			});
		}
		for(auto& [name, value]: valuesV) {
			value->addSetter([&](sf::Vector2f var) {
				setUniform(name, var);
			});
		}
	}
	
	BoxWithShader::~BoxWithShader() {
		delete shader;
	}
	
	void BoxWithShader::setUniform(std::string name, float var) {
		shader->setUniform(name, var);
	}
	
	void BoxWithShader::setUniform(std::string name, int var) {
		shader->setUniform(name, var);
	}
	
	void BoxWithShader::setUniform(std::string name, bool var) {
		shader->setUniform(name, var);
	}
	
	void BoxWithShader::setUniform(std::string name, sf::Color var) {
		shader->setUniform(name, sf::Glsl::Vec4{var});
	}
	
	void BoxWithShader::setUniform(std::string name, sf::Vector2f var) {
		shader->setUniform(name, var);
	}
	
	void BoxWithShader::setSize(sf::Vector2f size) {
		if(transmission & Transmission::size)
			shader->setUniform("size", size);
		if(transmission & Transmission::aspectRatio)
			shader->setUniform("aspectRatio", size.x / size.y);
		ILayout::setSize(size);
	}
	
	void BoxWithShader::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			drawManager.draw();
			renderTexture.display();
			sprite.setTexture(renderTexture.getTexture());
			active = false;
		}
		if(transmission & Transmission::time)
			shader->setUniform("time", clock.getElapsedTime().asSeconds());
		if(transmission & Transmission::texture)
			shader->setUniform("texture", renderTexture.getTexture());
		renderTarget->draw(sprite, shader);
	}
	
	void BoxWithShader::resize(sf::Vector2f size, sf::Vector2f position) {
		if(transmission & Transmission::size)
			shader->setUniform("size", size);
		if(transmission & Transmission::aspectRatio)
			shader->setUniform("aspectRatio", size.x / size.y);
		BoxWithRenderTexture::resize(size, position);
	}
	
	bool BoxWithShader::updateInteractions(sf::Vector2f mousePosition) {
		if(transmission & Transmission::mousePosition)
			shader->setUniform("mousePosition", mousePosition - layout.position);
		return BoxWithRenderTexture::updateInteractions(mousePosition);
	}
	
	template<typename T>
	std::map<std::string, std::shared_ptr<T>> getSValuesDef(const YAML::Node& node) {
		std::map<std::string, std::shared_ptr<T>> result;
		if(node) {
			for(auto& [name, nodeValue]: node.as<std::map<std::string, YAML::Node>>()) {
				result[name] = Buffer::get<T>(nodeValue);
			}
		}
		return result;
	}
	
	bool DecodePointer<BoxWithShader>::decodePointer(const YAML::Node& node, BoxWithShader*& boxWithShader) {
		sf::Shader* shader{new sf::Shader{}};
		if(node["shader"]) {
			node["shader"] >> *shader;
		}
		boxWithShader = new BoxWithShader{
			node["object"].as<BoxPtr<IScalable> >(),
			shader,
			convertTransmissionDef(node["transmission"]),
			getSValuesDef<ISfloat>(node["values-f"]),
			getSValuesDef<ISint>(node["values-i"]),
			getSValuesDef<ISbool>(node["values-b"]),
			getSValuesDef<ISValue<sf::Color> >(node["values-c"]),
			getSValuesDef<SRVec2f>(node["values-v"]),
			convDef(node["optimize"], true),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}
