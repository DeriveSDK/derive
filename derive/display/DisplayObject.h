#pragma once

// Derive
#include "derive/display/AlignMode.h"
#include "derive/display/BitmapData.h"
#include "derive/display/FitMode.h"
#include "derive/events/Dispatcher.h"
#include "derive/geom/Bounds.h"
#include "derive/geom/Grid.h"
#include "derive/geom/Point.h"
#include "derive/geom/HitArea.h"
// Skia
#include "core/SkSurface.h"
#include "core/SkMatrix.h"
// QuickJS(pp)
#ifdef DERIVE_SCRIPT
#include "quickjspp.hpp"
#endif

// Other
#include <vector>

using namespace std;
using namespace derive::events;
using namespace derive::geom;

namespace derive {
	namespace display {

		/**
		 * @brief Holds the display properties of an object
		 * Used internally to check if a display object has changed
		 */
		class DisplayObjectProps {
		public:
			virtual ~DisplayObjectProps();

			// X coordinate
			double x = 0;

			// Y coordinate
			double y = 0;

			// origin X coordinate
			double originX = 0;

			// origin Y coordinate
			double originY = 0;

			// X scale
			double scaleX = 1.0;

			// Y scale
			double scaleY = 1.0;

			// Rotation in radians
			double rotation = 0;

			// Width
			double width = 0;

			// Height
			double height = 0;

			// visibility
			bool visible = true;

			// Alpha
			double alpha = 1.0;

			/**
			 * @brief Copy the properties from another object
			 *
			 * @param from The object to copy from
			 * @return true If any of the properties have changed
			 * @return false If all of the propeties are the same
			 */
			virtual bool copy( DisplayObjectProps* from );
		};

		/**
		 * @brief The base class for any object that is in the display list
		 *
		 */
		class DisplayObject : public DisplayObjectProps, public Dispatcher {
		protected:
			DisplayObject* _stage = nullptr;
			DisplayObject* _parent = nullptr;
			vector<DisplayObject*> _children;
			DisplayObjectProps* _state;
			bool _dirty = false;
			Point* _cursor;
			Grid* _grid;
			Bounds* _bounds;
			SkMatrix* _transform; // The global transform
			HitArea* _hitArea = nullptr;
			int _depth = 0;

			#ifdef DERIVE_SCRIPT
			// Call JS update
			JSValueConst thisJS;
			#endif

			/**
			 * @brief Called when this objects is added to a parent
			 */
			virtual void _added( DisplayObject* parent );

			/**
			 * @brief Called when this objects is removed from it's parent
			 */
			virtual void _removed();

		public:
			DisplayObject();
			virtual ~DisplayObject();

			/**
			 * @brief Return the bounds of this display object
			 * The bounds are owned by the display object and should not be freed outside of this object.
			 * Changing the bounds will have no affect on the display object. It is intended as a read-only
			 * object.
			 * @return Bounds* The bounds
			 */
			virtual Bounds* bounds();

			/**
			 * @brief Return the parent display object
			 *
			 * @return DisplayObject* The parent
			 */
			virtual DisplayObject* parent();

			/**
			 * @brief Return the stage
			 *
			 * @return DisplayObject* The stage
			 */
			virtual DisplayObject* stage();

			/**
			 * @brief Set the stage (recursive)
			 * Called internally. Do not call manually
			 * @param stage The stage
			 */
			virtual void stage( DisplayObject* stage );

			/**
			 * @brief Add a display object as a child to this one
			 * The display object is added to the top of the list
			 * @param child The child to add
			 * @return DisplayObject* The child that was added
			 */
			virtual DisplayObject* addChild( DisplayObject* child );

			/**
			 * @brief Adds a child display object at the specififed position
			 *
			 * @param child The child to add
			 * @param index The position to add the child at
			 * @return DisplayObject* The child that was added
			 */
			virtual DisplayObject* addChildAt( DisplayObject* child, int index );

			/**
			 * @brief Remove the specified child from the display object
			 * The child is returned even if it was not a child of the display object
			 * @param child
			 * @return DisplayObject* The child that was removed
			 */
			virtual DisplayObject* removeChild( DisplayObject* child );

			/**
			 * @brief Remove the child at the specified position
			 *
			 * @param index The position at which to remove the child
			 * @return DisplayObject* The child that was removed
			 */
			virtual DisplayObject* removeChildAt( int index );

			/**
			 * @brief Remove all children
			 *
			 */
			virtual void removeAllChildren();

			/**
			 * @brief Get the number of children
			 *
			 * @return int The number of children
			 */
			virtual int numChildren();

			/**
			 * @brief Get the child at the specified position
			 *
			 * @param index The position of the child to get
			 * @return DisplayObject* The child at the position
			 */
			virtual DisplayObject* childAt( int index );

			/**
			 * @brief Get the position of the child in the list of children
			 *
			 * @param child The child to get the position of
			 * @return int The position of the child, or -1 if not found
			 */
			virtual int indexOfChild( DisplayObject* child );

			/**
			 * @brief Check if the child exists in the object
			 *
			 * @param child The child to add
			 * @return true If the child exists
			 * @return false If the child does not exist
			 */
			virtual bool hasChild( DisplayObject* child );

			/**
			 * @brief Get the first child of this display object
			 *
			 * @return DisplayObject* The child
			 */
			virtual DisplayObject* first();

			/**
			 * @brief Get the last child of this display object
			 *
			 * @return DisplayObject* The child
			 */
			virtual DisplayObject* last();

			/**
			 * @brief Get the next sibling of this display object
			 *
			 * @return DisplayObject* The sibling
			 */
			virtual DisplayObject* next();

			/**
			 * @brief Get the previous sibling of this display object
			 *
			 * @return DisplayObject* The sibling
			 */
			virtual DisplayObject* prev();

			/**
			 * @brief Add a sibling display object after this one
			 *
			 * @param sibling The display object to add
			 * @return DisplayObject* The display object that was added
			 */
			virtual DisplayObject* addBefore( DisplayObject* sibling );

			/**
			 * @brief Add a sibling display object before this one
			 *
			 * @param sibling The display object to add
			 * @return DisplayObject* The display object that was added
			 */
			virtual DisplayObject* addAfter( DisplayObject* sibling );

			/**
			 * @brief Remove this object as a child from it's parent
			 *
			 * @return DisplayObject* Return the display object that was removed (itself)
			 */
			virtual DisplayObject* remove();

			/**
			 * @brief Set the depth of the object
			 * Used internally
			 * @param d The depth
			 */
			virtual void depth( int d );

			/**
			 * @brief Set the cursor position
			 * Should be called by the parent. Point should be in parent coordinates
			 * @param x The x coordinate of the cursor
			 * @param y The y coordinate of the cursor
			 */
			virtual void cursor( double x, double y );

			/**
			 * @brief Return the cursor position
			 * Do not destroy the cursor. Modifying the position using the pointer directly will not
			 * affect children.
			 * @return Point* The cursor position
			 */
			virtual Point* cursor();

			/**
			 * @brief Get the snap grid for this object
			 * A snap grid is optional. Use it to automatically snapp an object to a grid.
			 * @return Grid* The grid
			 */
			virtual Grid* snap();

			/**
			 * @brief Get the current hit area for cursor/mouse events
			 * 
			 * @return HitArea* The hit area, or null
			 */
			virtual HitArea* hitArea();

			/**
			 * @brief Set the hit area for cursor/mouse events
			 * Any existing hit area will be freed first.
			 * @param hitArea The hit area, or null to remove it
			 */
			virtual void hitArea( HitArea* hitArea );

			/**
			 * @brief Fit the object to the supplied rectangular area
			 *
			 * @param rect The area to fit to
			 * @param type How to fit the object (@see FitMode)
			 */
			virtual void fit( Bounds* rect, int fitMode = FitMode::Contain, int alignMode = AlignMode::Center );

			/**
			 * @brief Convert a point in local space to global space
			 * Only works if the object is on the display list
			 * @param p The point to convert
			 */
			virtual void localToGlobal( Point* p );

			/**
			 * @brief Convert a point in global space to local space
			 * Only works if the object is on the display list
			 * @param p The point to convert
			 */
			virtual void globalToLocal( Point* p );

			/**
			 * @brief Perform any steps in preparation for user update
			 * Generally do not override this unless you know what you are doing (@see update)
			 * @param dt The time, in seconds, since the last call to update
			 */
			virtual void preUpdate( double dt );

			/**
			 * @brief Called every update step
			 * Use this to update physics or other operations that need to happen is often as
			 * possible. Do not use this to perform any drawing or rendering (@see render).
			 * @param dt The time, in seconds, since the last call to update
			 */
			virtual void update( double dt ) { }

			/**
			 * @brief Called after update to continue stepping the display list
			 * Generally do not override this unless you know what you are doing (@see update)
			 * @param dt The time, in seconds, since the last call to update
			 */
			virtual void postUpdate( double dt );

			/**
			 * @brief Preparation steps for the render
			 * Generally do not override this unless you know what you are doing (@see render)
			 * XXX: Use derive transform instead of skia
			 * @param surface The Skia surface to draw to
			 * @param transform The global transform
			 * @param forceTransformUpdate Force the trasnform to be updated (usually because the parent has changed)
			 * @param dt The time, in seconds, since the last call to render
			 */
			virtual void preRender( SkSurface* surface, SkMatrix* transform, bool forceTransformUpdate, double dt );

			/**
			 * @brief Called every render step
			 * Override this to perform actual rendering to the surface
			 * Usually called less often than update (@see update).
			 * Use this to perform any drawing or rendering operatons.
			 * @see update
			 * @param surface The Skia surface to draw to
			 * @param dt The time, in seconds, since the last call to render
			 */
			virtual void render( SkSurface* surface, double dt ) { }

			/**
			 * @brief Called after render to continue stepping the display list
			 * Generally do not override this unless you know what you are doing (@see render)
			 * XXX: Use derive transform instead of skia
			 * @param surface The Skia surface to draw to
			 * @param transform The global transform
			 * @param dt The time, in seconds, since the last call to render
			 */
			virtual void postRender( SkSurface* surface, SkMatrix* transform, double dt );
		};

	} // display
} // derive