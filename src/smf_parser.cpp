/**
	@file 		smf_parser.cpp
	@author 	Ravi Agrawal (ravia@sfu.ca)
	@date		November 7, 2017
	@version 	1.0

	@brief		CMPT-764: Assignment 2, Implements SMF parser.
*/

#include <smf_parser.h>

// Read SMF file and parse data
Mesh *parseSmfFile (string filename) {
	ifstream smf_file;
	smf_file.open(filename.c_str());

	if (smf_file.fail()) {
		cerr << "Error opening file." << endl << "Exiting..." << endl;
		exit(1);
	}

	// Read data
	char type;
	Mesh *mesh = new Mesh(); // Initialize an empty mesh

	while (smf_file >> type) {
		string line;
		float x, y, z;
		int v1, v2, v3;

		switch (type) {
			case '#':
				getline(smf_file, line); // Ignore comments starting with '#'
				break;
			case 'v':
				smf_file >> x >> y >> z;
				mesh->insertVertex(x, y, z);
				break;
			case 'f':
				smf_file >> v1 >> v2 >> v3;
				mesh->insertTriangle(v1, v2, v3);
				break;
			default:
				getline(smf_file, line); // Ignore arbitrary lines
				break;
		}
	}

	smf_file.close();

	return mesh;
}

void writeSmfFile (Mesh *mesh, string filename) {
	ofstream smf_file;
	smf_file.open(filename.c_str());
	
	if (smf_file.fail()) {
		cerr << "Error opening file." << endl << "Exiting..." << endl;
		exit(1);
	}

	smf_file << "# " << mesh->numVertices << " " << mesh->numFaces << endl;
	
	for (int i = 1; i <= mesh->numVertices; i++) {
		Vertex *vertex = mesh->vertexMap[i];
		vec3 position = vertex->position;
		smf_file << "v " << position.x << " " << position.y << " " << position.z << endl;
	}

	for (int i = 1; i <= mesh->numFaces; i++) {
		Face *face = mesh->faceMap[i];
		Vertex *vertices[3];
		mesh->getAllVerticesForFace(face, vertices);
		smf_file << "f " << mesh->vertexIndexMap[vertices[0]] << " " << mesh->vertexIndexMap[vertices[1]] << " " << mesh->vertexIndexMap[vertices[2]] << endl;
	}
	
	smf_file.close();
}