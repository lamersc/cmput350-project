#include "DrawContext.h"

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text textObject(*mFont, text);
    textObject.setLineAlignment(sf::Text::LineAlignment::Center);
    textObject.setCharacterSize(pixelSize);
    const auto bounds = textObject.getLocalBounds();
    textObject.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    textObject.setPosition({p.x, p.y});
    textObject.setFillColor({c.r, c.g, c.b});
    mWindow->draw(textObject);
}

void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text textObject(*mFont, text);
    textObject.setCharacterSize(pixelSize);
    textObject.setPosition({p.x, p.y});
    textObject.setFillColor({c.r, c.g, c.b});
    mWindow->draw(textObject);
}

void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition({p.x, p.y});
    circle.setFillColor({c.r, c.g, c.b});
    mWindow->draw(circle);
}

void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rect({r.width, r.height});
    rect.setPosition({r.topLeft.x, r.topLeft.y  });
    rect.setFillColor({c.r, c.g, c.b});
    mWindow->draw(rect);
}

void DrawContext::FrameRect(Rect r, float width, RGBColor c) {
    sf::RectangleShape rect({r.width, r.height});
    rect.setPosition({r.topLeft.x, r.topLeft.y  });
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(width);
    rect.setOutlineColor({c.r, c.g, c.b});
    mWindow->draw(rect);
}

/**
 * @brief Draws a line between two points with a specified width and color.
 *
 * @param from The starting point of the line (Point2D).
 * @param to The ending point of the line (Point2D).
 * @param width The width of the line in pixels.
 * @param c The color of the line, specified as an RGBColor object.
 *
 * This function calculates the distance and angle between the two points
 * and uses a polygone shape to represent the line. The line is drawn
 * relative to the world offset and rendered onto the associated window.
 */
void DrawContext::DrawLine(Point2D from, Point2D to, float width, RGBColor c) {
    sf::ConvexShape convex;
    Point2D perpendicular_slope(to.y - from.y, -(to.x - from.x));
    perpendicular_slope.Normalize();
    perpendicular_slope *= width / 2;

    Point2D corner1 = from + perpendicular_slope;
    Point2D corner2 = from - perpendicular_slope;
    Point2D corner3 = to - perpendicular_slope;
    Point2D corner4 = to + perpendicular_slope;
    convex.setPointCount(4);
    convex.setPoint(0, {corner1.x, corner1.y});
    convex.setPoint(1, {corner2.x, corner2.y});
    convex.setPoint(2, {corner3.x, corner3.y});
    convex.setPoint(3, {corner4.x, corner4.y});

    convex.setFillColor({c.r, c.g, c.b});

    mWindow->draw(convex);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

}  // namespace CMPUT350
