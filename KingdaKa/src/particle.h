#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class particle
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        particle();
		virtual ~particle(){};
        void setupImage(int playerNumber);
        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		void addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
		
		void addDampingForce();
        
		void setInitialCondition(float px, float py, float vx, float vy);
        void update();
        void draw();
    
		void bounceOffWalls();
	
	
		float damping;
    int particleStance;
    float angle;
    
    int playerNo;
    bool bCartoonMode;
    ofImage player[3];
    ofImage face[2];
    float size;
    int faceNum;
    
    protected:
    private:
};

#endif // PARTICLE_H
