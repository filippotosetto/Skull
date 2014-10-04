#ifndef _DRAG
#define _DRAG

#include "ofMain.h"

class Drag {
    public:
        Drag();
        Drag(ofVec3f _pos);

        void update();
        void draw();

        void mouseMoved();
        void mousePressed();
        void mouseReleased();
        void mouseOver();
        void mouseOut();

        ofVec3f pos;
        int radius;
        int lineWidth;
        int alpha;
        bool down;
        bool over;

        static const int RADIUS = 10;
        static const int HIT_RADIUS_SQ = RADIUS * RADIUS;

};
#endif


