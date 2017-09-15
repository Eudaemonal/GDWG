/** Class Node
 *
 */

template<typename N, typename E>
Node<N,E>::Node()
{};


template<typename N, typename E>
Node(const N& val)
	: data_(val)
{};
	

template<typename N, typename E>
void setData(const N& val){
	data_ = val;
}


		
/** Add edge to a node
	return true if edge is added to the node
	return false if edge with same weight, destination already exists
@param 
@return
*/
template<typename N, typename E>
bool addEdge(const E &w, std::shared_ptr<Node<N,E>> d) const
{
	for(unsigned int i=0; i!=next_.size();++i)
		if(getWeight(i) == w && getDst(i)==d)
			return false;
	next_.push_back(std::make_tuple(w, d));
	return true;
}

/** Delete edge from a node
	return true if edge is deleted from the node
	return false if edge with specified weight and destination not found
@param 
@return
*/
template<typename N, typename E>
bool deleteEdge(const E &w, std::shared_ptr<Node<N,E>> d){
	for(unsigned int i=0; i!=next_.size();++i)
		if(getWeight(i) == w && getDst(i)==d){
			next_.erase(next_.begin()+i);
			return true;
		}
	return false;
}


template<typename N, typename E>
N getData()
{
	return data_;
}


template<typename N, typename E>
unsigned int getNumEdge(){
	return next_.size();
}



template<typename N, typename E>
E getWeight(const unsigned int idx){
	return std::get<0>(next_[idx]);
}


template<typename N, typename E>
std::shared_ptr<Node<N,E>> getDst(const unsigned int idx){
	return std::get<1>(next_[idx]);
}


/** Class Graph
 *
 */
template<typename N, typename E>
Graph()
{};

		


template<typename N, typename E>
bool addNode(const N& val)
{
	std::shared_ptr<Node<N,E>> n (new Node<N,E>);
	n->setData(val);
	if(isNode(val))
		return false;
	arr_.push_back(n);
	
	return true;
}


template<typename N, typename E>
bool addEdge(const N &src, const N &dst, const E &w){
	std::shared_ptr<Node<N,E>> s (new Node<N,E>);
	std::shared_ptr<Node<N,E>> d (new Node<N,E>);

	if(!isNode(src)||!isNode(dst))
	       throw std::runtime_error("Error: One or two nodes not exist.");
		
	s = findNode(src);
	d = findNode(dst);

	return s->addEdge(w,d);
}


template<typename N, typename E>
bool replace(const N& oldData, const N& newData){
	std::shared_ptr<Node<N,E>> n (new Node<N,E>);
	if(!isNode(oldData))
		throw std::runtime_error("Error: No node with oldData exist.");

	if(isNode(newData))
		return false;

	n = findNode(oldData);
	n->setData(newData);

	return true;
}


template<typename N, typename E>
void mergeReplace(const N& oldData, const N& newData){
	if(!isNode(oldData)||!isNode(newData))
		throw std::runtime_error("Error: One or two nodes with specified data do not exist.");
	std::shared_ptr<Node<N,E>> old_node (new Node<N,E>);
	old_node = findNode(oldData);

	std::shared_ptr<Node<N,E>> new_node (new Node<N,E>);
	new_node = findNode(oldData);

	for(unsigned int i=0; i!=old_node->getNumEdge();++i)
		new_node->addEdge(old_node->getWeight(i), old_node->getDst(i));
			
	deleteNode(old_node);
}


template<typename N, typename E>
void deleteNode(const N& val) noexcept{
	for(unsigned int i = 0; i<arr_.size(); ++i)
		if(arr_[i]->getData() == val)
			arr_.erase(arr_.begin()+i);
}


template<typename N, typename E>
void deleteEdge(const N& src, const N& dst, const E& w) noexcept {
	if(!isNode(src))
		return;
	std::shared_ptr<Node<N,E>> s (new Node<N,E>);
	std::shared_ptr<Node<N,E>> d (new Node<N,E>);

	s = findNode(src);
	d = findNode(dst);

	s->deleteEdge(w,d);					
}


template<typename N, typename E>
void clear() noexcept{
	arr_.clear();
}


template<typename N, typename E>
bool isNode(const N &val) const{
	for(unsigned int i = 0; i<arr_.size(); ++i){
		if(arr_[i]->getData() == val)
			return true;
	}
	return false;	
}



template<typename N, typename E>
bool isConnected(const N& val, const N& dst) const{
	if(!isNode(val)||!isNode(dst))
		throw std::runtime_error("Error: One or two nodes with specified data do not exist.");
	
	std::shared_ptr<Node<N,E>> s (new Node<N,E>);
	std::shared_ptr<Node<N,E>> d (new Node<N,E>);
	s = findNode(val);
	d = findNode(dst);

	for(unsigned int i=0;i!=s->getNumEdge(); ++i)
		if(s->getDst(i) == d)
			return true;
	return false;
}

		
template<typename N, typename E>
std::shared_ptr<Node<N,E>> findNode(const N &src){
	for(unsigned int i = 0; i<arr_.size(); ++i){
		if(arr_[i]->getData() == src)
			return arr_[i];
	}
	return NULL;
}

	
template<typename N, typename E>
void printNodes() const {
	for(unsigned int i = 0;i<arr_.size();++i){
		std::cout << arr_[i]->getData()<<std::endl;
	}
}


template<typename N, typename E>
void printEdges(const N& val) const{
			
}



template<typename N, typename E>		
void printGraph() const{
	std::cout <<"size: " << arr_.size() << std::endl;
	for(unsigned int i = 0;i<arr_.size();++i){
		std::cout << "Adjacency list of vertex " << arr_[i]->getData()<<std::endl;
		for(unsigned int j=0;j<arr_[i]->getNumEdge();++j)
			std::cout << arr_[i]->getDst(j)->getData() << " -> ";
		std::cout <<std::endl;
		for(unsigned int j=0;j<arr_[i]->getNumEdge();++j)
			std::cout << arr_[i]->getWeight(j) << " -> ";
		std::cout <<std::endl;
	}
}




