#include "ofMain.h"
#include "Marker.h"

class Map
{
public:
    void setup(ofJson);
    void update();
    void draw();
    void deformVertex();
    void printMap();

    vector<Marker> markers;

private:
    ofFbo fbo;
    ofMesh mesh;
    bool canPrint = false;
};