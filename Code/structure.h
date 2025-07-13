#include<iostream>
using namespace std;


//Code Below
struct ClothingItem{
    int position;
    string id;
    string name;
    string size;
    string color;
    double price;
    int quantity;
};

struct Element{
    ClothingItem data;
    Element* next;
    Element* previous;
};
struct List{
    int size;
    Element* head;
    Element* tail;
};

List* createEmptyList(){
    List* ls = new List;
    ls->head = nullptr;
    ls->tail = nullptr;
    ls->size = 0;
    return ls;
}
void add_at_nth(List* ls, ClothingItem data, int position) {
    if (position <= 0 || position > ls->size + 1) {
        return;
    }
    ls->size++;
    Element* tmp = new Element;
    tmp->data = data;
    tmp->data.position = position;

    if (position == 1) {
        tmp->next = ls->head;
        tmp->previous = nullptr;
        if (ls->head != nullptr) {
            ls->head->previous = tmp;
        }
        ls->head = tmp;
        if (ls->tail == nullptr) {
            ls->tail = tmp;
        }
    } else {
        Element* current = ls->head;
        for (int i = 1; i < position - 1; ++i) {
            current = current->next;
        }
        tmp->next = current->next;
        tmp->previous = current;
        if (current->next != nullptr) {
            current->next->previous = tmp;
        }
        current->next = tmp;
        if (tmp->next == nullptr) {
            ls->tail = tmp;
        }
    }

    // Increase the position of the next elements
    Element* i = tmp->next;
    while (i != nullptr) {
        i->data.position++;
        i = i->next;
    }

}
void delete_at_nth(List* ls, int position) {
    if (position <= 0 || position > ls->size) {
        return;
    }

    Element* tmp;
    if (position == 1) {
        tmp = ls->head;
        ls->head = ls->head->next;
        if (ls->head != nullptr) {
            ls->head->previous = nullptr;
        } else {
            ls->tail = nullptr;
        }
    } else {
        Element* current = ls->head;
        for (int i = 1; i < position - 1; ++i) {
            current = current->next;
        }
        tmp = current->next;
        current->next = tmp->next;
        if (tmp->next != nullptr) {
            tmp->next->previous = current;
        } else {
            ls->tail = current;
        }
    }

    // Decrease the position of the next elements
    Element* i = tmp->next;
    while (i != nullptr) {
        i->data.position--;
        i = i->next;
    }

    delete tmp;
    ls->size--;
}

void delete_all(List* ls){
    while(ls->size > 0){
        delete_at_nth(ls,1);
    }
}