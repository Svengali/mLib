#pragma once

#ifndef _PLANE_H_
#define _PLANE_H_

namespace ml {

template<class FloatType>
class Plane {
public:
	Plane() {

	}

	Plane(const vec3<FloatType>& p0, const vec3<FloatType>& p1, const vec3<FloatType>& p2) {
		const vec3<FloatType> p[] = {p0,p1,p2};
		createFromPoints(p);
	}

	Plane(const vec3<FloatType> *points) {
		createFromPoints(points);
	}

	Plane(const vec3<FloatType>& normal, FloatType dist) {
		m_Normal = normal;
		m_Distance = dist;
	}

	Plane(const vec3<FloatType>& normal, const vec3<FloatType>& p) {
		m_Normal = normal;
		m_Distance = m_Normal | p;
	}

	inline vec3<FloatType> getNormal() const {
		return m_Normal;
	}

	inline FloatType getDistance() const {
		return m_Distance;
	}

	inline FloatType distanceToPoint(const vec3<FloatType>& point) const {
		return (m_Normal | point) - m_Distance;
	}

	inline FloatType distanceToPointAbs(const vec3<FloatType>& point) const {
		return std::abs(distanceToPoint(point));
	}

	inline vec3<FloatType> projectPointToPlane(const vec3<FloatType>& point) const {
		return point - distanceToPoint(point) * getNormal();
	}

	inline static Plane<FloatType> xyPlane() {
		return Plane<FloatType>(vec3<FloatType>(0,0,1), 0);
	}
	inline static Plane<FloatType> xzPlane() {
		return Plane<FloatType>(vec3<FloatType>(0,1,0), 0);
	}
	inline static Plane<FloatType> yzPlane() {
		return Plane<FloatType>(vec3<FloatType>(1,0,0), 0);
	}

	inline Plane<FloatType> operator-() const {
		return Plane<FloatType>(-m_Normal, m_Distance);
	}

private:
	void createFromPoints( const vec3<FloatType>* points ) 
	{
		m_Normal = ((points[1] - points[0])^(points[2] - points[0])).getNormalized();
		m_Distance = (m_Normal | points[0]);
		//make sure normal points away from origin (i.e., distance is positive)
		if (m_Distance < (FloatType)0) {
			m_Distance = -m_Distance;
			m_Normal = -m_Normal;
		}	
	}

	vec3<FloatType> m_Normal;
	FloatType m_Distance;
};

typedef Plane<float> Planef;
typedef Plane<double> Planed;

} //namespace ml


#endif
