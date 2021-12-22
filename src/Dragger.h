#pragma once
#include "objects/Object.h"
#include <list>

class Dragger {
private:
    Object* nowDragging;
public:
    Dragger();
    void TryCapture(list<Object*>& objects, sf::Event& event);
    void DoDrag(sf::Window& window);
    void Release();
};