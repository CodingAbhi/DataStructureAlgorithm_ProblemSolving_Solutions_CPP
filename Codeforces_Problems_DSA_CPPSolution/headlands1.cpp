#include <iostream>
using namespace std;

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};


void makinglist(ListNode*& head, int val) {
    ListNode* newNode = new ListNode(val);
    if (head == nullptr) {
        head = newNode;
    } else {
        ListNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

ListNode* finallist(ListNode* list1, int a, int b, ListNode* list2) {
    ListNode* dummy = new ListNode(0); 
    dummy->next = list1;
    ListNode* curr = dummy;
    ListNode* oldst = nullptr; 
    ListNode* nexend = nullptr; 

    while (curr && curr->next) {
        if (curr->next->val == a) {
            oldst = curr; 
        }
        if (curr->next->val == b) {
            nexend = curr->next->next; 
            break;
        }
        curr = curr->next;
    }

    if (!oldst || !nexend) {
        cout << "WTF, a and b not good" << endl;
        return list1; 
    }


    oldst->next = list2;
    ListNode* list2Tail = list2;
    while (list2Tail->next) {
        list2Tail = list2Tail->next;
    }
    list2Tail->next = nexend;

    return dummy->next;
}

void printList(ListNode* node) {
    while (node) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    ListNode* list1 = nullptr;
    makinglist(list1, 1);
    makinglist(list1, 2);
    makinglist(list1, 3);
    makinglist(list1, 4);
    makinglist(list1, 5);

    ListNode* list2 = nullptr;
    makinglist(list2, 6);
    makinglist(list2, 7);
    makinglist(list2, 8);
    makinglist(list2, 9);

    int a = 2, b = 3;
    ListNode* result = finallist(list1, a, b, list2);
    printList(result);

    return 0;
}
