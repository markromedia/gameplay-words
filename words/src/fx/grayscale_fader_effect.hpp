#ifndef __GRAYSCALE_FADER_EFFECT
#define __GRAYSCALE_FADER_EFFECT

#include "gameplay.h"


class GrayScaleFaderEffect { 
public:

	/// Values that represent EffectState.
	enum EffectState { IDLE, RUNNING, FINISHED };

	/// Constructor.
	/// @param [in,out]	callback	If non-null, the callback.
	GrayScaleFaderEffect(void (*callback) (EffectState), gameplay::Node* target);

	/// Updates the given delay.
	/// @param	delay	The delay.
	void Update(float delay);

	/// Renders this object.
	void Render();
private:
	/// call back for this
	///
	/// @param	parameter1	The first parameter.
	void (*callback) (EffectState);

	/// @summary	Target for this effect
	gameplay::Node* target;

	/// @summary	The current state.
	EffectState current_state;
};

#endif  // __GRAYSCALE_FADER_EFFECT