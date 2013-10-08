#include "time_tank_view.hpp"

#include "../../renderable_node_repository.hpp"
#include "../../camera_control.hpp"
#include "../board/board.hpp"

TimeTankView* TimeTankView::instance;

TimeTankView::TimeTankView()
{
	int x_pos = Board::get()->bottom_left_x;
	int y_pos = Board::get()->bottom_left_y;
	
}

void TimeTankView::Init()
{
	instance = new TimeTankView();
}

void TimeTankView::Update( float delay )
{

}

void TimeTankView::Render()
{

}

/**
gameplay::Quaternion TimeTank::getBillboardTransformation() {

	gameplay::Quaternion q, p;
	gameplay::Matrix m, m2;

	CameraControl::CreateBillboardHelper(active_renderable_node->getTranslationWorld(), &m);

	//the models are facing the other way, rotate them
	m2.rotateX(90 * (MATH_PI / 180));
	m2.getRotation(&p);

	//get the billboard quaternion
	m.getRotation(&q);

	//premultiply our 90 degree x-axis rotation
	gameplay::Quaternion::multiply(q, p, &q);

	return q;
}

TimeTank::TimeTank()
{	this->active_renderable_node = RENDERABLE("time_tank_active");
	this->inactive_renderable_node = RENDERABLE("time_tank_inactive");

	this->inactive_renderable_node->setScale(0.5f);
	this->active_renderable_node->setScale(0.5f);
}

void TimeTank::Update( float delay )
{

}

void TimeTank::Render()
{
	gameplay::Quaternion q;
	q = getBillboardTransformation();
	active_renderable_node->setRotation(q);

	active_renderable_node->getModel()->draw();
}
**/