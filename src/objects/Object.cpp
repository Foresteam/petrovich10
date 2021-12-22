#include "Object.h"

Object::Object(string filename, Vector2 textureRectSize) {
	gonnaBeDeleted = false;
	
	texture.loadFromFile(filename);
	image.setTexture(texture);

	if (textureRectSize.Length() > 0)
		size = textureRectSize;
	else
		size = Vector2(texture.getSize().x, texture.getSize().y);
	image.setOrigin(GetW() / 2, GetH() / 2);
	pos = Vector2(image.getPosition().x, image.getPosition().y);

	velocity = Vector2(.0, .0);

	scale = Vector2(1, 1);

	background = false;
	kinematic = false;

	hitbox = HitboxRect(&pos, &size);
}
Object::~Object() {}
int Object::MoveTo(const Vector2& npos) {
    int moved = (GetPos().x != npos.x) + ((fabs(GetPos().y - npos.y) > 0.0001) << 1);
	image.setPosition(npos.x, npos.y);
	pos = npos;
    return moved;
}
int Object::Move(const Vector2& add) {
	return MoveTo(pos + add);
}
void Object::setImage(string filename) {
	texture.loadFromFile(filename);
	image.setTexture(texture);
}
void Object::Scale(const Vector2& scale) {
	image.setScale(scale.x, scale.y);
	this->scale = Vector2(scale.x * this->scale.x, scale.y * this->scale.y);
	size = Vector2(size.x * scale.x, size.y * scale.y);
}
float Object::GetW() {
	return size.x;
}
float Object::GetH() {
	return size.y;
}
Vector2 Object::GetPos() {
	return pos;
}
Vector2 Object::GetScale() {
	return scale;
}
Vector2 Object::GetSize() {
	return size;
}

// void Object::Control() {
// }