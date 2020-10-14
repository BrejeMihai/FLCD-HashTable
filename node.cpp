#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <typeinfo>
#include <Windows.h>
#include <string>
#include "node.h"

#define NULL_POSITION INT_MAX
 
class HashTable
{
    HashNode<std::string> **theArray;
    int capacity;
    int size;
    HashNode<std::string> *dummy;

public:

    HashTable()
    { 
        capacity = 20;
        size = 0;
        theArray = new HashNode<std::string>*[capacity];

        for (int i = 0; i < capacity; i++)
        {
            theArray[i] = NULL;
        }

        dummy = new HashNode<std::string>("");
    }

    HashTable(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        theArray = new HashNode<std::string>*[capacity];

        for (int i = 0; i < capacity; i++)
        {
            theArray[i] = NULL;
        }

        dummy = new HashNode<std::string>("");
    }

    ~HashTable()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (NULL != theArray[i])
            {
                delete theArray[i];
            }
        }
        delete[] theArray;
    }

    int hashFunction(std::string key)
    {
        int subhash = 0;
        for (unsigned int i = 0; i < key.size(); i++)
        {
            subhash = subhash + int(key[i]);
            subhash = subhash % capacity;
        }
        return subhash;
    }

    void insertNode(std::string key)
    {
        HashNode<std::string> *temp = new HashNode<std::string>(key);

        int hashIndex = hashFunction(key);
  
        while (theArray[hashIndex] != NULL && 0 != theArray[hashIndex]->key.compare(key) && theArray[hashIndex]->key.size() != 1)
        {
            hashIndex++;
            hashIndex %= capacity;
        }

        if (theArray[hashIndex] == NULL || theArray[hashIndex]->key.size() == 0)
        {
            size++;
        }
        theArray[hashIndex] = temp;
    }

    bool deleteNode(std::string key)
    {
        int hashIndex = hashFunction(key);

        while (theArray[hashIndex] != NULL)
        {
            if (theArray[hashIndex]->key == key)
            {
                HashNode<std::string> *temp = theArray[hashIndex];
                theArray[hashIndex] = dummy;
                size--;
                return TRUE;
            }
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL;
    }

    int getPosition(std::string key)
    {
        int hashIndex = hashFunction(key);
        int counter = 0;
        
        while (theArray[hashIndex] != NULL)
        {
            int counter = 0;
            if (counter++ > capacity)
            {
                return NULL_POSITION;
            }

            if (0 == theArray[hashIndex]->key.compare(key))
            {
                return hashIndex;
            }
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL_POSITION;
    }

    int sizeOfTable()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void display()
    {

        for (int i = 0; i < capacity; i++)
        {
                if (theArray[i] != NULL && theArray[i]->key.size() != 0)
                {
                    std::cout << "key-position = { " << theArray[i]->key
                        << ", " << i
                        << " }"
                        << std::endl;
                }
        }
    }
};

void mainString()
{
    HashTable *h = new HashTable;
    h->insertNode("Breje");
    h->insertNode("are");
    h->insertNode("mere");
    h->insertNode("mere");
    h->insertNode("reme");
    h->display();
    std::cout << h->getPosition("reme") << std::endl;
    h->deleteNode("reme");
    h->display();
    system("pause");
}

int main()
{
    mainString();
    return 0;
}
