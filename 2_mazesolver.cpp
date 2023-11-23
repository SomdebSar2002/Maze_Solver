#include <bits/stdc++.h>
#include<fstream>
#include<utility>
using namespace std;

struct Node {
    pair<int, int> position;
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    Node(pair<int, int> coor) : position(coor), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {}
};


bool checkCorner(vector<vector<int>> matrix, int i, int j) {
    int u = matrix[i][j-1];
    int d = matrix[i][j+1];
    int l = matrix[i-1][j];
    int r = matrix[i+1][j];
    int ul = matrix[i-1][j-1];
    int ur = matrix[i+1][j-1];
    int dl = matrix[i-1][j+1];
    int dr = matrix[i+1][j+1];
    int one  = l+ul+u;
    int two = r+ur+u;
    int three = d+dl+l;
    int four = d + dr+r;
    if((one==3)||(two==3)||(three==3)||(four==3))
    return true;
    return false;
}

bool checkThreeOrMoreWays(vector<vector<int>> matrix, int i, int j) {
    int u = !matrix[i][j-1];
    int d = !matrix[i][j+1];
    int l = !matrix[i-1][j];
    int r = !matrix[i+1][j];
    int sum = u+l+d+r;
    if (sum>=3)
        return true;
    return false;
}

bool isConnected(Node* a, Node* b) {
    return (a->right == b || a->up == b || a->down == b || a->left == b);
}

int findDistance(Node* a, Node* b) {
    pair<int, int> a1 = a->position;
    pair<int, int> b1 = b->position;
    int dx = a1.first - b1.first;
    int dy = a1.second - b1.second;
    int ans = int(sqrt(dx * dx + dy * dy));
    return ans;
}

int findMinimumdistance(bool *visited, int *distance, int *prev, int n) {
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (pos == -1 || distance[pos] > distance[i])
                pos = i;
        }
    }
    return pos;
}
void djkstra(vector<vector<int>> edges,int n,vector<Node*> &nodeNumber)
{
    int source = 0;
    int destination = n-1;
   bool *visited = new bool[n];
    int *distance = new int[n];
    int *prev = new int[n];

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        if (i == source)
            distance[i] = 0;
        else
            distance[i] = INT_MAX / 2;

        prev[i] = -1; // Initialize previous node as undefined
    }

    for (int i = 0; i < n; i++) {
        int v = findMinimumdistance(visited, distance, prev, n);
        visited[v] = true;
        for (int j = 0; j < n; j++) {
            if (j != v && (!visited[j]) && (edges[j][v] != -1)) {
                int distance_ut_j = edges[j][v] + distance[v];
                if (distance_ut_j < distance[j]) {
                    distance[j] = distance_ut_j;
                    prev[j] = v; // Update the previous node for path tracing
                }
            }
        }
    }

    // Trace the path from destination to source
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = prev[current];
    }
    

    // Print the minimum path from source to destination in reverse order
    string file_path = "node_cordinates.txt";
    ofstream outfile(file_path);
    for (int i = path.size() - 1; i >= 1; i--) {
        int x1  = nodeNumber[path[i]]->position.first;
        int y1 = nodeNumber[path[i]]->position.second;
        int x2  = nodeNumber[path[i-1]]->position.first;
        int y2 = nodeNumber[path[i-1]]->position.second;
        outfile<< x1<< "," <<y1<< "\n";
        if(x1!=x2)
        for(int i=min(x1,x2)+1;i<max(x1,x2);i++)
        outfile << i<< "," <<y1<< "\n";
        if(y1!=y2)
        for(int i=min(y1,y2)+1;i<max(y1,y2);i++)
        outfile << x1<< "," <<i<< "\n";
    }
      int x1  = nodeNumber[path[0]]->position.first;
        int y1 = nodeNumber[path[0]]->position.second;
        outfile << x1<< "," <<y1<< "\n";
        outfile.close();
        cout<<"Data has been written to node_coordinates.txt";
}
    
int main() {
    string file_path = "img_to_maze_matrix.txt";
    ifstream infile(file_path);
     if (!infile.is_open()) {
        std::cout << "Error opening the file.\n";
        return 1;
    }
    
    string line;

    
    vector<vector<int>> matrix;
    
    while (getline(infile,line))
    {
        vector<int> row;
        stringstream ss(line);
        int val;
        while(ss>>val)
        {
            row.push_back(val);
        }
        matrix.push_back(row);
        /* code */
    }
    infile.close();

    vector<Node*> nodeNumber;
    unordered_map<string,int> nodePositions;
    Node* rightNode = nullptr;
    int counter = 0;
    for(int i=0;i<matrix.size();i++)
    {
        if(matrix[0][i]==0)
        {
           string pos = "0x"+to_string(i)+"y";
           nodePositions[pos]=counter++;
           Node *newNode = new Node({0,i});
           nodeNumber.push_back(newNode);
           break;
        }
    }
    
    for (int i = 1; i < matrix.size() - 1; i++) {
        rightNode  =nullptr;
        for (int j = 1; j < matrix[0].size() - 1; j++) {
            if (matrix[i][j] == 0) {
                if (checkCorner(matrix, i, j) || checkThreeOrMoreWays(matrix, i, j)) {
                    string pos  = to_string(i)+"x"+to_string(j)+"y";
                    nodePositions[pos] = counter++;
                    Node* newNode = new Node({i, j});
                    nodeNumber.push_back(newNode);
                    
                    if (rightNode != nullptr) {
                        rightNode->right = newNode;
                        newNode->left = rightNode;
                    }
                    rightNode = newNode;
                } 
            }
            else
            {
                rightNode = nullptr;
            }
        }
    }
    
    // cout<<matrix.size()<<endl;
    for(int i=0;i<matrix.size();i++)
    {
        if(matrix[matrix.size()-1][i]==0)
        {
           string pos  = to_string(matrix.size()-1)+"x"+to_string(i)+"y";
           nodePositions[pos]=counter++;
           Node *newNode = new Node({matrix.size()-1,i});
           nodeNumber.push_back(newNode);
        }
    }
   //counter contains the length 
    Node* downNode = nullptr;   //change the downnode connection and make sure that every node is connected
    for (int i = 0; i < matrix[0].size(); i++) {
        downNode = nullptr;
    for (int j = 0; j < matrix.size(); j++) {
        string found = to_string(j) + "x" + to_string(i) + "y";
        if (matrix[j][i] == 1) { //checks if the black pixel is present
            downNode = nullptr;
        } else if (nodePositions.count(found) != 0) {
            int index = nodePositions[found];
            Node* newNode = nodeNumber[index];
            if (downNode != nullptr) {
                downNode->down = newNode;
                newNode->up = downNode;
            }
            downNode = newNode;
        }
    }
}
    vector<vector<int>> edges(nodeNumber.size(), vector<int>(nodeNumber.size(), -1));
    for (int i = 0; i < nodeNumber.size(); i++) {
        for (int j = i+1; j < nodeNumber.size(); j++) {
            if (isConnected(nodeNumber[i], nodeNumber[j])) {
                int distance = findDistance(nodeNumber[i], nodeNumber[j]);
                edges[i][j] = distance;
                edges[j][i] = distance;
            }
        }
    }
    
    
    djkstra(edges,nodeNumber.size(),nodeNumber);
    return 0;
}

