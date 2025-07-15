#include "Assets.h"

sf::Texture Assets::PLAYER_TEXTURE;

void Assets::init()
{
	PLAYER_TEXTURE.loadFromFile("./asset/sprite/player.png");
}
