#include "time_tank_view.hpp"

#include "../../renderable_node_repository.hpp"
#include "../../camera_control.hpp"
#include "../board/board.hpp"
#include "../game_state_model.hpp"

///-----------------------------------------------------------------------------------------------

TimeTankView* TimeTankView::instance;

TimeTankView::TimeTankView()
{
	int x_pos = Board::get()->bottom_left_x - 8;
	int y_pos = Board::get()->bottom_left_y - 4;
	
	for (int i = 0; i < GameStateModel::MaxNumberOfTimeTanks(); i++) {
		TimeTank* time_tank = new TimeTank();
		time_tank->position.x = x_pos;
		time_tank->position.y = y_pos;
		time_tank->position.z = 0;
		time_tank->index = i;

		x_pos += 30;

		this->time_tank_repository.push_back(time_tank);
	}
}

void TimeTankView::Init()
{
	instance = new TimeTankView();
}

void TimeTankView::Update( float delay )
{
	for (unsigned int i = 0; i < instance->active_time_tanks.size(); i++) {
		TimeTank* time_tank = instance->active_time_tanks[i];
		time_tank->Update(delay);
	}
}

void TimeTankView::Render()
{
	for (unsigned int i = 0; i < instance->active_time_tanks.size(); i++) {
		TimeTank* time_tank = instance->active_time_tanks[i];
		time_tank->Render();
	}
}

void TimeTankView::Reset()
{
	for (unsigned int i = 0; i < GameStateModel::TimeTanks().size(); i++) {
		TimeTank* time_tank = instance->time_tank_repository[i];
		instance->active_time_tanks.push_back(time_tank);
	}
}

///-----------------------------------------------------------------------------------------------

TimeTank::TimeTank()
{	this->active_renderable_node = RENDERABLE("time_tank_active");
	this->inactive_renderable_node = RENDERABLE("time_tank_inactive");

	this->inactive_renderable_node->setScale(0.5f);
	this->active_renderable_node->setScale(0.5f);

	this->mode = INACTIVE;
}

void TimeTank::Update( float delay )
{

}

void TimeTank::Render()
{
	Node* node_to_draw = NULL;
	switch (mode) 
	{
	case INACTIVE :
	case PROGESSING : 
		{
			node_to_draw = inactive_renderable_node;
			break;
		}
	case ACTIVE : 
		{
			node_to_draw = active_renderable_node;
			break;
		}

	}

	gameplay::Quaternion q;
	q = getBillboardTransformation();
	node_to_draw->setRotation(q);
	node_to_draw->setTranslation(position.x, position.y, position.z);
	node_to_draw->getModel()->draw();
}

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

///-----------------------------------------------------------------------------------------------