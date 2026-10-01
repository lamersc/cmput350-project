#include "DrawContext.h"

namespace CMPUT350 {

/**
 * @brief Creates a draw context for the given window and font.
 * @param window Shared pointer to the render window.
 * @param font Shared pointer to the font.
 * @return No return value.
 */
DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

/**
 * @brief Draws text centered at the given position.
 * @param text Text to draw.
 * @param pixelSize Character size in pixels.
 * @param p Center position of the text.
 * @param c Text color.
 * @return No return value.
 */
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

/**
 * @brief Draws text with the top-left corner at the given position.
 * @param text Text to draw.
 * @param pixelSize Character size in pixels.
 * @param p Top-left position of the text.
 * @param c Text color.
 * @return No return value.
 */
void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text textObject(*mFont, text);
    textObject.setCharacterSize(pixelSize);
    textObject.setPosition({p.x, p.y});
    textObject.setFillColor({c.r, c.g, c.b});
    mWindow->draw(textObject);
}

/**
 * @brief Draws a filled circle.
 * @param p Center position of the circle.
 * @param radius Circle radius in pixels.
 * @param c Fill color.
 * @return No return value.
 */
void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition({p.x, p.y});
    circle.setFillColor({c.r, c.g, c.b});
    mWindow->draw(circle);
}

/**
 * @brief Draws a filled rectangle.
 * @param r Rectangle position and size.
 * @param c Fill color.
 * @return No return value.
 */
void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rect({r.width, r.height});
    rect.setPosition({r.topLeft.x, r.topLeft.y  });
    rect.setFillColor({c.r, c.g, c.b});
    mWindow->draw(rect);
}

/**
 * @brief Draws a rectangle outline.
 * @param r Rectangle position and size.
 * @param width Outline thickness in pixels.
 * @param c Outline color.
 * @return No return value.
 */
void DrawContext::FrameRect(Rect r, float width, RGBColor c) {
    sf::RectangleShape rect({r.width, r.height});
    rect.setPosition({r.topLeft.x, r.topLeft.y  });
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(width);
    rect.setOutlineColor({c.r, c.g, c.b});
    mWindow->draw(rect);
}

/**
 * @brief Draws a thick line between two points.
 * @param from Start position of the line.
 * @param to End position of the line.
 * @param width Line thickness in pixels.
 * @param c Line color.
 * @return No return value.
 * @details The method builds a four-corner polygon around the center line.
 */
void DrawContext::DrawLine(Point2D from, Point2D to, float width, RGBColor c) {
    sf::ConvexShape convex;
    // A perpendicular vector with half-width length gives the polygon edges.
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

/**
 * @brief Gets the current window width.
 * @param None.
 * @return Window width in pixels.
 */
int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

/**
 * @brief Gets the current window height.
 * @param None.
 * @return Window height in pixels.
 */
int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

}  // namespace CMPUT350
