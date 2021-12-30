/* CSCI261 Final Project: Shortest path
 * Hue function file
 *
 * Project Author: Joseph Brownlee (jmbrownlee)
 * Function original Author: [Tenry](https://en.sfml-dev.org/forums/index.php?action=profile;u=2463)
 */

#include <SFML/Graphics/Color.hpp>
/// @param hue color: 0-360° @param sat saturation: 0.f-1.f @param val brightness: 0.f-1.f
/// @source https://en.sfml-dev.org/forums/index.php?topic=7313.0
sf::Color hsv(int hue, float sat, float val) {
    /* // verification and defaulting of parameters, not needed.
    hue %= 360;
    while(hue<0) hue += 360;

    if(sat<0.f) sat = 0.f;
    if(sat>1.f) sat = 1.f;

    if(val<0.f) val = 0.f;
    if(val>1.f) val = 1.f;// */

    int h = hue/60;
    float f = float(hue)/60-h;
    float p = val*(1.f-sat);
    float q = val*(1.f-sat*f);
    float t = val*(1.f-sat*(1-f));

    switch(h) {
        default:
        case 0:
        case 6: return sf::Color(val*255, t*255, p*255);
        case 1: return sf::Color(q*255, val*255, p*255);
        case 2: return sf::Color(p*255, val*255, t*255);
        case 3: return sf::Color(p*255, q*255, val*255);
        case 4: return sf::Color(t*255, p*255, val*255);
        case 5: return sf::Color(val*255, p*255, q*255);
    }
}