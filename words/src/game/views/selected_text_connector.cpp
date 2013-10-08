#include "selected_text_connector.hpp"

#include "../../renderable_node_repository.hpp"
#include "../../camera_control.hpp"

using namespace gameplay;

SelectedTextConnector* SelectedTextConnector::instance = NULL;

void SelectedTextConnector::Init()
{
	instance = new SelectedTextConnector();
	instance->connector_node = RENDERABLE("connector");
	instance->connector_batch = gameplay::SpriteBatch::create("res/png/selected_connector.png");

	instance->model_width = instance->connector_node->getModel()->getMesh()->getBoundingBox().max.x 
		- instance->connector_node->getModel()->getMesh()->getBoundingBox().min.x;
	instance->model_height = instance->connector_node->getModel()->getMesh()->getBoundingBox().max.z 
		- instance->connector_node->getModel()->getMesh()->getBoundingBox().min.z;
}


void SelectedTextConnector::Draw(std::vector<Tile*> tiles_to_draw)
{
	if (tiles_to_draw.size() < 2) {
		return;
	}

	int x_off = gameplay::Game::getInstance()->getWidth() / 2 - 32;
	int y_off = 200;

	instance->connector_batch->start();
	for (unsigned int i = 0; i < tiles_to_draw.size() - 1; i++) {
		Tile* first_tile = tiles_to_draw[i];
		Tile* second_tile = tiles_to_draw[i + 1];

		int dx = -1 * (first_tile->col_index - second_tile->col_index);
		int dy = -1 * (first_tile->row_index - second_tile->row_index);

		int rot = 0, x_pos = 0, y_pos = 0;
		//handle all the cases
		if (dx == 0 && dy == 1) { //straight up
			rot = 90;
			x_pos = first_tile->cell->x;
			y_pos = (first_tile->cell->y + second_tile->cell->y) / 2;
		} else if (dx == 0 && dy == -1) { //straight down
			rot = 90;
			x_pos = first_tile->cell->x;
			y_pos = (first_tile->cell->y + second_tile->cell->y) / 2;
		} else if (dx == 1 && dy == 0) { //right
			rot = 0;
			x_pos = (first_tile->cell->x + second_tile->cell->x) / 2;
			y_pos = first_tile->cell->y;
		} else if (dx == -1 && dy == 0) { //left
			rot = 0;
			x_pos = (first_tile->cell->x + second_tile->cell->x) / 2;
			y_pos = first_tile->cell->y;
		} else if (dx == 1 && dy == 1) { //up right
			rot = -45;
			x_pos = (first_tile->cell->x + second_tile->cell->x) / 2;
			y_pos = (first_tile->cell->y + second_tile->cell->y) / 2;
		} else if (dx == -1 && dy == 1) { //up left
			rot = 45;
			x_pos = (first_tile->cell->x + second_tile->cell->x) / 2;
			y_pos = (first_tile->cell->y + second_tile->cell->y) / 2;
		} else if (dx == -1 && dy == -1) { //down left
			rot = -45;
			x_pos = (first_tile->cell->x + second_tile->cell->x) / 2;
			y_pos = (first_tile->cell->y + second_tile->cell->y) / 2;

		} else if (dx == 1 && dy == -1) { //down right
			rot = 45;
			x_pos = (first_tile->cell->x + second_tile->cell->x) / 2;
			y_pos = (first_tile->cell->y + second_tile->cell->y) / 2;
		}

		//move over x-pos by half-width
		y_pos -= 25; //TODO hardcoded

		//adjust position based on angle
		if (rot == 0) {
			y_pos += 4;
		} else if (rot == 90) {
			x_pos += 4;
		} else if (rot == 45) {
			y_pos += 4;
			x_pos += 2;
		}  else if (rot == -45) {
			y_pos += 4;
			x_pos -= 2;
		}


		/**
		instance->connector_batch->draw(x_pos + x_off, gameplay::Game::getInstance()->getWidth() - (y_pos + y_off), 0.0f, 
										64, 16, 
										0.0f, 1.0f, 1.0f, 0.0f, 
										gameplay::Vector4::one(), 
										gameplay::Vector2(0.5f,0.5f), MATH_DEG_TO_RAD(rot), 
										true);
		*/
		//update the first nodes position so we can use it to figure out the billboard transformation
		instance->connector_node->setTranslation(x_pos, y_pos, 0);
		
		gameplay::Quaternion p, q;
		gameplay::Matrix m;

		m.rotateY(MATH_DEG_TO_RAD(rot));
		m.getRotation(&p);

		q = getBillboardTransformation();

		//premultiply our z axis rotation
		gameplay::Quaternion::multiply(q, p, &q);

		instance->connector_node->setRotation(q);

		instance->connector_node->getModel()->draw();
	}
	instance->connector_batch->finish();
}

gameplay::Quaternion SelectedTextConnector::getBillboardTransformation() {

	gameplay::Quaternion q, p;
	gameplay::Matrix m, m2;

	CameraControl::CreateBillboardHelper(instance->connector_node->getTranslationWorld(), &m);

	//the models are facing the other way, rotate them
	m2.rotateX(90 * (MATH_PI / 180));
	m2.getRotation(&p);

	//get the billboard quaternion
	m.getRotation(&q);

	//premultiply our 90 degree x-axis rotation
	gameplay::Quaternion::multiply(q, p, &q);

	return q;
}

