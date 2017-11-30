/**
	@file 		part.h
	@author 	Ravi Agrawal (ravia@sfu.ca)
	@date		November 29, 2017
	@version 	1.0

	@brief		CMPT-764: Project, Header file for Part class.
*/

#ifndef PART_H
#define PART_H

#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;

class Part {
public:
	vec3 min, max;
	vec3 color;
	mat4 transformationMatrix;

	Part () {};
	~Part () {};
};

#endif