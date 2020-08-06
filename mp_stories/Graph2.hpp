#include <queue>
#include <algorithm>
#include <string>
#include <list>
using namespace std;

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
list<std::string> path;
unordered_map<string , string> predecessor;//for mapping predecessors
  bool flag = false;
  queue<string> que;
  que.push(start);
  predecessor.insert({start,start});//start maps to self as predecessor
  while(!flag)
  {
    string runner = que.front();//popping front
    que.pop();
    list<std::reference_wrapper<E>> EList = incidentEdges(runner);
    for(Edge & e : EList)
    {
      string dest = e.dest().key();
      string source = e.source().key();
      if(source==end || dest==end )//set flag as true
      {
        flag = true;
      }
      if(predecessor.find(source)==predecessor.end())
      {
        que.push(source);
        predecessor.insert({source,dest});
      }
      if(predecessor.find(dest)==predecessor.end())
      {
        que.push(dest);
        predecessor.insert({dest,source});
      }
    }
  }
    string tmp = end;
    path.push_back(end);
    while(tmp != start){
      path.push_back(predecessor[tmp]);
      tmp = predecessor[tmp];
    }
    reverse(path.begin(),path.end());
    return path;
}
