#include "../abstract/AbstractScene.h"

class ExampleScene : public AbstractScene {

    public:
        ExampleScene();
        ExampleScene(int index, string name, Skull* skull):AbstractScene(index, name, skull) {}

        void setup();
        void update();
        void show();
        void hide();

        void initGUI();


    private:
        ofRectangle rect;
        float rectSize = 20.f;

        void onRectSlideIn(float* arg);
        void onRectSlideOut(float* arg);

};
