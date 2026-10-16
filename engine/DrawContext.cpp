#include "DrawContext.h"

#include <numbers>

namespace CMPUT350 {

constexpr float radsToDegs = 180.0f / std::numbers::pi;

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
void DrawContext::DrawCenteredText(const std::string& text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text textObject(*mFont, text);
    textObject.setLineAlignment(sf::Text::LineAlignment::Center);
    textObject.setCharacterSize(pixelSize);
    const auto bounds = textObject.getLocalBounds();
    textObject.setOrigin(
        {bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    const Point2D screenPos = Transform(p);
    textObject.setPosition({screenPos.x, screenPos.y});
    textObject.setRotation(sf::degrees(mRotation * radsToDegs));
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
void DrawContext::DrawText(const std::string& text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text textObject(*mFont, text);
    textObject.setCharacterSize(pixelSize);
    const Point2D screenPos = Transform(p);
    textObject.setPosition({screenPos.x, screenPos.y});
    textObject.setRotation(sf::degrees(mRotation * radsToDegs));
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
    const Point2D screenPos = Transform(p);
    circle.setPosition({screenPos.x, screenPos.y});
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
    const Point2D screenPos = Transform(r.topLeft);
    rect.setPosition({screenPos.x, screenPos.y});
    rect.setRotation(sf::degrees(mRotation * radsToDegs));
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
    const Point2D screenPos = Transform(r.topLeft);
    rect.setPosition({screenPos.x, screenPos.y});
    rect.setRotation(sf::degrees(mRotation * radsToDegs));
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
    const Point2D screenFrom = Transform(from);
    const Point2D screenTo = Transform(to);
    // A perpendicular vector with half-width length gives the polygon edges.
    Point2D perpendicular_slope(screenTo.y - screenFrom.y, -(screenTo.x - screenFrom.x));
    perpendicular_slope.Normalize();
    perpendicular_slope *= width / 2;

    Point2D corner1 = screenFrom + perpendicular_slope;
    Point2D corner2 = screenFrom - perpendicular_slope;
    Point2D corner3 = screenTo - perpendicular_slope;
    Point2D corner4 = screenTo + perpendicular_slope;
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

void DrawContext::SetContextOffset(Point2D p) { mOffset = p; }

void DrawContext::SetContextRotation(float rotation) {
    mRotation = rotation;
    const float cosine = std::cos(rotation);
    const float sine = std::sin(rotation);
    mTransform = sf::Transform(cosine, -sine, 0.0f, sine, cosine, 0.0f, 0.0f, 0.0f, 1.0f);
    mInverseTransform = sf::Transform(cosine, sine, 0.0f, -sine, cosine, 0.0f, 0.0f, 0.0f, 1.0f);
}

Point2D DrawContext::Transform(Point2D p) {
    const sf::Vector2f rotated = mTransform.transformPoint({p.x, p.y});
    return Point2D(rotated.x + mOffset.x, rotated.y + mOffset.y);
}

Point2D DrawContext::ReverseTransform(Point2D p) {
    const sf::Vector2f local = mInverseTransform.transformPoint({p.x - mOffset.x, p.y - mOffset.y});
    return Point2D(local.x, local.y);
}

Rect DrawContext::Transform(Rect r) {
    const Point2D topLeft = r.topLeft;
    Rect bounds(Transform(topLeft), Transform(topLeft + Point2D(r.width, 0.0f)));
    bounds |= Transform(topLeft + Point2D(0.0f, r.height));
    bounds |= Transform(topLeft + Point2D(r.width, r.height));
    return bounds;
}

}  // namespace CMPUT350
