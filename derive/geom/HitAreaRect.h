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
		class HitAreaRect: public HitArea {
		public:
            /**
             * @brief Construct a new empty shape
             * 
             */
            HitAreaRect(): HitArea(){}

            /**
             * @brief Construct a new Hit Area Circle object
             * 
             * @param x The x coordinate of the center
             * @param y The y coordinate of the center
             * @param radius The radius
             */
            HitAreaRect( double x, double y, double w, double h ):HitArea(x,y){
                this->width = w;
                this->height = h;
            }

			/**
			 * @brief Destroy the shape
			 */
			virtual ~HitAreaRect(){}

            /**
             * @brief Width of shape
             * 
             */
            double width = 0;

            /**
             * @brief Height of shape
             * 
             */
            double height = 0;

			/**
			 * @brief Check if the point is within the shape
			 * @param p The point to check
			 */
			virtual bool hit( Point* p ){
                return (p->x >= x) && (p->x <= (x + width)) && (p->y >= y) && (p->y <= (y + height));
            }

		};

	} // geom
} // derive