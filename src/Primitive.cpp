//
//  Primitive.cpp
//  LAIG - P1
//

#include "Primitive.h"
#include "math.h"

namespace scene {
    
    Primitive::Primitive() {
        
    }
    
    Primitive::Primitive(string id) {
        this->id = id;
    }
    
    Primitive::~Primitive() {
        
    }
    
    void Primitive::setId(string id) {
        this->id = id;
    }
    
    void Primitive::setTexlength_s(float texlength_s) {
        this->texlength_s = texlength_s;
    }
    
    void Primitive::setTexlength_t(float texlength_t) {
        this->texlength_t = texlength_t;
    }
    
    string Primitive::getId() {
        return this->id;
    }
    
    float Primitive::getTexlength_s() {
        return this->texlength_s;
    }
    
    float Primitive::getTexlength_t() {
        return this->texlength_t;
    }
    
    Cylinder::~Cylinder() {
        gluDeleteQuadric(cylinderQuadric);
    }
    
    Rectangle::Rectangle(string id, float x1, float y1, float x2, float y2) : Primitive(id) {
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
        this->verticesRectangle = new float*[4];
        this->verticesRectangle[0] = new float[3];
        this->verticesRectangle[1] = new float[3];
        this->verticesRectangle[2] = new float[3];
        this->verticesRectangle[3] = new float[3];
        this->verticesRectangle[0][0] = x1;
        this->verticesRectangle[0][1] = y1;
        this->verticesRectangle[0][2] = 0;
        this->verticesRectangle[1][0] = x2;
        this->verticesRectangle[1][1] = y1;
        this->verticesRectangle[1][2] = 0;
        this->verticesRectangle[2][0] = x2;
        this->verticesRectangle[2][1] = y2;
        this->verticesRectangle[2][2] = 0;
        this->verticesRectangle[3][0] = x1;
        this->verticesRectangle[3][1] = y2;
        this->verticesRectangle[3][2] = 0;
        this->normalRectangle = get_normal_newell(verticesRectangle, 4);
        
        this->length = abs(x2-x1);
        this->height = abs(y2-y1);
        
    }
    
    Triangle::Triangle(string id, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) : Primitive(id) {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->y1 = y1;
        this->y2 = y2;
        this->y3 = y3;
        this->z1 = z1;
        this->z2 = z2;
        this->z3 = z3;
        
        // calculate triangle normal
        this->verticesTriangle = new float*[3];
        this->verticesTriangle[0] = new float[3];
        this->verticesTriangle[1] = new float[3];
        this->verticesTriangle[2] = new float[3];
        this->verticesTriangle[0][0] = x1;
        this->verticesTriangle[0][1] = y1;
        this->verticesTriangle[0][2] = z1;
        this->verticesTriangle[1][0] = x2;
        this->verticesTriangle[1][1] = y2;
        this->verticesTriangle[1][2] = z2;
        this->verticesTriangle[2][0] = x3;
        this->verticesTriangle[2][1] = y3;
        this->verticesTriangle[2][2] = z3;
        
        this->normalTriangle = get_normal_newell(verticesTriangle, 3);
        
        // calculate triangle texture
        this->a = sqrt(pow(x1-x3,2) + pow(y1-y3,2) + pow(z1-z3,2));
        this->b = sqrt(pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2));
        this->c = sqrt(pow(x3-x2,2) + pow(y3-y2,2) + pow(z3-z2,2));
        
        this->cos_beta = (pow(this->a,2) - pow(b,2) + pow(c,2))/(2*a*c);
        
        //sin_beta = sqrt(1 - pow(cos_beta, 2));
        sin_beta = acos(cos_beta);
        
        this->p0[0] = c - (a * cos_beta);
        this->p0[1] = a * sin_beta;
        
        this->p1[0] = 0;
        this->p1[1] = 0;
        
        this->p2[0] = c;
        this->p2[1] = 0;
        
    }
    
    Cylinder::Cylinder(string id, float base, float top, float height, int slices, int stacks) : Primitive(id) {
        this->base = base;
        this->top = top;
        this->height = height;
        this->slices = slices;
        this->stacks = stacks;
        
        this->cylinderQuadric = gluNewQuadric();
        gluQuadricDrawStyle(cylinderQuadric, GLU_FILL);
        gluQuadricNormals(cylinderQuadric, GLU_SMOOTH);
        gluQuadricOrientation(cylinderQuadric, GLU_OUTSIDE);
        gluQuadricTexture(cylinderQuadric, GL_TRUE);
    }
    
    Sphere::Sphere(string id, float radius, int slices, int stacks) : Primitive(id) {
        this->radius = radius;
        this->slices = slices;
        this->stacks = stacks;
        
        this->sphereQuadric = gluNewQuadric();
        gluQuadricDrawStyle(sphereQuadric, GLU_FILL);
        gluQuadricNormals(sphereQuadric, GLU_SMOOTH);
        gluQuadricOrientation(sphereQuadric, GLU_OUTSIDE);
        gluQuadricTexture(sphereQuadric, GL_TRUE);
    }
    
    Torus::Torus(string id, float inner, float outer, int slices, int loops) : Primitive(id) {
        this->inner = inner;
        this->outer = outer;
        this->slices = slices;
        this->loops = loops;
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    }
    
    void Rectangle::draw() {
        
        glBegin(GL_QUADS);
        
        //glNormal3f(0,0,1);
        glNormal3f(normalRectangle[0], normalRectangle[1], normalRectangle[2]);
        
        glTexCoord2f(0, 0);
        glVertex3f(x1, y1, 0);
        glTexCoord2f(length/getTexlength_s(), 0);
        glVertex3f(x2, y1, 0);
        glTexCoord2f(length/getTexlength_s(), height/getTexlength_t());
        glVertex3f(x2, y2, 0);
        glTexCoord2f(0, height/getTexlength_t());
        glVertex3f(x1, y2, 0);
        
        glEnd();
    }
    
    void Triangle::draw() {
        
        /*
         float acN= sqrt( (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) + (z3-z1)*(z3-z1));
         float abN= sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
         float ab[3],ac[3];
         ab[0]=(x2-x1)/abN;
         ab[1]=(y2-y1)/abN;
         ab[2]=(z2-z1)/abN;
         ac[0]=(x3-x1)/acN;
         ac[1]=(y3-y1)/acN;
         ac[2]=(z3-z1)/acN;
         
         float cosAlfa =abs(ab[0]*ac[0]+ab[1]*ac[1]+ab[2]*ac[2]);
         float AD = abN*cosAlfa;
         float AE = abN*sin(acos(cosAlfa));*/
        
        glBegin(GL_TRIANGLES);
        
        glNormal3f(normalTriangle[0], normalTriangle[1], normalTriangle[2]);
        
        glTexCoord2f(p0[0]/getTexlength_s(), p0[1]/getTexlength_t());
        glVertex3f(x1, y1, z1);
        glTexCoord2f(p1[0], p1[1]);
        glVertex3f(x2, y2, z2);
        glTexCoord2f(p2[0]/getTexlength_s(), p2[1]);
        glVertex3f(x3, y3, z3);
        
        glEnd();
        
    }
    
    void Cylinder::draw() {
        glEnable(GL_NORMALIZE);
        
        // top of the cylinder
        glPushMatrix();
        
        gluDisk(cylinderQuadric, 0, base, slices, stacks);
        glTranslated(0, 0, height);
        gluDisk(cylinderQuadric, 0, top, slices, stacks);
        
        glPopMatrix();
        
        // side of the cylinder
        gluCylinder(cylinderQuadric, base, top, height, slices, stacks);
        
        // base of the cylinder
        glPushMatrix();
        glRotated(180, 0, 1, 0);
        gluDisk(cylinderQuadric, 0, base, slices, stacks);
        glPopMatrix();
    }
    
    void Sphere::draw() {
        gluSphere(sphereQuadric, radius, slices, stacks);
    }
    
    void Torus::draw() {
        
        glEnable(GL_NORMALIZE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        
        glutSolidTorus(inner, outer, slices, loops);
        
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        
    }
    
    float *Primitive::get_normal_newell(float **vertices, int size) {
        float *normal = (float*) malloc(sizeof (float)*3);
        float *vertex_act, *vertex_next;
        
        /*while(vertices[count]){
         cout << vertices[count][0] << "," << vertices[count][1] << "," << vertices[count][2] << endl;
         count++;
         } */
        for (int vert = 0; vert < size; ++vert) {
            vertex_act = vertices[vert];
            vertex_next = vertices[(vert + 1) % size];
            /*
             Set Normal.x to Sum of Normal.x and (multiply (Current.y minus Next.y) by (Current.z plus Next.z))
             Set Normal.y to Sum of Normal.y and (multiply (Current.z minus Next.z) by (Current.x plus Next.x))
             Set Normal.z to Sum of Normal.z and (multiply (Current.x minus Next.x) by (Current.y plus Next.y))
             */
            normal[0] = normal[0]+(vertex_act[1] - vertex_next[1])*(vertex_act[2] + vertex_next[2]);
            normal[1] = normal[1]+(vertex_act[2] - vertex_next[2])*(vertex_act[0] + vertex_next[0]);
            normal[2] = normal[2]+(vertex_act[0] - vertex_next[0])*(vertex_act[1] + vertex_next[1]);
            
            // Normalize (divide by root of dot product)
            float tmp = (float) sqrt((normal[0] * normal[0]) + (normal[1] * normal[1]) + (normal[2] * normal[2]));
            normal[0] /= tmp;
            normal[1] /= tmp;
            normal[2] /= tmp;
        }
        return normal;
    }
    
}

