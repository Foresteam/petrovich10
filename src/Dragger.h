#pragma once
#include "entities/Entity.h"
#include <list>

class Dragger {
private:
    Entity* nowDragging;
public:
    Dragger();
    void TryCapture(list<Entity*>& objects, sf::Event& event);
    void DoDrag(sf::Window& window);
    void Release();
};