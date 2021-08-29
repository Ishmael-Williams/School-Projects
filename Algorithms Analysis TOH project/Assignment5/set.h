#ifndef _SET_H_
#define _SET_H_

#include <cstdlib>
#include <iostream>
#include "node1.h"


namespace assignment5{

class set
{
public:
    typedef int value_type;
    typedef std::size_t size_type;
    set();
    
    ~set();
   // postcondition: all dynamically allocated memory has been deallocated
     set(const set& s);
    // copy of s has been created;
    void operator = (const set& s);
    // postcondition: exact copy of s has been assigned to the current set object
    void erase(const value_type& target);
    // postcondition: target has been removed from the set
    void insert(const value_type& entry);
     // postcondition: if entry was not in the set, then entry has been added, else nothing was done
    
     // postcondition: non-duplicating elements from addend have been added to the set
    size_type size() const;
    
	
	//complement, return set containing elements in lefthand set not in righthand set 
		//(operator overload?)
	
	
	//union, return new set containing unique elements of both
	set operator+(const set& set1);
	
	//intersection, return set containing elements only in both sets
	set intersection(const set& set1, const set& set2);
	
	
	
	
	// postcondition: number of elements in the set has been returned
    bool contains(const value_type& target) const;
    // postcondition: returned whether target is in the set
    
	
	void printSet();
	set complement(const set& set2);
	
	
	
	node *head_ptr;
    size_type used;            // How much of array is used
    size_type capacity;
	
	 
	
	
	
private:
};

	
}


#endif // _SET_H_