#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int PUMPING_LIMIT = 200;



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

void floydWarshall(int road_intersections, vector<vector<int>>& graph){

	int i, j, k;
	for (k = 0; k < road_intersections; k++) {
		for (i = 0; i < road_intersections; i++) {
			for (j = 0; j < road_intersections; j++) {
				if (graph[i][j] > (graph[i][k] + graph[k][j])
					&& (graph[k][j] != INF
						&& graph[i][k] != INF))
					graph.at(i).at(j) = graph[i][k] + graph[k][j];
			}
		}
	}

}

int pump_water(vector<vector<int>> graph, vector<int> correct_order, int time){
	//correct_order = {1,2,3,4};
	cout << "order: " <<endl;
	for(int i=0; i < correct_order.size(); i++){
		cout << correct_order.at(i) << " ";
	}
	cout << "\n";
	int n = 0;
	int water_pumped = 0;
	if(correct_order.at(0) == 1){
		time -= 10;
		n++;
	}
	else{
		int begin = graph.at(0).at(correct_order.at(0) -1);
		cout << "First step: " << graph.at(0).at(correct_order.at(0) -1) << endl;
		cout << time << endl;
		time -= begin;	
		time -= 10;
		cout << "New time" << time << endl;
		n++;
	}
	for(int i = 0; i +1 < correct_order.size(); i++){
		cout << "Time: " << time << endl;
	 	cout << "current consideration: " << graph.at(correct_order.at(i) - 1).at(correct_order.at(i+1) - 1) << endl;
		cout << "From: " << correct_order.at(i) << "To: " << correct_order.at(i+1) << endl;
		cout << "Water pumped before: " << water_pumped << " " << endl;
		if(time - graph.at(correct_order.at(i) - 1).at(correct_order.at(i+1) - 1) > 0){
			water_pumped += (graph.at(correct_order.at(i) - 1).at(correct_order.at(i+1) - 1)) * n * PUMPING_LIMIT;
			cout << "Water pumped at arrival: " << water_pumped << " " << endl;
			water_pumped += 10 * n * PUMPING_LIMIT;
			cout << "Water pumped while changing direction: " << water_pumped << " " << endl;
			time -= graph.at(correct_order.at(i) - 1).at(correct_order.at(i+1) - 1);
			time -= 10;
			cout << "New time: " << time <<endl;
			n++;
			cout << "Water pumped right now: " << water_pumped << endl;
			cout << "PUMPING STATIONS ACTIVE: " << n << endl;
		}
	}
	if(time > 0){
		water_pumped += time * PUMPING_LIMIT * n; 	
	}
	return water_pumped;
}

int shortestPath(vector<vector<int>> graph, vector<int> order){
	int distance = graph.at(0).at(order.at(0) - 1); 
	cout << "Current order: " << endl;
	for (int i = 0; i < order.size(); i++){
		cout << order.at(i) << " ";
	}
	for (int i = 0; i + 1 < order.size(); i++){
		distance += graph.at(order.at(i) - 1).at(order.at(i+1) - 1);
	}
	cout << " with distance: " << distance << endl;
	return distance; 
}

void solution(vector<vector<int>> graph, vector<int> pumping_stations, int& time){
	int water_pumped = pump_water(graph, pumping_stations, time);
	cout << "first perm water: " << water_pumped << endl;
	//int min_dist = INF;
	int min_dist = shortestPath(graph, pumping_stations);
	vector<int> correct_order = pumping_stations;
	if(pumping_stations.at(0) == 1){
		while(next_permutation((pumping_stations.begin() + 1), pumping_stations.end())){
		int current_dist = shortestPath(graph, pumping_stations);
		int current_water = pump_water(graph, pumping_stations, time);
		if(current_dist < time && current_water > water_pumped){
			min_dist = current_dist;
			correct_order = pumping_stations;
			water_pumped = current_water;
		}
	}
	}
	else{
		while(next_permutation(pumping_stations.begin(), pumping_stations.end())){
			int current_dist = shortestPath(graph, pumping_stations);
			int current_water = pump_water(graph, pumping_stations, time);
			if(current_dist < time && current_water > water_pumped){
				min_dist = current_dist;
				correct_order = pumping_stations;
				water_pumped = current_water;
			}
		}
	}
	cout << "Correct order: "<<endl;
	for(int i = 0; i < correct_order.size(); i++){
		cout << correct_order.at(i)<<endl;
	}
	cout << "MINIMUM DISTANCE: " << min_dist << endl;

	// cout << "SOLUTION : "; 
	// for(int i = 0; i < pumping_stations.size(); i++){
	// 	cout << pumping_stations.at(i);
	// }
	//cout << "\n";
	cout << water_pumped << "\n";
}



// Driver's code
int main(){

    int road_intersections, amount_pumping_stations, roads, time_limit;

    cin >> road_intersections >> amount_pumping_stations >> roads >> time_limit;

    vector<int> pumping_stations;

    for(int i = 0; i < amount_pumping_stations; i++){
        int station; 
        cin >> station; 
        pumping_stations.push_back(station); 
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
    
	//printGraph(road_intersections, graph);
	// Function call
	floydWarshall(road_intersections, graph);
	solution(graph, pumping_stations, time_limit);
	// int water = solution(graph, pumping_stations, time_limit);
	printGraph(road_intersections, graph);
	//cout << graph.at(road_intersections).at(road_intersections);
	return 0;
}
