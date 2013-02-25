#ifndef __ANIMATION__hpp
#define __ANIMATION__hpp

#include <vector>

namespace words {
	class Animation;

	struct Step {
		void (*func)(Animation*, float);
		float duration;
		float running_time;
	};

	class Animation {
	private:
		/// @summary	Zero-based index of the step.
		unsigned int step_index;

		/// the list of functions to call with their steps
		std::vector<Step> steps;

		/// @summary	Time of the total running.
		float total_running_time;

		/// @summary	whether or not this animation is running.
		bool running;

		/// Resets this object.
		void reset();
	public:
		/// Adds a step to this animation
		/// @param	duration			The duration.
		/// @param [in,out]	StepFunc	If non-null, the step function.
		void Add(float duration, void (*StepFunc)(Animation*, float));

		/// Advances animation to next step
		///` @return	true if animation has next step, false otherwise
		bool Next();

		/// Starts animation
		void Start();

		/// Stops the animation
		void Stop();

		/// Updates this object
		/// @param	dt	The dt.
		void Update(float dt);
	};
};

#endif  // __ANIMATION__hpp