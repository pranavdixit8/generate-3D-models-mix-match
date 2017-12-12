/**
	@file 		group.h
	@author 	Ravi Agrawal (ravia@sfu.ca)
	@date		December 1, 2017
	@version 	1.0

	@brief		CMPT-764: Project, Header file for Group class.
*/

#ifndef GROUP_H
#define GROUP_H

#include <part_base.h>

#include <vector>
#include <map>

#include <boost/algorithm/string/predicate.hpp>

using std::vector;
using std::map;
using std::make_pair;

class Group : public PartBase {
public:
	vector<PartBase*> members;
	map<string, int> labelIndexMap;

	Group (string label);
	~Group () {};

	void addMember (PartBase *member);
	void render (DisplayType displayType) override;

	PartBase *getMember (string label);
	PartBase *getMemberGlobally (string label);	
	void setMember (string label, PartBase *member);
};

Group::Group (string label) {
	this->setLabel(label + "_Group");
}

void Group::addMember (PartBase *member) {
	if (members.size() == 0)
		boundingBox = member->boundingBox;

	boundingBox += member->boundingBox;

	// Insert label in labelIndexMap
    //std::cout << "a part with label '" << member->label << "' has been added" << std::endl;
	//labelIndexMap.insert(make_pair(member->label, members.size()));
	labelIndexMap[member->label] = members.size();

	members.push_back(member);
}

void Group::render (DisplayType displayType) {
	renderBoundingBox();
	for (vector<PartBase*>::iterator it = members.begin() ; it != members.end(); ++it) {
		PartBase* member = *it;

		member->render(displayType);
	}
}

PartBase *Group::getMember (string label) {

    //std::cout << "getMember: " << label << ", index = " << labelIndexMap.size() << ", " << std::endl;


	// std::cout << "\t" << this->label << endl;
	// for (std::map<string,int>::iterator it=labelIndexMap.begin(); it!=labelIndexMap.end(); ++it)
 //    	std::cout << "\t\t" << it->first << " - " << it->second << endl;
   

	if (labelIndexMap.count(label) > 0) {		
		return members[labelIndexMap[label]];
	}
	else {		
		return NULL;
	}
}

PartBase *Group::getMemberGlobally (string label) {

	// std::cout << "\t" << this->label << endl;
	// for (std::map<string,int>::iterator it=labelIndexMap.begin(); it!=labelIndexMap.end(); ++it)
 //    	std::cout << "\t\t" << it->first << " - " << it->second << endl;


    // if(this->label == label)
    // 	return this;

	if (labelIndexMap.count(label) > 0) {		
		return members[labelIndexMap[label]];
	}
	else {	
		for (std::map<string,int>::iterator it=labelIndexMap.begin(); it!=labelIndexMap.end(); ++it)
			if(boost::algorithm::ends_with(it->first, "_Group")) {
				PartBase *theGroup = this->members[it->second];
				PartBase *thePart = theGroup->getMember(label);
				if(NULL != thePart) 
					return thePart;
			}

		return NULL;
	}
}



void Group::setMember (string label, PartBase *member) {
	if (labelIndexMap.count(label) > 0)
		members[labelIndexMap[label]] = member;
}

#endif