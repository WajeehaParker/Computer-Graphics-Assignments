#include <iostream>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <string>>



//################## class VertexID ################
//used to define a Mesh
class VertexID
{

public:
	int vertIndex, normIndex;

	VertexID(){}

	VertexID(int VI,int NI)
	{
	vertIndex = VI;
	normIndex = NI;
	}

};


//################# class FACE ##############
//used to define a Mesh
class Face
{

public:
  int nVerts;
  VertexID * Points; // array of vertex and normal indices
  Face(){ nVerts = 0; Points = NULL;}
  
  Face(int n,VertexID *VI)
  {
    nVerts = n;
	Points = VI;
  
  }

  ~Face(){Points = NULL; nVerts = 0;}
 
};

//@$@$@$@$@$@$@$@$@$@ Mesh class @$@$@$@$@$@$@$@$@$
class Mesh 
{

private:
  int numVerts, numNorms, numFaces;
  Point3 *pt; // array of Points
  Vector3 *norm; // array of normals
  Face *face; // array of faces
  int lastVertUsed;
  int lastNormUsed;
  int lastFaceUsed;

public:
  char* meshFileName; // holds file name for this Mesh

  Mesh();
  Mesh(int Vertices, int Normals, int Faces);
  Mesh(char* fname); // read this file to build mesh
  Mesh(int nv,Point3* v, int nf, Face*f, int nn, Vector3* n);
  //void InitializeTetrahedron ();
  void InitializeCube();
  void readMesh(char* fname);
  void writeMesh(char* fname);
  void drawMesh();
  void freeMesh();
  int isEmpty(); 
  void makeEmpty(); 
};

//<<<<<<<<<<<<<<<<<<<<<< Constructors >>>>>>>>>>>>>>>>>>>>

Mesh :: Mesh(){
  numVerts = numFaces = numNorms = 0; 
  pt = NULL; norm  =  NULL; face = NULL;
  lastVertUsed = lastNormUsed = lastFaceUsed = -1;
}

Mesh :: Mesh(int Vertices, int Normals, int Faces)
{
	numVerts = Vertices;
	numNorms = Normals;
	numFaces = Faces;
}

Mesh :: Mesh(char* fname){ // read this file to build mesh
  numVerts = numFaces = numNorms = 0; 
  pt = NULL; norm  =  NULL; face = NULL;
  lastVertUsed = lastNormUsed = lastFaceUsed = -1;
  readMesh(fname);
}

Mesh ::Mesh(int nv,Point3 *v, int nf, Face *f, int nn, Vector3 *n)
{
  numVerts = nv;
  pt=v;

  numFaces = nf;
  face = f;

  numNorms = nn;
  norm = n;
}

// Initializes Tetrahedron Mesh
//void Mesh :: InitializeTetrahedron ()
//{
//	static Point3 Points[4];          //  Vertices
//	static Vector3 Vectors[4];        //  Normals
//	static VertexID VertexIDs[4][3];  // Indices
//	static Face FaceLists[4];         //     
//
//	// Hard Code Vertices of Tetrahedron
//	Points[0].set(0,0,0);
//	Points[1].set(1,0,0);
//	Points[2].set(0,1,0);
//	Points[3].set(0,0,1);
//
//	// Hard Code normal of Tetrahedron
//	Vectors[0].set(0.527,0.527,0.527);
//	Vectors[1].set(0,0,1);
//	Vectors[2].set(-1,0,0);
//	Vectors[3].set(0,-1,0);
//
//	// Vertex ID and Normal Vector ID  for Face 0
//	VertexIDs[0][0]=VertexID(1,0);
//	VertexIDs[0][1]=VertexID(2,0);
//	VertexIDs[0][2]=VertexID(3,0);
//	
//	// Vertex ID and Normal Vector ID  for Face 1
//	VertexIDs[1][0]=VertexID(0,1);
//	VertexIDs[1][1]=VertexID(2,1);
//	VertexIDs[1][2]=VertexID(1,1);
//	
//	// Vertex ID and Normal Vector ID  for Face 2
//	VertexIDs[2][0]=VertexID(0,2);
//	VertexIDs[2][1]=VertexID(3,2);
//	VertexIDs[2][2]=VertexID(2,2);
//
//	// Vertex ID and Normal Vector ID  for Face 3
//	VertexIDs[3][0]=VertexID(1,3);
//	VertexIDs[3][1]=VertexID(3,3);
//	VertexIDs[3][2]=VertexID(0,3);
//
//	// Create FaceList with the help of vertex and normal index
//	FaceLists[0]= Face(3,VertexIDs[0]);
//	FaceLists[1]= Face(3,VertexIDs[1]);
//	FaceLists[2]= Face(3,VertexIDs[2]);
//	FaceLists[3]= Face(3,VertexIDs[3]);
//
//	pt = &Points[0];
//	face = &FaceLists[0];
//	norm = &Vectors[0];
//}

void Mesh::InitializeCube()
{
	static Point3 Points[10];          //  Vertices
	static Vector3 Vectors[7];        //  Normals
	static VertexID VertexIDs[7][5];  // Indices
	static Face FaceLists[7];         //     

	// Hard Code Vertices of Cube
	Points[0].set(0, 0, 0);
	Points[1].set(1, 0, 0);
	Points[2].set(1, 1, 0);
	Points[3].set(0.5, 1.5, 0);
	Points[4].set(0, 1, 0);
	Points[5].set(0, 0, 1);
	Points[6].set(1, 0, 1);
	Points[7].set(1, 1, 1);
	Points[8].set(0.5, 1.5, 1);
	Points[9].set(0, 1, 1);

	// Hard Code normal of Cube
	Vectors[0].set(-1, 0, 0);
	Vectors[1].set(-0.707, 0.707, 0);
	Vectors[2].set(0.707, 0.707, 0);
	Vectors[3].set(1, 0, 0);
	Vectors[4].set(0, -1, 0);
	Vectors[5].set(0, 0, 1);
	Vectors[6].set(0, 0, -1);

	// Vertex ID and Normal Vector ID  for Face 0
	VertexIDs[0][0] = VertexID(0, 0);
	VertexIDs[0][1] = VertexID(5, 0);
	VertexIDs[0][2] = VertexID(9, 0);
	VertexIDs[0][3] = VertexID(4, 0);

	// Vertex ID and Normal Vector ID  for Face 1
	VertexIDs[1][0] = VertexID(3, 1);
	VertexIDs[1][1] = VertexID(4, 1);
	VertexIDs[1][2] = VertexID(9, 1);
	VertexIDs[1][3] = VertexID(8, 1);

	// Vertex ID and Normal Vector ID  for Face 2
	VertexIDs[2][0] = VertexID(2, 2);
	VertexIDs[2][1] = VertexID(3, 2);
	VertexIDs[2][2] = VertexID(8, 2);
	VertexIDs[2][3] = VertexID(7, 2);

	// Vertex ID and Normal Vector ID  for Face 3
	VertexIDs[3][0] = VertexID(1, 3);
	VertexIDs[3][1] = VertexID(2, 3);
	VertexIDs[3][2] = VertexID(7, 3);
	VertexIDs[3][3] = VertexID(6, 3);

	// Vertex ID and Normal Vector ID  for Face 4
	VertexIDs[4][0] = VertexID(0, 4);
	VertexIDs[4][1] = VertexID(1, 4);
	VertexIDs[4][2] = VertexID(6, 4);
	VertexIDs[4][3] = VertexID(5, 4);

	// Vertex ID and Normal Vector ID  for Face 5
	VertexIDs[5][0] = VertexID(5, 5);
	VertexIDs[5][1] = VertexID(6, 5);
	VertexIDs[5][2] = VertexID(7, 5);
	VertexIDs[5][3] = VertexID(8, 5);
	VertexIDs[5][4] = VertexID(9, 5);

	// Vertex ID and Normal Vector ID  for Face 6
	VertexIDs[6][0] = VertexID(0, 6);
	VertexIDs[6][1] = VertexID(4, 6);
	VertexIDs[6][2] = VertexID(3, 6);
	VertexIDs[6][3] = VertexID(2, 6);
	VertexIDs[6][4] = VertexID(1, 6);

	// Create FaceList with the help of vertex and normal index
	FaceLists[0] = Face(4, VertexIDs[0]);
	FaceLists[1] = Face(4, VertexIDs[1]);
	FaceLists[2] = Face(4, VertexIDs[2]);
	FaceLists[3] = Face(4, VertexIDs[3]);
	FaceLists[4] = Face(4, VertexIDs[4]);
	FaceLists[5] = Face(5, VertexIDs[5]);
	FaceLists[6] = Face(5, VertexIDs[6]);

	pt = &Points[0];
	face = &FaceLists[0];
	norm = &Vectors[0];
}

//<<<<<<<<<<<<<<<<<<<<<< drawMesh >>>>>>>>>>>>>>>>>>>>
void Mesh :: drawMesh()
{ // draw each face of this mesh using OpenGL: draw each polygon.
  if(isEmpty()) return; // mesh is empty
  for(int f = 0; f < numFaces; f++)
    {
      int n = face[f].nVerts;

	  glPushAttrib(GL_LIGHTING);

	  if (f==0)
	  {
			float Ambuse[] =   { 0.4, 0.2, 0.9, 1.0 };
			float Specular[] = { 0.3, 0.2, 0.6, 1.0 };
			float Shininess[] = { 10 };

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Ambuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, Shininess);
	  }
	  
	  else if (f==1)
	  {
			float Ambuse[] =   { 1.0, 1.0, 0.1, 1.0 };
			float Specular[] = { 1.0, 1.0, 0.1, 1.0 };
			float Shininess[] = { 10 };

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Ambuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, Shininess);
	  }

	  else if (f==2)
	  {
			float Ambuse[] =   { 1.0, 0.1, 1.0, 1.0 };
			float Specular[] = { 1.0, 0.1, 1.0, 1.0 };
			float Shininess[] = { 10 };

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Ambuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, Shininess);
	  }

	  else if (f==3)
	  {
			float Ambuse[] =   { 0.5, 0.8, 0.1, 1.0 };
			float Specular[] = { 0.4, 0.6, 0.9, 1.0 };
			float Shininess[] = { 10 };

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Ambuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, Shininess);
	  }

	  
	  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	  glBegin(GL_POLYGON);
      for(int v = 0; v < n; v++)
	  {
		  int iv = face[f].Points[v].vertIndex; assert(iv >= 0 && iv < numVerts);
		  glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
	  }
      glEnd();	

	  glPopAttrib();
    }
	
	
}		


//<<<<<<<<<<<<<<<<<<<<<<<<<<<< readMesh >>>>>>>>>>>>>>>>>>>>>>>>
void Mesh:: readMesh(char* fname)
{
  fstream inStream;
  inStream.open(fname, ios ::in); //open needs a c-like string
  if(inStream.fail() || inStream.eof()) 
  {
    cout << "can't open file or eof: " << fname << endl; 
    makeEmpty();return;
  }
  inStream >> numVerts >> numNorms >> numFaces;
  // make arrays for vertices, normals, and faces
  pt = new Point3[numVerts];        assert(pt != NULL);
  norm = new Vector3[numNorms];     assert(norm != NULL);
  face = new Face[numFaces];        assert(face != NULL);
  for(int i = 0; i < numVerts; i++) 	// read in the vertices
    inStream >> pt[i].x >> pt[i].y >> pt[i].z;
  for(int ii = 0; ii < numNorms; ii++) 	// read in the normals
    inStream >> norm[ii].x >> norm[ii].y >> norm[ii].z;
  for(int f = 0; f < numFaces; f++)   // read in face data
    {
      inStream >> face[f].nVerts;
      int n = face[f].nVerts;
      face[f].Points = new VertexID[n]; assert(face[f].Points != NULL);
      for(int k = 0; k < n; k++) 		// read vertex indices for this face
	inStream >> face[f].Points[k].vertIndex;
      for(int kk = 0; kk < n; kk++) 		// read normal indices for this face
	inStream >> face[f].Points[kk].normIndex;
    }
  inStream.close();
} // end of readMesh


//<<<<<<<<<<<<<<<<<<<<<<<<<<<< write mesh>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Mesh:: writeMesh(char * fname)
{ // write this mesh object into a new Chapter 6 format file.
  if(numVerts == 0 || numNorms   == 0 || numFaces == 0) return; //empty
  fstream outStream(fname, ios ::out); // open the output stream
  if(outStream.fail()) {cout << "can't make new file: " << fname << endl; return;}
  outStream << numVerts << " " << numNorms << " " << numFaces << "\n";
  // write the vertex and vertex normal list
  for(int i = 0; i < numVerts; i++)
    outStream << pt[i].x   << " " << pt[i].y   << " " << pt[i].z << "\n";
  for(int ii = 0; ii < numNorms; ii++)
    outStream  << norm[ii].x << " " << norm[ii].y << " " << norm[ii].z << "\n";
  // write the face data
  for(int f = 0; f < numFaces; f++)
    {
      int n = face[f].nVerts;
      outStream << n << "\n";
      for(int v = 0; v < n; v++)// write vertex indices for this face
	outStream << face[f].Points[v].vertIndex << " ";	outStream << "\n";
      for(int k = 0; k < n; k++)	// write normal indices for this face 
	outStream << face[f].Points[k].normIndex << " "; outStream << "\n";
    }
  outStream.close();
}

void Mesh::freeMesh()
{ // free up memory used by this mesh.
  delete [] pt; // release whole vertex list
  delete [] norm;
  for(int f = 0; f < numFaces; f++)
    delete[] face[f].Points; // delete the Points[] array of this face
  delete [] face;
}

int Mesh :: isEmpty()
{return (numVerts == 0) || (numFaces == 0) || (numNorms == 0);}
void Mesh :: makeEmpty()
{ numVerts = numFaces = numNorms = 0;}


