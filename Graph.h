#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <memory>
#include <algorithm>

namespace gdwg
{
	template <typename N, typename E> 
	class Node{

	private:
		N data_;
		std::vector<std::tuple<E, std::weak_ptr<Node<N,E>>>> next_;

	public:
		Node();
		Node(const N&);
		void setData(const N&);
		bool addEdge(const E &w, std::shared_ptr<Node<N,E>> d);
		bool deleteEdge(const E &w, std::shared_ptr<Node<N,E>> d);
		N& getData();
		unsigned int getNumEdge();
		E getWeight(const unsigned int idx);
		std::shared_ptr<Node<N,E>> getDst(const unsigned int idx);

	};
	
	template <typename N, typename E> 
	class Graph{
	private:
		std::vector<std::shared_ptr<Node<N,E>>> arr_;
		mutable typename std::vector<std::shared_ptr<Node<N,E>>>::const_iterator iterator_;
		
		std::shared_ptr<Node<N,E>> findNode(const N &) const;

	public:
		Graph();
		Graph(const Graph<N,E> &);
		Graph(Graph<N,E> &&);
		Graph<N,E>& operator=(const Graph<N,E> &);
		Graph<N,E>& operator=(Graph<N,E> &&);

		bool addNode(const N&val);
		bool addEdge(const N &src, const N &dst, const E &w);
		bool replace(const N& oldData, const N& newData);
		void mergeReplace(const N& oldData, const N& newData);
		void deleteNode(const N& val) noexcept;
		void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
		void clear() noexcept;
		bool isNode(const N &val) const;
		bool isConnected(const N& val, const N& dst) const;
		void printNodes() const;
		void printEdges(const N& val) const;
		
		void begin() const;
		bool end() const;
		void next() const;
		const N& value() const;
	};
	
	#include "Graph.tem"
}

#endif
