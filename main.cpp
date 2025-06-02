#pragma once
#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <queue>
using namespace std;

class Task 
{
public:
    int taskID;
    string description;
    int priorityLevel;
    string assigneeID;

    Task() : taskID(-1), description(""), priorityLevel(-1), assigneeID("") {}
    Task(int ID, const std::string& desc, int priority, string assigneeID2)
        : taskID(ID), description(desc), priorityLevel(priority), assigneeID(assigneeID2) {}
};

class Assignee {
public:
    int assigneeID;
    string firstName;
    string lastName;
    string ID;
    string address;
    string dob;
    int* tasks;

    Assignee() : assigneeID(1), firstName(""), lastName(""), ID(""), address(""), dob(""), tasks(NULL){}

    Assignee(const std::string& first, const std::string& last, const string address1, const string dob1)
    {
        firstName = first;
        lastName = last;
        assigneeID = 1;
        address = address1;
        dob = dob1;
        tasks = new int[100];

        for (int i = 0; i < 100; i++)
        {
            tasks[i] = -1;
        }
    }
        
};


class Node 
{
public:
    
    Assignee assignee;
    bool is_red;
    Node* left, * right, * parent;
    bool is_deleted;

    Node()
    {
        assignee = {"", "", "", ""};
        is_red = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
        is_deleted = 0;
    }

    Node(Assignee val) : assignee(val), is_red(true), left(nullptr), right(nullptr), parent(nullptr), is_deleted(0) {}
};

class RedBlackTree 
{


public:
    int assigneeCount;
    Node* root;

    RedBlackTree()
    {
        root = NULL;
        assigneeCount = 1;
    }

    void leftRotate(Node* x) 
    {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) 
    {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void insertFixup(Node* z) 
    {
        while (z != root && z->parent->is_red) 
        {
            if (z->parent == z->parent->parent->left) 
            {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->is_red) 
                {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                }
                else 
                {
                    if (z == z->parent->right) 
                    {

                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    rightRotate(z->parent->parent);
                }
            }
            else 
            {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->is_red) 
                {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                }
                else 
                {
                    if (z == z->parent->left) 
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->is_red = false;
    }

    void transplant(Node* u, Node* v) 
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    void deleteNode(Node* z) 
    {
        Node* y = z;
        Node* x;
        bool y_original_color = y->is_red;
        if (z->left == nullptr) 
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) 
        {
            x = z->left;
            transplant(z, z->left);
        }
        else 
        {
            y = findMinimum(z->right);
            y_original_color = y->is_red;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else 
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->is_red = z->is_red;
        }
        if (!y_original_color) 
        {
            deleteFixup(x);
        }
    }

    void deleteFixup(Node* x) 
    {
        while (x != root && !x->is_red) 
        {
            if (x == x->parent->left) 
            {
                Node* w = x->parent->right;
                if (w->is_red) 
                {
                    w->is_red = false;
                    x->parent->is_red = true;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (!w->left->is_red && !w->right->is_red) 
                {
                    w->is_red = true;
                    x = x->parent;
                }
                else 
                {
                    if (!w->right->is_red) 
                    {
                        w->left->is_red = false;
                        w->is_red = true;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->right->is_red = false;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else 
            {
                Node* w = x->parent->left;
                if (w->is_red) 
                {
                    w->is_red = false;
                    x->parent->is_red = true;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (!w->right->is_red && !w->left->is_red) 
                {
                    w->is_red = true;
                    x = x->parent;
                }
                else 
                {
                    if (!w->left->is_red) 
                    {
                        w->right->is_red = false;
                        w->is_red = true;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->left->is_red = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->is_red = false;
    }

    Node* findMinimum(Node* node) 
    {
        while (node->left != nullptr) 
        {
            node = node->left;
        }
        return node;
    }

    Node* findSuccessor(Node* node) 
    {
        if (node->right != nullptr)
            return findMinimum(node->right);

        Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) 
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    void insert(Assignee key) 
    {
        Node* newNode = new Node(key);
        newNode->assignee.ID = generateAssigneeID();
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) 
        {
            y = x;
            if (newNode->assignee.assigneeID < x->assignee.assigneeID)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;

        if (y == nullptr)
            root = newNode;
        else if (newNode->assignee.assigneeID < y->assignee.assigneeID)
            y->left = newNode;
        else
            y->right = newNode;

        insertFixup(newNode);
        
        assigneeCount++;
    }



    string generateAssigneeID() 
    {
        std::ostringstream oss;
        oss << "A" << std::setfill('0') << std::setw(3) << assigneeCount;
        return oss.str();
    }

    //// Remove
    //void remove(int key) {
    //    Node* z = root;
    //    while (z != nullptr) {
    //        if (key == z->assignee.assigneeID) {
    //            deleteNode(z);
    //            return;
    //        }
    //        else if (key < z->assignee.assigneeID) {
    //            z = z->left;
    //        }
    //        else {
    //            z = z->right;
    //        }
    //    }
    //    std::cout << "Node with key " << key << " not found in the tree." << std::endl;
    //}

    Node* removeHelper(Node* node, const string& ID) 
    {
        if (node == NULL) 
        {
            return node;
        }

        if (ID < node->assignee.ID) 
        {
            node->left = removeHelper(node->left, ID);
        }

        else if (ID > node->assignee.ID) 
        {
            node->right = removeHelper(node->right, ID);
        }

        else 
        {
            if (node->left == nullptr) 
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == nullptr) 
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMinimum(node->right);
            node->assignee.ID = temp->assignee.ID;
            node->right = removeHelper(node->right, temp->assignee.ID); 
        }

        return node;
    }


    void remove(const std::string& ID)
    {
        root = removeHelper(root, ID);
    }

    void inorderTraversal(Node* node, std::stringstream& output) 
    {
        if (node == nullptr)
            return;

        inorderTraversal(node->left, output);

        if (!node->is_deleted) 
        {
            output << "Name: " << node->assignee.firstName << " " << node->assignee.lastName
                << ", Address: " << node->assignee.address
                << ", DOB: " << node->assignee.dob
                << ", Assignee ID: " << node->assignee.ID << "\n";
        }
        inorderTraversal(node->right, output);
    }

    void inorderTraversal2(Node* node, std::stringstream& output)
    {
        if (node == nullptr)
            return;


        inorderTraversal2(node->left, output);


        output << node->assignee.ID << " (" << (node->is_red ? "red" : "black") << ")\n";
        inorderTraversal2(node->right, output);
    }

    Node* searchAssigneeByID(const std::string& ID1) 
    {
        Node* currentNode = root;

        while (currentNode != nullptr && currentNode->assignee.ID != ID1) 
        {
            if (ID1 < currentNode->assignee.ID) 
            {
                currentNode = currentNode->left;
            }
            else 
            {
                currentNode = currentNode->right;
            }
        }

        return currentNode;
    }

    queue<Node*> searchAssigneeByName(const std::string& first, const std::string& last) 
    {
        queue<Node*> matchingNodes;
        Node* currentNode = root;

        if (currentNode == nullptr) 
        {
            return matchingNodes;
        }

        queue<Node*> nodeQueue;
        nodeQueue.push(currentNode);

        while (!nodeQueue.empty()) 
        {
            Node* current = nodeQueue.front();
            nodeQueue.pop();

            if (current->assignee.firstName == first && current->assignee.lastName == last) 
            {
                matchingNodes.push(current);
            }

            if (current->left != nullptr) 
            {
                nodeQueue.push(current->left);
            }

            if (current->right != nullptr) 
            {
                nodeQueue.push(current->right);
            }
        }

        return matchingNodes;
    }

    void addAssigneeTask(int task_ID, string a_ID)
    {
        Node* ptr = searchAssigneeByID(a_ID);
        for (int i = 0; i < 100; i++)
        {
            if (ptr->assignee.tasks[i] == -1)
            {
                ptr->assignee.tasks[i] = task_ID;
                break;
            }
        }
    }

    queue<Node*> searchByNoTask() 
    {
        queue<Node*> matchingNodes;
        inorderTraversalNoTask(root, matchingNodes);
        return matchingNodes;
    }

    void inorderTraversalNoTask(Node* node, queue<Node*>& matchingNodes) 
    {
        if (node == nullptr)
            return;

        inorderTraversalNoTask(node->left, matchingNodes);

        if (node->assignee.tasks[0] == -1) {
            matchingNodes.push(node);
        }

        inorderTraversalNoTask(node->right, matchingNodes);
    }


    int* removeTask(string ID1)
    {
        int* removed_tasks = new int[100];
        int count = 0;
        Node* ptr = searchAssigneeByID(ID1);

        for (int i = 0; i < 100; i++)
        {
            if (ptr->assignee.tasks[i] != -1)
            {
                removed_tasks[count++] = ptr->assignee.tasks[i];
                ptr->assignee.tasks[i] = -1;
            }
        }

        return removed_tasks;
    }

    queue<Assignee> rearrangeTree(Node* node, queue<Assignee>& Q1, string ID)
    {
        if (node == NULL)
            return Q1;

        Node* temp = node;
        Node* node2 = searchAssigneeByID(ID);

        rearrangeTree(node->left, Q1, ID);


        if (node != node2)
        {
            Q1.push(node->assignee);
        }

        else if (node->assignee.tasks[0] != -1)
        {
            Q1.push(node->assignee);
        }

        rearrangeTree(node->right, Q1, ID);

        return Q1;
    }

    void markDeleted(string ID)
    {
        Node* node = searchAssigneeByID(ID);
        if (node->assignee.tasks[0] == -1)
            node->is_deleted = 1;
    }

    void assignColors(Node* node) 
    {
        if (node == nullptr)
            return;

        queue<Node*> nodeQueue;
        nodeQueue.push(node);

        while (!nodeQueue.empty()) {
            int levelSize = nodeQueue.size();
            bool isRed = false; 

            for (int i = 0; i < levelSize; ++i) 
            {
                Node* current = nodeQueue.front();
                nodeQueue.pop();

                current->is_red = isRed ? 1 : 0;

                if (current->left != nullptr)
                    nodeQueue.push(current->left);
                if (current->right != nullptr)
                    nodeQueue.push(current->right);

                isRed = !isRed;
            }
        }
    }

};



class T_Node
{
public:

    Task task;
    bool is_red; 
    T_Node* left, * right, * parent;
    bool completed, deleted;

    T_Node()
    {
        task = { 0, "", 0, ""};
        is_red = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
        completed = 0;
        deleted = 0;
    }

    T_Node(Task val) : task(val), is_red(true), deleted(0), left(nullptr), right(nullptr), parent(nullptr), completed(0) {}
};

class T_RedBlackTree
{

public:
    T_Node* root;
    int count;

    T_RedBlackTree() : root(nullptr), count(0) {}

    void leftRotate(T_Node* x) {
        T_Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(T_Node* y) {
        T_Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void insertFixup(T_Node* z) {
        while (z != root && z->parent->is_red) {
            if (z->parent == z->parent->parent->left) {
                T_Node* y = z->parent->parent->right;
                if (y != nullptr && y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    rightRotate(z->parent->parent);
                }
            }
            else {
                T_Node* y = z->parent->parent->left;
                if (y != nullptr && y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->is_red = false;
    }

    void transplant(T_Node* u, T_Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    void deleteNode(T_Node* z) {
        T_Node* y = z;
        T_Node* x;
        bool y_original_color = y->is_red;
        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = findMinimum(z->right);
            y_original_color = y->is_red;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->is_red = z->is_red;
        }
        if (!y_original_color) {
            deleteFixup(x);
        }
    }

    void deleteFixup(T_Node* x) {
        while (x != root && !x->is_red) {
            if (x == x->parent->left) {
                T_Node* w = x->parent->right;
                if (w->is_red) {
                    w->is_red = false;
                    x->parent->is_red = true;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (!w->left->is_red && !w->right->is_red) {
                    w->is_red = true;
                    x = x->parent;
                }
                else {
                    if (!w->right->is_red) {
                        w->left->is_red = false;
                        w->is_red = true;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->right->is_red = false;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                T_Node* w = x->parent->left;
                if (w->is_red) {
                    w->is_red = false;
                    x->parent->is_red = true;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (!w->right->is_red && !w->left->is_red) {
                    w->is_red = true;
                    x = x->parent;
                }
                else {
                    if (!w->left->is_red) {
                        w->right->is_red = false;
                        w->is_red = true;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->left->is_red = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->is_red = false;
    }

    T_Node* findMinimum(T_Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    T_Node* findSuccessor(T_Node* node) {
        if (node->right != nullptr)
            return findMinimum(node->right);

        T_Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    void insert(Task key) {
        T_Node* newNode = new T_Node(key);
        T_Node* y = nullptr;
        T_Node* x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->task.priorityLevel < x->task.priorityLevel)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;

        if (y == nullptr)
            root = newNode;
        else if (newNode->task.priorityLevel < y->task.priorityLevel)
            y->left = newNode;
        else
            y->right = newNode;

        insertFixup(newNode);
        count++;
    }

    void remove(int key) {
        T_Node* z = root;
        while (z != nullptr) {
            if (key == z->task.priorityLevel) {
                deleteNode(z);
                return;
            }
            else if (key < z->task.priorityLevel) {
                z = z->left;
            }
            else {
                z = z->right;
            }
        }
        std::cout << "T_Node with key " << key << " not found in the tree." << std::endl;
        count--;
    }

    void inorderTraversal(T_Node* node, std::stringstream& output) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left, output);
        output << node->task.taskID << " (" << (node->is_red ? "red" : "black") << ")\n";
        inorderTraversal(node->right, output);
    }

    T_Node* searchTaskByTaskID(const int& ID1) {
        T_Node* currentNode = root;

        while (currentNode != nullptr && currentNode->task.taskID != ID1) {
            if (ID1 > currentNode->task.taskID) {
                currentNode = currentNode->left;
            }
            else {
                currentNode = currentNode->right;
            }
        }

        return currentNode; 
    }

    void changeAssigneeID(const int* task_ID, string ID2)
    {
        T_Node* ptr;
        int count = 0;

        while (ptr = searchTaskByTaskID(task_ID[count]))
        {  
            ptr->task.assigneeID = ID2;
            count++;
        }
    }

    void printTasksByPriority(T_Node* node, std::stringstream& output, RedBlackTree* tree2) {
        if (node == nullptr)
            return;

        RedBlackTree* tree = tree2;
        Node* node2 = tree->searchAssigneeByID(node->task.assigneeID);

        printTasksByPriority(node->left, output, tree);
        if (node->completed == 0) {
            output << "Task ID: " << node->task.taskID
                << ", Description: " << node->task.description
                << ", Priority: " << node->task.priorityLevel
                << ", Assignee: " << node2->assignee.firstName << " (" << node->task.assigneeID << ")" << "\n";
        }
        printTasksByPriority(node->right, output, tree);
    }

    void findHighest(T_Node* node, std::stringstream& output, RedBlackTree* tree2)
    {
        if (node == nullptr)
            return;


        RedBlackTree* tree = tree2;
        Node* node2 = tree->searchAssigneeByID(node->task.assigneeID);

        if (node->right != nullptr) {
            findHighest(node->right, output, tree);
            return;
        }

        output << "Task ID: " << node->task.taskID
            << ", Description: " << node->task.description
            << ", Priority: " << node->task.priorityLevel
            << ", Assignee: " << node2->assignee.firstName << " (" << node->task.assigneeID << ")" << "\n";
    }

    void displayTasks(T_Node* node, std::stringstream& output, RedBlackTree* tree2, string ID, int& count)
    {
        if (node == nullptr)
            return;

        RedBlackTree* tree = tree2;
        Node* node2 = tree->searchAssigneeByID(node->task.assigneeID);

        displayTasks(node->left, output, tree, ID, count);

        if (node->task.assigneeID == ID)
        {
            if (count == 1)
            {
                output << "Tasks Assigned to \"" << node2->assignee.firstName << " (" << node->task.assigneeID << ")\":" << "\n";
                count++;
            }

               output << "Task ID: " << node->task.taskID
                << ", Description: " << node->task.description
                << ", Priority: " << node->task.priorityLevel
                << ", Assignee: " << node2->assignee.firstName << " (" << node->task.assigneeID << ")" << "\n";
        }
        displayTasks(node->right, output, tree, ID, count);
    }

    void printPriorityRange(int lower, int higher, std::stringstream& output, T_Node* node, RedBlackTree* tree2, int& count)
    {
        if (node == nullptr)
            return;

        RedBlackTree* tree = tree2;
        Node* node2 = tree->searchAssigneeByID(node->task.assigneeID);

        printPriorityRange(lower, higher, output, node->left, tree2, count);

        if (node->task.priorityLevel >= lower && node->task.priorityLevel <= higher)
        {
            if (count == 1)
            {
                output << "Tasks within Priority Range (1 to 2):\n";
                count++;
            }

            output << "Task ID: " << node->task.taskID
                << ", Description: " << node->task.description
                << ", Priority: " << node->task.priorityLevel
                << ", Assignee: " << node2->assignee.firstName << " (" << node->task.assigneeID << ")" << "\n";
        }
        printPriorityRange(lower, higher, output, node->right, tree2, count);
    }

    void markCompleted(int ID1)
    {
        T_Node* node;
        node = searchTaskByTaskID(ID1);
        node->completed = 1;
    }

    void printByCompletedTasks(std::stringstream& output, T_Node* node, RedBlackTree* tree2, int& count)
    {
        if (node == nullptr)
            return;

        RedBlackTree* tree = tree2;
        Node* node2 = tree->searchAssigneeByID(node->task.assigneeID);

        printByCompletedTasks(output, node->left, tree2, count);

        if (node->completed == 1)
        {
            if (count == 1)
            {
                output << "Completed Tasks:\n";
                count++;
            }

            output << "Task ID: " << node->task.taskID
                << ", Description: " << node->task.description
                << ", Priority: " << node->task.priorityLevel
                << ", Assignee: " << node2->assignee.firstName << " (" << node->task.assigneeID << ")" << "\n";
        }
        printByCompletedTasks(output, node->right, tree2, count);
    }

    queue<Task> rearrangeTree(T_Node* node, queue<Task>& Q1)
    {
        if (node == NULL)
            return Q1;
        
        T_Node* temp = node;

        rearrangeTree(node->left, Q1);
        if (!node->completed && !node->deleted)
            Q1.push(node->task);
        rearrangeTree(node->right, Q1);

        return Q1;
    }

    T_RedBlackTree* makeNewTree(queue<Task>& Q1, T_RedBlackTree* T_tree)
    {
        T_Node* node;
        T_RedBlackTree* tree = new T_RedBlackTree();

        while (!Q1.empty())
        {
            tree->insert(Q1.front());
            Q1.pop();
        }

        return tree;
    }

    queue<Task> updatePriority(int ID1, int priority, T_RedBlackTree* T_tree)
    {
        T_Node* node;
        node = searchTaskByTaskID(ID1);
        //remove(ID1);
        node->task.priorityLevel = priority;
        //insert(node->task);
        queue<Task> Q1;
        //remove(node->task.taskID);
        //insert(node->task);
        return rearrangeTree(root, Q1);
        
    }

    void assignColors(T_Node* node)
    {
        if (node == nullptr)
            return;

        queue<T_Node*> nodeQueue;
        nodeQueue.push(node);

        while (!nodeQueue.empty()) {
            int levelSize = nodeQueue.size();
            bool isRed = false;

            for (int i = 0; i < levelSize; ++i)
            {
                T_Node* current = nodeQueue.front();
                nodeQueue.pop();

                current->is_red = isRed ? 1 : 0;

                if (current->left != nullptr)
                    nodeQueue.push(current->left);
                if (current->right != nullptr)
                    nodeQueue.push(current->right);

                isRed = !isRed;
            }
        }
    }

    void removeNode(T_Node* node) {
        if (node->is_red) {
            if (node->left && node->right) {
                // Child x 2
                // Find successor, then fill 'node' with successor
                T_Node* successor = node->right;
                while (successor->left)
                    successor = successor->left;
                node->task = successor->task;
                removeNode(successor);
            }
            else if (node->left) {
                // Only left child
                // Fill 'node' with left child
                node->task = node->left->task;
                node->is_red = node->left->is_red;
                removeNode(node->left);
            }
            else if (node->right) {
                // Only right child
                // Fill 'node' with right child
                node->task = node->right->task;
                node->is_red = node->right->is_red;
                removeNode(node->right);
            }
            else {
                // No child
                if (node->parent == nullptr) {
                    delete node;
                    root = nullptr;
                    return;
                }
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
                delete node;
            }
        }
        else {
            if (node->left && node->right) {
                // Child x 2
                // Find successor, then fill 'node' with successor
                T_Node* successor = node->right;
                while (successor->left)
                    successor = successor->left;
                node->task = successor->task;
                removeNode(successor);
            }
            else if (node->left) {
                // Only left child
                // Fill 'node' with left child
                node->task = node->left->task;
                removeNode(node->left);
            }
            else if (node->right) {
                // Only right child
                // Fill 'node' with right child
                node->task = node->right->task;
                removeNode(node->right);
            }
            else {
                // No child
                if (node->parent == nullptr) {
                    // 'node' is root
                    delete node;
                    root = nullptr;
                    return;
                }
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                    if (node->parent->right && node->parent->right->is_red) {
                        node->parent->right->is_red = false;
                        leftRotate(node->parent);
                    }
                }
                else {
                    node->parent->right = nullptr;
                    if (node->parent->left && node->parent->left->is_red) {
                        node->parent->left->is_red = false;
                        rightRotate(node->parent);
                    }
                }
                if (!node->parent->left && !node->parent->right && node->parent->parent) {
                    // 'node->parent->parent' must be RED
                    rightRotate(node->parent->parent);
                }
                delete node;
            }
        }
    }

    bool remove2(int key) {
        T_Node* curr = root;
        T_Node* parent = nullptr;
        while (curr) {
            parent = curr;
            if (key == curr->task.priorityLevel)
                break;
            if (key > curr->task.priorityLevel)
                curr = curr->right;
            else
                curr = curr->left;
        }
        if (!curr || curr->task.priorityLevel != key)
            return false;

        if (!curr->left || !curr->right)
            removeNode(curr);
        else {
            T_Node* successor = curr->right; 
            while (successor->left)
                successor = successor->left;
            curr->task.priorityLevel = successor->task.priorityLevel;
            removeNode(curr);
        }

        return true;
    }


};

class taskManagementSystem
{
public:

    RedBlackTree* A_tree;
    T_RedBlackTree* T_tree;
    queue<Task> plsWork;

    taskManagementSystem()
    {
        A_tree = new RedBlackTree();
        T_tree = new T_RedBlackTree();
    }

    void addAssignee(string a, string b, string c, string d)
    {
        Assignee a1(a, b, c, d);
        A_tree->insert(a1);
    }

    Assignee searchByID(string assigneeID)
    {
        Node* n1 = A_tree->searchAssigneeByID(assigneeID);
        Assignee a1 = n1->assignee;
        return a1;
    }

    void displaybyID(std::stringstream& output, const std::string& assigneeID)
    {
        Assignee assignee = searchByID(assigneeID);
        output.str(""); 

        output << "Name: " << assignee.firstName << " " << assignee.lastName
            << ", Address: " << assignee.address
            << ", DOB: " << assignee.dob
            << ", Assignee ID: " << assignee.ID << "\n";
    }

    void displaybyname(std::stringstream& output, const std::string& firstName, const string& lastName)
    {
        output.str("");
        queue<Node*> matchingNodes = A_tree->searchAssigneeByName(firstName, lastName);

        while (!matchingNodes.empty()) {
            Node* matchingNode = matchingNodes.front();

            Assignee assignee = matchingNode->assignee;

            output << "Name: " << assignee.firstName << " " << assignee.lastName
                << ", Address: " << assignee.address
                << ", DOB: " << assignee.dob
                << ", Assignee ID: " << assignee.ID << "\n";

            matchingNodes.pop();
        }
    }

    void addTask(int a, string b, int c, string d)
    {
        Task t1(a, b, c, d);
        T_tree->insert(t1);
        A_tree->addAssigneeTask(a, d);
        plsWork.push(t1);
    }

    void AssigneeWithNoTask(std::stringstream& output)
    {
        output.str("");
        queue<Node*> matchingNodes = A_tree->searchByNoTask();

        while (!matchingNodes.empty()) {
            Node* matchingNode = matchingNodes.front();

            Assignee assignee = matchingNode->assignee;

            output << "Name: " << assignee.firstName << " " << assignee.lastName
                << ", Address: " << assignee.address
                << ", DOB: " << assignee.dob
                << ", Assignee ID: " << assignee.ID << "\n";

            matchingNodes.pop();
        }

    }

    void ShiftTask(string ID1, string ID2)
    {
        int* task_ID = new int[100];
        for (int i = 0; i < 100; i++)
        {
            task_ID[i] = -1;
        }

        task_ID = A_tree->removeTask(ID1);
        T_tree->changeAssigneeID(task_ID, ID2);

        for (int i = 0; i < 100; i++)
        {
            if (task_ID[i] != -1)
            {
                A_tree->addAssigneeTask(task_ID[i], ID2);
            }
        }

        delete [] task_ID;
    }

    void printTaskQueue(std::stringstream& output)
    {
        T_tree->printTasksByPriority(T_tree->root, output, A_tree);
    }

    int convertStringToInt(const std::string& inputString) 
    {
        std::string numericPart = inputString.substr(1); 
        return std::stoi(numericPart); 
    }


    //void DeleteAssignee(string ID)
    //{
    //    int ID2 = convertStringToInt(ID);
    //    A_tree->remove(ID2);
    //}

    void DeleteAssignee(const std::string& ID)
    {
        Node* assigneeNode = A_tree->searchAssigneeByID(ID);

        if (assigneeNode != NULL)
        {
            if (assigneeNode->assignee.tasks[0] == -1) 
            {
                A_tree->remove(ID);
                //A_tree->deleteFixup(assigneeNode);
                A_tree->assignColors(A_tree->root);
            }
        }
    }

    //void DeleteAssignee(const std::string& ID)
    //{
    //    queue<Assignee> Q1;
    //    Q1 = A_tree->rearrangeTree(A_tree->root, Q1, ID);
    //    delete A_tree;
    //    A_tree = new RedBlackTree();

    //    while (!Q1.empty())
    //    {
    //        A_tree->insert(Q1.front());
    //        Q1.pop();
    //    }
    //}

    //void DeleteAssignee(const std::string& ID)
    //{
    //    A_tree->markDeleted(ID);
    //    A_tree->assignColors(A_tree->root);
    //}

    void DisplayAssignee(std::stringstream& output)
    {
        A_tree->inorderTraversal(A_tree->root, output);
    }

    void findHighestPriorityTask(std::stringstream& output)
    {
        T_tree->findHighest(T_tree->root, output, A_tree);
    }

    void findTasksByAssignee(string ID, std::stringstream& output)
    {
        int count = 1;
        output.str("");
        int ID2 = convertStringToInt(ID);
        T_tree->displayTasks(T_tree->root, output, A_tree, ID, count);
    }

    void countTotalTasks(std::stringstream& output)
    {
        output << "Total Tasks in the System: " << T_tree->count << "\n";
    }

    void searchTasksByPriorityRange(int lower, int higher, std::stringstream& output)
    {
        int count = 1;
        T_tree->printPriorityRange(lower, higher, output, T_tree->root, A_tree, count);
    }

    void PrintTreeInorder(std::stringstream& output)
    {
        T_tree->inorderTraversal(T_tree->root, output);
    }

    void AssigneeInOrder(std::stringstream& output)
    {
       // output.str("");
        A_tree->inorderTraversal2(A_tree->root, output);
    }

    void completeTask(int ID1)
    {
        T_tree->markCompleted(ID1);
    }

    void displayCompletedTasks(std::stringstream& output)
    {
        int count = 1;
        T_tree->printByCompletedTasks(output, T_tree->root, A_tree, count);
    }

    void updateTaskPriority(int ID1, int priority)
    {
        queue<Task> Q1, Q2;
        Q1 = T_tree->updatePriority(ID1, priority, T_tree);
        //T_tree = T_tree->makeNewTree(Q1, T_tree);
        delete T_tree;
        //delete A_tree;
        T_tree = new T_RedBlackTree();
        //A_tree = new RedBlackTree();
        while (!Q1.empty())
        {
            T_tree->insert(Q1.front());
            Q1.pop();
        }

        T_tree->assignColors(T_tree->root);
    }

    //void deleteTask(int ID)
    //{
    //    T_Node* node = T_tree->searchTaskByTaskID(ID);
    //    T_tree->remove2(node->task.priorityLevel);
    //    //T_tree->deleteFixup(T_tree->root);
    //}

    void deleteTask(int ID)
    {
        T_Node* node = T_tree->searchTaskByTaskID(ID);
        queue<Task> Q1;

        while (!plsWork.empty())
        {
            if (plsWork.front().taskID != ID)
            {
                Q1.push(plsWork.front());
            }
            plsWork.pop();
        }
        
        //Q1 = T_tree->rearrangeTree(T_tree->root, Q1);
        delete T_tree;
        T_tree = new T_RedBlackTree();

        while (!Q1.empty())
        {
            Task task = Q1.front();
            Q1.pop();
            T_tree->insert(task);
        }

        //T_tree->deleteFixup(T_tree->root);
        //T_tree->assignColors(T_tree->root);

    }
};

