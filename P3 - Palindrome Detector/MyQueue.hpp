#ifndef CPSC131_MYQUEUE_HPP
#define CPSC131_MYQUEUE_HPP


/**
 * TODO: Complete this class
 */


//
#include <list>
#include <stdexcept>


//
namespace CPSC131
{
	//
	template <class T>
	class MyQueue
	{
		//
		public:
			
			///	 YOUR WELCOME
			MyQueue() {}
			
			/**
			 * enqueue()
			 * 
			 * Takes an item and puts it into the queue
			 */
			void enqueue(const T& item)
			{
				size_++;
				list.push_back(item);
			}
			
			/**
			 * Removes the next item from the queue
			 * 
			 * Does not return a value
			 * 
			 * If the queue is empty: throw an std::range_error
			 */
			void dequeue()
			{
				if (!empty()) {
					list.pop_front();
					size_--;
				}
				else {
					throw std::range_error("already empty");
				}
			}
			
			/**
			 * Peek at the front of the queue
			 * 
			 * Does not remove anything.
			 * 
			 * If the queue is empty: throw an std::range_error
			 */
			const T& front()
			{
				if (empty()) {
					throw std::range_error("already empty");
				}
				else {
					return list.front();
				}
			}
			
			/**
			 * Remove all items from the queue
			 */
			void clear()
			{
				typename std::list<T>::iterator duh;
				for (duh = list.begin(); duh != list.end(); duh++) {
					*duh = T();
				}
				size_ = 0;
				list.clear();
			}
			
			/**
			 * Return the number of items in the queue
			 */
			size_t size()
			{
				return size_;
			}
			
			/**
			 * Return true if the queue is empty, false otherwise
			 */
			bool empty()
			{
				return size_ == 0;
			}
		
		//
		private:
			
			/**
			 * Do not change these privates.
			 * You may add additional privates below this block, if you wish.
			 */
			std::list<T> list;
			size_t size_ = 0;
			/******************************/
	};
}









#endif
