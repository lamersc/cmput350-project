#ifndef BEZIER_H
#define BEZIER_H

#include "MathUtil.h"

#include <vector>

namespace CMPUT350 {


/**
 * @brief Evaluates cubic Bezier curves built from sequences of control points.
 * @details Each curve segment uses 4 control points. Passing k*3+1 points
 * defines k segments, and valid parameter values cover 0 <= t <= k. The class
 * can be used statically or instantiated with a stored set of points.
 */
class Bezier {
public:
	/**
	 * @brief Creates a Bezier curve from a sequence of control points.
	 * @param pts Control points. Point count must be 3*k+1 for k segments.
	 * @return No return value. The constructor stores the points.
	 */
	Bezier(const std::vector<Point2D> &pts);

	/**
	 * @brief Gets the curve position at parameter t.
	 * @param t Curve parameter. Integer part selects the segment.
	 * @return Point on the curve for the given parameter.
	 */
	Point2D GetPoint(float t) const;

	/**
	 * @brief Gets the curve tangent direction at parameter t.
	 * @param t Curve parameter. Integer part selects the segment.
	 * @return Tangent vector of the curve at the given parameter.
	 */
	Point2D GetSlope(float t) const;

	/**
	 * @brief Gets the curve position at parameter t without a stored curve.
	 * @param pts Control points. Point count must be 3*k+1 for k segments.
	 * @param t Curve parameter. Integer part selects the segment.
	 * @return Point on the curve for the given parameter.
	 */
	static Point2D GetPoint(const std::vector<Point2D> &pts, float t);

	/**
	 * @brief Gets the curve tangent direction at parameter t without a stored curve.
	 * @param pts Control points. Point count must be 3*k+1 for k segments.
	 * @param t Curve parameter. Integer part selects the segment.
	 * @return Tangent vector of the curve at the given parameter.
	 */
	static Point2D GetSlope(const std::vector<Point2D> &pts, float t);

private:
	std::vector<Point2D> mPts;
};
}

#endif
