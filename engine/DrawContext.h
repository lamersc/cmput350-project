#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include <cstdint>

#include "MathUtil.h"
#include <SFML/Graphics.hpp>

namespace CMPUT350 {

struct RGBColor {
    uint8_t r, g, b;
    /**
     * @brief Creates a color from red, green, and blue values.
     * @param r Red component from 0 to 255.
     * @param g Green component from 0 to 255.
     * @param b Blue component from 0 to 255.
     * @return No return value. The constructor initializes the color.
     */
    RGBColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

namespace Colors {

const RGBColor red(255, 0, 0);
const RGBColor green(0, 255, 0);
const RGBColor blue(0, 0, 255);
const RGBColor yellow(255, 255, 0);
const RGBColor cyan(0, 255, 255);
const RGBColor magenta(255, 0, 255);
const RGBColor white(255, 255, 255);
const RGBColor black(0, 0, 0);
const RGBColor gray(100, 100, 100);
const RGBColor grey(200, 200, 200);

}  // namespace Colors

class DrawContext {
public:
    /**
     * @brief Creates a draw context for the given window and font.
     * @param mWindow Shared pointer to the render window.
     * @param font Shared pointer to the font.
     * @return No return value. The constructor stores the window and font.
     */
    DrawContext(std::shared_ptr<sf::RenderWindow> mWindow, std::shared_ptr<sf::Font> font);
    /**
     * @brief Draws text with the top-left corner at the given position.
     * @param text Text to draw.
     * @param pixelSize Character size in pixels.
     * @param p Top-left position of the text.
     * @param c Text color.
     * @return No return value.
     */
    void DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c);
    /**
     * @brief Draws text centered at the given position.
     * @param text Text to draw.
     * @param pixelSize Character size in pixels.
     * @param p Center position of the text.
     * @param c Text color.
     * @return No return value.
     */
    void DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c);
    /**
     * @brief Draws a filled circle.
     * @param p Center position of the circle.
     * @param radius Circle radius in pixels.
     * @param c Fill color.
     * @return No return value.
     */
    void DrawCircle(Point2D p, float radius, RGBColor c);
    /**
     * @brief Draws a filled rectangle.
     * @param r Rectangle position and size.
     * @param c Fill color.
     * @return No return value.
     */
    void DrawRect(Rect r, RGBColor c);
    /**
     * @brief Draws a rectangle outline.
     * @param r Rectangle position and size.
     * @param width Outline thickness in pixels.
     * @param c Outline color.
     * @return No return value.
     */
    void FrameRect(Rect r, float width, RGBColor c);
    /**
     * @brief Draws a thick line between two points.
     * @param from Start position of the line.
     * @param to End position of the line.
     * @param width Line thickness in pixels.
     * @param c Line color.
     * @return No return value.
     */
    void DrawLine(Point2D from, Point2D to, float width, RGBColor c);
    /**
     * @brief Gets the current window width.
     * @param None.
     * @return Window width in pixels.
     */
    int GetWindowWidth();
    /**
     * @brief Gets the current window height.
     * @param None.
     * @return Window height in pixels.
     */
    int GetWindowHeight();

private:
    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<sf::Font> mFont;
};

}  // namespace CMPUT350

#endif  // RENDERTARGET_H
