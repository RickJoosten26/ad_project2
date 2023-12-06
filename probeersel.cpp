// C++ Program for Floyd Warshall Algorithm
#include <iostream>
#include <vector>

using namespace std;

#define V 4

const int PUMPING_LIMIT = 200;
const int TIME_TO_CHANGE_PUMPING_DIRECTION = 10;
const int MAX_VERTICES = 10000;
const int MAX_TIME = 20000;
const int MAX_PUMPING_STATIONS = 15;
const int MAX_NR_OF_ROADS = 30000;


const int INF = 99999;

void printGraph(int road_intersections, vector<vector<int>> graph){
    for(int i = 0; i < road_intersections; i++){
        for (int j = 0; j < road_intersections; j++){
            if(graph.at(i).at(j) == INF){
                cout << "INF ";
            }
            else{
                cout << graph.at(i).at(j) << " ";
            }
        }
        cout << "\n";
    }
}


// A function to print the solution matrix
 void printSolution(int dist[][V]);


// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall(vector<vector<int>> graph){

	int i, j, k;

	/* Add all vertices one by one to
	the set of intermediate vertices.
	---> Before start of an iteration,
	we have shortest distances between all
	pairs of vertices such that the
	shortest distances consider only the
	vertices in set {0, 1, 2, .. k-1} as
	intermediate vertices.
	----> After the end of an iteration,
	vertex no. k is added to the set of
	intermediate vertices and the set becomes {0, 1, 2, ..
	k} */
	for (k = 0; k < V; k++) {
		// Pick all vertices as source one by one
		for (i = 0; i < V; i++) {
			// Pick all vertices as destination for the
			// above picked source
			for (j = 0; j < V; j++) {
				// If vertex k is on the shortest path from
				// i to j, then update the value of
				// dist[i][j]
				if (graph[i][j] > (graph[i][k] + graph[k][j])
					&& (graph[k][j] != INF
						&& graph[i][k] != INF))
					graph.at(i).at(j) = graph[i][k] + dist[k][j];
			}
		}
	}

}



// Driver's code
int main(){

    int road_intersections, amount_pumping_stations, roads, time_limit;

    cin >> road_intersections >> amount_pumping_stations >> roads >> time_limit;

    vector<bool> pumping_stations(road_intersections+1, false);

    for(int i = 0; i < amount_pumping_stations; i++){
        int station; 
        cin >> station; 
        pumping_stations.at(station) = true; 
    }
    for (int i = 0; i < pumping_stations.size(); i++){
        cout << pumping_stations.at(i);
    }


	vector<vector<int>> graph(road_intersections,vector<int>(road_intersections + 1, INF));

	for (int i = 0; i < graph.size(); i++){
		graph.at(i).at(i) = 0; 
	}

    for(int i = 1; i < roads + 1; i++){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        graph.at(v1-1).at(v2-1) = w;
        graph.at(v2-1).at(v1-1) = w;
        
    }

    vector<vector<int>> times(road_intersections, vector<int>(road_intersections, INF));
    for (int i = 0; i < times.size(); i++){
		times.at(i).at(i) = 0; 
	}
    
	// Function call
	//floydWarshall(graph);
	return 0;
}
