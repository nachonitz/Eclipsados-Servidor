/*
 * Hitbox.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: franco
 */

#include "Hitbox.h"

Hitbox::Hitbox() {
	this->deltax = 0;//35;
	this->deltaz = 0;//21;
	this->width = 120;//54;
	this->height = 120;//93;
	this->depth = 50;

}

Hitbox::Hitbox (const Hitbox &obj) {
	this->deltax = obj.deltax;
	this->deltaz = obj.deltaz;
	this->width = obj.width;
	this->height = obj.height;
	this->depth = obj.depth;
}

Hitbox::Hitbox(float deltax, float deltaz, float width, float height, float depth) {

	this->deltax = deltax;
	this->deltaz = deltaz;
	this->width = width;
	this->height = height;
	this->depth = depth;

}

void Hitbox::set(float deltax, float deltaz, float width, float height, float depth) {
	this->deltax = deltax;
	this->deltaz = deltaz;
	this->width = width;
	this->height = height;
	this->depth = depth;

}

Hitbox::~Hitbox() {
	// TODO Auto-generated destructor stub
}

