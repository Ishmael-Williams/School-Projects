#include "set.h" 
#include <algorithm> 
using namespace std; 
using namespace assignment5;

 

set::set(){ 
	used = 0; 
	head_ptr = NULL; 
} 

 

set::set(const set& s){ 
	used = s.used; 
	node *tail_ptr = head_ptr;
	list_copy(s.head_ptr, head_ptr, tail_ptr); 
	
} 

void set::operator= (const set& s) {  
	if (this == &s) return;  

	used = s.used; 
	node *tail_ptr = head_ptr;
	list_copy(s.head_ptr, head_ptr, tail_ptr); 

} 


 

void set::erase(const value_type& target){ 
	
	node* targetNode = list_search(head_ptr, target);
	node* cursor = head_ptr;
	if (targetNode != NULL){
		
		while (cursor->link() != targetNode){
			cursor++;
			
		}
		list_remove(cursor);
		used--;
	}

} 

 
void set::insert(const value_type& entry){ 
	bool found = false;
	if (used == 0 ){ 
		list_head_insert(head_ptr,entry);
		used++; 
		return; 
	} 
	node *cursor = head_ptr;
	while (cursor->link() != NULL){
		if (cursor->data() != entry){
			found = true;
			cout << "Item already exists in the set, duplicate item not inserted.\n";
			break;
		}
		cursor = cursor->link();
	}
	if (found == false){
		list_insert(cursor, entry);
		++used; 
		
	}
} 

  
set::size_type set::size() const{ 
	return used; 
} 

//Return intersection of sets
set set::intersection(const set& set1, const set& set2){
	node* cursor1 = set1.head_ptr;
	node* cursor2 = set2.head_ptr;
	set *newSet = new set();
	node *tail_ptr = newSet->head_ptr;
	while (cursor1 != NULL){
		if (list_search(cursor2, cursor1->data()) != NULL){
			list_insert(tail_ptr, cursor1->data());
			newSet->used++;
		}
		cursor1 = cursor1->link();
		
	}
	return *newSet;
}

//Return complement of sets  

set set::complement(const set& set2){
	set *newSet = new set();
	node*tail_ptr = newSet->head_ptr;
	
	if (set2.head_ptr == NULL){
		*newSet->head_ptr 1= head_ptr;
		return *newSet;
	}else if (set1.head_ptr == NULL){
		*newSet = set2;
		return *newSet;
	}
	
	node* cursor = head_ptr;
	while (cursor != NULL){
		if (list_search(set2.head_ptr, cursor->data()) == NULL){
			list_insert(tail_ptr, cursor->data());
			newSet->used++;
		}
		cursor = cursor->link();
	}
	return *newSet;
}
 
//Union operator

set set::operator+(const set& set1){ 
	
	node *newList = NULL; 
	node *tail_ptr = newList;
	list_copy(head_ptr, newList, tail_ptr);
	int listUsed = 0;
	listUsed = used;
	
	node *cursor = set1.head_ptr;
	while (cursor != NULL){
		if(list_search(newList, cursor->data()) == NULL){
			list_insert(tail_ptr, cursor->data());
			listUsed++;
		}
		cursor = cursor->link();
	}
	set *newSet = new set();
	newSet->head_ptr = newList;
	newSet->used = listUsed;
	return *newSet;
	
} 

bool set::contains(const value_type& target) const{ 
	bool found = false;
	
	if (list_search(head_ptr, target))
		found = true;
	
	return found;
} 

 

void set::printSet(){
	node *cursor = head_ptr;
	while (cursor != NULL){
		cout << cursor->data() << " "; 
		cursor = cursor->link();
	} 
	cout << endl;
}
 

 


 

set::~set(){
	delete this;
}
