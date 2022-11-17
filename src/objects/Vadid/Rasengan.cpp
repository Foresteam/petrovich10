#include "Rasengan.h"
#include "../Player.h"
#include "../Wall.h"
bool pizda = false;
Rasengan::Rasengan(Vector2 pos, Vector2 velocity, float damage) : Object(ASSETS + "textures/rasengan.png", Vector2(384)) {
	kinematic = true;
	transparent = false;
	this->velocity = velocity;
	_destroy = false;
	_grewMax = false;
	_startPos = pos;
	Scale(INITIAL_SCALE);
	MoveTo(pos);
	_attack = new MeleeAttack(GetW(), 0, damage, 0, .3f);
	_attack->SetKnockback(2000 * damage / 30);
	_lifeSound = new Sound(true, ASSETS + "sounds/air_wave_begin.ogg", ASSETS + "sounds/air_wave_loop.ogg", ASSETS + "sounds/air_wave_end.ogg");
	globalSounds.push_back(&_lifeSound);
}
Rasengan::~Rasengan() {
	if (_lifeSound)
		_lifeSound->EndLoop();
	delete _attack;
	Object::~Object();
}

bool Rasengan::CanCollide(Object* other, Vector2 direction) {
	if (!other) {
		_destroy = true;
		return false;
	}
	if (instanceof<Player>(other) || instanceof<Wall>(other))
		return false;
	return true;
}
bool Rasengan::Update(list<Object*>& objects) {
	for (auto obj : objects) {
		if (!instanceof<Player>(obj))
			continue;
		Player* ply = (Player*)obj;
		if (_attack->Ready() && _attack->GetZone(this, 0).intersects(ply->image.getGlobalBounds())) {
			_attack->DoAttack(this, 0, objects);
			anAirWaveSound.Play();
		}
		// else
		// 	printf("%f %f %f %f\n", _attack->GetZone(this).left, _attack->GetZone(this).top, _attack->GetZone(this).width, _attack->GetZone(this).height);
			// ah crap...
			// else
			// 	_attack->Prepare();
	}
	if (!pizda) {
		_lifeSound->Play();
		pizda = true;
	}
	return Object::Update(objects) || _destroy;
}

void Rasengan::Draw(sf::RenderWindow& window) {
	if (!_grewMax) {
		auto progress = min(1.f, GetPos().Distance(_startPos) / GROW_DISTANCE);
		if (progress == 1.f)
			_grewMax = true;
		SetScale(INITIAL_SCALE + (MAX_SCALE - INITIAL_SCALE) * progress);
	}
	image.rotate(RPS * 360 / 180 * M_PI);
	Object::Draw(window);
}