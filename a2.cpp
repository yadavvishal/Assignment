


#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

#define INF INT_MAX

// Define a structure to represent a graph edge
struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// Define a function for Dijkstra's algorithm
bool downloadGraphData() {
    // Replace this URL with the GitHub repository URL of your "graph.txt" file
    const string githubUrl = "https://raw.githubusercontent.com/your-username/your-repo-name/main/graph.txt";
    
    // Use curl to download the file
    string command = "curl -o graph.txt " + githubUrl;
    int result = system(command.c_str());
    
    // Return true if the download was successful
    return result == 0;
}
bool downloadinput() {
    // Replace this URL with the GitHub repository URL of your "graph.txt" file
    const string githubUrl = "https://raw.githubusercontent.com/your-username/your-repo-name/main/graph.txt";
    
    // Use curl to download the file
    string command = "curl -o input.txt " + githubUrl;
    int result = system(command.c_str());
    
    // Return true if the download was successful
    return result == 0;
}


int dijkstra(vector<vector<Edge>>& graph, int source, int destination) {
    int numNodes = graph.size();
    vector<int> distance(numNodes, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distance[source] = 0;
    pq.push({0, source});
    
    auto start_time = high_resolution_clock::now(); // Start measuring time
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (const Edge& e : graph[u]) {
            int v = e.to;
            int w = e.weight;
            
            if (distance[u] != INF && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                pq.push({distance[v], v});
            }
        }
    }
    
    auto end_time = high_resolution_clock::now(); // Stop measuring time
    auto execution_time = duration_cast<milliseconds>(end_time - start_time);
    
    // Return execution time in milliseconds
    return execution_time.count();
}

int main() {
    // Open input and output files
    ifstream inputFile("graph.txt");
    ifstream inputfl("input.txt");
    
    ofstream outputFile("output.txt");

    if (!inputFile || !outputFile || !inputfl) {
        cerr << "Failed to open input or output file." << endl;
        return 1;
    }

    // Read source and destination from the input file
    int source, destination;
    inputfl >> source >> destination;

    // Create a map to map node indices from the input file to valid indices in the graph
    unordered_map<int, int> nodeMap;

    // Read graph data from the input file and populate nodeMap
    int numNodes, numEdges;
    inputFile >> numNodes >> numEdges;

    vector<vector<Edge>> graph(numNodes);

    for (int i = 0; i < numEdges; ++i) {
        int node1, node2, distance;
        inputFile >> node1 >> node2 >> distance;

        // Check if node1 and node2 are already mapped
        if (nodeMap.find(node1) == nodeMap.end()) {
            nodeMap[node1] = nodeMap.size(); // Map the node to the next available index
        }
        if (nodeMap.find(node2) == nodeMap.end()) {
            nodeMap[node2] = nodeMap.size(); // Map the node to the next available index
        }

        // Add the edge to the graph using mapped indices
        int mappedNode1 = nodeMap[node1];
        int mappedNode2 = nodeMap[node2];
        graph[mappedNode1].push_back(Edge(mappedNode2, distance));
    }

    // Call Dijkstra's algorithm and get the execution time
    int execution_time = dijkstra(graph, nodeMap[source], nodeMap[destination]);

    // Print the shortest distance to the output file
    outputFile << "Shortest distance from " << source << " to " << destination << " is " << execution_time << " milliseconds" << endl;

    // Close input and output files
    inputFile.close();
    outputFile.close();
    inputfl.close();
    return 0;
}
