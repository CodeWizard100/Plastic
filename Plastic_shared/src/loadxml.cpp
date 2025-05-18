#include "loadxml.h"
void loadxml(  int* width,   int* height,   int* fullscreen,   int* borderless,   int* vsync,   int* msaa,   int* msaa_count, int* msaa_quality) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError eResult = doc.LoadFile("config.xml");
    if (eResult != tinyxml2::XML_SUCCESS) {
        printf("Error loading Config file: %s\n", doc.ErrorIDToName(eResult));
        return;
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    if (root == nullptr) {
        printf("Error: No root element found in XML file.\n");
        return;
    }

    tinyxml2::XMLElement* windowElement = root->FirstChildElement("window");
    if (windowElement == nullptr) {
        printf("Error: No window element found in XML file.\n");
        return;
    }

    windowElement->QueryIntAttribute("width", width);
    windowElement->QueryIntAttribute("height", height);
    windowElement->QueryIntAttribute("fullscreen", fullscreen);
    windowElement->QueryIntAttribute("borderless", borderless);
    windowElement->QueryIntAttribute("vsync", vsync);
    windowElement->QueryIntAttribute("msaa", msaa);
    windowElement->QueryIntAttribute("msaa_count", msaa_count);
    windowElement->QueryIntAttribute("msaa_quality", msaa_quality);
}