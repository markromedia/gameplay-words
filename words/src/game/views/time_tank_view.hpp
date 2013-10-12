#ifndef __TIME_TANK_VIEW__hpp
#define __TIME_TANK_VIEW__hpp

#include <vector>
#include <math.h>
#include <sstream>

#include "gameplay.h"

class TimeTank;

class TimeTankView {
private:

	/// @summary	The instance.
	static TimeTankView* instance;

	/// Default constructor.
	TimeTankView();

	/// @summary	The time tank repository.
	std::vector<TimeTank*> time_tank_repository;

	/// @summary	The active time tanks.
	std::vector<TimeTank*> active_time_tanks;

	int active_tank_index;
public:

	/// Initialises this object.
	static void Init();

	/// Updates the given delay.
	/// @param	delay	The delay.
	static void Update(float delay);

	/// Renders this object.
	static void Render();

	/// Resets this object.
	static void Reset();
};


class TimeTank {
	friend class TimeTankView;
private:
	/// Values that represent Mode.
	enum Mode { ACTIVE, INACTIVE, SHRINKING};

	/// @summary	the position
	gameplay::Vector3 position;

	/// @summary	The active renderable node.
	gameplay::Node* active_renderable_node;

	/// @summary	The inactive renderable node.
	gameplay::Node* inactive_renderable_node;

	/// @summary	The progress ring renderable node.
	gameplay::Node* progress_ring_renderable_node;

	/// @summary	The progress ring renderable node glow
	gameplay::Node* progress_ring_renderable_node_glow;

	/// Gets the billboard transformation.
	/// @return	The billboard transformation.
	gameplay::Quaternion getBillboardTransformation();

	/// @summary	The mode.
	Mode mode;

	/// @summary	current charge
	float current_charge;

	/// @summary	Target charge.
	float target_charge;

	/// @summary	The maximum charge.
	float max_charge;

	/// @summary	The alpha threshold.
	float alpha_threshold;

	/// @summary	Zero-based index of the.
	int index;

	/// @summary	true if this object is progressing.
	bool is_progressing;
public:

	/// Default constructor.
	TimeTank();

	/// Updates the given delay.
	/// @param	delay	The delay.
	void Update(float delay);

	/// Renders this object.
	void Render();
};

#endif  // __TIME_TANK_VIEW__hpp