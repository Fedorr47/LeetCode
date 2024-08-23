#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

// Структура для хранения ребер графа
struct Edge {
    int to;
    int weight;
};

// Алгоритм Дейкстры
pair<unordered_map<int, int>, unordered_map<int, int>> dijkstra(int source, unordered_map<int, vector<Edge>>& adj) {
    unordered_map<int, int> dist;  // Вектор для хранения минимальных расстояний от источника
    unordered_map<int, int> prev;  // Вектор для хранения предшествующих вершин для восстановления пути

    for (const auto& [vertex,_] : adj) {
        dist[vertex] = INF;
    }
    dist[source] = 0;

    // Приоритетная очередь для выбора вершины с минимальным расстоянием
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, source });

    while (!pq.empty()) {
        auto [distance, vertex] = pq.top();
        pq.pop();

        if (distance > dist[vertex]) continue;

        for (const Edge& edge : adj[vertex]) {
            int neighbor = edge.to;
            int weight = edge.weight;

            if (dist[vertex] + weight < dist[neighbor]) {
                dist[neighbor] = dist[vertex] + weight;
                prev[neighbor] = vertex;
                pq.push({ dist[neighbor], neighbor });
            }
        }
    }

    return { dist, prev };
}

// Функция для восстановления пути
vector<int> get_path(int target, const unordered_map<int, int>& prev) {
    vector<int> path;
    for (int at = target; prev.find(at) != prev.end(); at = prev.at(at)) {
        path.push_back(at);
    }
    path.push_back(target); // добавляем начальную вершину
    reverse(path.begin(), path.end());
    return path;
}

// https://leetcode.com/problems/network-delay-time/description/
vector<pair<int, int>> adj[101];
vector<int> signalReceivedAt;
void dijkstra(int source) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
        greater<pair<int, int>>>
        pq;
    pq.push({ 0, source });

    signalReceivedAt[source] = 0;

    while (!pq.empty()) {
        auto [currNodeTime, currNode] = pq.top();
        pq.pop();

        if (currNodeTime > signalReceivedAt[currNode]) {
            continue;
        }

        for (auto [time, neighborNode] : adj[currNode]) {

            if (signalReceivedAt[neighborNode] > currNodeTime + time) {
                signalReceivedAt[neighborNode] = currNodeTime + time;
                pq.push({ signalReceivedAt[neighborNode], neighborNode });
            }
        }
    }
}

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    for (vector<int> time : times) {
        int source = time[0];
        int dest = time[1];
        int travelTime = time[2];

        adj[source].push_back({ travelTime, dest });
    }

    signalReceivedAt = vector<int>(n + 1, INT_MAX);
    dijkstra(k);

    int answer = INT_MIN;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, signalReceivedAt[i]);
    }

    return answer == INT_MAX ? -1 : answer;
}

// https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    if (src == dst) {
        return 0;
    }

    vector<int> previous(n, INT_MAX);
    vector<int> current(n, INT_MAX);
    previous[src] = 0;
    for (int i = 1; i < k + 2; i++) {
        current[src] = 0;
        for (vector<int>& flight : flights) {
            int previous_flight = flight[0];
            int current_flight = flight[1];
            int cost = flight[2];

            if (previous[previous_flight] < INT_MAX) {
                current[current_flight] = min(current[current_flight],
                    previous[previous_flight] + cost);
            }
        }
        previous.assign(current.begin(), current.end());
    }
    return current[dst] == INT_MAX ? -1 : current[dst];
}


struct EdgBF {
    int src, dest, weight;
};

void bellmanFord(int V, int E, int start, vector<EdgBF>& edges) {
    vector<int> distance(V, numeric_limits<int>::max());
    distance[start] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Проверка на наличие отрицательных циклов
    for (int j = 0; j < E; ++j) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;

        if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    // Вывод результата
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " has minimum distance " << distance[i] << endl;
    }
}

bool spfa(int V, int E, int start, vector<EdgBF>& edges) {
    vector<int> distance(V, numeric_limits<int>::max());
    vector<int> inQueue(V, 0);
    vector<int> count(V, 0);

    distance[start] = 0;
    queue<int> q;
    q.push(start);
    inQueue[start] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = 0;

        for (const auto& edge : edges) {
            if (edge.src == u) {
                int v = edge.dest;
                int weight = edge.weight;

                if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;

                    if (!inQueue[v]) {
                        q.push(v);
                        inQueue[v] = 1;
                        count[v]++;

                        // Если узел был в очереди V раз, значит существует отрицательный цикл
                        if (count[v] > V) {
                            cout << "Graph contains negative weight cycle" << endl;
                            return false;
                        }
                    }
                }
            }
        }
    }

    // Вывод результата
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " has minimum distance " << distance[i] << endl;
    }

    return true;
}