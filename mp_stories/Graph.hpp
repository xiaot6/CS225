#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
using namespace std;
/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  return vertexMap.size();
}
/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  return adjList.at(v.key()).size();
}
/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.emplace(key,v);
  adjList[key] = list<edgeListIter>();
  return v;
}
/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const string & key) {
  // TODO: Part 2
  if(vertexMap.find(key) == vertexMap.end()) {
    return;
  }
  for(auto it = vertexMap.begin(); it != vertexMap.end();it++){
  // for(auto it :incidentEdges){
    removeEdge(key, it->first);
    if(edgeList.front().get().directed()) {
      removeEdge(it->first,key);
    }
  }
  vertexMap.erase(key);
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
   edgeList.push_front(e);
   edgeListIter it = edgeList.begin();
   adjList[v1.key()].push_front(it);
   adjList[v2.key()].push_front(it);
   return e;
}
/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const string key1, const string key2) {
  // TODO: Part 2
  for(edgeListIter it = edgeList.begin();it!=edgeList.end();++it)
   {
     Edge e = *it;
     string source = e.source().key();
     string dest = e.dest().key();
     if(source==key1 && dest==key2)
     {
       removeEdge(it);
       break;
     }
     if(source==key2 && dest==key1 && e.directed())
     {
       removeEdge(it);
       break;
     }

   }
}
/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  string v1 = (*it).get().source().key();
  string v2 = (*it).get().dest().key();
  edgeList.erase(it);
  for (auto iter = adjList[v1].begin();iter != adjList[v1].end();iter++) {
    if((*iter) == it) {
        adjList[v1].erase(iter);
        break;
    }
  }
  for (auto iter = adjList[v2].begin();iter != adjList[v2].end();iter++) {
    if((*iter) == it) {
        adjList[v1].erase(iter);
        break;
    }
  }
  return;
}
/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const list<reference_wrapper<E>> Graph<V,E>::incidentEdges(const string key) const {
  // TODO: Part 2
  list<reference_wrapper<E>> edges;
  for(edgeListIter it : adjList.at(key))
  {
    edges.push_front(*it);
  }
  return edges;
}
/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const string key1, const string key2) const {

  // list<reference_wrapper<E>> EList = incidentEdges(key1);
  bool flag = false;
  for(Edge e : incidentEdges(key1))
  {
    if(e.source().key()==key1 && e.dest().key()==key2)
    {
      flag = true;
    }
    if(e.source().key()==key2 && e.dest().key()==key1 && e.directed())
    {
      flag = true;
    }
  }
  return flag;

}
