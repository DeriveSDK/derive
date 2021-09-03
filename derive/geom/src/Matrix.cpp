// Derive
#include "../Matrix.h"

namespace derive {
	namespace geom {

		Matrix::Matrix() {
			identity();
		}

		Matrix::Matrix( double scaleX, double scaleY, double rotation, double tx, double ty, double ox, double oy ) {
			if (rotation == 0) {
				a = 1.0; d = 1.0;
				b = 0.0; c = 0.0;
			} else {
				a = cos(rotation);
				b = sin(rotation);
				c = -b;
				d = a;
			}
			if (scaleX != 1) {
				a *= scaleX;
				c *= scaleX;
			}
			if (scaleY != 1) {
				b *= scaleY;
				d *= scaleY;
			}
			this->tx = tx - (ox * a + oy * c);
			this->ty = ty - (ox * b + oy * d);
		}

		void Matrix::apply( double scaleX, double scaleY, double rotation, double tx, double ty, double ox, double oy ) {
			Matrix* m = new Matrix( scaleX, scaleY, rotation, tx, ty, ox, oy );
			concat( m );
			delete m;
		}

		void Matrix::transform( Point* p ) {
			double px = a*p->x + c*p->y + tx;
			double py = b*p->x + d*p->y + ty;
			p->set( px, py );
		}

		void Matrix::transform( Point* from, Point* to ) {
			to->set( a*from->x + c*from->y + tx, b*from->x + d*from->y + ty );
		}

		Point* Matrix::transform( double x, double y ) {
			return new Point( a*x + c*y + tx, b*x + d*y + ty );
		}

		void Matrix::transform( Point* p, double originX, double originY ) {	
			transform( p );
		}

		void Matrix::inverseTransform( Point* p ) {
			double det = a * d - b * c;
			double dd = (0.0 == det) ? 1.0 : 1.0 / det;

			double ta = d * dd;
			double tb = -b * dd;
			double tc = -c * dd;
			double td = a * dd;
			double ttx = - (ta * tx + tc * ty);
			double tty = - (tb * tx + td * ty);

			p->set( ta*p->x + tc*p->y + ttx, tb*p->x + td*p->y + tty );
		}

		void Matrix::inverseTransform( Point* from, Point* to ) {
			to->copy( from );
			inverseTransform( to );
		}

		Point* Matrix::inverseTransform( double x, double y ) {
			double det = a * d - b * c;
			double dd = (0.0 == det) ? 1.0 : 1.0 / det;

			double ta = d * dd;
			double tb = -b * dd;
			double tc = -c * dd;
			double td = a * dd;
			double ttx = - (ta * tx + tc * ty);
			double tty = - (tb * tx + td * ty);

			return new Point( ta*x + tc*y + ttx, tb*x + td*y + tty );
		}

		void Matrix::inverseTransform( Point* p, double ox, double oy ) {
			translate( -ox, -oy );
			inverseTransform( p );
			translate( ox, oy );
		}

		void Matrix::concat( Matrix* m ) {
			double ta = a;
			double tb = b;
			double tc = c;
			double td = d;
			double ttx = tx;
			double tty = ty;

			a = ta * m->a + tc * m->b;
			b = tb * m->a + td * m->b;
			c = ta * m->c + tc * m->d;
			d = tb * m->c + td * m->d;
			tx = ta * m->tx + tc * m->ty + ttx;
			ty = tb * m->tx + td * m->ty + tty;
		}

		void Matrix::identity() {
			a = 1.0; d = 1.0;
			b = 0.0; c = 0.0; tx = 0.0; ty = 0.0;
		}

		void Matrix::invert() {
			double det = a * d - b * c;
			double dd = (0.0 == det) ? 1.0 : 1.0 / det;

			double ta = a;
			double tb = b;
			double tc = c;
			double td = d;
			double ttx = tx;
			double tty = ty;

			a = td * dd;
			b = -tb * dd;
			c = -tc * dd;
			d = ta * dd;

			tx = - (a * ttx + c * tty);
			ty = - (b * ttx + d * tty);
		}

		void Matrix::rotate( double angle ) {
			if (angle!=0) {
				double tcos = cos(angle);
				double tsin = sin(angle);

				double ta = a;
				double tb = b;
				double tc = c;
				double td = d;
				double ttx = tx;
				double tty = ty;

				a = ta*tcos - tb*tsin;
				b = ta*tsin + tb*tcos;
				c = tc*tcos - td*tsin;
				d = tc*tsin + td*tcos;
				tx = ttx*tcos - tty*tsin;
				ty = ttx*tsin + tty*tcos;
			}
		}

		void Matrix::rotate( double angle, double ox, double oy ) {
			rotate( angle );
			this->tx = tx - (ox * a + oy * c);
			this->ty = ty - (ox * b + oy * d);
		}

		void Matrix::scale( double sx, double sy ) {
			if (sx != 1.0) {
				a *= sx;
				c *= sx;
				tx *= sx;
			}
			if (sy != 1.0) {
				b *= sy;
				d *= sy;
				ty *= sy;
			}
		}

		void Matrix::translate( double dx, double dy ) {
			tx += dx;
			ty += dy;
			//tx += a * dx + c * dy;
			//ty += b * dx + d * dy;
		}

		Matrix* Matrix::clone() {
			Matrix* m = new Matrix();
			m->a = a;
			m->b = b;
			m->c = c;
			m->d = d;
			m->tx = tx;
			m->ty = ty;
			return m;
		}

		void Matrix::copy( Matrix* from ) {
			a = from->a;
			b = from->b;
			c = from->c;
			d = from->d;
			tx = from->tx;
			ty = from->ty;
		}

	} // ns:geom
} // ns:derive