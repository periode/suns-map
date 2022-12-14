#include "ofApp.h"

ofColor Map::YELLOW = ofColor(201, 165, 72);
ofColor Map::BLUE = ofColor(126, 171, 195);
ofColor Map::GREEN = ofColor(131, 160, 116);
ofColor Map::ORANGE = ofColor(178, 96, 48);
ofColor Map::RED = ofColor(195, 73, 76);
ofColor Map::NONE = ofColor(255, 255, 255, 0);
ofColor Map::PINK = ofColor(250, 209, 225);
ofColor Map::MUD = ofColor(211, 174, 166);
ofColor Map::PURPLE = ofColor(124, 112, 130);
ofColor Map::CORAL = ofColor(255, 156, 150);
ofColor Map::SAND = ofColor(255, 251, 235);
ofColor Map::AMBER = ofColor(120, 53, 15, 50);

void Map::setup(string _mode)
{
    mode = _mode;

    //-- allocating data for drawing into fbo
    fbo.allocate(MAP_WIDTH, MAP_HEIGHT, GL_RGB);
    fbo.begin();
    ofClear(255, 255, 255);
    fbo.end();
}

void Map::update()
{

    fbo.begin();
    ofClear(255, 255, 255);
    fbo.end();

    //-- get latest generation
    for (Marker m : markers)
    {
        if (m.generation > latestGeneration)
        {
            latestGeneration = m.generation;
        };
    }

    for (Marker &m : markers)
    {
        m.update(latestGeneration);
    }

    connections.clear();
    for (Marker m1 : markers)
    {
        for (Marker m2 : markers)
        {
            if (m1.cluster == m2.cluster && m1.pos.distance(m2.pos) < markerDistance)
            {
                float r = ofRandom(10);
                if (r > 5)
                {
                    Connection c = Connection(m1.pos, m2.pos);
                    connections.push_back(c);
                }
            }
        }
    }

    canPrint = true;
}

void Map::draw()
{
    if (canPrint)
    {
        fbo.begin();
        drawBackground();

        ofPushMatrix();
        ofTranslate(MAP_WIDTH / 2, MAP_HEIGHT / 2);
        for (Marker m : markers)
        {
            m.draw();
        }

        for (Connection c : connections)
        {
            c.draw();
        }
        ofPopMatrix();
        fbo.end();

        if (canDraw)
        {
            fbo.draw(0, 0);
        }

        printMap();
        canPrint = false;
    }
}

void Map::drawBackground()
{
    ofBackground(Map::SAND);
    ofSetColor(Map::AMBER);
    ofFill();
    int gridStep = 15;
    int rad = 3;
    for (int x = 0; x < MAP_WIDTH; x += gridStep)
    {
        for (int y = 0; y < MAP_WIDTH; y += gridStep)
        {
            ofDrawEllipse(x, y, rad, rad);
        }
    }
}

void Map::printMap()
{
    ofLog() << "printing image";
    ofPixels pix;
    ofImage img;
    pix.allocate(MAP_WIDTH, MAP_HEIGHT, OF_PIXELS_RGB);
    img.allocate(MAP_WIDTH, MAP_HEIGHT, OF_IMAGE_COLOR);

    fbo.readToPixels(pix);
    img.setFromPixels(pix);

    if (mode == "dev")
    {
        img.save(ofGetTimestampString() + "_map.png");
        img.save("map.png");
    }
    else if (mode == "prod")
    {
        img.save("/var/www/" + ofGetTimestampString() + "_map.png");
        img.save("/var/www/map.png");
    }
    else
    {
        ofLog() << "Wrong mode specified, not writing to file";
    }
}