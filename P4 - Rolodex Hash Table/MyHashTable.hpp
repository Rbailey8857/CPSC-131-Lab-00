#ifndef MY_HASH_TABLE_HPP
#define MY_HASH_TABLE_HPP


/**
 * TODO: Complete this class!
 */


/// Your welcome
#include <stdexcept>
#include <forward_list>
#include <functional>
#include <memory>
#include <string>


//	More includes ... ?


///	Begin our class namespace
namespace CPSC131::MyHashTable
{
	//
	template<class VTYPE>
	class MyHashTable
	{
		//
		public:
			
			//
			static constexpr size_t DEFAULT_CAPACITY = 1024;
			static constexpr size_t ULLONG_WRAP_AT = 4294967295;
			
			/**
			 * Constructor
			 * 
			 * Probably easiest to do the following:
			 * 
			 *   1. Call on setCapacity() to set the table's capacity
			 */
			MyHashTable(size_t capacity = MyHashTable::DEFAULT_CAPACITY)
			{
				setCapacity(capacity);
			}
			
			/**
			 * Copy constructor
			 */
			MyHashTable(const MyHashTable& other)
			{
				setCapacity(other.capacity_);
				size_ = other.size_;
				n_collisions_ = other.n_collisions_;
				for (size_t i = 0; i < capacity_; ++i) {
					table_[i] = other.table_[i];
				}
			}
			
			/**
			 * Destructor
			 * 
			 * Deallocate the table (array of std::forward_list 's), and set the table to nullptr
			 * Don't double-deallocate if the table is already a null pointer
			 */
			~MyHashTable()
			{
				delete[] table_;
			}
			
			/**
			 * Should return the capacity_ of this hash table
			 * Meaning, the total number of rows in this hash table
			 * Doesn't discern between used/unused/collided rows
			 */
			size_t capacity() const
			{
				return capacity_;
			}
			
			/**
			 * Should return the number of items currently in the hash table
			 */
			size_t size() const
			{
				return size_;
			}
			
			/**
			 * Return true if the table is empty, false otherwise
			 */
			bool empty()
			{
				return size_ == 0;
			}
			
			/**
			 * Should return the number of collisions currently present in the hash table
			 */
			size_t n_collisions() const
			{
				return n_collisions_;
			}
			
			/**
			 * Set the capacity for this table.
			 * Changes the total number of hash table rows available.
			 * 
			 * Existing entries should survive the change,
			 * 	so you probably want to do the following:
			 * 
			 *  1. Keep the existing table array pointer in a temporary pointer
			 *  
			 *  2. Re-initialize 'this' to contain a new empty table of the right capacity
			 *  
			 *  3. The temporary pointer should now contain the OLD data (old table),
			 *     while 'this' contains the brand new table of the new size.
			 * 
			 *  4. Iterate through all key/value pairs in the old data (temp pointer).
			 * 
			 *  5. For each key/value pair in the old data, call this->add() to insert
			 *     properly into the new table.
			 *  
			 *  6. Deallocate the old table by calling `delete []` on the temporary pointer.
			 * 
			 * Don't forget to check whether the current table is a nullptr before you
			 *  decide to do iterations!
			 */
			void setCapacity(size_t c)
			{
				if (c == capacity_) {
        			return;
    			}

    			std::forward_list<std::pair<std::string, VTYPE>>* temp = table_;
    			size_t old_capacity = capacity_;
    			capacity_ = c;
    			table_ = new std::forward_list<std::pair<std::string, VTYPE>>[capacity_];
    			n_collisions_ = 0;
    			size_ = 0;

    			for (size_t i = 0; i < old_capacity; ++i) {
        			for (const auto& entry : temp[i]) {
            			size_t newIndex = hash(entry.first) % capacity_;
            			if (!table_[newIndex].empty()) {
                			++n_collisions_;
            			}
            			table_[newIndex].push_front(entry);
            			++size_;
        			}
    			}

    			delete[] temp;
			}
			
			///	Your welcome
			unsigned long long int hash(std::string key) const
			{
				return this->midSquareHash(key);
			}
			
			/**
			 * Implement the "modified mid square" hash function,
			 * as described in the instructions.
			 */
			unsigned long long int midSquareHash(std::string key) const
			{
				unsigned long long int sum = 1;

				for (const char &c : key)
				{
					sum *= static_cast<unsigned long long int>(c);
					sum %= ULLONG_WRAP_AT;
				}

				unsigned long long int square = sum * sum;
				std::string square_str = std::to_string(square);
				size_t substr_len = square_str.length() / 2;

				std::string hashCode_str = square_str.substr(substr_len / 2, substr_len);
				unsigned long long int hashCode = std::stoull(hashCode_str);

				return hashCode % capacity_;
			}
			
			/**
			 * Implement your own custom hash functions to compete on the Gradescope Leaderboard!
			 * Four stubs are provided to make experimentation a little easier.
			 * Only the best hash function will count towards the leaderboard.
			 */
			unsigned long long int myCustomHashFunction1(std::string key) const
			{
				return 0;

			}
			unsigned long long int myCustomHashFunction2(std::string key) const
			{
				return 0;
			}
			unsigned long long int myCustomHashFunction3(std::string key) const
			{
				return 0;
			}
			unsigned long long int myCustomHashFunction4(std::string key) const
			{
				return 0;
			}
			
			/**
			 * Return true if a key exists in the table, or false otherwise.
			 */
			bool exists(std::string key) const
			{
				size_t index = hash(key) % capacity_;

				for (const auto& value : table_[index]) {
					if (value.first == key) {
						return true;
					}
				}
				
				return false;
			}
			
			/**
			 * Add a key/value pair to this table.
			 * If the key already exists, throw a runtime_error.
			 */
			void add(std::string key, VTYPE value)
			{
				if (exists(key)) {
        			throw std::runtime_error("Key already exists: " + key);
    			}

    			size_t index = hash(key) % capacity_;

    			if (!table_[index].empty()) {
        			++n_collisions_;
    			}

    			table_[index].push_front(std::make_pair(key, value));
    			++size_;
			}
			
			/**
			 * Should return a reference to the VTYPE value associated to the provided key.
			 * If the key/value pair isn't in the table, a runtime_error should be thrown.
			 */
			VTYPE& get(std::string key) const
			{
				size_t index = hash(key);
				
				for (auto& entry : table_[index]) {
					if (entry.first == key) {
						return entry.second;
					}
				}

				throw std::runtime_error("Cannot get value for key because it doesn't exist: " + key);
			}
			
			/**
			 * In a single std::forward_list, return every key currently present in the table
			 * 
			 * If no keys exist (empty table), just return an empty std::forward_list.
			 * 
			 * It's okay that when sorted == false, std::forward_list::push_front will
			 *  return your keys in backwards-order, as there is no guarantee
			 *  of properly-ordered keys anyway.
			 * 
			 * However, if the caller passes sorted=true, you should sort the keys
			 * 	as a last step before returning them.
			 * 	Try using the built-in method std::forward_list::sort
			 */
			std::forward_list<std::string> getAllKeys(bool sorted = false) const
			{
				std::forward_list<std::string> keys;
				
				for (size_t i = 0; i < capacity_; ++i) {
					for (const auto& entry : table_[i]) {
						keys.push_front(entry.first);
					}
				}
				
				if (sorted) {
					keys.sort();
				}

				return keys;

			}
			
			/**
			 * Remove a key/value pair that corresponds to the provided key.
			 * If no such key exists, throw a runtime_error.
			 */
			void remove(std::string key)
			{
				if (!exists(key)) {
					throw std::runtime_error("Cannot remove value for key because it doesn't exist: " + key);
				} else {
					size_t index = hash(key);
					auto& list = table_[index];

					list.remove_if([&key](const std::pair<std::string, VTYPE>& entry) {
						return entry.first == key;
					});
					
					--size_;
				}
			}
			
			/**
			 * Remove all entries in this table
			 * Iterate over each table row and call clear on the row's list
			 */
			void clear()
			{
				for (size_t i = 0; i < capacity_; ++i) {
					table_[i].clear();
				}

				size_ = 0;
				n_collisions_ = 0;
			}
			
			/**
			 * Assignment Operator
			 */
			MyHashTable<VTYPE>& operator=(const MyHashTable<VTYPE>& other)
			{
				if (this != &other) {
					delete[] table_;
					capacity_ = other.capacity_;
					size_ = other.size_;
					n_collisions_ = other.n_collisions_;
					table_ = new std::forward_list<std::pair<std::string, VTYPE>>[capacity_];
					for (size_t i = 0; i < capacity_; ++i) {
						table_[i] = other.table_[i];
					}
				}

				return *this;
			}
			
		//
		private:
			
			/**
			 * Keeps track of the capacity of this hash table
			 * (total number of rows in the table, whether used or not)
			 * (does not care about collisions)
			 */
			size_t capacity_ = 0;
			
			/**
			 * Keeps track of the total number of items currently in
			 * the hash table
			 */
			size_t size_ = 0;
			
			/**
			 * Keeps track of the number of collisions currently present in the table
			 */
			size_t n_collisions_ = 0;
			
			/**
			 * The actual hash table.
			 * We'll make this a fixed-sized array,
			 *   but dynamically allocated so we can resize whenever we need.
			 * 
			 * Try to imagine each table row is actually a complete forward_list.
			 * In a perfect situation where a table has no collisions, each list
			 *   will simply contain one item.
			 * 
			 * One "item" in this case refers to an std::pair<std::string, VTYPE>,
			 *   where the first part of the pair is the key and the second
			 *   is the value (of type VTYPE).
			 */
			std::forward_list<std::pair<std::string, VTYPE>> * table_ = nullptr;
	};
}

#endif
