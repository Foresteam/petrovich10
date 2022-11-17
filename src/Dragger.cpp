#include "Dragger.h"

Dragger::Dragger() {
    nowDragging = nullptr;
}
void Dragger::TryCapture(list<Entity*>& objects, sf::Event& event) {
    if (nowDragging)
        return;
    for (auto it = objects.rbegin(); it != objects.rend(); it++) {
        Entity* o = *it;
        if (
            !o->background &&
            event.mouseButton.x <= o->GetPos().x + o->GetW() / 2 &&
            event.mouseButton.x >= o->GetPos().x - o->GetW() / 2 &&
            event.mouseButton.y <= o->GetPos().y + o->GetH() / 2 &&
            event.mouseButton.y >= o->GetPos().y - o->GetH() / 2) {
                nowDragging = o;
                break;
            }
    }
}
void Dragger::DoDrag(sf::Window& window) {
	if (!nowDragging)
        return;
	nowDragging->MoveTo(i2v(sf::Mouse::getPosition(window)));
	nowDragging->velocity = Vector2();
}
void Dragger::Release() {
    nowDragging = nullptr;
}