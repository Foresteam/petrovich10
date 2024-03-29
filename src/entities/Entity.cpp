#include "Entity.h"

Entity::Entity(string filename, Vector2 textureRectSize) {
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
	_movementLock = 0;

	background = false;
	kinematic = false;
	transparent = false;
	enabled = true;
	collideWorld = true;

	onGround = false;
	hitbox = HitboxRect(&_pos, &_size);
}
int Entity::MoveTo(const Vector2& npos) {
    int moved = (GetPos().x != npos.x) + ((fabs(GetPos().y - npos.y) > 0.0001) << 1);
	image.setPosition(npos.x, npos.y);
	_pos = npos;
    return moved;
}
int Entity::Move(const Vector2& add) {
	return MoveTo(_pos + add);
}
void Entity::SetImage(string filename) {
	texture.loadFromFile(filename);
	image.setTexture(texture);
}
void Entity::Scale(const Vector2& scale) {
	image.setScale(scale.x, scale.y);
	this->_scale = Vector2(scale.x * this->_scale.x, scale.y * this->_scale.y);
	_size = Vector2(_size.x * scale.x, _size.y * scale.y);
}
void Entity::Scale(const float& scale) {
	Scale(Vector2(scale, scale));
}
void Entity::SetScale(const Vector2& scale) {
	image.setScale(scale.x, scale.y);
	_size = Vector2(_size.x / _scale.x * scale.x, _size.y / _scale.y * scale.y);
	_scale = scale;
}
void Entity::SetScale(const float& scale) {
	SetScale(Vector2(scale, scale));
}
void Entity::SetColor(const sf::Color& color) {
	image.setColor(color);
}
void Entity::ApplyForce(const Vector2& force, const float& lockTime) {
	velocity += force;
	_movementLock = clock() + lockTime * CLOCKS_PER_SEC;
}
bool Entity::GetMovementLocked() {
	return clock() < _movementLock;
}

Vector2 Entity::GravitationVector() {
	return Vector2(0, 1) * (mass * G * G_SCALE);
}
void Entity::Gravitate() {
	if (kinematic) {
		Move(Vector2(0, velocity.y * deltaTime));
		return;
	}
	auto ex = velocity;
	velocity += GravitationVector() * deltaTime;
#ifdef DEBUG
	if (ex.y * velocity.y < 0)
		printf("%s\n", _pos.ToString().c_str());
#endif
	Move(Vector2(0, velocity.y * deltaTime));
}
void Entity::Collide(Entity& other) {
	Entity* pair[] = { this, &other };

	if ((int)pair[0]->background + (int)pair[1]->background == 1 || pair[1]->kinematic && pair[0]->kinematic || pair[0]->transparent || pair[1]->transparent || !pair[0]->enabled || !pair[1]->enabled)
		return;
	Vector2 pushVec = pair[0]->hitbox.GetPushOutVector(pair[1]->hitbox);
	if (pushVec.Length() == 0 || !CanCollide(&other, pushVec.Normalized()))
		return;

	Vector2 push[2] = { pushVec / 2, pushVec / -2 };
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
bool Entity::CanCollide(Entity* other, Vector2 direction) {
	return collideWorld;
}

float Entity::GetW() {
	return _size.x;
}
float Entity::GetH() {
	return _size.y;
}
Vector2 Entity::GetPos() {
	return _pos;
}
Vector2 Entity::GetScale() {
	return _scale;
}
Vector2 Entity::GetSize() {
	return _size;
}
sf::Color Entity::GetColor() {
	return image.getColor();
}

bool Entity::Update(list<Entity*>& objects) {
	Move(Vector2(velocity.x * deltaTime, 0));
	if (onGround)
		velocity.x *= max(0., 1 - 3.5 * deltaTime);
	if (abs(velocity.x) < 50)
		velocity.x = 0;
	return false;
}
void Entity::Draw(sf::RenderWindow& window) {
	if (!enabled)
		return;
	window.draw(image);
}

void Entity::Rotate(int direction, bool reversed) {
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