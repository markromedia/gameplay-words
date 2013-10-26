#include "grayscale_fader_effect.hpp"


GrayScaleFaderEffect::GrayScaleFaderEffect( void (*callback) (EffectState), gameplay::Node* target )
{
	this->callback = callback;
	this->target = target;
	this->current_state = IDLE;
}

void GrayScaleFaderEffect::Update( float delay )
{

}

void GrayScaleFaderEffect::Render()
{

}
