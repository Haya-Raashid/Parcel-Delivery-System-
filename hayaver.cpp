#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Package{
    string id;
    string destination;
    float weight;
    int priority;
    string senderName;
    string receiverName;
    string status;
    string deliveryDate;
};

struct AreaInfo{
    string areaName;
    int parcelCount;
};

struct QNode{
    Package pkg;
    QNode*next;
};

class Queue{
private:
    QNode*front;
    QNode*rear;
public:
    Queue(){
        front=nullptr;
        rear = nullptr;
    }

    void enqueue(Package p){
        QNode *newNode = new QNode();
        newNode->pkg  = p;
        newNode->next = nullptr;
        if(front == nullptr){
            front = rear = newNode;
        }else{
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue(){
        if (isEmpty()){
            cout << "Queue is empty.\n";
            return;
        }
        QNode *temp = front;
        if (front == rear){
            front = rear = nullptr;
        }
        else{
            front = front->next;
        }
        delete temp;
    }

    bool isEmpty(){
        return front == nullptr;
    }

    Package peek(){
        if(isEmpty()){
            cout << "Queue is Empty\n";
            return Package(); 
        }
        return front->pkg;
    }

    void displayQueue(){
        if(isEmpty()){
            cout << "Queue is empty.\n";
            return;
            }
        QNode *temp = front;
        while(temp != nullptr){
            cout << temp->pkg.id <<" | "
                 << temp->pkg.destination <<" | "
                 << temp->pkg.weight <<" kg | "
                 << "Priority: "<<temp->pkg.priority <<" | "
                 << temp->pkg.senderName <<" -> "
                 << temp->pkg.receiverName<<" | "
                 << temp->pkg.status <<" | "
                 << temp->pkg.deliveryDate<< "\n";
            temp = temp->next;
        }
    }
};

struct Node{
    Package pkg;
    Node *next;
    Node *prev;
};

class DLL{
private:
    Node *head;
    Node *tail;
public:
    DLL(){
        head = nullptr;
        tail = nullptr;
    }

    void insertPackage(Package p){
        Node *newNode  = new Node();
        newNode->pkg = p;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        if(head == nullptr){
            head = tail = newNode;
        } 
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    bool deletePackage(string ID)
    {
        Node *temp = head;
        while(temp != nullptr){
            if(temp->pkg.id == ID){
                if(temp == head && temp == tail){
                    head = tail = nullptr;
                }
                else if(temp == head){
                    head = head->next;
                    head->prev = nullptr;
                }
                else if(temp == tail){
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                else{
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                delete temp;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    void buildqueue(Queue &q){
        Node *temp = head;
        while(temp != nullptr){
            q.enqueue(temp->pkg);
            temp = temp->next;
        }
    }

    void display(){
        Node *temp = head;
        if (temp == nullptr){
            cout<<"No packages.\n"; 
            return;
        }
        cout<< "\n--- Package List ---\n";
        while(temp != nullptr){
            cout << "ID: "      << temp->pkg.id << " | Dest: "  << temp->pkg.destination
                << " | "        << temp->pkg.weight << " kg" << " | Pri: "   << temp->pkg.priority
                << " | From: "  << temp->pkg.senderName << " | To: "    << temp->pkg.receiverName
                << " | Status: "<< temp->pkg.status << " | Date: "  << temp->pkg.deliveryDate << "\n";
            temp = temp->next;
        }
    }

    void buildAreaData(vector<string> &areaNames, vector<int> &counts){
        Node *temp = head;
        while (temp != nullptr){
            string area  = temp->pkg.destination;
            bool found = false;
            for (size_t i = 0; i < areaNames.size(); i++){
                if (areaNames[i] == area){
                    counts[i]++; found = true;
                    break; 
                }
            }
            if(!found){
                areaNames.push_back(area);
                counts.push_back(1); 
            }
            temp = temp->next;
        }
    }
};

struct AVLNode{
    AreaInfo area;
    int height;
    AVLNode *left;
    AVLNode *right;
};

class AVL{
private:
    AVLNode *root;

    int height(AVLNode *n){
        if(n==nullptr){
            return 0;
        }
        else{
            return n->height;
        }
    }
    int balanceFactor(AVLNode *n){
        if (n==nullptr){
            return 0;
        }
        else{
            return height(n->left) - height(n->right);
        }
    }
    void updateHeight(AVLNode *n){
        if (n != nullptr){
            int leftHeight = height(n->left);
            int rightHeight = height(n->right);
            if(leftHeight > rightHeight){
                n->height = 1 + leftHeight;
            }
            else{
                n->height = 1 + rightHeight;
            }
        }
    }
    // Rotations
    AVLNode* rotateRight(AVLNode *y){
        AVLNode*x  = y->left;
        AVLNode*T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode *x){
        AVLNode*y  = x->right;
        AVLNode*T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* rebalance(AVLNode *node){
        updateHeight(node);
        int bf = balanceFactor(node);

        // Left-Left
        if (bf > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);
        // Left-Right
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Right
        if (bf < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);
        // Right-Left
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode* insert(AVLNode *node, const AreaInfo &a){
        if(node ==nullptr){
            AVLNode *n = new AVLNode();
            n->area = a;
            n->height = 1;
            n->left = n->right = nullptr;
            return n;
        }
        if(a.parcelCount < node->area.parcelCount){
            node->left = insert(node->left,  a);
        }    
        else{
            node->right = insert(node->right, a);
        }
        return rebalance(node);
    }

    void inorder(AVLNode *node){
        if(!node){
            return;
        }
        inorder(node->left);
        cout << node->area.areaName << " -> " << node->area.parcelCount << " parcels"
             << "  (h=" << node->height << ")\n";
        inorder(node->right);
    }

public:
    AVL(){
        root = nullptr; 
    }

    void insertArea(const AreaInfo &a){
        root = insert(root, a); 
    }
    void display(){
        cout <<"\n--- AVL Tree---\n";
        inorder(root);
    }
    string getMaxAreaName(){
        AVLNode *temp = root;
        while(temp && temp->right){
            temp = temp->right;
        }
        if(temp != nullptr){
            return temp->area.areaName;
        }
        else{
            return "";
        }
    }

    int getMaxAreaCount(){
        AVLNode *temp = root;
        while(temp && temp->right){
            temp = temp->right;
        }
        if(temp != nullptr){
            return temp->area.parcelCount;
        }
        else {
            return 0;
        }
    }
};

const int TABLE_SIZE = 1579;

struct HashNode {
    Package pkg;
    HashNode *next;
    HashNode(Package p){
        pkg = p;
         next = nullptr;
    }
};

class HashTable {
private:
    HashNode *table[TABLE_SIZE];

    int hashFunction(const string &id){
        int hash = 0;
        for (char c : id){ 
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return (hash + TABLE_SIZE) % TABLE_SIZE;
    }

public:
    HashTable(){
        for(int i = 0; i < TABLE_SIZE; i++){
            table[i] = nullptr;
        }
    }

    void insert(Package p){
        int idx = hashFunction(p.id);
        HashNode *newNode = new HashNode(p);
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    Package* search(const string &id){
        int idx = hashFunction(id);
        HashNode *curr = table[idx];
        while (curr != nullptr) {
            if(curr->pkg.id == id){
                return &curr->pkg;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void remove(const string &id) {
        int idx = hashFunction(id);
        HashNode *curr = table[idx];
        HashNode *prev = nullptr;
        while (curr != nullptr) {
            if (curr->pkg.id == id) {
                if (prev == nullptr){
                    table[idx] = curr->next;
                }
                else{
                    prev->next = curr->next;
                }
                delete curr;
                cout<<"Package "<< id <<" removed from hash table.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout<<"Package "<< id <<" not found in hash table.\n";
    }

    void display(){
        cout << "\n--- Hash Table Contents ---\n";
        int printed = 0;
        for(int i = 0; i < TABLE_SIZE; i++){
            if(table[i] != nullptr){
                cout << "Bucket [" << i << "]: ";
                HashNode *curr = table[i];
                while(curr){
                    cout << curr->pkg.id << " ";
                    curr = curr->next;
                }
                cout<<endl;
                printed++;
            }
        }
        if(printed == 0){
            cout<<"(empty)\n";
        }
    }

    void stats(){
        int used = 0, collisions = 0, totalElements = 0;
        for (int i = 0; i < TABLE_SIZE; i++){
            if(table[i]){
                used++;
                HashNode *curr = table[i];
                while(curr){
                    totalElements++;
                    if(curr->next){
                        collisions++;
                    }
                    curr = curr->next;
                }
            }
        }
        cout << "\nHash Table Stats: " << used << " buckets used, "
            << collisions << " collision(s), " << "total elements = " << totalElements << ", "
            << "load factor = " << (float)totalElements / TABLE_SIZE << "\n";
    }
};

class Graph{
private:
    int areaNum;
    int adj[100][100];
public:
    Graph(int v){
    areaNum = v;
    for(int i = 0; i < areaNum; i++){
        for(int j = 0; j < areaNum; j++){
            adj[i][j] = 0;
        }
    }
}

    void addEdge(int u, int v, int weight){
        adj[u][v] = weight;
        adj[v][u] = weight;
    }

    void printPath(int parent[], int node){
        if(node == -1){
            return;
        }
        printPath(parent, parent[node]);
        cout<<node<<" ";
    }

    void dijsktra(int src, vector<int> &destIndices, const vector<string> &areaNames){
        int currentCity = src;
        vector<bool> visitedDest(destIndices.size(), false);
        
        cout << "\n=========================================\n";
        cout << "      OPTIMIZED DELIVERY ROUTE            \n";
        cout << "=========================================\n";
        cout << "FROM: " << areaNames[src] << " (Warehouse)\n";
        
        int totalDistance = 0;
        int stopNum = 1;
        
        // For each destination, find the best order
        for (int d = 0; d < destIndices.size(); d++){
            // Run Dijkstra from CURRENT city
            int dist[100];
            bool visited[100];
            int parent[100];

            for(int i = 0; i < areaNum; i++){
                dist[i] = 1e9;
                visited[i] = false;
                parent[i] = -1;
            }
            dist[currentCity] = 0;

            for(int i = 0; i < areaNum - 1; i++){
                int u = -1, minDist = 1e9;
                for (int j = 0; j < areaNum; j++){
                    if (!visited[j] && dist[j] < minDist){
                        minDist = dist[j]; u = j;
                    }
                }
                if (u == -1){
                    break;
                }    
                visited[u] = true;
                for (int v = 0; v < areaNum; v++){
                    if (adj[u][v] != 0 && !visited[v] && dist[u] + adj[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + adj[u][v];
                        parent[v] = u;
                    }
                }
            }
            
            // Find nearest unvisited destination
            int nearestIndex = -1;
            int nearestDist = 1e9;
            int nearestDest = -1;
            
            for (int i = 0; i < destIndices.size(); i++) {
                if (!visitedDest[i]) {
                    if (destIndices[i] == currentCity) continue;
                    if (dist[destIndices[i]] < nearestDist) {
                        nearestDist = dist[destIndices[i]];
                        nearestDest = destIndices[i];
                        nearestIndex = i;
                    }
                }
            }
            
            if (nearestDest != -1) {
                visitedDest[nearestIndex] = true;
                
                cout << "\nStop " << stopNum << ": " << areaNames[nearestDest] << "\n";
                cout << "  Distance from " << areaNames[currentCity] << ": " << nearestDist << " km\n";
                cout << "  Route: " << areaNames[currentCity] << " -> ";
                
                vector<int> path;
                int temp = nearestDest;
                while(temp != currentCity){
                    path.push_back(temp);
                    temp = parent[temp];
                }
                reverse(path.begin(), path.end());
                for(size_t j = 0; j < path.size(); j++){
                    cout << areaNames[path[j]];
                    if (j < path.size() - 1){
                        cout << " -> ";
                    }
                }
                cout<<"\n";
                
                totalDistance += nearestDist;
                currentCity = nearestDest;
                stopNum++;
            }
        }
        
        cout << "\n-----------------------------------------\n";
        cout << "TOTAL DELIVERY DISTANCE: " << totalDistance << " km\n";
        cout << "-----------------------------------------\n";
    }
};

int loadCSV(DLL &packages, HashTable &ht){
    ifstream file("package_dataset_1180_entries.csv");
    if (!file.is_open()){
        cerr << "ERROR: Cannot open 'package_dataset_1180_entries.csv'.\n";
        return -1;
    }

    string line;
    getline(file, line); // skip header
    int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        Package p;
        string weightStr, priorityStr;

        getline(ss,p.id,',');
        getline(ss,p.destination,',');
        getline(ss,weightStr,',');
        getline(ss,priorityStr,',');
        getline(ss,p.senderName,',');
        getline(ss,p.receiverName,',');
        getline(ss,p.status,',');
        getline(ss,p.deliveryDate,',');

        // Safe conversion with error check
        try{
            p.weight = stof(weightStr);
            p.priority = stoi(priorityStr);
        }
        catch (const invalid_argument &){
            cerr << "Warning: skipping invalid line (non-numeric weight/priority): "<< line <<"\n";
            continue;
        }
        catch (const out_of_range &){
            cerr << "Warning: skipping line with out-of-range number: "<< line <<"\n";
            continue;
        }
        packages.insertPackage(p);
        ht.insert(p);
        count++;
    }
    file.close();
    cout <<"CSV loaded successfully. "<<count << " packages imported.\n";
    return count;
}

void displayMenu(){
    cout << "\n+--------------------------------------+\n";
    cout << "|     PARCEL DELIVERY SYSTEM             |\n";
    cout << "+----------------------------------------+\n";
    cout << "|  1. View All Parcels                   |\n";
    cout << "|  2. Dispatch Parcels (Queue)           |\n";
    cout << "|  3. View Areas by Parcel Count         |\n";
    cout << "|  4. View Hash Table Details            |\n";
    cout << "|  5. Search Parcel by ID                |\n";
    cout << "|  6. Remove Parcel                      |\n";
    cout << "|  7. Find Shortest Delivery Routes      |\n";
    cout << "|  0. Exit                               |\n";
    cout << "+----------------------------------------+\n";
    cout << "  Enter choice: ";
}

void loadDistances(Graph &g, const vector<string> &areaNames){
    ifstream file("Distances.csv");
    if(!file.is_open()){
        cout << "Warning: Distances.csv not found. Using random edges.\n";
        return;
    }

    // Create map
    unordered_map<string, int> areaMap;
    for (size_t i = 0; i < areaNames.size(); i++) {
        areaMap[areaNames[i]] = i;
    }

    string line;
    getline(file, line);
    int count = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string src, dest, distStr;
        int dist;

        getline(ss,src,',');
        getline(ss,dest,',');
        getline(ss,distStr,',');

        try{
            dist = stoi(distStr);
        }
        catch (...) {
            continue;
        }
        // Only add edge if both cities exist in our area list
        if(areaMap.find(src) != areaMap.end() && areaMap.find(dest) != areaMap.end()){
            int u = areaMap[src];
            int v = areaMap[dest];
            g.addEdge(u, v, dist);
            count++;
        }
    }
    file.close();
    cout<<"Loaded "<<count<<" road distances.\n";
}

int main(){
    DLL packages;
    HashTable ht;

    // Load data 
    if(loadCSV(packages, ht) <= 0){
        cout<<"No data loaded – program cannot continue.\n";
        cout<<"Press Enter to exit...";
        cin.get();
        return 1;
    }

    int choice;
    do{
        displayMenu();

   
    while (!(cin >> choice)) {
        if (cin.eof()) {             
            cout << "\nEOF detected. Exiting.\n";
            choice = 0;              
            break;
        }
        cout<<"Invalid input. Please enter a number: ";
        cin.clear();                  // clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');     // discard newline
    if (choice == 0) break;          

        switch(choice){

        case 1:{
            packages.display();
            break;
        }

        case 2:{
            Queue q;
            packages.buildqueue(q);
            cout << "\n--- Queue (first 5 packages) ---\n";
            for(int i = 0; i < 5 && !q.isEmpty(); i++){
                Package front = q.peek();
                cout << front.id << " | " << front.destination << " | " << front.status << "\n";
                q.dequeue();
            }
            break;
        }

        case 3:{
            vector<string> areaNames;
            vector<int> counts;
            packages.buildAreaData(areaNames, counts);

            AVL avlTree;
            for(size_t i = 0; i < areaNames.size(); i++){
                AreaInfo a;
                a.areaName = areaNames[i];
                a.parcelCount = counts[i];
                avlTree.insertArea(a);
            }
            avlTree.display();
            break;
        }

        case 4: {
            ht.display();
            ht.stats();
            break;
        }

        case 5: {
            string searchID;
            cout << "Enter Package ID to search: ";
            getline(cin, searchID);

            Package *found = ht.search(searchID);
            if (found){
                cout<<"\nFound: "<<found->id << " | "<< found->destination<< " | "<< found->status << "\n";
            }
            else{
                cout<<"\nPackage "<<searchID << " not found.\n";
            }
            break;
        }

        case 6: {
            string removeID;
            cout << "Enter Package ID to remove: ";
            getline(cin, removeID);

            bool removed = packages.deletePackage(removeID);

            if(removed){
                ht.remove(removeID);
                cout<<"Package removed successfully.\n";
            }
            else{
                cout<<"Package not found.\n";
            }
            break;
        }

case 7: {
            // Get areas and counts from packages
            vector<string> areaNames;
            vector<int> counts;
            packages.buildAreaData(areaNames, counts);

            // Build AVL tree
            AVL avlTree;
            for (size_t i = 0; i < areaNames.size(); i++) {
                AreaInfo a;
                a.areaName = areaNames[i];
                a.parcelCount = counts[i];
                avlTree.insertArea(a);
            }

            // Find PRIMARY warehouse
            string primaryWH = avlTree.getMaxAreaName();
            int maxCount = avlTree.getMaxAreaCount();

            cout << "\n>>> PRIMARY WAREHOUSE: " << primaryWH 
                 << " (" << maxCount << " parcels)\n";

            // Build graph
            Graph g(areaNames.size());
            loadDistances(g, areaNames);

            // Show available cities
            cout << "\n--- Available Cities ---\n";
            for (size_t i = 0; i < areaNames.size(); i++) {
                cout << i + 1 << ". " << areaNames[i] << "\n";
            }

            // Ask how many cities to deliver to
            cout << "\nHow many cities to deliver to? ";
            int numDest;
            cin >> numDest;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            vector<int> destIndices;
            
            // Ask for each destination
            for (int i = 0; i < numDest; i++) {
                cout << "Enter destination city #" << i + 1 << ": ";
                int cityNum;
                cin >> cityNum;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                destIndices.push_back(cityNum - 1);
            }

            // Find source index (primary warehouse)
            int srcIndex = -1;
            for (size_t i = 0; i < areaNames.size(); i++) {
                if (areaNames[i] == primaryWH) {
                    srcIndex = i;
                    break;
                }
            }

            // Run optimized delivery route
            if (srcIndex != -1) {
                g.dijsktra(srcIndex, destIndices, areaNames);
            }
            break;
        }

        case 0: {
            cout<<"Exiting. Goodbye!\n";
            break;
        }

        default:
            cout<<"Invalid option. Please try again.\n";
        }
    } 
    while (choice != 0);

    return 0;
}
