
// Student ID last 3 digits : 006

#include <iostream>
#include <string>
using namespace std;

const int MAXN = 30;    
const int MAXE = 100;   

string names[MAXN];     
int n = 0;              

int eu[MAXE], ev[MAXE], ew[MAXE]; 
int m = 0;                        

int adjM[MAXN][MAXN];   

int dsuParent[MAXN];    
int dsuRank[MAXN];      

int addLocation(string name) {
    names[n] = name;   
    n = n + 1;         
    return n - 1;      
}

void addRoad(int u, int v, int w) {
    eu[m] = u;         
    ev[m] = v;         
    ew[m] = w;         
    m = m + 1;
    adjM[u][v] = w;    
    adjM[v][u] = w;
}

void buildCity() {
    
    addLocation("Warehouse");          
    addLocation("Mirpur Hub");         
    addLocation("Gulshan-2");          
    addLocation("Banani");             
    addLocation("Uttara");             
    addLocation("Dhanmondi");          
    addLocation("Mohammadpur");        
    addLocation("Farmgate");           
    addLocation("Motijheel");          
    addLocation("Old Dhaka");          
    addLocation("Tejgaon");            
    addLocation("Mohakhali");          
    addLocation("Badda");              
    addLocation("Rampura");            
    addLocation("Khilgaon");           
    addLocation("Jatrabari");          
    addLocation("Airport Checkpoint"); 
    addLocation("Bashundhara");        
    addLocation("Shahbagh");          
    addLocation("Malibagh");           
    addLocation("Lalbagh");           
    addLocation("Gulistan");           

    
    addRoad(0, 1, 8);   addRoad(0, 6, 5);   addRoad(0, 7, 3);   addRoad(0, 10, 4);
    addRoad(1, 4, 9);   addRoad(1, 6, 4);   addRoad(1, 7, 6);   addRoad(1, 16, 7);
    addRoad(2, 3, 2);   addRoad(2, 11, 3);  addRoad(2, 12, 5);  addRoad(2, 17, 6);
    addRoad(3, 11, 2);  addRoad(3, 16, 4);  addRoad(4, 16, 5);  addRoad(4, 17, 8);
    addRoad(5, 6, 3);   addRoad(5, 7, 4);   addRoad(5, 18, 5);  addRoad(5, 20, 7);
    addRoad(6, 20, 8);  addRoad(7, 10, 2);  addRoad(7, 11, 5);  addRoad(7, 18, 6);
    addRoad(8, 9, 4);   addRoad(8, 18, 3);  addRoad(8, 19, 5);  addRoad(8, 21, 2);
    addRoad(9, 20, 3);  addRoad(9, 21, 3);  addRoad(10, 11, 3); addRoad(11, 13, 7);
    addRoad(11, 16, 6); addRoad(12, 13, 3); addRoad(12, 17, 4); addRoad(13, 14, 5);
    addRoad(13, 19, 4); addRoad(14, 15, 4); addRoad(14, 19, 3); addRoad(15, 8, 6);
    addRoad(15, 21, 5); addRoad(16, 17, 7); addRoad(18, 19, 4); addRoad(20, 21, 4);
}

void printAdjacencyList() {
    int i, j;
    for (i = 0; i < n; i++) {
        cout << i << " " << names[i] << " -> ";
        for (j = 0; j < n; j++) {
            if (adjM[i][j] != 0) {
                cout << names[j] << "(" << adjM[i][j] << " km)  ";
            }
        }
        cout << endl;
    }
}


int findSet(int x) {

    if (dsuParent[x] == x) {
        return x;           
    } else {
        dsuParent[x] = findSet(dsuParent[x]); 
        return dsuParent[x];
    }
}

bool unionSets(int a, int b) {
    int ra = findSet(a);
    int rb = findSet(b);
    if (ra == rb) {
        return false;                         
    }
    if (dsuRank[ra] < dsuRank[rb]) {
        dsuParent[ra] = rb;                   
    } else if (dsuRank[ra] > dsuRank[rb]) {
        dsuParent[rb] = ra;
    } else {
        dsuParent[rb] = ra;
        dsuRank[ra] = dsuRank[ra] + 1;        
    }
    return true;
}

void sortEdgesByWeight() {
    
    int i, j;
    int tu, tv, tw;
    for (i = 1; i < m; i++) {
        tu = eu[i]; tv = ev[i]; tw = ew[i];
        j = i - 1;
        while (j >= 0 && ew[j] > tw) {
            eu[j + 1] = eu[j];
            ev[j + 1] = ev[j];
            ew[j + 1] = ew[j];
            j = j - 1;
        }
        eu[j + 1] = tu; ev[j + 1] = tv; ew[j + 1] = tw;
    }
}

void runKruskal() {
    int i;
    int mstCount = 0;
    int totalCost = 0;
    int mu[MAXN], mv[MAXN], mw[MAXN];    

    for (i = 0; i < n; i++) {            
        dsuParent[i] = i;
        dsuRank[i] = 0;
    }

    sortEdgesByWeight();

    cout << "Sorted edge list (ascending by distance):" << endl;
    for (i = 0; i < m; i++) {
        cout << "  E" << (i + 1) << ": " << names[eu[i]] << " - " << names[ev[i]]
             << " = " << ew[i] << " km" << endl;
    }

    cout << endl << "Step-by-step Kruskal:" << endl;
    for (i = 0; i < m; i++) {
        if (mstCount == n - 1) {
            cout << "MST complete (" << (n - 1) << " edges selected). Remaining edges skipped." << endl;
            break;
        }
        int ra = findSet(eu[i]);
        int rb = findSet(ev[i]);
        cout << "Step " << (i + 1) << ": edge " << names[eu[i]] << " - " << names[ev[i]]
             << " (" << ew[i] << " km), roots = " << ra << "," << rb << " -> ";
        if (ra != rb) {
            unionSets(eu[i], ev[i]);
            mu[mstCount] = eu[i]; mv[mstCount] = ev[i]; mw[mstCount] = ew[i];
            mstCount = mstCount + 1;
            totalCost = totalCost + ew[i];
            cout << "ACCEPT  (total = " << totalCost << " km)" << endl;
        } else {
            cout << "REJECT  (cycle)" << endl;
        }
    }

    cout << endl << "Selected MST edges:" << endl;
    for (i = 0; i < mstCount; i++) {
        cout << "  " << (i + 1) << ". " << names[mu[i]] << " - " << names[mv[i]]
             << " : " << mw[i] << " km" << endl;
    }
    cout << "Edges in MST = " << mstCount << " (expected " << (n - 1) << ")" << endl;
    cout << "Total MST cost (minimum cable length) = " << totalCost << " km" << endl;
    if (mstCount == n - 1) {
        cout << "Result: all hubs are connected by the MST." << endl;
    } else {
        cout << "Result: graph is disconnected, only a spanning forest was found." << endl;
    }
}

void runBFS(int source) {
    bool visited[MAXN];
    int dist[MAXN];
    int q[MAXN];                        
    int front = 0, back = 0;
    int i, u, v;
    int visitedCount = 0;

    for (i = 0; i < n; i++) {
        visited[i] = false;
        dist[i] = -1;
    }

    visited[source] = true;             
    dist[source] = 0;
    q[back] = source; back = back + 1;

    cout << "BFS traversal order from " << names[source] << ":" << endl;
    while (front < back) {
        u = q[front]; front = front + 1; 
        visitedCount = visitedCount + 1;
        cout << "  visit " << names[u] << "  (hops = " << dist[u] << ")" << endl;
        for (v = 0; v < n; v++) {
            if (adjM[u][v] != 0) {       
                if (visited[v] == false) {
                    visited[v] = true;
                    dist[v] = dist[u] + 1;
                    q[back] = v; back = back + 1;
                }
            }
        }
    }

    cout << endl << "Reachable locations : " << visitedCount << " / " << n << endl;
    if (visitedCount == n) {
        cout << "Result: ALL locations are reachable from " << names[source] << "." << endl;
    } else {
        cout << "Result: UNREACHABLE / ISOLATED locations detected:" << endl;
        for (i = 0; i < n; i++) {
            if (visited[i] == false) {
                cout << "  - " << names[i] << endl;
            }
        }
    }
}

int main() {
    int i, j;
    for (i = 0; i < MAXN; i++) {
        for (j = 0; j < MAXN; j++) {
            adjM[i][j] = 0;
        }
    }

    buildCity();

    cout << "================ TASK 1 : CITY NETWORK ================" << endl;
    cout << "Locations (nodes) = " << n << ", Roads (edges) = " << m << endl << endl;
    printAdjacencyList();

    cout << endl << "================ TASK 2 : MST (KRUSKAL) ================" << endl;
    runKruskal();

    cout << endl << "================ TASK 3 : CONNECTIVITY (BFS) ================" << endl;
    cout << "--- Test A : current city network ---" << endl;
    runBFS(0);

    
    cout << endl << "--- Test B : two new delivery zones added (no road to the main network) ---" << endl;
    int z1 = addLocation("Keraniganj Zone");
    int z2 = addLocation("Purbachal Zone");
    addRoad(z1, z2, 6);   
    runBFS(0);

    return 0;
}
