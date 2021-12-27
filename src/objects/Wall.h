#pragma once
#include "Healthy.h"
#include <SFML/Audio.hpp>

class Wall : public Healthy {
private:
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
public:
    Wall();
    bool TakeDamage(float amount) override;
};