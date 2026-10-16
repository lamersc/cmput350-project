#include "Bezier.h"

#include <algorithm>
#include <assert.h>

namespace CMPUT350 {
namespace {

int SegmentCount(size_t pointCount) {
    return static_cast<int>((pointCount - 1) / 3);
}

}  // namespace

Bezier::Bezier(const std::vector<Point2D>& pts) : mPts(pts) {}

Point2D Bezier::GetPoint(float t) const { return GetPoint(mPts, t); }

Point2D Bezier::GetSlope(float t) const { return GetSlope(mPts, t); }

Point2D Bezier::GetPoint(const std::vector<Point2D>& pts, float t) {
    const int segments = SegmentCount(pts.size());
    assert(segments >= 1);
    const int segment = std::min(static_cast<int>(t), segments - 1);
    const float u = t - segment;
    Point2D pointA = Line::Tween(pts[3 * segment], pts[3 * segment + 1], u);
    Point2D pointB = Line::Tween(pts[3 * segment + 1], pts[3 * segment + 2], u);
    Point2D pointC = Line::Tween(pts[3 * segment + 2], pts[3 * segment + 3], u);
    pointA = Line::Tween(pointA, pointB, u);
    pointB = Line::Tween(pointB, pointC, u);
    return Line::Tween(pointA, pointB, u);
}

Point2D Bezier::GetSlope(const std::vector<Point2D>& pts, float t) {
    const int segments = SegmentCount(pts.size());
    assert(segments >= 1);
    const int segment = std::min(static_cast<int>(t), segments - 1);
    const float u = t - segment;
    Point2D pointA = pts[3 * segment + 1] - pts[3 * segment];
    Point2D pointB = pts[3 * segment + 2] - pts[3 * segment + 1];
    Point2D pointC = pts[3 * segment + 3] - pts[3 * segment + 2];
    pointA = Line::Tween(pointA, pointB, u);
    pointB = Line::Tween(pointB, pointC, u);
    return Line::Tween(pointA, pointB, u) * 3.0f;
}
}  // namespace CMPUT350
