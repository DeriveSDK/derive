#pragma once

// Derive
#include "derive/events/KeyEvent.h"

namespace derive {
	namespace events {

		/**
		 * @brief Events that relate to mouse actions
		 *
		 */
		class MouseEvent : public KeyEvent {
		public:
			MouseEvent() : KeyEvent() { }
			MouseEvent( int type ) : KeyEvent( type ) { }
			MouseEvent( int type, void* target ) : KeyEvent( type, target ) { }

			// Mouse moves over an object
			static const int Over = 100;
			// Mouse moves out of an object
			static const int Out = 101;
			// Mouse changes position
			static const int Move = 102;

			// Left button clicked
			static const int Click = 103;
			// Left button double clicked
			static const int DblClick = 104;
			// Left button pressed down
			static const int Down = 105;
			// Left button released
			static const int Up = 106;
			// Left button released outside of the window
			static const int ReleaseOutside = 107;

			// Right button clicked
			static const int RightClick = 108;
			// Right button double clicked
			static const int RightDblClick = 109;
			// Right button pressed down
			static const int RightDown = 110;
			// Right button released
			static const int RightUp = 111;
			// Right button released outside of the window
			static const int RightReleaseOutside = 112;

			// Middle button clicked
			static const int MiddleClick = 113;
			// Middle button double clicked
			static const int MiddleDblClick = 114;
			// Middle button pressed down
			static const int MiddleDown = 115;
			// Middle button released
			static const int MiddleUp = 116;
			// Middle button released outside of the window
			static const int MiddleReleaseOutside = 117;

			// Scroll wheel is used (can be X and/or Y)
			static const int Scroll = 118;

			// The X coordinate of the mouse cursor within the object
			double localX = 0;

			// The Y coordinate of the mouse cursor within the object
			double localY = 0;

			// The X coordinate of the mouse cursor in global space
			double stageX = 0;

			// The Y coordinate of the mouse cursor in global space
			double stageY = 0;

			// For move event, the amount of movement in the X direction in global space
			double moveX = 0;

			// For move event, the amount of movement in the Y direction in global space
			double moveY = 0;

			// For a scroll event, the amount of scroll in the X direction
			double scrollX = 0;

			// For a scroll event, the amount of scroll in the Y direction
			double scrollY = 0;

			/**
			 * @brief Clear event to defaults
			 */
			virtual void reset() {
				KeyEvent::reset();
				localX = 0;
				localY = 0;
				stageX = 0;
				stageY = 0;
				moveX = 0;
				moveY = 0;
				scrollX = 0;
				scrollY = 0;
			}

			// ### MEMORY POOLING

			/**
			 * Create a new object or take one from the pool
			 * @return The new or recycled object
			 */
			static MouseEvent* Create(){
				return (MouseEvent*)MemoryPool::Create<MouseEvent>();
			}
			static MouseEvent* Create( int type ){
				MouseEvent* event = Create();
				event->type = type;
				return event;
			}
			static MouseEvent* Create( int type, void* target ){
				MouseEvent* event = Create( type );
				event->target = target;
				return event;
			}
		protected:
			/**
			 * Memory pool of recycled objects
			 */
			friend class MemoryPool;
			static list<MemoryPool*>* Pool;

			/**
			 * Pool getter
			 */
			virtual list<MemoryPool*>* _getPool(){
				return MouseEvent::Pool;
			}
		};

	} // events
} // derive