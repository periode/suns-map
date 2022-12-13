#include "ofMain.h"
#include "Marker.h"

class Map
{
public:

    static ofColor YELLOW;
    static ofColor BLUE;
    static ofColor GREEN;
    static ofColor ORANGE;
    static ofColor RED;
    static ofColor NONE;


    void setup(string mode);
    void update();
    void draw();
    void drawBackground();
    void printMap();

    vector<Marker> markers;

private:
    ofFbo fbo;
    string mode;
    bool canPrint = false;
    int latestGeneration;
};