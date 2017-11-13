#include<iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;
#define PI 3.14159265

class Vertex{
public:
    double x,y,z;
    Vertex(double x,double y,double z):x(x),y(y),z(z){}
};

class Shape {
public:
    string name;
    vector<Vertex> vertexes;
};

class Cylinder : public Shape{
private:
    double r, h;
    int facets;
public:
    Cylinder(double x, double y, double z, double r, double h, int facets) {
        this->name="Cylinder";

        double xs[facets],ys[facets];

        for(int i=0;i<facets;i++)
        {
            double angle=360.0/facets*i;

            xs[i]=x+r*cos (angle*PI/180);
            ys[i]=y+r*sin(angle*PI/180);
        }

        for(int i=0;i<facets;i++)
        {
            this->vertexes.emplace_back(x,y,z);
            this->vertexes.emplace_back(xs[(i+1)%facets],ys[(i+1)%facets],z);
            this->vertexes.emplace_back(xs[i],ys[i],z);

            this->vertexes.emplace_back(x,y,z+h);
            this->vertexes.emplace_back(xs[i],ys[i],z+h);
            this->vertexes.emplace_back(xs[(i+1)%facets],ys[(i+1)%facets],z+h);

            this->vertexes.emplace_back(xs[i],ys[i],z+h);
            this->vertexes.emplace_back(xs[i],ys[i],z);
            this->vertexes.emplace_back(xs[(i+1)%facets],ys[(i+1)%facets],z);

            this->vertexes.emplace_back(xs[i],ys[i],z+h);
            this->vertexes.emplace_back(xs[(i+1)%facets],ys[(i+1)%facets],z);
            this->vertexes.emplace_back(xs[(i+1)%facets],ys[(i+1)%facets],z+h);
        }
    }
};

class Cube: public Shape {
private:
    double size;
public:
    Cube(double x, double y, double z, double size) : size(size) {
        this->name="Cube";

        size/=2;
        double ccwx[]={size,-size,-size},ccwy[]={size,size,-size};

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x+size,y+ccwx[i],z+ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x+size,y-ccwx[i],z-ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x-size,y-ccwx[i],z+ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x-size,y+ccwx[i],z-ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x-ccwx[i],y+size,z+ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x+ccwx[i],y+size,z-ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x+ccwx[i],y-size,z+ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x-ccwx[i],y-size,z-ccwy[i]);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x+ccwx[i],y+ccwy[i],z+size);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x-ccwx[i],y-ccwy[i],z+size);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x-ccwx[i],y+ccwy[i],z-size);
        }

        for(int i=0;i<3;i++)
        {
            vertexes.emplace_back(x+ccwx[i],y-ccwy[i],z-size);
        }
    }
};

class CAD {
private:
    vector<Shape*> shapes;
public:
    void add(Shape* shape){
        shapes.push_back(shape);
    }

    void write(string filename)
    {
        ofstream output(filename);
        if(output.is_open())
        {
            for(Shape* shape:shapes)
            {
                output<<"solid "+shape->name<<endl;

                int i=0;
                for(Vertex vertex:shape->vertexes)
                {
                    if(i%3==0)
                        output<<"facet normal 0 0 0"<<endl<<"outer loop"<<endl;

                    output<<"vertex "+to_string(vertex.x)+' '+to_string(vertex.y)+' '+to_string(vertex.z)<<endl;
                    i++;

                    if(i%3==0)
                        output<<"endloop"<<endl<<"endfacet"<<endl;
                }

                output<<"endsolid "+shape->name<<endl;
            }
            output.close();
        }
    }
};

//https://www.stratasccwysdirect.com/resources/how-to-prepare-stl-files/
//https://www.viewstl.com/
int main() {
    CAD c;
    c.add(new Cube(0,0,0,   5));
    c.add(new Cylinder(100,0,0,    3, 10, 10));
  c.write("test.stl");
}
