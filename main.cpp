/* CSCI261 Final Project: Shortest path
 * main file
 *
 * Author: Joseph Brownlee (jmbrownlee@mines.edu)
 *
 * see acknowledgements.md for resources used (Math Professors, other students, online forums, etc)
 */

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
using namespace std;

#include "class/World.h"
#include "class/coord.hpp"

//#include "funct/hue.cpp"
sf::Color hsv(int hue, float sat=1, float val=1); // hue function for visual display of height

int main() {

    // preset inputs "fileName, heightCoeff, start(x,y), end(x,y) "
//    std::string stringvalues = "testSurface1w.txt 6  1 3 1 1";
//    std::string stringvalues = "testSurface1a.txt 5  9 5 0 13";
//    std::string stringvalues = "testSurface1a.txt 4  9 0 9 14";
//    std::string stringvalues = "mazeTestNoisy.txt 1.5 0 0 7 9"; // maze

//    std::istringstream iss (stringvalues);
//    istream& input = iss;
    istream& input = cin;

    // request file name
    string fileName;
    cout << "fileName: ";
//    fileName = "mazeTest.txt";
//    fileName = "testSurface1a.txt";
    input >> fileName;
    cout << '(' << fileName << ")\n";

    // create surface based on our file
    World mountain(fileName);
//    World mountain("testSurface1a.txt");

    // request height coefficient
    float coeff;
    cout << "heightCoefficient: ";
    input >> coeff;
    if ( mountain.setHeightCoeff(coeff) ) {
        cout << "error: height coefficient failed to set";
    }
    cout << '(' << mountain.getHeightCoeff() << ")\n";


    // validate surface
    if (!mountain.valid()) {
        cout << "Surface is invalid and may cause unexpected behavior. Continue anyway?";
        string answer;
        cin >> answer;
        // check if answer is a yes
        bool yes = false;
        if (!answer.empty()) {
            const char a = answer[0];
            if (a == 'y' || a == 'Y' || (a >= '1' && a <= '9') ) // y, Y, [any digit not zero]
                yes = true;
        }

        if (!yes) return 0; // exit program unless user approved
    }

    // display surface to text out
    cout << "\nread surface." << endl;
    mountain.exportSurface(cout);

    // request start and end points
    coord<unsigned short> start, end;
    cout << "start point (x y) ";
    input >> start; // take 2 integers from stream
    cout << '(' << start.x << ' ' << start.y << ")\n";
    cout << "end point (x y) ";
    input >> end;
    cout << '(' << end.x << ' ' << end.y << ")\n";

    cout << endl << endl;


    // calculate shortest path
    vector<coord<unsigned short>> bestPath = mountain.getBestPath(start, end);

    // display shortest path to text out
    if (bestPath.empty()) {
        cout << "could not find a valid path." << endl;
        return 0;
    } // else:
    for(auto node : bestPath) {
        cout << "(" << node.x << ", " << node.y << ")" << endl;
    }


    /** display data in SFML window **/
//{
//    using namespace sf;

    // parameters used in visual display
    const short MAX_HUE = 300; // highest hue (300 = pink)
    const sf::Vector2<unsigned> WINDOW_SIZE = {720, 640}; // SFML window

    const sf::Vector2<unsigned> SURFACE_SIZE = {640, 600}; // area to show mountain or maze surface

    // create window object
    sf::RenderWindow window(sf::VideoMode( WINDOW_SIZE.x, WINDOW_SIZE.y ), "SFML Example Window");

    // draw hue key (gradient) on side for easier reading
    sf::RectangleShape gradient;
    const float GRADIENT_HEIGHT = (float)WINDOW_SIZE.y / MAX_HUE;
    gradient.setSize({40, GRADIENT_HEIGHT} ); // hue key fills right side of window
    for (int i = 0; i < MAX_HUE; ++i) {
        gradient.setPosition(WINDOW_SIZE.x-40, GRADIENT_HEIGHT * i);
        gradient.setFillColor(hsv(MAX_HUE - i)); // starting at top, go from highest to lowest hue
        window.draw(gradient);
    }

//    float COL_COUNT = mountain.getSize().y;
//    float ROW_COUNT = mountain.getSize().x;
    const auto Surf_size = mountain.getSize();
    /* draw pixel for each point */
    // properties that all pixels share:
    sf::RectangleShape pix;
    const sf::Vector2<float> PSIZE = {
            (float)SURFACE_SIZE.x / Surf_size.y, // note: surface points stored with x and y reversed
            (float)SURFACE_SIZE.y / Surf_size.x
    };
    pix.setSize(PSIZE);

    int heightRange = mountain.getHeightRange().y - mountain.getHeightRange().x;
    int heightMin = mountain.getHeightRange().x;

    // draw base state of each pixel:
    for (unsigned i = 0; i < Surf_size.x; ++i) {
        for (unsigned j = 0; j < Surf_size.y; ++j) {
            // set position and color based on location and height
            pix.setPosition(PSIZE.x*j, PSIZE.y*i);
            pix.setFillColor(hsv( // set color so min -> 0 (red), max -> MAX_HUE (pink)
                    MAX_HUE * (mountain.getPoint(i, j).getHeight() - heightMin) / heightRange ));

            window.draw(pix); // draw this pixel
        }
    }
    window.display(); // show all on screen

    // draw loop: while our window is open, keep it open
    while( window.isOpen() ) {

        // HANDLE EVENTS
        sf::Event event;
        while( window.pollEvent(event) ) { // ask the window if any events occurred

            switch(event.type) {
                case sf::Event::Closed: // if event type is a closed event (X in window)
                    window.close();                 // then close our window
                    break;

                case sf::Event::KeyReleased:
                    // draw darker version of each pixel in path
                    for (const auto &node : bestPath) {
                        const auto i = node.x;
                        const auto j = node.y;
                        pix.setPosition(PSIZE.x * j, PSIZE.y * i);
                        pix.setFillColor(hsv( // set color so min -> 0 (red), max -> 300 (pink)
                                300 * (mountain.getPoint(i, j).getHeight() - heightMin) / heightRange,
                                1 , .5));

                        window.draw(pix); // draw this pixel
                    }
                    window.display();

                    break;
            }
        }

    }

//} // end sf namespace

    return 0;
}