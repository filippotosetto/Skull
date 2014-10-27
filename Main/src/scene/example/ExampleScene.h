#include "../abstract/AbstractScene.h"
#include "../../skull/SkullDelegate.h"


class ExampleScene : public AbstractScene, public SkullDelegate {

    public:
        ExampleScene();
        ExampleScene(int index, string name):AbstractScene(index, name) {}

        void setup();
        void update();
        void show();
        void hide();

        void initGUI();

        ofColor getSkullColor();
    
    
    private:
        ofRectangle rect;
        float rectSize = 20.f;

        void onRectSlideIn(float* arg);
        void onRectSlideOut(float* arg);

};
