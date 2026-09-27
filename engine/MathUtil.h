#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <iostream>

namespace CMPUT350 {

struct Point2D {
    float x, y;
    Point2D(float x = 0, float y = 0) : x(x), y(y) {}
    double Distance(const Point2D &other) const {

        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
    Point2D operator+(const Point2D &other) const {
        return Point2D(this->x + other.x, this->y + other.y);
    }
    Point2D operator+(const float &other) const {
        return Point2D(this->x + other, this->y + other);
    }
    Point2D operator-(const Point2D &other) const {
        return Point2D(this->x - other.x, this->y - other.y);
    }
    Point2D operator-(const float &other) const {
        return Point2D(this->x - other, this->y - other);
    }
    Point2D operator*(const float &scalar) const {
        return Point2D(this->x * scalar, this->y * scalar);
    }
    Point2D &operator+=(const float &scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }
    Point2D &operator+=(const Point2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Point2D &operator-=(const Point2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    bool operator==(const Point2D &other) const {

        return x == other.x && y == other.y;
    }
    Point2D &operator*=(const int &scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Point2D &operator/=(const int &scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    float operator*(const Point2D &other) const {
        return Dot(other);
    }
    float Dot(Point2D b) const {
        return x * b.x + y * b.y;
    }
    static float Dot(Point2D a, Point2D b) {
        return a.Dot(b);
    }
    static float Cross(Point2D a, Point2D b) {
        return a.x * b.y - a.y * b.x;
    }
    void Normalize() {
        const float length = sqrt(x * x + y * y);
        x /= length;
        y /= length;
    }
};

static std::ostream &operator<<(std::ostream &os, const Point2D &p) {
    os << "Point2D(" << p.x << ", " << p.y << ")";
    return os;
}

static Point2D operator*(float number, const Point2D &rhs) {
    return Point2D(number * rhs.x, number * rhs.y);
}

struct Line {
    Point2D p1, p2;

    Line(Point2D p1 = {0, 0}, Point2D p2 = {0, 0}) : p1(p1), p2(p2) {}
    Line(float x1, float y1, float x2, float y2) : p1(x1, y1), p2(x2, y2) {}
    float Length() const {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }
    Point2D ClosestPoint(const Point2D &p) const {
        double p1Distance = p1.Distance(p);
        double p2Distance = p2.Distance(p);
        return p1Distance < p2Distance ? p1 : p2;
    }
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

static std::ostream &operator<<(std::ostream &os, const Line &l) {
    os << "Line(" << l.p1 << ", " << l.p2 << ")";
    return os;
}

struct Circle {
    Point2D center;
    float radius;

    Circle(Point2D c = {0, 0}, float r = 0) : center(c), radius(r) {}

    Circle(float x, float y, float r) : center(x, y), radius(r) {}
};

struct Rect {
    Point2D topLeft;
    float width, height;

    Rect(float left, float top, float width, float height)
        : topLeft(Point2D(top, left)), width(width), height(height) {}

    Rect(Point2D tl = {0, 0}, int w = 0, int h = 0) : topLeft(tl), width(w), height(h) {}

    // Creates bounding box around p1 and p2 with positive width/height
    Rect(Point2D p1, Point2D p2)
        : topLeft(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
          width(fabs(p1.x - p2.x)),
          height(fabs(p1.y - p2.y)) {}

    Rect(Point2D center, float radius)
        : topLeft(center.x - radius, center.y - radius), width(2 * radius), height(2 * radius) {}

    Rect &operator|=(const Rect &other) {
        // TODO: write this code
        return *this;
    }
    Rect &operator|=(const Point2D &other) {
        // TODO: write this code
        return *this;
    }
    Rect &operator|=(const Line &other) {
        // TODO: write this code
        return *this;
    }
    Rect &operator&=(const Rect &other) {
        // TODO: write this code
        return *this;
    }
    Rect &operator+=(const Point2D &other) {
        // TODO: write this code
        return *this;
    }
    Rect operator+(const Point2D &other) const {
        // TODO: write this code
        return *this;
    }
    void Inset(int inset) {
        // TODO: write this code
    }
    bool IsInside(const Point2D &p) const {
        // TODO: write this code
        return false;
    }
};

static std::ostream &operator<<(std::ostream &os, const Rect &l) {
    // TODO: write this code
    return os;
}

}  // namespace CMPUT350

#endif  // MATHUTIL_H
