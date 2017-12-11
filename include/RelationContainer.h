//
// Created by homapour on 12/10/2017.
//

#ifndef TEST_BOOST_RELATIONGRAPH_H
#define TEST_BOOST_RELATIONGRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graph_utility.hpp>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using std::string;

struct VertexData
{
    string label;
    string type; // i.e. Group or Part
};

struct RelationProperty
{

};

struct EdgeData
{
//    std::string edge_name;
//    double dist;

    vector<RelationProperty> propertyVector;
    map<string, RelationProperty> propertyMap;


};

typedef boost::adjacency_list<boost::vecS, boost::vecS,
        boost::undirectedS,
        VertexData,
        boost::no_property
> CutGraph;

typedef boost::adjacency_list<boost::vecS, boost::vecS,
        boost::directedS,
        VertexData,
        EdgeData
> DataGraph;

//descriptors
typedef boost::graph_traits<DataGraph>::vertex_descriptor VD;
typedef boost::graph_traits<DataGraph>::edge_descriptor ED;

class RelationContainer {
private:
    DataGraph dataGraph;
    map<string, int> label_vertex_map;

    CutGraph cutGraph;

public:
    DataGraph getDataGraph()
    {
        return this->dataGraph;
    }

    map<string, int> getLabelVertexMap()
    {
         return this->label_vertex_map;
    }

    void addVertex(string label, string type)
    {
        //VertexData vd = { label };
        //SV v = boost::add_vertex(vd, this->dataGraph);

        VertexData vd = { label, type };
        int vIndex = boost::add_vertex(this->dataGraph);
        this->dataGraph[vIndex] = vd;
        this->label_vertex_map[label] = vIndex;

        boost::add_vertex(this->cutGraph);
        this->cutGraph[vIndex] = vd;
    }


    VertexData getVertexData(string label)
    {
        int vIndex = this->label_vertex_map[label];
        VertexData vd = this->dataGraph[vIndex];
        return vd;
    }

    bool addEdge(string label_1, string label_2)
    {
        //ED e = boost::add_edge(v_1, v_2, {"the edge", 77.3}, G).first;
        int v_1 = this->label_vertex_map[label_1];
        int v_2 = this->label_vertex_map[label_2];

        // returns std::pair<edge_descriptor, bool> and the elements can be accessed using "first" and "second"
        auto e = boost::add_edge(v_1, v_2, this->dataGraph);

        //EdgeData edgeData = this->dataGraph[e.first];

        if(e.second) {
            boost::add_edge(v_1, v_2, this->cutGraph);
        }

        return e.second; // true if edge is created and false if the edge exists
    }

    EdgeData getEdgeData(string label_1, string label_2)
    {
        int v_1 = this->label_vertex_map[label_1];
        int v_2 = this->label_vertex_map[label_2];

        auto e = boost::edge(v_1, v_2, this->dataGraph);

        // get edge_descriptor using first
        EdgeData edgeData = this->dataGraph[e.first];

        return edgeData;
    }

    void print()
    {
        std::cout << "vertices: " << std::endl;
        auto vpair = boost::vertices(this->dataGraph);
        for(auto iter=vpair.first; iter!=vpair.second; iter++) {
            std::cout << this->dataGraph[*iter].label << "(" << this->dataGraph[*iter].type << ")" << std::endl;
        }

        std::cout << std::endl << "edges: " << std::endl;
        auto epair = boost::edges(this->dataGraph);
        for(auto iter=epair.first; iter!=epair.second; iter++) {
            std::cout << this->dataGraph[source(*iter, this->dataGraph)].label << " - " << this->dataGraph[target(*iter, this->dataGraph)].label << std::endl;
        }
    }

    DataGraph copyGraph()
    {
        DataGraph copyGraph;
        //boost::copy_graph(this->dataGraph, copyGraph);
        boost::copy_graph(this->dataGraph, copyGraph);
    }
};


#endif //TEST_BOOST_RELATIONGRAPH_H
