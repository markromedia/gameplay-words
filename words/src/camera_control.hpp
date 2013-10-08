#ifndef __CAMERA_CONTROL__hpp
#define __CAMERA_CONTROL__hpp

#include "gameplay.h"

using namespace gameplay;

class CameraControl

{
private:
	/// Values that represent CAMERA_DIRECTION.
	enum CAMERA_DIRECTION { LEFT = 1, RIGHT = 2, FORWARD = 4, BACKWARDS = 8, NONE = 0 };

	/// @summary	The camera target.
	Vector3 camera_target;

	/// @summary	The camera move direction.
	int camera_move_direction;

	/// @summary	The camera.
	Camera* camera;
	
	/// @summary	The camera node.
	Node* camera_node;

	/// @summary	true if this object is looking at origin.
	bool is_looking_at_origin;

	/// @summary	The instance.
	static CameraControl* instance;
public:
	/// Constructor.
	/// @param [in,out]	camera	   	If non-null, the camera.
	/// @param [in,out]	camera_node	If non-null, the camera node.
	CameraControl(Camera* camera, Node* camera_node);

	/// Initialises this object.
	/// @param [in,out]	camera	   	If non-null, the camera.
	/// @param [in,out]	camera_node	If non-null, the camera node.
	static void Init(gameplay::Camera* camera, Node* camera_node);

	/// Gets the static instance
	/// @return	null if it fails, else.
	static CameraControl* Get();

	/// Updates the given delta.
	/// @param	delta	The delta.
	void Update(float delta);

	/// The keyboard input event handler
	/// @param	evt	The event.
	/// @param	key	The key.
	void KeyEventHandler(Keyboard::KeyEvent evt, int key);

	/// Handler, called when the Mouse event.
	/// @param	evt		  	The event.
	/// @param	x		  	The x coordinate.
	/// @param	y		  	The y coordinate.
	/// @param	wheelDelta	The wheel delta.
	void HandleMouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta);

	/// Helper method that create billboard.
	/// @param	objectPosition	   	The object position.
	/// @param	cameraPosition	   	The camera position.
	/// @param	cameraUpVector	   	The camera up vector.
	/// @param	cameraForwardVector	The camera forward vector.
	/// @param [in,out]	dst		   	If non-null, destination for the.
	static void CreateBillboardHelper(const gameplay::Vector3& objectPosition, const gameplay::Vector3& cameraPosition,
		const gameplay::Vector3& cameraUpVector, const gameplay::Vector3& cameraForwardVector,
		gameplay::Matrix* dst);

	//CameraControl::CreateBillboardHelper(physics_node->getTranslationWorld(), camera->getNode()->getTranslationWorld(), camera->getNode()->getUpVectorWorld(), camera->getNode()->getForwardVector(), &m);

	/// Helper method that create billboard. Uses in
	/// @param	objectPosition	The object position.
	/// @param [in,out]	dst   	If non-null, destination for the.
	static void CreateBillboardHelper(const gameplay::Vector3& objectPosition, gameplay::Matrix* dst);
};

#endif  // __CAMERA_CONTROL__hpp