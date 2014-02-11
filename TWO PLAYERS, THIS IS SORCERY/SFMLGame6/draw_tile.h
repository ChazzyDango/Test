#pragma once
#include <SFML\Graphics.hpp>

class draw_tile :public sf::Drawable, public sf::Transformable
{
public:
	draw_tile(void);
	~draw_tile(void);
	bool load(const std::string& tileset, sf::Vector2u squareSize, const int* squares, unsigned int width, unsigned int height);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

};
