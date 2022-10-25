#pragma once
#include <iostream>

namespace myList
{
    template<typename T>
    struct nodeT
    {
        T element;
        nodeT* next;
        nodeT()
        {

        }
    };


    template<typename T>
    class List
    {
        private:
            nodeT<T>* head;

        public:
            
            int size;

            List()
            {
                head = nullptr;
                size = 0;
            }

            ~List()
            {
                Clean();
            }

            List(T* array, int arraySize)
            {
                head = nullptr;
                size = 0;
                for (int i = 0; i < arraySize; i++)
                {
                    Add(array[i]);
                }
                
            }

            nodeT<T>* Add(T element)
            {
                nodeT<T>* n = new nodeT<T>;
                n->element = element;
                n->next = nullptr;

                if(head)
                {
                    nodeT<T>* curr = head;
                    while(curr->next)
                    {
                        curr = curr->next;
                    }
                    curr->next = n;
                }else
                {
                    head = n;
                }
                size++;
                return n;
            }

            nodeT<T>* Insert(T element, int index)
            {
                if(index < 0 || index > size)
                    return nullptr;

                nodeT<T>* n = new nodeT<T>;
                n->element = element;

                if(index == 0)
                {
                    nodeT<T>* prevHead = head;
                    head = n;
                    n->next = prevHead;
                    return n;
                }

                nodeT<T>* curr = head;
                for (int i = 0; i < index - 1; i++)
                {
                    curr = curr->next;
                }
                n->next = curr->next;
                curr->next = n;
            }

            bool Contain(T element)
            {
                nodeT<T>* curr = head;
                while(curr)
                {
                    if(curr->element == element)
                    {
                        return true;
                    }
                    curr = curr->next;
                }
                return false;
            }

            void Remove(T element)
            {
                size --;
                if(head)
                {
                    if(head->element == element)
                    {
                        nodeT<T>* prevHead = head;
                        head = head->next;
                        delete prevHead;
                        return;
                    }
                }
                nodeT<T>* curr = head;
                while(curr)
                {
                    if(curr->next->element == element)
                    {
                        nodeT<T>* toDelete = curr->next;
                        curr->next = curr->next->next;
                        delete toDelete;
                        return;
                    }
                    curr = curr->next;
                }
            }

            T* ToArray()
            {
                T* result = new T[size];
                for (int i = 0; i < size; i++)
                {
                    result[i] = (*this)[i];
                }
                return result;
            }

            T* operator [](int index)
            {
                if(index < 0 || index >= size)
                {
                    std::cout << "index out of range | index : " << index << " | size : " << size << std::endl;
                }
                else
                {
                    int i = 0;
                    nodeT<T>* curr = head;
                    while(curr)
                    {
                        if(index == i)
                        {
                            return &curr->element;
                        }
                        curr = curr->next;
                        i++;
                    }
                }
                return 0;
            }

            void Clean()
            {
                nodeT<T>* curr = head;
                nodeT<T>* prev = nullptr;
                while(curr)
                {
                    prev = curr;
                    curr = curr->next;
                    delete prev;
                }
                head = nullptr;
            }

            void Print()
            {
                nodeT<T>* curr = head;
                while(curr)
                    curr = curr->next;
            }
    };
}



