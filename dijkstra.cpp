#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
// Declaration of global constants
const int PUMPING_LIMIT = 200;
const int INF = 99999;

// Implementation of Dijkstra's algorithm to find the shortest paths
void dijkstra(int start, vector<vector<int>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    vector<bool> visited(n, false);
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (v == -1 || dist[j] < dist[v])){
                v = j;
            }
        }
        if (dist[v] != INF){
            visited[v] = true;
            for (int j = 0; j < n; j++) {
                if (graph[v][j] != INF && dist[v] + graph[v][j] < dist[j]) {
                    dist[j] = dist[v] + graph[v][j];
                }
            }
        }
    }
}

// This function uses Dijkstra's algorithm to obtain a subgraph that only contains the distances of the start vertex and the pumping stations
vector<vector<int>> dijkstra_simple(vector<int>& vertices, vector<bool>& available_pumps, vector<vector<int>>& graph) {
    vector<vector<int>> new_graph;
    /* 
    Main loop: Run Dijkstra's algorithm on every vertex to obtain the shortest distances. If the current vertex is a pumping station, then it
    is added to the subgraph. 
    */
    for (int v : vertices) {
        vector<int> distance_list;
        dijkstra(v - 1, graph, distance_list);
        vector<int> new_list;
        for (int index = 0; index < distance_list.size(); ++index) {
            if (available_pumps[index]) {
                new_list.push_back(move(distance_list[index]));
            }
        }
        new_graph.push_back(new_list);
    }
    return new_graph;
}

/*
    This function calculates the maximum amount of water that can be pumped using a specific order of visiting pumping stations.
*/
int pump_water(const vector<vector<int>>& dist, vector<int> order, map<int, int>& indices, int time){
    int active_pumps = 0;
    int water_pumped = 0;
    // Check whether vertex 1 is a pumping station, if so change the direction of the water there
    if(order[0] == 1){
        time -= 10;
        active_pumps++;
        /* 
        Main loop: Travels the current road and if there is time left, then goes to the pumping station to change the direction. If there is
        enough time left, change the direction of the water.
        */
        for(int i = 0; i +1 < order.size(); i++){
            int current_road = dist[indices[order[i]]][indices[order[i+1]]];
            if(time - current_road > 0){
                water_pumped += current_road * active_pumps * PUMPING_LIMIT;
                if(time - 10 > 0){
                    water_pumped += 10 * active_pumps * PUMPING_LIMIT;
                    time -= current_road;
                    time -= 10;
                    active_pumps++;
                }
            }
        }
    }
    else{
        /*
        If 1 was not a pumping station, then we need to travel to the first pumping station and change the direction of the water there.
        The rest of the loop remains the same.
        */
        int begin = dist[0][indices[order[0]]+1];
        time -= begin;    
        time -= 10;
        active_pumps++;
        for(int i = 0; i +1 < order.size(); i++){
            int current_road = dist[indices[order[i]]+1][indices[order[i+1]]+1];
            if(time - current_road > 0){
                water_pumped += current_road * active_pumps * PUMPING_LIMIT;
                if(time - 10 > 0){
                    water_pumped += 10 * active_pumps * PUMPING_LIMIT;
                    time -= current_road;
                    time -= 10;
                    active_pumps++;
                }
            }
        }
    }
    /*
    If there is still time left after changing the water direction at every pumping station, then for the remaining time the amount of water
    that is pumped away will be added to the total.
    */
    if(time > 0){
        water_pumped += time * PUMPING_LIMIT * active_pumps;     
    }
    return water_pumped;
}

/*
This function returns the maximum amount of water that can be pumped away in the given time period by checking for every permutation of the 
pumping stations which path pumps away the maximum amount of water.
*/
int water_total(const vector<vector<int>>& dist, vector<int> pumping_stations, map<int, int>& indices, int time){
    int water_pumped = pump_water(dist, pumping_stations, indices, time);
    if(pumping_stations[0] == 1){
        while(next_permutation((pumping_stations.begin()+1), pumping_stations.end())){
            int current_water = pump_water(dist, pumping_stations, indices, time);
            if(current_water > water_pumped){
                water_pumped = current_water;
            }
        }
    }
    else{
        while(next_permutation(pumping_stations.begin(), pumping_stations.end())){
            int current_water = pump_water(dist, pumping_stations, indices, time);
            if(current_water > water_pumped){
                water_pumped = current_water;
             }
        }
    }
    return water_pumped;
}

int main(){
    int road_intersections, amount_pumping_stations, roads, time_limit;

    cin >> road_intersections >> amount_pumping_stations >> roads >> time_limit;

    vector<int> pumping_stations;

    for(int i = 0; i < amount_pumping_stations; i++){
        int station; 
        cin >> station; 
        pumping_stations.push_back(station); 
    }

	sort(pumping_stations.begin(), pumping_stations.end());

	vector<vector<int>> graph(road_intersections,vector<int>(road_intersections + 1, INF));

	for (int i = 0; i < graph.size(); i++){
		graph.at(i).at(i) = 0; 
	}

    // Initialize the graph with the given edges.
    for(int i = 1; i < roads + 1; i++){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
		if(graph.at(v1-1).at(v2-1) > w){
        	graph.at(v1-1).at(v2-1) = w;
        	graph.at(v2-1).at(v1-1) = w;
		}
        
    }

    bool modified = false;

    vector<bool> available_pumps(road_intersections, false);
    // We insert the starting vertex 1 at the beginning if it is not a pumping station. This makes sure it is included in the subgraph
    if (find(pumping_stations.begin(), pumping_stations.end(), 1) == pumping_stations.end()) {
        pumping_stations.insert(pumping_stations.begin(), 1);
        modified = true;
    }
    
    for (int station : pumping_stations) {
        available_pumps[station - 1] = true;
    
    }
    // Subgraph of the shortest distances of vertex 1 and the pumping stations
    vector<vector<int>> dist = dijkstra_simple(pumping_stations, available_pumps, graph);
    
    map<int,int> indices;
    // If we inserted vertex 1 manually, we erase it from the pumping stations
    if(modified){
        pumping_stations.erase(pumping_stations.begin());
    }
    // Since we use a subgraph, we need to map the pumping stations to their corresponding indices in the subgraph, otherwise we would go out of bounds
    for (int i = 0; i < pumping_stations.size(); i++) {
        indices[pumping_stations[i]] = i;
    }

	cout << water_total(dist, pumping_stations, indices, time_limit) << "\n";
	return 0;
}
