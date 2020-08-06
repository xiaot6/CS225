/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0 || curDim >= Dim) {
      return false;
    }
    if(first[curDim] < second[curDim]){
       return true;
    } else if(first[curDim] > second[curDim]){
       return false;
    } else{
       return first < second;
    }

}


template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>& point1, const Point<Dim>& point2) const
{
    double d = 0;
    for (int i = 0; i < Dim; i++) {
        d += pow((point1[i] - point2[i]), 2);
    }
    return d;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& curBestNode,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    if (getDistance(target, curBestNode) < getDistance(target, potential)) {
      return false;
    }
    if (getDistance(target, curBestNode) > getDistance(target, potential)) {
      return true;
    }
    return (potential < curBestNode);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

	vector<Point<Dim>> pointsVec = newPoints;
	size = pointsVec.size();
	root = buildTree(0, pointsVec.size()-1, 0, pointsVec);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildTree(int startNode, int endNode, int d, vector<Point<Dim>>& pointsVec)
{

	if (endNode < startNode) {
    return NULL;
  }
	KDTreeNode * rootNode = new KDTreeNode();
	int median = (startNode+endNode)/2;
  int dime = (d+1)%Dim;
	quickselect(startNode, endNode, median, d%Dim, pointsVec);
	rootNode->point = pointsVec[median];
	rootNode->left = buildTree(startNode, median-1, dime, pointsVec);
	rootNode->right = buildTree(median+1, endNode, dime, pointsVec);
	return rootNode;
}


template<int Dim>
void KDTree<Dim>::quickselect(int left, int right, int k, int d, vector<Point<Dim>> & pointsVec){
	if (left >= right) {
    return;
  }
  int pivotIndex = (left + right) / 2;
  Point<Dim> pivotValue = pointsVec[pivotIndex];
  swap(pointsVec[pivotIndex], pointsVec[right]);
	int storeIndex = left;
	for (int i=left; i<right; i++) {
		if (smallerDimVal(pointsVec[i], pivotValue, d)) {
			swap(pointsVec[storeIndex],pointsVec[i]);
			storeIndex++;
		}
	}
	swap(pointsVec[right], pointsVec[storeIndex]);

	if (k == storeIndex) {
    return;
  }
  if (storeIndex < k) {
    return quickselect(storeIndex+1, right, k, d, pointsVec);
  }
	if (storeIndex > k) {
    return quickselect(left, storeIndex-1, k, d, pointsVec);
  }
	return;
}


template <int Dim>
void KDTree<Dim>::copyTree(KDTreeNode * node1, KDTreeNode * node2) {
  if (node2 == NULL) {
    return;
  }
	node1 = new KDTreeNode();
	node1->point = node2->point;
	copyTree(node1->left, node2->left);
	copyTree(node1->right, node2->right);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copyTree(this->root, other.root);
	size = other.size;
}

template <int Dim>
void KDTree<Dim>::deleteTree(KDTreeNode * node) {
	if (node == NULL) {
    return;
  }
	if (node->left != NULL) {
    deleteTree(node->left);
  }
	if (node->right != NULL) {
    deleteTree(node->right);
  }
	delete node;
	node = NULL;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != NULL) {
    deleteTree(this->root);
  }
  copyTree(this->root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   deleteTree(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(root, query, 0);;

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * curNode, const Point<Dim>& query,int dimension) const {
	Point<Dim> curBestNode = curNode->point;
  int dime = (dimension + 1) % Dim;
	bool ifTravRight;
  if(curNode == NULL){
    return NULL;
  }

  if (curNode->left == NULL && curNode->right == NULL) {
    return curNode->point;
  }

  KDTreeNode * tempNext;

	if (smallerDimVal(query, curNode->point, dimension)) {
		if (curNode->left != NULL) {
      tempNext = curNode->left;
			curBestNode = findNearestNeighbor(tempNext, query, dime);
		  ifTravRight = true;
    } else {
 	    tempNext = curNode->right;
      curBestNode = findNearestNeighbor(tempNext, query, dime);
    }
	} else {
		if (curNode->right != NULL) {
      tempNext = curNode->right;
      curBestNode = findNearestNeighbor(tempNext, query, dime);
		  ifTravRight = false;
		} else {
			tempNext = curNode->left;
      curBestNode = findNearestNeighbor(tempNext, query, dime);
    }
	}

	if (shouldReplace(query, curBestNode, curNode->point)) {
    curBestNode = curNode->point;
  }

	double r = 0;
	for (int i = 0; i < Dim; i++) {
		r += (query[i] - curBestNode[i]) * (query[i] - curBestNode[i]);
	}

	double d = (curNode->point[dimension] - query[dimension]) * (curNode->point[dimension] - query[dimension]);

	if (d > r) {
    return curBestNode;
  } else {
    KDTreeNode * travOtherTree;
    if (ifTravRight) {
      travOtherTree = curNode->right;
    } else {
      travOtherTree = curNode->left;
    }
		if (travOtherTree != NULL) {
			Point<Dim> newBest;
      newBest = findNearestNeighbor(travOtherTree, query, dime);
			if (shouldReplace(query, curBestNode, newBest)) {
        curBestNode = newBest;
      }
		}
	}
	return curBestNode;
}
