#ifndef GRAPH_H
#define GRAPH_H

namespace gdwg
{
	template <typename N, typename E> 
	class Node{
	private:
		N data_;
		std::vector<std::tuple<E, std::shared_ptr<Node<N,E>>>> next_;

	public:
		Node();
		Node(const N&);
		void setData();
		bool addEdge(const E &w, std::shared_ptr<Node<N,E>> d) const;
		N getData();
		unsigned int getNumEdge();
		E getWeight(const unsigned int idx);
		std::shared_ptr<Node<N,E>> getDst(const unsigned int idx);

	};
	
	template <typename N, typename E> 
	class Graph{
	private:
		std::vector<std::shared_ptr<Node<N,E>>> arr_;

	public:
		Graph();
		

		bool addNode(const N&val);
		bool addEdge(const N &src, const N &dst, const E &w);
		bool replace(const N& oldData, const N& newData);

		bool isNode(const N &val) const;
		std::shared_ptr<Node<N,E>> findNode(const N &src);
		void printNodes() const;
		void printGraph() const;
	};




	#include "Graph.tem"
}

#endif
