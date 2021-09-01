#pragma once

// Derive
#include "derive/geom/HitArea.h"

using namespace derive::geom;

namespace derive {
	namespace geom {

		/**
		 * @brief A class that describes a hit area
		 *
		 */
		class HitAreaCircle: public HitArea {
        protected:
			double _r = 0;
            double _r2 = 0;
		public:
            /**
             * @brief Construct a new empty shape
             * 
             */
            HitAreaCircle(): HitArea() {}

            /**
             * @brief Construct a new Hit Area Circle object
             * 
             * @param x The x coordinate of the center
             * @param y The y coordinate of the center
             * @param radius The radius
             */
            HitAreaCircle( double x, double y, double radius ) : HitArea(x,y) {
                this->radius( radius );
            }

			/**
			 * @brief Destroy the shape
			 */
			virtual ~HitAreaCircle(){}

            /**
			 * @brief Get the radius
			 * 
			 * @return double the radius
			 */
			virtual double radius() { return _r; }

			/**
			 * @brief Set the radius
			 * 
			 * @param v the radius
			 */
			virtual void radius( double v ) {
                _r = v;
                _r2 = _r*_r;
            }

			/**
			 * @brief Check if the point is within the shape
			 * @param p The point to check
			 */
			virtual bool hit( Point* p ) {
                double xx = x - p->x();
                double yy = y - p->y();
                return ( xx*xx + yy*yy ) <= _r2;
            }

		};

	} // geom
} // derive