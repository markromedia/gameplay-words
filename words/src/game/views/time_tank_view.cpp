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
    instance->active_time_tanks.clear();
	for (unsigned int i = 0; i < GameStateModel::TimeTanks().size(); i++) {
		TimeTank* time_tank = instance->time_tank_repository[i];
        time_tank->Reset();
		instance->active_time_tanks.push_back(time_tank);
	}
}

///-----------------------------------------------------------------------------------------------

TimeTank::TimeTank()
{	this->active_renderable_node = RENDERABLE("time_tank_active");
	this->inactive_renderable_node = RENDERABLE("time_tank_inactive");
	this->progress_ring_renderable_node = RENDERABLE("time_tank_progress_ring");
	this->progress_ring_renderable_node_glow = RENDERABLE("time_tank_progress_ring_glow");
    
    this->Reset();
}

void TimeTank::Reset()
{
	this->mode = INACTIVE;
	this->current_charge = 0;
    this->target_charge = 0;
	this->max_charge = GameStateModel::MaxTimeTankCharge();
}

void TimeTank::Update( float delay )
{
	TimeTankModel* model = GameStateModel::TimeTanks()[index];
	this->target_charge = model->CurrentCharge();

	if (model->IsCharged() && current_charge + 0.1 > max_charge) {
		this->mode = ACTIVE;
	} else {
		this->mode = INACTIVE;
	}

	if (current_charge + 0.1 >= target_charge) {
		current_charge = target_charge;
		is_progressing = false;
	} else {
		is_progressing = true;
		current_charge += (target_charge - current_charge) * (delay / (delay + 250));
		alpha_threshold = this->current_charge / this->max_charge;
	}
}

void TimeTank::Render()
{
	Node* node_to_draw = NULL;
	switch (mode) 
	{
	case INACTIVE :
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

	//update scale
	this->inactive_renderable_node->setScale(0.5f);
	this->active_renderable_node->setScale(0.5f);
	this->progress_ring_renderable_node ->setScale(0.5f);
	this->progress_ring_renderable_node_glow->setScale(0.5f);

	//update position
	gameplay::Quaternion q;
	q = getBillboardTransformation();
	
	node_to_draw->setRotation(q);
	progress_ring_renderable_node->setRotation(q);
	progress_ring_renderable_node_glow->setRotation(q);
	
	progress_ring_renderable_node->setTranslation(position.x, position.y, position.z);
	progress_ring_renderable_node_glow->setTranslation(position.x, position.y, position.z);
	node_to_draw->setTranslation(position.x, position.y, position.z);

	//draw the main image
	node_to_draw->getModel()->draw();

	//if progressing, figure out alpha threshold and draw
	if (mode == INACTIVE) {

		//if (index == 0 && alpha_threshold > 0)
		//{
		//	std::stringstream ss;
		//	ss << alpha_threshold << "\n";
		//	gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, ss.str().c_str());
		//}

		progress_ring_renderable_node->getModel()->getMaterial()->getParameter("u_alphaThreshold")->setValue(alpha_threshold);
		progress_ring_renderable_node->getModel()->draw();

		if (is_progressing) {
			progress_ring_renderable_node_glow->getModel()->getMaterial()->getParameter("u_alphaThreshold")->setValue(alpha_threshold);
			progress_ring_renderable_node_glow->getModel()->draw();
		}
	}
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