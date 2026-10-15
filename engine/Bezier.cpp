#include "Bezier.h"

#include <assert.h>

namespace CMPUT350 {
Bezier::Bezier(const std::vector<Point2D>& pts) : mPts(pts) {}

Point2D Bezier::GetPoint(float t) const { return GetPoint(mPts, t); }

Point2D Bezier::GetSlope(float t) const { return GetSlope(mPts, t); }

Point2D Bezier::GetPoint(const std::vector<Point2D>& pts, float t) {
    static std::vector<Point2D> tmp;
    assert(pts.size() > 1);
    tmp.clear();
    for (int x = 0; x < pts.size() - 1; x++)
        tmp.push_back(Line::Tween(pts[x], pts[x + 1], t));
    while (tmp.size() > 1) {
        for (int x = 0; x < tmp.size() - 1; x++)
            tmp[x] = Line::Tween(tmp[x], tmp[x + 1], t);
        tmp.pop_back();
    }
    return tmp[0];
}

Point2D Bezier::GetSlope(const std::vector<Point2D>& pts, float t) {
    assert(pts.size() > 1);
    if (pts.size() == 2)
        return pts[1] - pts[0];
    static std::vector<Point2D> tmp;
    tmp.clear();
    for (int x = 0; x < pts.size() - 1; x++)
        tmp.push_back(Line::Tween(pts[x], pts[x + 1], t));
    while (tmp.size() > 2) {
        for (int x = 0; x < tmp.size() - 1; x++)
            tmp[x] = Line::Tween(tmp[x], tmp[x + 1], t);
        tmp.pop_back();
    }
    return (tmp[1] - tmp[0]) * float(pts.size() - 1);
}
}  // namespace CMPUT350
