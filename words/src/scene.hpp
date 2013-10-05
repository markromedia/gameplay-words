#ifndef __SCENE__hpp
#define __SCENE__hpp

#include "words.h"
#include "gameplay.h"

namespace Words {
	class Scene {
	private:
	public:
		/// Handles the touch event.
		///
		/// @param [in,out]	ray	The ray.
		/// @param	x		   	The x coordinate.
		/// @param	y		   	The y coordinate.
		///
		/// @return	true if it succeeds, false if it fails.
		virtual bool HandleTouchDownEvent(gameplay::Ray& ray, int x, int y) = 0;

		/// Handles the touch event.
		///
		/// @param [in,out]	ray	The ray.
		/// @param	x		   	The x coordinate.
		/// @param	y		   	The y coordinate.
		///
		/// @return	true if it succeeds, false if it fails.
		virtual bool HandleTouchUpEvent(gameplay::Ray& ray, int x, int y) = 0;

		/// Basic update function
		///
		/// @param	elapsedTime	Time of the elapsed.
		virtual void Update(float elapsedTime) = 0;

		/// Render this scene
		virtual void Render() = 0;
	};
}
#endif  // __SCENE__hpp