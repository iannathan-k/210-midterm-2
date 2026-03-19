#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// COMSC-210 | Midterm 2 | Ian Kusmiantoro

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// I'm changing all value ints to string, because I'm assuming that
// The list stores names rather than some random integer which doesn't mean anything

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    string getNodeDataAt(int pos) {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return "";
        }

        for (int i = 0; i < pos && current; i++) {
            current = current->next;
        } 

        return current->data;
    }

    string getNodeDataAtTail() {
        if (!tail) {
            cout << "List is empty." << endl;
            return "";
        }
        return tail->data;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    DoublyLinkedList* store_queue = new DoublyLinkedList();
    ifstream fin;
    int length = 0;

    fin.open("names.txt");

    // Store Opens
    
    cout << "STORE OPENS" << endl;
    for (int i = 0; i < 5; i++) {
        string name;
        fin >> name;
        cout << name << " joined the line" << endl;
        store_queue->push_back(name);
        length++;
    }

    cout << "Resulting line: ";
    store_queue->print();

    // Next 20 minutes

    for (int i = 1; i <= 20; i++) {
        cout << "TIME STEP #" << i << endl;

        string name;
        int probability;
        
        probability = rand() % 100 + 1;
        if (probability <= 40) {
            cout << store_queue->getNodeDataAt(0) << " is served" << endl;
            store_queue->pop_front();
            length--;
        }

        probability = rand() % 100 + 1;
        if (probability <= 60) {
            fin >> name;
            cout << name << " joined the line" << endl;
            store_queue->push_back(name);
        }

        probability = rand() % 100 + 1;
        if (probability <= 20) {
            cout << store_queue->getNodeDataAtTail() << " (at the rear) left the line" << endl;
            store_queue->pop_back();
        }

        probability = rand() % 100 + 1;
        if (probability <= 10) {
            // This particular requirement is a bit ambiguous, as I don't know whether
            // It's a 10% chance someone leaves, or a 10% chance for each person to leave
            // But I interpret it to be a 10% for a random person to leave


        }

        probability = rand() % 100 + 1;
        if (probability <= 10) {
            fin >> name;
            cout << name << " (VIP) joins the front of the line" << endl;
            store_queue->push_front(name + " (VIP)");
        }

        cout << "Resulting line: ";
        store_queue->print();
    }
    
    return 0;
}