#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <iostream>

namespace CMPUT350 {

struct Point2D {
    float x, y;
    /**
     * @brief Creates a point with the given coordinates.
     * @param x Horizontal coordinate. Default is 0.
     * @param y Vertical coordinate. Default is 0.
     * @return No return value. The constructor initializes the point.
     */
    Point2D(float x = 0, float y = 0) : x(x), y(y) {}
    /**
     * @brief Measures Euclidean distance to a different point.
     * @param other Target point.
     * @return Distance as a double value.
     */
    double Distance(const Point2D &other) const {

        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
    /**
     * @brief Adds two points coordinate by coordinate.
     * @param other Point to add.
     * @return New point with summed coordinates.
     */
    Point2D operator+(const Point2D &other) const {
        return Point2D(this->x + other.x, this->y + other.y);
    }
    /**
     * @brief Adds a scalar to both coordinates.
     * @param other Scalar value to add.
     * @return New point with increased coordinates.
     */
    Point2D operator+(const float &other) const {
        return Point2D(this->x + other, this->y + other);
    }
    /**
     * @brief Subtracts a different point coordinate by coordinate.
     * @param other Point to subtract.
     * @return New point with subtracted coordinates.
     */
    Point2D operator-(const Point2D &other) const {
        return Point2D(this->x - other.x, this->y - other.y);
    }
    /**
     * @brief Subtracts a scalar from both coordinates.
     * @param other Scalar value to subtract.
     * @return New point with decreased coordinates.
     */
    Point2D operator-(const float &other) const {
        return Point2D(this->x - other, this->y - other);
    }
    /**
     * @brief Multiplies both coordinates by a scalar.
     * @param scalar Scalar multiplier.
     * @return New scaled point.
     */
    Point2D operator*(const float &scalar) const {
        return Point2D(this->x * scalar, this->y * scalar);
    }
    /**
     * @brief Adds a scalar to this point in place.
     * @param scalar Scalar value to add.
     * @return Reference to this point after the change.
     */
    Point2D &operator+=(const float &scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }
    /**
     * @brief Adds a different point to this point in place.
     * @param other Point to add.
     * @return Reference to this point after the change.
     */
    Point2D &operator+=(const Point2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    /**
     * @brief Subtracts a different point from this point in place.
     * @param other Point to subtract.
     * @return Reference to this point after the change.
     */
    Point2D &operator-=(const Point2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    /**
     * @brief Compares two points for equality.
     * @param other Point to compare.
     * @return True if both coordinates match. False if not.
     */
    bool operator==(const Point2D &other) const {

        return x == other.x && y == other.y;
    }
    /**
     * @brief Multiplies this point by an integer scalar in place.
     * @param scalar Integer multiplier.
     * @return Reference to this point after the change.
     */
    Point2D &operator*=(const int &scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    /**
     * @brief Divides this point by an integer scalar in place.
     * @param scalar Integer divisor. The value must not be zero.
     * @return Reference to this point after the change.
     */
    Point2D &operator/=(const int &scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    /**
     * @brief Computes the dot product with a different point.
     * @param other Point to combine.
     * @return Dot product as a float value.
     */
    float operator*(const Point2D &other) const {
        return Dot(other);
    }
    /**
     * @brief Computes the dot product with point b.
     * @param b Point to combine.
     * @return Dot product as a float value.
     */
    float Dot(Point2D b) const {
        return x * b.x + y * b.y;
    }
    /**
     * @brief Computes the dot product of points a and b.
     * @param a First point.
     * @param b Second point.
     * @return Dot product as a float value.
     */
    static float Dot(Point2D a, Point2D b) {
        return a.Dot(b);
    }
    /**
     * @brief Computes the 2D cross product of points a and b.
     * @param a First point.
     * @param b Second point.
     * @return Cross product as a float value.
     */
    static float Cross(Point2D a, Point2D b) {
        return a.x * b.y - a.y * b.x;
    }
    /**
     * @brief Scales this point to unit length.
     * @param None.
     * @return No return value. The point keeps its direction.
     */
    void Normalize() {
        const float length = sqrt(x * x + y * y);
        x /= length;
        y /= length;
    }
};

/**
 * @brief Writes a point to an output stream.
 * @param os Output stream.
 * @param p Point to write.
 * @return Reference to the output stream.
 */
static std::ostream &operator<<(std::ostream &os, const Point2D &p) {
    os << "Point2D(" << p.x << ", " << p.y << ")";
    return os;
}

/**
 * @brief Multiplies a point by a scalar from the left side.
 * @param number Scalar multiplier.
 * @param rhs Point to scale.
 * @return New scaled point.
 */
static Point2D operator*(float number, const Point2D &rhs) {
    return Point2D(number * rhs.x, number * rhs.y);
}

struct Line {
    Point2D p1, p2;

    /**
     * @brief Creates a line from two points.
     * @param p1 Start point. Default is origin.
     * @param p2 End point. Default is origin.
     * @return No return value. The constructor initializes the line.
     */
    Line(Point2D p1 = {0, 0}, Point2D p2 = {0, 0}) : p1(p1), p2(p2) {}
    /**
     * @brief Creates a line from four coordinates.
     * @param x1 Start x coordinate.
     * @param y1 Start y coordinate.
     * @param x2 End x coordinate.
     * @param y2 End y coordinate.
     * @return No return value. The constructor initializes the line.
     */
    Line(float x1, float y1, float x2, float y2) : p1(x1, y1), p2(x2, y2) {}
    /**
     * @brief Measures the length of the line segment.
     * @param None.
     * @return Length as a float value.
     */
    float Length() const {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }
    /**
     * @brief Finds the nearer endpoint to point p.
     * @param p Query point.
     * @return Copy of p1 or p2, whichever is nearer.
     */
    Point2D ClosestPoint(const Point2D &p) const {
        double p1Distance = p1.Distance(p);
        double p2Distance = p2.Distance(p);
        return p1Distance < p2Distance ? p1 : p2;
    }
    /**
     * @brief Tests if this segment crosses a different segment.
     * @param other Second line segment.
     * @param crossingPoint Output location of the crossing. Valid only if true.
     * @return True if the segments cross. False if parallel or outside range.
     */
    bool Crosses(Line other, Point2D &crossingPoint) const {
        // (Chris) I want to note this thinking isn't completely original, and
        // I am likely heavily influenced by the answer at:
        // https://stackoverflow.com/a/3838357
        //
        // While I do like the more efficient answer they have on the site, I have
        // yet to build an intuitive understanding of that answer, and so wanted
        // to implement something I could explain

        // (Chris) note I don't check for the case where two lines perfectly overlap with
        // an infinite number of points

        // (Chris) now my high level understanding of this problem is
        // if the lines do intersect, we'll have two equations with a shared
        // point U, such that the intersection of the two is defined as:
        // p1 + ɑ*(p2 - p1) = other.p1 + b*(other.p2 - other.p1), where a, b ∈ [0, 1].
        // p1 - other.p1 = b*(other.p2 - other.p1) - ɑ*(p2 - p1)

        Point2D offset1 = p2 - p1;
        Point2D offset2 = other.p2 - other.p1;
        Point2D p1Diff = p1 - other.p1;
        // p1Diff = b*(offset2) - ɑ*(offset1)
        // take the cross product with offset1 on both sides now to cancel:
        // https://en.wikipedia.org/wiki/Cross_product#Algebraic_properties
        float lhsB = Point2D::Cross(p1Diff, offset1);
        float rhsB = Point2D::Cross(offset2, offset1);
        if (rhsB == 0)
            return false;

        float b = lhsB / rhsB;

        float lhsA = Point2D::Cross(offset1, offset2);
        float rhsA = Point2D::Cross(other.p1 - p1, offset2);
        if (lhsA == 0)
            return false;

        float a = rhsA / lhsA;

        if (a < 0 || a > 1 || b < 0 || b > 1)
            // lines meet at point outside of our segment range
            return false;

        crossingPoint = p1 + a * offset1;

        return true;
    }
};

/**
 * @brief Writes a line to an output stream.
 * @param os Output stream.
 * @param l Line to write.
 * @return Reference to the output stream.
 */
static std::ostream &operator<<(std::ostream &os, const Line &l) {
    os << "Line(" << l.p1 << ", " << l.p2 << ")";
    return os;
}

struct Circle {
    Point2D center;
    float radius;

    /**
     * @brief Creates a circle from a center point and a radius.
     * @param c Center point. Default is origin.
     * @param r Radius value. Default is 0.
     * @return No return value. The constructor initializes the circle.
     */
    Circle(Point2D c = {0, 0}, float r = 0) : center(c), radius(r) {}

    /**
     * @brief Creates a circle from coordinates and a radius.
     * @param x Center x coordinate.
     * @param y Center y coordinate.
     * @param r Radius value.
     * @return No return value. The constructor initializes the circle.
     */
    Circle(float x, float y, float r) : center(x, y), radius(r) {}
};

struct Rect {
    Point2D topLeft;
    float width, height;

    /**
     * @brief Creates a rectangle from position and size.
     * @param left Left edge position.
     * @param top Top edge position.
     * @param width Rectangle width.
     * @param height Rectangle height.
     * @return No return value. The constructor initializes the rectangle.
     */
    Rect(float left, float top, float width, float height)
        : topLeft(Point2D(left, top)), width(width), height(height) {}

    /**
     * @brief Creates a rectangle from a corner point and size.
     * @param tl Top-left corner. Default is origin.
     * @param w Width value. Default is 0.
     * @param h Height value. Default is 0.
     * @return No return value. The constructor initializes the rectangle.
     */
    Rect(Point2D tl = {0, 0}, int w = 0, int h = 0) : topLeft(tl), width(w), height(h) {}

    /**
     * @brief Creates a bounding box around points p1 and p2.
     * @param p1 First corner point.
     * @param p2 Second corner point.
     * @return No return value. The width and height stay positive.
     */
    Rect(Point2D p1, Point2D p2)
        : topLeft(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
          width(fabs(p1.x - p2.x)),
          height(fabs(p1.y - p2.y)) {}

    /**
     * @brief Creates a square around a center point.
     * @param center Center point of the square.
     * @param radius Half of the side length.
     * @return No return value. The constructor initializes the rectangle.
     */
    Rect(Point2D center, float radius)
        : topLeft(center.x - radius, center.y - radius), width(2 * radius), height(2 * radius) {}

    /**
     * @brief Expands this rectangle to include a different rectangle.
     * @param other Rectangle to include.
     * @return Reference to this rectangle after the change.
     */
    Rect &operator|=(const Rect &other) {
        float left = std::min(topLeft.x, other.topLeft.x);
        float top = std::min(topLeft.y, other.topLeft.y);
        float right = std::max(topLeft.x + width, other.topLeft.x + other.width);
        float bottom = std::max(topLeft.y + height, other.topLeft.y + other.height);
        topLeft = Point2D(left, top);
        width = right - left;
        height = bottom - top;
        return *this;
    }
    /**
     * @brief Expands this rectangle to include a point.
     * @param other Point to include.
     * @return Reference to this rectangle after the change.
     */
    Rect &operator|=(const Point2D &other) {
        float left = std::min(topLeft.x, other.x);
        float top = std::min(topLeft.y, other.y);
        float right = std::max(topLeft.x + width, other.x);
        float bottom = std::max(topLeft.y + height, other.y);
        topLeft = Point2D(left, top);
        width = right - left;
        height = bottom - top;
        return *this;
    }
    /**
     * @brief Expands this rectangle to include a line.
     * @param other Line to include.
     * @return Reference to this rectangle after the change.
     */
    Rect &operator|=(const Line &other) {
        *this |= other.p1;
        *this |= other.p2;
        return *this;
    }
    /**
     * @brief Reduces this rectangle to the intersection area.
     * @param other Rectangle to intersect.
     * @return Reference to this rectangle after the change.
     */
    Rect &operator&=(const Rect &other) {
        float left = std::max(topLeft.x, other.topLeft.x);
        float top = std::max(topLeft.y, other.topLeft.y);
        float right = std::min(topLeft.x + width, other.topLeft.x + other.width);
        float bottom = std::min(topLeft.y + height, other.topLeft.y + other.height);
        topLeft = Point2D(left, top);
        width = std::max(0.0f, right - left);
        height = std::max(0.0f, bottom - top);
        return *this;
    }
    /**
     * @brief Moves this rectangle by a point offset in place.
     * @param other Offset to add to the top-left corner.
     * @return Reference to this rectangle after the change.
     */
    Rect &operator+=(const Point2D &other) {
        topLeft += other;
        return *this;
    }
    /**
     * @brief Returns a copy of this rectangle moved by an offset.
     * @param other Offset to add to the top-left corner.
     * @return New moved rectangle.
     */
    Rect operator+(const Point2D &other) const {
        Rect copy = *this;
        copy += other;
        return copy;
    }
    /**
     * @brief Shrinks the rectangle on all sides.
     * @param inset Number of pixels to remove from each side.
     * @return No return value.
     */
    void Inset(int inset) {
        topLeft.x += inset;
        topLeft.y += inset;
        width -= 2 * inset;
        height -= 2 * inset;
    }
    /**
     * @brief Tests if a point is inside the rectangle.
     * @param p Point to test.
     * @return True if the point is inside or on the edge. False if not.
     */
    bool IsInside(const Point2D &p) const {
        return p.x >= topLeft.x && p.x <= topLeft.x + width &&
               p.y >= topLeft.y && p.y <= topLeft.y + height;
    }
};

/**
 * @brief Writes a rectangle to an output stream.
 * @param os Output stream.
 * @param l Rectangle to write.
 * @return Reference to the output stream.
 */
static std::ostream &operator<<(std::ostream &os, const Rect &l) {
    os << "Rect(" << l.topLeft << ", " << l.width << ", " << l.height << ")";
    return os;
}

}  // namespace CMPUT350

#endif  // MATHUTIL_H
