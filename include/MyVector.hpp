#include <cstddef>
#include <stdexcept>
#include <assert.h>
#include <iostream>
#include <string>

namespace CPSC131::MyVector
{
	template <typename T>
	class MyVector
	{
		public:
			
			/*******************
			 * Static constants
			 ******************/
			
			/// Default capacity
			static constexpr size_t DEFAULT_CAPACITY = 64;
			
			/// Minimum capacity
			static constexpr size_t MINIMUM_CAPACITY = 8;
			
			/*****************************
			 * Constructors / Destructors
			 ****************************/
			
			/// Normal constructor
			MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY)
			{
				// TODO: Your code here
				size_ = 0;
				capacity_ = capacity_bounds_check(capacity);
				elements_ = new T [capacity_];
			}
	
			/// Copy constructor
			MyVector(const MyVector& other)
			{
				// TODO: Your code here
				size_ = other.size_;
				capacity_ = other.capacity_;
				elements_ = new T [capacity_];

				copy_loop_helper(other);
			}
			
			/**
			 * Destructor
			 * Cleanup here.
			 */
			~MyVector()
			{
				// TODO: Your code here
				delete [] elements_;
				elements_ = nullptr;
			}
			
			/************
			 * Operators
			 ************/
			
			///	Assignment operator
			MyVector& operator=(const MyVector& rhs)
			{
				// TODO: Your code here
				if (this == &rhs)
				{
					return *this;
				}

				delete [] elements_;
				elements_ = nullptr;
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				elements_ = new T [capacity_];

				copy_loop_helper(rhs);
				return *this;
			}
			/// Operator overload to at()
			// Non-const overload
			T& operator[](size_t index)
			{
				// TODO: Your code here
				out_of_range_helper(index);
				return elements_[index];
			}

			// Const overload
			const T& operator[](size_t index) const
			{
				out_of_range_helper(index);
				return elements_[index];
			}
			
			/************
			 * Accessors
			 ************/
			
			/// Return a raw pointer to the elements_ array
			T* elements()
			{
				// TODO: Your code here
				return elements_;
			}
			
			/// Return the number of valid elements in our data
			size_t size() const
			{
				// TODO: Your code here
				return size_;
			}
			
			/// Return the capacity of our internal array
			size_t capacity() const
			{
				// TODO: Your code here
				
				return capacity_;
			}
			
			/**
			 * Check whether our vector is empty
			 * Return true if we have zero elements in our array (regardless of capacity)
			 * Otherwise, return false
			 */
			bool empty() const
			{
				// TODO: Your code here
				if (size_ == 0)
				{
					return true;
				}
				return false;
			}
			
			/// Return a reference to the element at an index
			T& at(size_t index)
			{
				// TODO: Your code here
				out_of_range_helper(index);
				return elements_[index];
			}

			const T& at(size_t index) const
			{
				out_of_range_helper(index);
				return elements_[index];
			}
			
			/***********
			 * Mutators
			 ***********/
			
			/**
			 * Reserve capacity in advance, if our capacity isn't currently large enough.
			 * Useful if we know we're about to add a large number of elements,
			 *   and we'd like to avoid the overhead of many internal changes to capacity.
			 */
			void reserve(size_t capacity)
			{
				// TODO: Your code here
				if (capacity < size_)
				{
					throw std::invalid_argument("Capacity is less than size");
				}
				else if (capacity > capacity_)
				{
					T* updated_array = nullptr;
					updated_array = new T [capacity];
					for (size_t i = 0; i < size_; i++)
					{
						updated_array[i] = elements_[i];
					}
					delete [] elements_;
					elements_ = nullptr;
					elements_ = updated_array;
					capacity_ = capacity;
				}
				else
				{
					return;
				}
			}
			
			/**
			 * Set an element at an index.
			 * Throws range error if outside the size boundary.
			 * Returns a reference to the newly set element (not the original)
			 */
			T& set(size_t index, const T& element)
			{
				// TODO: Your code here
				out_of_range_helper(index);
				elements_[index] = element;
				return elements_[index];
			}
			
			/**
			 * Add an element onto the end of our vector.
			 * Returns a reference to the newly inserted element.
			 */
			T& push_back(const T& element)
			{
				// TODO: Your code here
				// first check
				increase_vector_check();
				elements_[size_] = element;
				size_++;
				
				return elements_[size_ - 1];
			}
			
			/**
			 * Remove the last element in our vector.
			 * Should throw std::range_error if the vector is already empty.
			 * Returns a copy of the element removed.
			 */
			T pop_back()
			{
				// TODO: Your code here
				if (empty())
				{
					throw std::underflow_error { "Vector is empty and an element cannot be deleted" };
				}
				
				T popped_element = elements_[size_ - 1];
				size_--;
				decrease_vector_check();
				return popped_element;

			}
			
			/**
			 * Insert an element at some index in our vector
			 * 
			 * Example:
			 * 	 Insert a 9 at index 2
			 *   Contents before: [6, 2, 7, 4, 3]
			 *   Contents after:  [6, 2, 9, 7, 4, 3]
			 * 
			 * Returns a reference to the newly added element (not the original).
			 */
			T& insert(size_t index, const T& element)
			{
				// TODO: Your code here
				if (index > size_)
				{
					throw std::out_of_range("Index out of range including last index");
				}

				increase_vector_check();

				for (size_t i = size_; i > index; i--)
				{
					elements_[i] = elements_[i - 1];
				}
				elements_[index] = element;
				size_++;
				return elements_[index];
			}
			
			/**
			 * Erase one element in our vector at the specified index
			 * 
			 * Throws std::range_error if the index is out of bounds.
			 * 
			 * Example:
			 *   Erase index 2
			 *   Contents before: [8, 4, 3, 9, 1]
			 *   Contents after:  [8, 4, 9, 1]
			 * 
			 * Returns a copy of the erased element.
			 * Hint: call DTOR on original after making the copy.
			 */
			T erase(size_t index)
			{
				// TODO: Your code here
				out_of_range_helper(index);

				T deleted_element = elements_[index];
				for (size_t i = index; i < size_ - 1; i++)
				{
					elements_[i] = elements_[i + 1];
				}
				
				size_--;
				decrease_vector_check();
				return deleted_element;
			}
			
			/**
			 * Removes all elements (i.e., size=0 and DTORs called)
			 * 
			 * Should also reset capacity, if needed
			*/
			void clear()
			{
				delete [] elements_;
				elements_ = nullptr;
				capacity_ = DEFAULT_CAPACITY;
				size_ = 0;
				elements_ = new T [capacity_];
			}
		
			//print helper function
			void print_helper() const
			{
				std::cout << "size: " << size_ << std::endl;
				std::cout << "capacity: " << capacity_ << std::endl;
			
				for (size_t i = 0; i < size_; i++)
				{
					std::cout << elements_[i] << " ";
				}
				std::cout << std::endl;
			}

		/**
		 * Begin private members and methods.
		 * You may add your own private helpers here, if you wish.
		*/

		private:
			
			// Checks if capacity is initialized below the minimum capacity
			size_t capacity_bounds_check(size_t capacity)
			{
				if (capacity < MINIMUM_CAPACITY)
				{
					return MINIMUM_CAPACITY;
				}
				return capacity;
			}

			// Copy loop for copy constructor and operator overload =
			void copy_loop_helper(const MyVector& root)
			{
				for (size_t i = 0; i < size_; i++)
				{
					elements_[i] = root.elements_[i];
				}
			}

			// Check if index is out of range of the dynamic array
			void out_of_range_helper(const size_t index) const
			{
				if (index >= size_)
				{
					throw std::out_of_range("Index out of range");
				}
			}

			// Increase capacity if size is equal to capacity of the array
			void increase_vector_check()
			{
				if (capacity_ == size_)
				{
					size_t updated_capacity = capacity_ * 2;
					reserve(updated_capacity);
				}
			}

			// Shrinks capacity when size drops below 1/3 to avoid wasted memory
			void decrease_vector_check()
			{
				size_t decrease_capacity = capacity_;
				while (size_ < (decrease_capacity / 3))
				{
					decrease_capacity = decrease_capacity / 2;
				}
				
				if (decrease_capacity <= MINIMUM_CAPACITY)
				{
					decrease_capacity = MINIMUM_CAPACITY;
				}

				if (decrease_capacity == capacity_)
				{
					return;
				}
				
				T* temp_elements;
				temp_elements = new T [decrease_capacity];
				for (size_t i = 0; i < size_; i++)
				{
					temp_elements[i] = elements_[i];
				}
				delete [] elements_;
				elements_ = nullptr;
				elements_ = temp_elements;
				capacity_ = decrease_capacity;
			}
			/// Number of valid elements currently in our vector
			size_t size_ = 0;
			
			/// Capacity of our vector; The actual size of our internal array
			size_t capacity_ = 0;
			
			/**
			 * Our internal array of elements of type T.
			 * Starts off as a null pointer.
			 */
			T* elements_ = nullptr;
	};

}

