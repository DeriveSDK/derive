#pragma once

/**
 * Memory pooling
 *
 * Usage for objects that implement pooling
 *
 *      // Create a new object (or get from pool)
 *      MyObj* obj = MyObj::Create();
 *
 *      // Delete the object (or return to pool)
 *      obj->recycle;
 *      obj = nullptr; // recommended
 *
 *      // On application exit (frees pool and remaining pooled objects)
 *      MemoryPool::Destroy<MyObj>();
 *
 * To implement object pooling your class must
 *
 *      1) extend MemoryPool
 *      2) have a static Pool property (list of pooled objects)
 *      3) implement _getPool (to return the pool)
 *      4) implement the static Create factory method (can overload for multiple constructors)
 *      5) implement reset (to reset the object ready for next re-use)
 *
 *      See derive::events::Event and derive::events::MouseEvent for an example
 */

#include <list>

using namespace std;

namespace derive {
	namespace mem {

		/**
		 * @brief Base class for memory pooled objects
		 */
		class MemoryPool {
		public:
			/**
			 * @brief Destroy the Pool object
			 *
			 */
			virtual ~MemoryPool() {}

			/**
			 * @brief Set all object properties back to defaults ready for re-use
			 */
			virtual void reset() {}

			/**
			 * Create factory method. Uses memory pool for object re-use.
			 */
			template<class T>
			static MemoryPool* Create() {
				MemoryPool* obj;
				list<MemoryPool*>* pool = T::Pool;
				if ( pool && pool->size() > 0 ) {
					obj = pool->back();
					pool->pop_back();
				}
				else {
					obj = new T();
				}
				return obj;
			}

			/**
			 * Return this object to the pool
			 */
			void recycle() {
				list<MemoryPool*>* pool = _getPool();
				if ( pool ) {
					this->reset();
					pool->push_back( this );
				}
				else {
					delete this;
				}
			}

			/**
			 * Destroys the memory pool and frees all objects in it
			 * Memory pooling will be disabled after this (calling Create
			 * and recycle will just call new and delete)
			 */
			template<class T>
			static void Destroy() {
				list<MemoryPool*>* pool = T::Pool;
				for ( auto event : *pool ) delete event;
				delete pool;
				T::Pool = nullptr;
			}

		protected:
			/**
			 * Pool getter
			 */
			virtual list<MemoryPool*>* _getPool() {
				return nullptr;
			}
		};

	} // events
} // derive