#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//#include "ofxTweenzor.h"
#include "ofAppDefines.h"
#include "../../audio/AudioManager.h"

class AbstractScene {
    public:
        AbstractScene();
        AbstractScene(int _index, string _name);

        virtual void setup();
        virtual void show();
        virtual void hide();
        virtual void update();

        int getIndex() { return index; }
        string getName() { return name; }

        ofxPanel gui;

    protected:
        virtual void initGUI();

        int index;
        string name;

        struct sortDistances {
            bool operator()(const std::pair<int, ofPoint> &left, const std::pair<int, ofPoint> &right) {
                return left.first < right.first;
            }
        };

        struct Loggetta
        {
            int x = 35;
            int y = 0;
            int width = 950;
            int height = 768;

            ofRectangle rectRoof = ofRectangle(x, y, width, 67);
            ofRectangle rectBar = ofRectangle(x, y + rectRoof.height, width, 46);
            ofRectangle rectArcs = ofRectangle(x, y + rectRoof.height + rectBar.height, width, 192);
            ofRectangle rectColumns = ofRectangle(x, y + rectRoof.height + rectBar.height + rectArcs.height, width, 273);
            ofRectangle rectFence = ofRectangle(x, y + rectRoof.height + rectBar.height + rectArcs.height + rectColumns.height, width, 90);
            ofRectangle rectFooter = ofRectangle(x, y + rectRoof.height + rectBar.height + rectArcs.height + rectColumns.height + rectFence.height, width, 100);

            int colWidth = 50;

            ofRectangle rectCol1 = ofRectangle(x + 27, rectColumns.y, colWidth, rectColumns.height);
            ofRectangle rectCol2 = ofRectangle(x + 311, rectColumns.y, colWidth, rectColumns.height);
            ofRectangle rectCol3 = ofRectangle(x + 593, rectColumns.y, colWidth, rectColumns.height);
            ofRectangle rectCol4 = ofRectangle(x + 874, rectColumns.y, colWidth, rectColumns.height);

            int circleRadius = 25;

            ofRectangle circleLeft = ofRectangle(rectCol2.x + colWidth / 2, rectColumns.y - 130, circleRadius, circleRadius);
            ofRectangle circleRight = ofRectangle(rectCol3.x + colWidth / 2, rectColumns.y - 130, circleRadius, circleRadius);

            vector<ofPoint> pointsPositive;
            vector<ofPoint> pointsNegative;
            vector<vector<ofPoint> > points;

        };

        Loggetta loggetta;

        ofEasyCam cam;

};

