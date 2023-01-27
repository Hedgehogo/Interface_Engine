#include "boxWithShader.hpp"

namespace ui {
	void convertTransmission(const YAML::Node &node, uint &transmission) {
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
			for(const auto &item: node) {
				strTransmission = item.as<std::string>();
				transmission = static_cast<BoxWithShader::Transmission>(transmission | transmissionMap[strTransmission]);
			}
		}
	}
	
	BoxWithShader::BoxWithShader(IScalable *object, sf::Shader *shader, uint transmission,
								 std::map<std::string, PISfloat> valuesF,
								 std::map<std::string, PISint> valuesI,
								 std::map<std::string, PISbool> valuesB,
								 std::map<std::string, PISValue<sf::Color>> valuesC,
								 std::map<std::string, PSRVec2f> valuesV,
								 bool optimize, sf::Vector2f minSize) :
		BoxWithRenderTexture(object, optimize, minSize), shader(shader), transmission(transmission) {
		clock.restart();
		
		for(auto &[name, value]: valuesF) {
			value->addSetter([&](float var) {
				setUniform(name, var);
			});
		}
		for(auto &[name, value]: valuesI) {
			value->addSetter([&](int var) {
				setUniform(name, var);
			});
		}
		for(auto &[name, value]: valuesB) {
			value->addSetter([&](bool var) {
				setUniform(name, var);
			});
		}
		for(auto &[name, value]: valuesC) {
			value->addSetter([&](sf::Color var) {
				setUniform(name, var);
			});
		}
		for(auto &[name, value]: valuesV) {
			value->addSetter([&](sf::Vector2f var) {
				setUniform(name, var);
			});
		}
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
		Layout::setSize(size);
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
			shader->setUniform("mousePosition", mousePosition - position);
		return BoxWithRenderTexture::updateInteractions(mousePosition);
	}
	
	template <typename T>
	std::map<std::string, std::shared_ptr<T>> getSValues(const YAML::Node &node) {
		std::map<std::string, std::shared_ptr<T>> result;
		for(auto &[name, nodeValue]: node.as<std::map<std::string, YAML::Node>>()) {
			result[name] = Buffer::get<T>(nodeValue);
		}
		return result;
	}
	
	bool convertPointer(const YAML::Node &node, BoxWithShader *&boxWithShader) {
		IScalable *object;
		sf::Shader *shader = new sf::Shader{};
		uint transmission{};
		std::map<std::string, PISfloat> valuesF;
		std::map<std::string, PISint> valuesI;
		std::map<std::string, PISbool> valuesB;
		std::map<std::string, PISValue<sf::Color>> valuesC;
		std::map<std::string, PSRVec2f> valuesV;
		bool optimize{true};
		sf::Vector2f minSize{0, 0};
		node["object"] >> object;
		if(node["transmission"])
			convertTransmission(node["transmission"], transmission);
		if(node["shader"])
			node["shader"] >> *shader;
		if(node["values-f"])
			valuesF = getSValues<ISfloat>(node["values-f"]);
		if(node["values-i"])
			valuesI = getSValues<ISint>(node["values-i"]);
		if(node["values-b"])
			valuesB = getSValues<ISbool>(node["values-b"]);
		if(node["values-c"])
			valuesC = getSValues<ISValue<sf::Color>>(node["values-c"]);
		if(node["values-v"])
			valuesV = getSValues<SRVec2f>(node["values-v"]);
		if(node["optimize"])
			node["optimize"] >> optimize;
		if(node["min-size"])
			node["min-size"] >> minSize;
		boxWithShader = new BoxWithShader{object, shader, transmission, valuesF, valuesI, valuesB, valuesC, valuesV, optimize, minSize};
		return true;
	}
}
