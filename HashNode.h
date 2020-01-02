#ifndef _HASH_NODE
#define _HASH_NODE

#include<string>

using namespace std;

template<class ItemType>
class HashNode {
private:
	string key;
	ItemType item;

public:
	// constructors
    HashNode(const ItemType & anItem) {key = ""; item = anItem;}
	HashNode(const string k, const ItemType & anItem) {key = k; item = anItem;}

	// accessors
	void setKey(const string k) {key = k;}
	void setItem(const ItemType & anItem) {item = anItem;}

	// mutators
	string getKey() const {return key;}
	ItemType getItem() const {return item;}
    
    
    // Overloaded operator functions
    bool operator > (const HashNode &right){     // Overloaded >
        return key > right.key;
    }
    bool operator < (const HashNode &right){     // Overloaded <
        return key < right.key;
    }
    bool operator == (const HashNode &right){     // Overloaded ==
        return key == right.key;
    }
    
    friend ostream &operator <<(ostream & strm, const HashNode & obj)
    {
        strm << obj.item;
        return strm;
    }
    
};
#endif 
