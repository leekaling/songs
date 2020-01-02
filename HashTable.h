#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "LinkedList.h"
#include "HashNode.h"
#include <iomanip>
#include <string>

using namespace std;

template <class ItemType>
class HashTable {

private:

	LinkedList<HashNode<ItemType>>* table;
	int size;
	int collisionCount;
	int count;  // Count number of buckets that have been occupied
	void _rehash();

public:

	// constructor
	HashTable() {
		size = 10;      // default size of hash table
		table = new LinkedList<HashNode<ItemType>>[size];
		collisionCount=0;
		count=0;
	}

    HashTable (int n){
        size = n;
        table = new LinkedList<HashNode<ItemType>>[size];
        collisionCount=0;
        count=0;
    }

	~HashTable() {
        destroyHash();
	}

	int hash(string key) {
		int k;
		k = stoi(key);
		return (k % size);
	}

    bool isPrime (int);
	bool insertHash(string key, ItemType & newData);
	bool deleteHash(string key, ItemType & returnedItem);
	bool searchHash(string key, ItemType & returnedItem);
	void destroyHash();
	void printHash() {
         for (int i = 0; i < size; i++)
         {
             table[i].displayList();
         }
	}

	void printStat(){
	    string Line = "========================================\n";
	    cout << Line << "Statistic of Hash" << Line << endl;
	    cout << "Load Factor:         " << getLoadFactor()*100 << "%" << endl;
	    cout << "Number of Collision: " << getCollisionCount() << endl;
	}

    // setters and getters
	int getSize() { return size; }
	int getCollisionCount () {return collisionCount;}
    int getCount () {return count;}
    double getLoadFactor () {return (double)count/(double)size;}
};

template <class ItemType>
bool HashTable<ItemType>::isPrime(int n)
{
    for (int i=3; i<n; ++i)
    {
        if (n%i==0)
            return false;
    }
    return true;
}

template <class ItemType>
bool HashTable<ItemType>::insertHash(string key, ItemType & newData)
{
    bool inserted = false;
    int index = hash(key);
    HashNode<ItemType> tempNode(key,newData);

    if (getLoadFactor()>=0.75)
        _rehash();

    inserted=table[index].insertNode(tempNode);

    if (inserted)
    {
        if (table[index].getCount()==1)
            count++;

        if (table[index].getCount()>1)
            collisionCount++;
    }
    return inserted;
}

template <class ItemType>
bool HashTable<ItemType>::deleteHash(string key, ItemType & returnedItem)
{
    int index = hash(key);
    bool found=false;
    bool deleted = false;

    HashNode<ItemType> tempNode(key,returnedItem);

    found = table[index].searchList(tempNode);

    if (found)
        deleted = table[index].deleteNode(tempNode);

    if (deleted && table[index].getCount()==0)
        count--;

    return deleted;
}

template <class ItemType>
bool HashTable<ItemType>::searchHash(string key, ItemType & returnedItem)
{
    int index;
    index = hash(key);

    HashNode<ItemType> tempNode(key,returnedItem);

    return table[index].searchList (tempNode);
}

template <class ItemType>
void HashTable<ItemType>::destroyHash()
{
    for (int i = 0; i < size; ++i)
    {
        if (table[i].getCount()!=0)
        {
            table[i].clearList();
            count--;
        }
    }
}

template <class ItemType>
void HashTable<ItemType>::_rehash()
{
    LinkedList<HashNode<ItemType>>* temp = table;

    int newSize=size*2;
    while (!isPrime(newSize))
    {
        newSize++;
    }

    table = new LinkedList<HashNode<ItemType>>[newSize];

    for (int i=0; i<size; i++)
    {
        ListNode<HashNode<ItemType>> *nodePtr = temp[i].getHead()->next;

        while (nodePtr)
        {
            HashNode<ItemType> aHashNode= nodePtr->item;
            ItemType anItem = aHashNode.getItem();
            insertHash(aHashNode.getKey(), anItem);
            nodePtr = nodePtr->next;
        }
    }
    
    size = newSize;
    delete temp;
}
#endif // _HASH_TABLE
