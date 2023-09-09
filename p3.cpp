#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize()
{
    return size;
}

void PersonList::printByHeight(ostream &os)
{
    Person* temp;
    temp = headHeightList;
    for(int i = 0; i < size; i++){
        os << temp->first << " " << temp->last << ": " << "height=" << temp->height << ", weight=" << temp->weight << endl;
        temp = temp->nextHeight;
    }
}

void PersonList::printByWeight(ostream &os)
{
    Person* temp;
    temp = headWeightList;
    for(int i = 0; i < size; i++){
        os << temp->first << " " << temp->last << ": " << "height=" << temp->height << ", weight=" << temp->weight << endl;
        temp = temp->nextWeight;
    }
}

bool PersonList::exists(string first, string last)
{   
    Person* temp;
    temp = headWeightList;
    for(int i = 0; i < size; i++){
        if(temp->first == first && temp->last == last){
            return true;
        }
        temp = temp->nextWeight;
    }
    return false;
}

int PersonList::getHeight(string first, string last) {
    Person* temp;
    temp = headHeightList;
     for(int i = 0; i < size; i++){
        if(temp->first == first && temp->last == last){
            return temp->height;
        }
        temp = temp->nextHeight;
    }
    return -1;
}

int PersonList::getWeight(string first, string last) {
    Person* temp;
    temp = headWeightList;
     for(int i = 0; i < size; i++){
        if(temp->first == first && temp->last == last){
            return temp->weight;
        }
        temp = temp->nextWeight;
    }
    return -1;
}

bool PersonList::add(string first, string last, int height, int weight)
{
   if (this->exists(first, last))
    {
        return false;
    }
    Person *p = new Person(first, last, height, weight);
     Person* currHeight = headHeightList;
     Person* prevHeight = nullptr;
	
     //find node where height must be inserted
     while(currHeight != nullptr && currHeight->height > p->height){
         prevHeight = currHeight;
         currHeight = currHeight->nextHeight;
     }

     //tiebreaker: tall person before short person
     while (currHeight != nullptr && currHeight->height == p->height && currHeight->weight < p->weight) {
         prevHeight = currHeight;
         currHeight = currHeight->nextHeight;
     }
     //if list is empty
     if(prevHeight == nullptr){
         p->nextHeight = headHeightList;
         headHeightList = p;
     }
     //if there are items in list
     else{
         p->nextHeight = prevHeight->nextHeight;
         prevHeight->nextHeight = p;
     }

     Person* currWeight = headWeightList;
     Person* prevWeight = nullptr;

     //find node where weight must be inserted
     while(currWeight != nullptr && currWeight->weight < p->weight){
         prevWeight = currWeight;
         currWeight = currWeight->nextWeight;
     }

     //tiebreaker: light person before heavy person
     while(currWeight!= nullptr && currWeight->weight == p->weight && currWeight->height > p->height){
         prevWeight = currWeight;
         currWeight = currWeight->nextWeight;
     }
     //if list is empty
     if(prevWeight == nullptr){
         p->nextWeight = headWeightList;
         headWeightList = p;
     }
     //if there are items in list
     else{
         p->nextWeight = prevWeight->nextWeight;
         prevWeight->nextWeight = p;
     }
     this->size++;
     return true;
}

bool PersonList::remove(string first, string last)
{
   if(!this->exists(first, last)){
    return false;
   }
   Person* currHeightPointer;
   Person* prevHeightPointer = nullptr;
   Person* currWeightPointer;
   Person* prevWeightPointer = nullptr;
   currHeightPointer = this->headHeightList;
   currWeightPointer = this->headWeightList;

    for(int i = 0; i < this->size; i++){
        if(currHeightPointer->first == first && currHeightPointer->last == last){
            if(prevHeightPointer == nullptr){
                headHeightList = currHeightPointer->nextHeight;
            }
            else{
                prevHeightPointer->nextHeight = currHeightPointer->nextHeight;
            }
            break;
        }
        prevHeightPointer = currHeightPointer;
        currHeightPointer = currHeightPointer->nextHeight;
    }
    for(int i = 0; i < this->size; i++){
        if(currWeightPointer->first == first && currWeightPointer->last == last){
            if(prevWeightPointer == nullptr){
                headWeightList = currWeightPointer->nextWeight;
            }
            else{
                prevWeightPointer->nextWeight = currWeightPointer->nextWeight;
            }
            delete currWeightPointer;
            size--;
            return true;
        }
        prevWeightPointer = currWeightPointer;
        currWeightPointer = currWeightPointer->nextWeight;
    }
    return false;
}

bool PersonList::updateName(string first, string last, string newFirst, string newLast)
{
    if(!this->exists(first, last)){
        return false;
    }
    Person* temp;
    temp = headHeightList;
     for(int i = 0; i < size; i++){
        if(temp->first == first && temp->last == last){
            temp->first = newFirst;
            temp->last = newLast;
            return true;
        }
        temp = temp->nextHeight;
    }
    return false;
}

bool PersonList::updateHeight(string first, string last, int height)
{
    if(!this->exists(first, last)){
        return false;
    }
    int weight = getWeight(first, last);
    this->remove(first, last);
    this->add(first, last, height, weight);
    return true;
}

bool PersonList::updateWeight(string first, string last, int weight)
{
    if(!this->exists(first, last)){
        return false;
    }
    int height = getHeight(first, last);
    this->remove(first, last);
    this->add(first, last, height, weight);
    return true;
}

PersonList::~PersonList()
{
    if(size != 0){
    Person* temp;
    temp = headWeightList;
    Person* next = temp->nextWeight;
    while(next != nullptr){
        delete temp;
        temp = next;
        next = temp->nextWeight;
    }
    delete temp;
    }
}

PersonList::PersonList(const PersonList &src)
{
    Person* copyPerson;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
    copyPerson = src.headHeightList;
    this->size = 0;
    for(int i = 0; i < src.size; i++){
        this->add(copyPerson->first, copyPerson->last, copyPerson->height, copyPerson->weight);
        copyPerson = copyPerson->nextHeight;
    }
}

const PersonList &PersonList::operator=(const PersonList &src)
{
    Person* copyPerson;
    copyPerson = src.headHeightList;
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
        for(int i = 0; i < src.size; i++){
            this->add(copyPerson->first, copyPerson->last, copyPerson->height, copyPerson->weight);
            copyPerson = copyPerson->nextHeight;
        }
    return *this;
}