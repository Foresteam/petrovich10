#include "Object.h"

Object::Object(string filename, Vector2 textureRectSize) {
	texture.loadFromFile(filename);
	image.setTexture(texture);

	if (textureRectSize.Length() > 0)
		_size = textureRectSize;
	else
		_size = Vector2(texture.getSize().x, texture.getSize().y);
	image.setOrigin(GetW() / 2, GetH() / 2);
	_pos = Vector2(image.getPosition().x, image.getPosition().y);

	velocity = Vector2(.0, .0);

	_scale = Vector2(1, 1);

	background = false;
	kinematic = false;
	transparent = false;
	enabled = true;

	onGround = false;
	hitbox = HitboxRect(&_pos, &_size);
}
Object::~Object() {}
int Object::MoveTo(const Vector2& npos) {
    int moved = (GetPos().x != npos.x) + ((fabs(GetPos().y - npos.y) > 0.0001) << 1);
	image.setPosition(npos.x, npos.y);
	_pos = npos;
    return moved;
}
int Object::Move(const Vector2& add) {
	return MoveTo(_pos + add);
}
void Object::SetImage(string filename) {
	texture.loadFromFile(filename);
	image.setTexture(texture);
}
void Object::Scale(const Vector2& scale) {
	image.setScale(scale.x, scale.y);
	this->_scale = Vector2(scale.x * this->_scale.x, scale.y * this->_scale.y);
	_size = Vector2(_size.x * scale.x, _size.y * scale.y);
}

Vector2 Object::GravitationVector() {
	return Vector2(0, 1) * (mass * G * G_SCALE);
}
void Object::Gravitate() {
	if (kinematic)
		return;
	auto ex = velocity;
	velocity += GravitationVector() * deltaTime;
	if (ex.y * velocity.y < 0)
		printf("%s\n", _pos.ToString().c_str());
	Move(Vector2(0, velocity.y * deltaTime));
}
void Object::Collide(Object& other) {
	Object* pair[] = { this, &other };

	if ((int)pair[0]->background + (int)pair[1]->background == 1 || pair[1]->kinematic && pair[0]->kinematic || pair[0]->transparent || pair[1]->transparent || !pair[0]->enabled || !pair[1]->enabled)
		return;
	Vector2 pushVec = pair[0]->hitbox.GetPushOutVector(pair[1]->hitbox);
	if (pushVec.Length() == 0)
		return;

	Vector2 push[2] = {pushVec / 2, pushVec / -2};
	for (int i = 0, j = (i + 1) % 2; i < 2; i++, j = (i + 1) % 2)
		if (pair[i]->kinematic) {
			push[i] = 0, push[j] *= 2;
			break;
		}
		// works damned as ... But it's even worse without this.
		else if (pair[i]->mass > pair[j]->mass) {
			float k = pair[j]->mass / pair[i]->mass;
			push[i] *= 2 * k;
			push[j] *= 2 * (1 - k);
		}

	for (int i = 0; i < 2; i++)
		if (!pair[i]->kinematic) {
			if (push[i].x != 0)
				pair[i]->velocity.x = 0;
			if (push[i].y != 0) {
				if (pair[i]->velocity.y > 0)
					pair[i]->onGround = true;
				pair[i]->velocity.y = 0;
			}
			pair[i]->Move(push[i]);
		}
}

float Object::GetW() {
	return _size.x;
}
float Object::GetH() {
	return _size.y;
}
Vector2 Object::GetPos() {
	return _pos;
}
Vector2 Object::GetScale() {
	return _scale;
}
Vector2 Object::GetSize() {
	return _size;
}

bool Object::Update(list<Object*>& objects) {
	Move(Vector2(velocity.x * deltaTime, 0));
	return false;
}
void Object::Draw(sf::RenderWindow& window) {
	if (!enabled)
		return;
	window.draw(image);
}

void Object::Rotate(int direction, bool reversed) {
	auto scale = image.getScale();
	bool dlz = direction < 0;
	if (reversed)
		dlz = !dlz;
	if (dlz && scale.x < 0)
		image.setScale(-scale.x, scale.y);
	else if (!dlz && scale.x > 0)
		image.setScale(-scale.x, scale.y);
}

// void Object::Control() {
// }