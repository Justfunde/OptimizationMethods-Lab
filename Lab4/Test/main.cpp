#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iostream> 
#include <iomanip>
#include <list>
#include <map>


using NodeId = std::size_t;

struct Edge
{
   NodeId from;
   NodeId to;
   int32_t weight;

   bool
   operator<(const Edge& rhs) const
   {
      return weight < rhs.weight;
   }
   bool
   operator==(const Edge& rhs) const
   {
      return from == rhs.from && to == rhs.to && weight == rhs.weight;
   }
};

static
void
InPrintSet(const std::multiset<Edge>& Edges)
{
   for(const auto& it : Edges)
   {
      std::cout << "x" + std::to_string(it.from) 
         << "<===>" << "x" + std::to_string(it.to)
         << " w = " << std::to_string(it.weight) << std::endl; 
   }
}

static
std::multiset<Edge> 
CreateKruskalTree(
   std::set<NodeId> NodeSet,
   std::multiset<Edge> tree)
{
   std::multiset<Edge> ret;

   if(tree.empty() || NodeSet.empty()) { return ret;}

   using NodeChunk = std::list<std::set<NodeId>>;

   NodeChunk chunkes;
   for(const auto& it : NodeSet)
   {
      chunkes.push_back( { it } );
   }

   std::size_t iteration = 0;
   while (chunkes.size() != 1)
   {

      bool inSameChunk = false;
      std::vector<NodeChunk::iterator> chunkIterArr;
      chunkIterArr.reserve(2);
      Edge edgeToInsert;

      for(auto edgeIt = tree.begin(); edgeIt != tree.end(); ++edgeIt )
      {  
         for(auto chunkIt = chunkes.begin(); chunkIt != chunkes.end(); ++chunkIt)
         {
            if(chunkIt->contains(edgeIt->from) && chunkIt->contains(edgeIt->to)) 
            { 
               tree.erase(edgeIt);
               inSameChunk = true;
               break;
            }

            if(chunkIt->contains(edgeIt->from))
            {
               chunkIterArr.push_back(chunkIt);
            }
            if(chunkIt->contains(edgeIt->to))
            {
               chunkIterArr.push_back(chunkIt);
            }
            if(chunkIterArr.size() == 2) { break;}

         }
         if(inSameChunk) {break;}
         if(chunkIterArr.size() == 2)
         {
            edgeToInsert = *edgeIt;
            tree.erase(edgeIt);
            break;
         }
      }
      if(inSameChunk) { continue; }

      std::copy(chunkIterArr[1]->begin(), chunkIterArr[1]->end(), std::inserter(*chunkIterArr[0], chunkIterArr[0]->end()));
      chunkes.erase(chunkIterArr[1]);
      ret.insert(edgeToInsert);
   }

   return ret;
}


std::vector<NodeId> PruferCode(const std::multiset<Edge>& edges) {
    std::map<NodeId, int> degree;
    std::map<NodeId, std::set<NodeId>> adjList;

    for (const auto& edge : edges) 
    {
      degree[edge.from]++;
      degree[edge.to]++;
      adjList[edge.from].insert(edge.to);
      adjList[edge.to].insert(edge.from);
    }

    std::set<NodeId> leaves;
    for (const auto& [node, deg] : degree) 
    {
      if (deg == 1) 
      {
            leaves.insert(node);
      }
    }

    std::vector<NodeId> prufer;

    while (prufer.size() < edges.size() - 1) 
    {
        NodeId leaf = *leaves.begin();
        leaves.erase(leaves.begin());

        NodeId neighbor = *adjList[leaf].begin();
        prufer.push_back(neighbor);

        if (--degree[neighbor] == 1) 
        {
            leaves.insert(neighbor);
        }
        adjList[neighbor].erase(leaf);
        adjList[leaf].erase(neighbor);
    }

    return prufer;
}

int main()
{
   std::set<NodeId> nodeIds{ 1, 2, 3, 4, 5, 6, 7};
   std::multiset<Edge> edges;
   edges.insert({1, 2, 3}); 
   edges.insert({1, 3, 2});
   edges.insert({1, 4, 3});
   edges.insert({1, 5, 5});
   edges.insert({1, 6, 3});
   edges.insert({2, 3, 2});
   edges.insert({4, 7, 4});
   edges.insert({5, 7, 4});
   edges.insert({6, 7, 2});



   std::multiset<Edge> resultTree = CreateKruskalTree(nodeIds, edges);
   std::cout << "\n\n\n\n\n";
   InPrintSet(resultTree);
  
   std::cout << std::endl;
   std::vector<NodeId> prufer = PruferCode(resultTree);
   for (NodeId node : prufer) {
        std::cout << "x" << node << " ";
    }
    std::cout << std::endl;

   return 0;
}