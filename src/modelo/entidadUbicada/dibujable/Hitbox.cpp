/*
 * Hitbox.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: franco
 */

#include "Hitbox.h"

#include "../../../defs.h"

Hitbox::Hitbox() {
	// tamanios defecto para cody quieto
	this->deltax = 65;
	this->deltay = 48;
	this->width = 106;
	this->height = 219;
	this->depth = HBX_DEPTH_DEFECTO;

}

Hitbox::Hitbox (const Hitbox &obj) {
	this->deltax = obj.deltax;
	this->deltay = obj.deltay;		//a veces rompe aca
	this->width = obj.width;
	this->height = obj.height;
	this->depth = obj.depth;
}

Hitbox::Hitbox(float deltax, float deltay, float width, float height, float depth) {

	this->deltax = deltax;
	this->deltay = deltay;
	this->width = width;
	this->height = height;
	this->depth = depth;

}

void Hitbox::set(float deltax, float deltay, float width, float height, float depth) {
	this->deltax = deltax;
	this->deltay = deltay;
	this->width = width;
	this->height = height;
	this->depth = depth;

}

Hitbox::~Hitbox() {
	// TODO Auto-generated destructor stub
}

