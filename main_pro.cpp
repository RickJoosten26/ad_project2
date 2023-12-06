#include <iostream>
#include <vector>

using namespace std;

const int PUMPING_LIMIT = 200;
const int TIME_TO_CHANGE_PUMPING_DIRECTION = 10;
const int MAX_VERTICES = 10000;
const int MAX_TIME = 20000;
const int MAX_PUMPING_STATIONS = 15;
const int MAX_NR_OF_ROADS = 30000;

int dp[MAX_TIME][MAX_VERTICES][MAX_PUMPING_STATIONS];

class Edge{
    public: 
        int vertex1;
        int vertex2; 
        int weight; 

        Edge(int v1, int v2, int w){
            vertex1 = v1;
            vertex2 = v2;
            weight = w;
        }
        
}; 


class Graph {
    public:
        int vertices; 
        vector<Edge> edges;
        vector<bool> isPumpingStation; 
    
    Graph(int nr_vertices, vector<Edge> e, vector<bool> pumping){
        vertices = nr_vertices;
        edges = e;
        isPumpingStation = pumping;
    }

    void addEdge(Edge e){
        edges.push_back(e);
    }
}; 





int main(){

    int road_intersections, amount_pumping_stations, roads, time_limit;

    cin >> road_intersections >> amount_pumping_stations >> roads >> time_limit;

    vector<bool> pumping_stations(road_intersections+1, false);

    vector<Edge> edges;

    for(int i = 0; i < amount_pumping_stations; i++){
        int station; 
        cin >> station; 
        pumping_stations.at(station) = true; 
    }
    for (int i = 0; i < pumping_stations.size(); i++){
        cout << pumping_stations.at(i);
    }
    Graph g = Graph(road_intersections, edges, pumping_stations);
    

    for(int i = 0; i < roads; i++){
        int v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        g.addEdge(Edge(v1,v2,weight));
    }

    
    

    return 0;
}