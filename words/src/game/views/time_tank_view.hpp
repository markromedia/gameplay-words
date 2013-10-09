#ifndef __TIME_TANK_VIEW__hpp
#define __TIME_TANK_VIEW__hpp

#include <vector>

#include "gameplay.h"

/**
class TimeTankView;

class TimeTank {
	friend class TimeTankView;
private:
	/// Values that represent Mode.
	enum Mode { ACTIVE, INACTIVE, PROGESSING};

	/// @summary	the position
	gameplay::Vector3 position;

	/// @summary	The active renderable node.
	gameplay::Node* active_renderable_node;

	/// @summary	The inactive renderable node.
	gameplay::Node* inactive_renderable_node;

	/// Gets the billboard transformation.
	/// @return	The billboard transformation.
	gameplay::Quaternion getBillboardTransformation();

	/// @summary	The mode.
	Mode mode;

	/// @summary	Target alpha.
	float target_alpha;
public:

	/// Default constructor.
	TimeTank();

	/// Updates the given delay.
	/// @param	delay	The delay.
	void Update(float delay);

	/// Renders this object.
	void Render();
};
**/


class TimeTankView {
private:

	/// @summary	The instance.
	static TimeTankView* instance;

	/// Default constructor.
	TimeTankView();

	/// @summary	The time tank repository.
	//std::vector<TimeTank*> time_tank_repository;

	/// @summary	The active time tanks.
	//std::vector<TimeTank*> active_time_tanks;

	int active_tank_index;
public:

	/// Initialises this object.
	static void Init();

	/// Updates the given delay.
	/// @param	delay	The delay.
	static void Update(float delay);

	/// Renders this object.
	static void Render();
};


#endif  // __TIME_TANK_VIEW__hpp