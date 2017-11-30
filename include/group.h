/**
	@file 		group.h
	@author 	Ravi Agrawal (ravia@sfu.ca)
	@date		November 29, 2017
	@version 	1.0

	@brief		CMPT-764: Project, Header file for Group class.
*/

#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <part.h>

using std::vector;

class Group : public Part {
public:
	vector<Part> members;

	Group () {};
	~Group () {};

	void addMember (Part member);
};

void Group::addMember (Part member) {
	members.push_back(member);
};

#endif