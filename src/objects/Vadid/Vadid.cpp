#include "Vadid.h"
#include "Afterimage.h"
#include "../Player.h"
#include "../Overlay.h"
#include <foresteamnd/Utils.h>

Vadid::Vadid(float kDamage) : Healthy(150, ASSETS + "textures/boss.png", RECT_SIZE) {
	this->_kDamage = kDamage;
	this->mass = 1;
	_direction = 1;
	Scale(SCALE);
	_touchAttack = new MeleeAttack(GetW() - 10, 0, 50, 0, 0.5f, 0);
	_spikeAttack = new SpikeAttack(100, 100, .4f, 0, .5f);
	_jumpAttack = new Attack(0, 0, 0, .5);
	_lastChoice = Choise();
	_choiseTimer = clock();
	_attacked = false;
	_state = STATE::IDLE;

	_wave = nullptr;
	_title = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ASSETS + "textures/boss_title.png");
	_afterimages = list<Object*>();

	_rasenganBuffer.loadFromFile(ASSETS + "sounds/rassengan.ogg");
	_rasenganSound.setBuffer(_rasenganBuffer);

	InitHealthBar();
	SetState(IDLE);
}
Vadid::~Vadid() {
	delete _touchAttack;
	delete _spikeAttack;
}

void Vadid::SetState(STATE state) {
	if (state == STATE::IDLE && GetPhase() == 1)
		state = STATE::AWAKEN;
	_state = state;
	image.setTextureRect(sf::IntRect(sf::Vector2i(RECT_SIZE.x * state, 0), v2i(RECT_SIZE)));
}
void Vadid::TakeDamage(float amount, Object* source) {
	Healthy::TakeDamage(amount, source);
	if (instanceof<Player>(source))
		if (!Alive())
			aSwordExecuteSound.Play();
		else
			aSwordSliceSound.Play();
}

bool Vadid::Update(list<Object*>& objects) {
	Player* ply = nullptr;
	for (Object* o : objects)
		if (instanceof<Player>(o)) {
			ply = (Player*)o;
			break;
		}

	if (!_lastChoice.attack)
		if (!ply || onGround) // wtf?
			SetState(IDLE);
		else
			SetState(JUMP_ATTACK);

	Rotate(_direction, false);
	if (ply) {
		_direction = (ply->GetPos().x > GetPos().x) * 2 - 1;
		if (_touchAttack->Ready() && _touchAttack->GetZone(this, 0).intersects(ply->image.getGlobalBounds())) {
				_touchAttack->DoAttack(this, 0, objects);
		}
		if (float(clock() - _choiseTimer) / CLOCKS_PER_SEC > choiseInterval) {
			if (_title) {
				delete _title;
				_title = nullptr;
			}
			if (!_lastChoice.attack) {
				Choise t[] = { Choise(_jumpAttack, JUMP_ATTACK, JUMP_PREPARE), Choise(_spikeAttack, ATTACK, ATTACK) };
				_lastChoice = t[(int)Utils::RandRange(0, GetPhase() + 1)];
				_lastChoice.attack->Prepare();
				SetState(_lastChoice.stateCharge);
				if (instanceof<SpikeAttack>(_lastChoice.attack)) {
					velocity.y -= CalcJumpPower(GetScale(), mass, 4);
					_wave = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100 / 2) , ASSETS + "textures/flame.png");
					_wave->enabled = false;
				}
			}
			if (_attacked) {
				if (_lastChoice.attack->Ready()) {
					_lastChoice = Choise();
					_choiseTimer = clock();
					_attacked = false;
					if (_wave) {
						delete _wave;
						_wave = nullptr;
					}
				}
			}
			else
				if (_lastChoice.attack->Prepared()) {
					_lastChoice.attack->DoAttack(this, 0, objects);
					SetState(_lastChoice.stateAttack);
					_attacked = true;
					if (_wave)
						_wave->enabled = true;
					if (instanceof<SpikeAttack>(_lastChoice.attack))
						_rasenganSound.play();
					else {
						velocity += Vector2(
							((ply->GetPos().x < GetPos().x) * 2 - 1) * -0.5 * abs(GetPos().x - ply->GetPos().x) * 8,
							-CalcJumpPower(GetScale(), mass, 1 + (GetPos().y / ply->GetPos().y) / Utils::RandRange(1.1f, 1.2f))
						);
					}
				}
		}
	}

	bool dead = Healthy::Update(objects);
	if (dead) {
		Overlay* victory = new Overlay(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ASSETS + "textures/victory.png");
		objects.push_back(victory);
	}

	return dead;
}
void Vadid::Draw(sf::RenderWindow& window) {
	_afterimageSkippedFrames++;
	if (_afterimageSkippedFrames > afterimagesMaxSkipFrames) {
		_afterimageSkippedFrames = 0;
		if (_state == JUMP_ATTACK)
			_afterimages.push_back(new Afterimage(GetPos()));
		if (_afterimages.size() > afterimagesMax || _state != JUMP_ATTACK && _afterimages.size() > 0) {
			_afterimages.pop_front();
		}
		auto i = 0;
		for (auto it = _afterimages.rbegin(); it != _afterimages.rend(); it++, i++) {
			printf("%i\n", (int)(255 / _afterimages.size() * i));
			(*it)->SetColor(sf::Color(255, 255, 255, 255 - 255 / _afterimages.size() * i));
		}
	}
	for (auto afterimage : _afterimages)
		afterimage->Draw(window);
	Healthy::Draw(window);
	if (_wave)
		_wave->Draw(window);
	if (_title)
		_title->Draw(window);
}
int Vadid::GetPhase() {
	if (HP() <= MaxHP() * .5)
		return 1;
	return 0;
}

Vector2 Vadid::RECT_SIZE = Vector2(253, 262);
Vector2 Vadid::SCALE = Vector2(.3f);