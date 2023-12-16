#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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
				if (graph.at(i).at(j) > (graph.at(i).at(k) + graph.at(k).at(j))
					&& (graph.at(k).at(j) != INF
						&& graph.at(i).at(k) != INF))
					graph.at(i).at(j) = graph[i][k] + graph[k][j];
			}
		}
	}
}

int pump_water(const vector<vector<int>>& graph, vector<int>& correct_order, int time){
	int n = 0;
	int water_pumped = 0;
	if(correct_order.at(0) == 1){
		time -= 10;
		n++;
	}
	else{
		int begin = graph.at(0).at(correct_order.at(0) -1);
		time -= begin;	
		time -= 10;
		n++;
	}
	for(int i = 0; i +1 < correct_order.size(); i++){
		if(time - graph.at(correct_order.at(i) - 1).at(correct_order.at(i+1) - 1) > 0){
			water_pumped += (graph.at(correct_order.at(i) - 1).at(correct_order.at(i+1) - 1)) * n * PUMPING_LIMIT;
			if(time - 10 > 0){
				water_pumped += 10 * n * PUMPING_LIMIT;
				time -= graph.at(correct_order.at(i) - 1).at(correct_order.at(i+1) - 1);
				time -= 10;
				n++;
			}
		}
	}
	if(time > 0){
		water_pumped += time * PUMPING_LIMIT * n; 	
	}
	return water_pumped;
}

int water_total(const vector<vector<int>>& graph, vector<int> pumping_stations, int time){
	int water_pumped = pump_water(graph, pumping_stations, time);
	vector<int> correct_order = pumping_stations;
	if(pumping_stations.at(0) == 1){
		while(next_permutation((pumping_stations.begin()+1), pumping_stations.end())){
		int current_water = pump_water(graph, pumping_stations, time);
		if(current_water > water_pumped){
				correct_order = pumping_stations;
				water_pumped = current_water;
			}
		}
	}
	else{
		while(next_permutation(pumping_stations.begin(), pumping_stations.end())){
			int current_water = pump_water(graph, pumping_stations, time);
			if(current_water > water_pumped){
				correct_order = pumping_stations;
				water_pumped = current_water;
			}
		}
	}
	return water_pumped;
}

int main(){
	clock_t start = clock();
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

    for(int i = 1; i < roads + 1; i++){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
		if(graph.at(v1-1).at(v2-1) > w){
        	graph.at(v1-1).at(v2-1) = w;
        	graph.at(v2-1).at(v1-1) = w;
		}
        
    }
	floydWarshall(road_intersections, graph);
	printGraph(road_intersections, graph);
	cout << water_total(graph, pumping_stations, time_limit) << endl;
	clock_t end = clock();
  	double runtime = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout << runtime << " Seconds" << endl;
	return 0;
}
