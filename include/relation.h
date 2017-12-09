/**
	@file 		relation.h
	@author 	Hamid Homapour (ravia@sfu.ca)
	@date		December 3, 2017
	@version 	1.0

	@brief		CMPT-764: Project, Header file for Relation class.
*/

#ifndef RELATION_H
#define RELATION_H

#include <part_base.h>
#include <vector>
#include <math.h>
#include <gdiam.h>

using std::vector;


class MinimumBoundingBox : public gdiam_bbox {
public:

	MinimumBoundingBox () {};
	~MinimumBoundingBox () {};
	void  init( gdiam_bbox  bb ) {
		        dir_1[ 0 ] = bb.dir_1[0];
		        dir_1[ 1 ] = bb.dir_1[1];
		        dir_1[ 2 ] = bb.dir_1[2];

				dir_2[ 0 ] = bb.dir_2[0];
				dir_2[ 1 ] = bb.dir_2[1];
				dir_2[ 2 ] = bb.dir_2[2];

				dir_3[ 0 ] = bb.dir_3[0];
				dir_3[ 1 ] = bb.dir_3[1];
				dir_3[ 2 ] = bb.dir_3[2];

		        low_1 = bb.low_1;
		        high_1 = bb.high_1;

		        low_2 = bb.low_2;
		        high_2 = bb.high_2;

		        low_3 = bb.low_3;
		        high_3 = bb.high_3;
		        f_init = true;
		}

	//void render (DisplayType displayType);


	static const int DEFAULT_GRID_SIZE = 5;
	static const int DEFAULT_SAMPLE_SIZE = 400;


	MinimumBoundingBox (Mesh mesh, int  grid_size=DEFAULT_GRID_SIZE, int  sample_size=DEFAULT_SAMPLE_SIZE) {
		gdiam_real  * points;
		double  x, y, z;


		points = (gdiam_point)malloc( sizeof( gdiam_point_t ) * mesh.number_of_vertices() );

		int idx = 0;
		for (VertexIndex v: mesh.vertices()) {
			Point p = mesh.point(v);

			points[ idx * 3 + 0 ] = p.x();
			points[ idx * 3 + 1 ] = p.y();
			points[ idx * 3 + 2 ] = p.z();

			idx++;

		}

		gdiam_point  * pnt_arr;
		//gdiam_bbox   bb;

		pnt_arr = gdiam_convert( (gdiam_real *)points, mesh.number_of_vertices() );
		gdiam_approx_mvbb_grid_sample( pnt_arr, mesh.number_of_vertices(), grid_size, sample_size );

		init(gdiam_approx_mvbb_grid_sample( pnt_arr, mesh.number_of_vertices(), 5, 400 ));
	}



	double low__1()
	{
	    return low_1;
	}

	double high__1()
	{
	    return high_1;
	}

	double low__2()
	{
	    return low_2;
	}

	double high__2()
	{
	    return high_2;
	}

	double low__3()
	{
	    return low_3;
	}

	double high__3()
	{
	    return high_3;
	}

	Vector direction_1()
	{
	    return Vector(dir_1[0], dir_1[1], dir_1[2]);
	}

	Vector direction_2()
	{
	    return Vector(dir_2[0], dir_2[1], dir_2[2]);
	}

	Vector direction_3()
	{
	    return Vector(dir_3[0], dir_3[1], dir_3[2]);
	}

};





class Relation {

	double epsilon = 0.0001;

public:

	enum CoPlanarityType {TOP, BOTTOM, LEFT, RIGHT, BACK, FRONT, NONE};

	BoundingBox fitAxisAlignedCuboid (PartBase *thePart);
	MinimumBoundingBox fitCuboid (Part* thePart);

	std::pair <Relation::CoPlanarityType,Relation::CoPlanarityType> checkAxisAlignedCoPlanarity (PartBase *part1, PartBase *part2);
	//std::pair <Relation::CoPlanarityType,Relation::CoPlanarityType> checkCoPlanarity (Part *part1, Part *part2);
	Vector checkAxisAlignedCoCentricity (PartBase *part1, PartBase *part2);
	//checkOrthogonality (PartBase *part1, PartBase *part2);

};

BoundingBox Relation::fitAxisAlignedCuboid (PartBase* thePart) {
		// todo: CGAL::Iso_cuboid_3 is the same as BoundingBox, but with two points as the handles, we can implement using this
		return thePart->boundingBox;
}	


// Computing a tight-fitting bounding box of the part - note that it is an approximation, however it is an epsilon approximation and in most of the cases is exact
MinimumBoundingBox Relation::fitCuboid (Part *thePart) {
	// todo: note that the default grid_size = 5 and grid_sample = 400 is used
	MinimumBoundingBox mbb(thePart->mesh);
	return mbb;
}

std::pair <Relation::CoPlanarityType,Relation::CoPlanarityType> Relation::checkAxisAlignedCoPlanarity (PartBase *part1, PartBase *part2) {

	BoundingBox bb1 = part1->boundingBox;
	BoundingBox bb2 = part2->boundingBox;

	// ------------------------------------
	// check TOP coplanarity
	if(fabs(bb1.zmax() - bb2.zmax()) < epsilon)
		return std::make_pair(Relation::TOP, Relation::TOP);

	// check BOTTOM coplanarity
		if(fabs(bb1.zmin() - bb2.zmin()) < epsilon)
			return std::make_pair(Relation::BOTTOM, Relation::BOTTOM);

	// check TOP from first and BOTTOM from second coplanarity
	if(fabs(bb1.zmax() - bb2.zmin()) < epsilon)
		return std::make_pair(Relation::TOP, Relation::BOTTOM);


	// check BOTTOM from first and TOP from second coplanarity
	if(fabs(bb1.zmax() - bb2.zmin()) < epsilon)
		return std::make_pair(Relation::BOTTOM, Relation::TOP);

	// ------------------------------------

	// check RIGHT coplanarity
	if(fabs(bb1.xmax() - bb2.xmax()) < epsilon)
		return std::make_pair(Relation::RIGHT, Relation::RIGHT);

	// check LEFT coplanarity
	if(fabs(bb1.xmin() - bb2.xmin()) < epsilon)
		return std::make_pair(Relation::LEFT, Relation::LEFT);

	// check RIGHT from first and LEFT from second coplanarity
	if(fabs(bb1.xmax() - bb2.xmin()) < epsilon)
		return std::make_pair(Relation::RIGHT, Relation::LEFT);

	// check LEFT from first and RIGHT from second coplanarity
	if(fabs(bb1.xmin() - bb2.xmax()) < epsilon)
		return std::make_pair(Relation::LEFT, Relation::RIGHT);

	// ------------------------------------

	// check FRONT coplanarity
	if(fabs(bb1.ymax() - bb2.ymax()) < epsilon)
		return std::make_pair(Relation::FRONT, Relation::FRONT);

	// check BACK coplanarity
	if(fabs(bb1.ymin() - bb2.ymin()) < epsilon)
		return std::make_pair(Relation::BACK, Relation::BACK);

	// check FRONT from first and BACK from second coplanarity
	if(fabs(bb1.ymax() - bb2.ymin()) < epsilon)
		return std::make_pair(Relation::FRONT, Relation::BACK);

	// check BACK from first and FRONT from second coplanarity
	if(fabs(bb1.ymin() - bb2.ymax()) < epsilon)
		return std::make_pair(Relation::BACK, Relation::FRONT);

	return std::make_pair(Relation::NONE, Relation::NONE);
}

//std::pair <Relation::CoPlanarityType,Relation::CoPlanarityType> Relation::checkCoPlanarity (Part *part1, Part *part2) {
//	vector<std::pair <Relation::CoPlanarityType,Relation::CoPlanarityType>> result;
//
//	// todo: note that the default grid_size = 5 and grid_sample = 400 is used
//	BoundingBox mbb1 = MinimumBoundingBox(part1->mesh);
//	BoundingBox mbb2 = MinimumBoundingBox(part2->mesh);
//
//
//
//	return result;
//}

Vector Relation::checkAxisAlignedCoCentricity(PartBase *part1, PartBase *part2) {

	double x1_mid = (part1->boundingBox.xmin() + part1->boundingBox.xmax())/2;
	double y1_mid = (part1->boundingBox.ymin() + part1->boundingBox.ymax())/2;
	double z1_mid = (part1->boundingBox.zmin() + part1->boundingBox.zmax())/2;

	double x2_mid = (part2->boundingBox.xmin() + part2->boundingBox.xmax())/2;
	double y2_mid = (part2->boundingBox.ymin() + part2->boundingBox.ymax())/2;
	double z2_mid = (part2->boundingBox.zmin() + part2->boundingBox.zmax())/2;
//
//	Point top_1		(x1_mid, y1_mid, part1->boundingBox.zmax());
//	Point bottom_1	(x1_mid, y1_mid, part1->boundingBox.zmin());
//	Point right_1	(part1->boundingBox.xmax(), y1_mid, z1_mid);
//	Point bottom_1	(part1->boundingBox.xmin(), y1_mid, z1_mid);
//	Point front_1	(x1_mid, part1->boundingBox.ymax(), z1_mid);
//	Point back_1	(x1_mid, part1->boundingBox.ymin(), z1_mid);
//
//
//	Point top_2		(x2_mid, y2_mid, part2->boundingBox.zmax());
//	Point bottom_2	(x2_mid, y2_mid, part2->boundingBox.zmin());
//	Point right_2	(part2->boundingBox.xmax(), y2_mid, z2_mid);
//	Point bottom_2	(part2->boundingBox.xmin(), y2_mid, z2_mid);
//	Point front_2	(x2_mid, part2->boundingBox.ymax(), z2_mid);
//	Point back_2	(x2_mid, part2->boundingBox.ymin(), z2_mid);


	Point_2 xy_1(x1_mid, y1_mid);
	Point_2 xy_2(x2_mid, y2_mid);
	if (CGAL::squared_distance(xy_1,xy_2) < epsilon)
		return Vector(0, 0, 1);

	Point_2 yz_1(y1_mid, z1_mid);
	Point_2 yz_2(y2_mid, z2_mid);
	if (CGAL::squared_distance(yz_1,yz_2) < epsilon)
		return Vector(1, 0, 0);

	Point_2 xz_1(x1_mid, z1_mid);
	Point_2 xz_2(x2_mid, z2_mid);
	if (CGAL::squared_distance(xz_1,xz_2) < epsilon)
		return Vector(0, 1, 0);

	return Vector();
}








#endif

