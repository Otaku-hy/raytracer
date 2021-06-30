#ifndef OBJ_Loader_H
#define OBJ_Loader_H
#include <string>
#include <vector>
#include "lib/Eigen/Eigen"
#include "cstdio"

using namespace Eigen;

class Loader
{
private:
    /* data */
public:
    Loader() = default;
    ~Loader();

    bool Loadfile(std::string fileName);

    std::vector<Vector3f> vertices;
    std::vector<Vector3i> faces;
};

Loader::Loader()
{
}

Loader::~Loader()
{
}

bool Loader::Loadfile(std::string fileName)
{
    /*
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "lib/Eigen/Eigen"

    using namespace Eigen;
    using namespace std;

    class Triangle
    {
    private:
       
    public:
        Triangle() = default;
        ~Triangle();

        vector<Vector3f> vertices;

        inline void printTriangle() const;
    };

    Triangle::~Triangle()
    {
    }

    void Triangle::printTriangle() const
    {
        cout << "vertex1: " << vertices[0] << "\t"
             << "vertex2: "
             << vertices[1] << "\t"
             << "vertex3: " << vertices[2];
    }

    class Object
    {
    private:
        
    public:
        Object() = default;
        ~Object();

        vector<Vector3f> vertices;
        vector<Vector3f> faces;

        inline void printAllVertices() const;
        inline void printAllFaces() const;

        Triangle searchFaceData(int ID);
    };

    Object::~Object()
    {
    }

    void Object::printAllVertices() const
    {
        cout << vertices.size() << "\n";

        for (auto &r : vertices)
        {
            cout << r << endl;
        }
    }

    void Object::printAllFaces() const
    {
        cout << faces.size() << "\n";

        for (auto &r : faces)
        {
            cout << r << endl;
        }
    }

    Triangle Object::searchFaceData(int ID)
    {
        Triangle T;

        T.vertices.push_back(vertices[faces[ID - 1][0] - 1]);
        T.vertices.push_back(vertices[faces[ID - 1][1] - 1]);
        T.vertices.push_back(vertices[faces[ID - 1][2] - 1]);

        return T;
    }

    Object OBJ_Loader(string fileName)
    {
        Object obj;

        ifstream is(fileName);

        string line;

        while (getline(is, line))
        {
            stringstream lineString(line);

            string type;
            float content;

            lineString >> type;

            if (type == "v")
            {
                vector<float> _vertex;

                while ((lineString >> content))
                {
                    _vertex.push_back(static_cast<float>(content));
                }
                Vector3f vertex(_vertex[0], _vertex[1], _vertex[2]);

                obj.vertices.push_back(vertex);
            }

            else if (type == "f")
            {
                vector<float> _face;

                while ((lineString >> content))
                {
                    _face.push_back(static_cast<float>(content));
                }
                Vector3f face(_face[0], _face[1], _face[2]);

                obj.faces.push_back(face);
            }
        }

        return obj;
    }
    */
}

// void OBJ_Loader(string fileName, Object &obj)
// {
//     ifstream is(fileName);
//     string line;

//     while (getline(is, line))
//     {
//         stringstream isl(line);
//         string type;

//         isl >> type;

//         if (type == "v")
//         {
//             Vector3f vertex;
//             isl >> vertex.x() >> vertex.y() >> vertex.z();

//             obj.vertices.push_back(vertex);
//         }
//         else if (type == "vt")
//         {
//             Vector2f texCoord;
//             isl >> texCoord.x() >> texCoord.y();

//             obj.texCoords.push_back(texCoord);
//         }
//         else if (type == "vn")
//         {
//             Vector3f normal;
//             isl >> normal.x() >> normal.y() >> normal.z();

//             obj.normals.push_back(normal);
//         }
//         else if (type == "f")
//         {
//             string data;
//             Vector3f vface;
//             Vector3f nface;
//             Vector3f tface;

//             int cnt = 0;

//             while (isl >> data)
//             {
//                 auto segmentF = data.find_first_not_of("0123456789");
//                 auto segmentL = data.find_last_not_of("0123456789");

//                 vface[cnt] = stof(data.substr(0, segmentF));
//                 tface[cnt] = stof(data.substr(segmentF + 1, segmentL - segmentF - 1));
//                 nface[cnt] = stof(data.substr(segmentL + 1));

//                 ++cnt;
//             }

//             obj.vfaces.push_back(vface);
//             obj.nfaces.push_back(nface);
//             obj.tfaces.push_back(tface);

//         }
//     }
// }

#endif
