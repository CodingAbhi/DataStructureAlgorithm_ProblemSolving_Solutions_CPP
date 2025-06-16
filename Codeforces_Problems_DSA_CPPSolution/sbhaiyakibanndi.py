from collections import deque
def calculateMax(network_nodes, network_from, network_to, frequency):
    n = network_nodes
    dist = [0 for i in range(n)]
    dist2 = [0 for i in range(n)]
    adj = [[] for i in range(n)]
    
    def bfs(src, dis):
        dis[src] = 1
        q = deque()
        q.append(src)
        maxdis, node = 1, src
        while len(q) > 0:
            u = q.popleft()
            for v in adj[u]:
                if dis[v] == 0:
                    q.append(v)
                    dis[v] = dis[u] + 1
                    if dis[v] > maxdis:
                        node = v
                        maxdis = dis[v]
        return node
                    
    for i in range(n - 1):
        if abs(frequency[network_from[i] - 1] - frequency[network_to[i] - 1]) <= 1:
            adj[network_from[i] - 1].append(network_to[i] - 1)
            adj[network_to[i] - 1].append(network_from[i] - 1)
  
    ans = 0    
    for i in range(n):
        if dist[i] == 0:
            src = bfs(i, dist)
            src2 = bfs(src, dist2)
            ans = max(ans, dist2[src2] - 1)
    return ans