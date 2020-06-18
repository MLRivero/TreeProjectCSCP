// TreeProjectv1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

template <class T> class Node {

public:
	T data;
	Node<T>* parent;
	vector <Node<T>*> children;

	Node(T data) {
		this->data = data;
		parent = NULL;
	}

	Node(T data, Node* par) {
		this->data = data;
		parent = par;
	}

	Node(const Node &nodeCopy) {
		this->data = nodeCopy.data;
		this->parent = nodeCopy.parent;
		this->children = nodeCopy.children;
	}

	T& info() {
		return data;
	}
	void setParent(Node* par) {
		parent = par;
	}
	void addChild(Node* child) {
		child->setParent(this);
		children.push_back(child);
	}
	int numChildren() const {
		return children.size();
	}

	~Node() {
		for (int i = 0; i < numChildren(); i++)
			delete[](children[i]);
	}

	Node operator-() {
		this->data *= -1;
		for (int i = 0; i < childrenNumber(); i++) {
			this->children[i].operator-();
		}

	}

	Node& operator= (const Node &n) {
		// delete if null?
		swap(data, n.data);
		swap(parent, n.parent);
		swap(children, n.children);

		return (*this);
	}

	bool noChildren() {
		if (numChildren()) {
			return true;
		}
		else { return false; }
	}


	int childrenNumber() {
		return children.size();

	}

	void printTree(const Node &tr, ostream &out) const {
		out << " Node data: " << tr.data << " ";
		if (tr.numChildren() > 0) {
			
			
		
			out << "Children of " << tr.data << ": ";
			for (int i = 0; i < tr.numChildren(); i++) {
				out << (*tr.children[i]).data;
				if (i < tr.numChildren() - 1) {
					out << ", ";
				}
				
			}
			out << endl;
		}
		else out << endl;

		for (int i = 0; i < tr.numChildren(); i++) {
			printTree(*tr.children[i], out);
		}

	}
	
	Node<T> sum(const Node<T> &t1, const Node<T> &t2) {


	}


	bool equals(const Node &t2) const {
		bool eq = false;
		//cout << data << t2.data;
		if (eqStructure(t2)) {
			if (data == t2.data) {
				eq = true;
				for (int i = 0; i < numChildren(); i++) {
					/*cout << (*this->children[i]).data;
					cout << (*t2.children[i]).data;*/

					eq = (*this->children[i]).equals(*t2.children[i]);
				}
			}
		}
		return eq;
	}


//private: 
	bool eqStructure(const Node &t2) const {
		bool eqS = false;
		if (numChildren() == t2.numChildren()) {
			eqS = true;
			for (int i = 0; i < numChildren(); i++) {
				eqS = (*this->children[i]).eqStructure(*t2.children[i]);
			}
		}
		return eqS;
	}

	bool operator!=(const Node<T> &t2) {
		return !(*this == t2);
	}
	template <class T> friend bool operator==(const Node<T> &t1, const Node<T> &t2);
	//template <class T> friend bool operator!=(const Node<T> &t1, const Node<T> &t2);
	template <class T> friend int nodesNumber(Node<T>* n1, int& count);
	template <class T> friend ostream& operator<<(ostream &out, const Node<T> &tr); 
	template <class T> friend Node<T> operator+(const Node<T> &t1, const Node<T> &t2);
};

//template <class T> Node<T> operator+ (const Node<T> &t1, const Node<T> &t2) {
//	Node<T>* aux = *t1;
//	if (*aux.eqStructure(t2)) {
//		aux.data = t1.data + t2.data;
//		for (int i = 0; i < numChildren(); i++) {
//			aux->children[i]->data = aux.sum(t1.children[i], t2.children[i]);
//		}
//
//	}
//}

bool operator==(const Node<int> &t1, const Node<int> &t2) {
	return t1.equals(t2);
}

template <class T> int nodesNumber(Node<T>* n1, int& count) {

	Node<T> *parent = n1;
	for (int i = 0; i < parent->childrenNumber(); i++) {
		count++;
		if (parent->children[i]->childrenNumber() > 0) {
			nodesNumber(parent->children[i], count);
		}
	}
	return count;
}
template <class T> ostream& operator<<(ostream &out, const Node<T> &tr) {
	tr.printTree(tr, out);
	return out;
}

int main()
{
	//Node<int>* prueba2;
	//Node<int>* hijo2 = new Node <int>(8);
	Node<int>* prueba = new Node <int>(1);
	Node<int>* hijo2 = new Node <int>(3);
	//Node<int>* hijo4 = new Node <int>(9);
	//Node<int>* hijo5 = new Node <int>(9);
	////hijo1->addChild(hijo4);
	//hijo3->addChild(hijo5);
	//vector <Node<int>*>::iterator it;
	//int loco=1;
	Node<int>* hijo1 = new Node<int>(2);
	hijo1->addChild(new Node<int>(4));
	hijo1->addChild(new Node<int>(5));
	//cout << *hijo1;
	prueba->addChild(hijo1);
	prueba->addChild(hijo2);
	//prueba->addChild(hijo2);
	//prueba->addChild(hijo3);
	//cout << prueba->childrenNumber();
	//prueba2 = prueba;
	////cout << nodesNumber(prueba2,loco);
	
	//hijo1->addChild(hijo3);
	hijo2->addChild(new Node<int>(6));
	hijo2->addChild(new Node<int>(7));
	//cout << *hijo2 << endl;
	//cout << *prueba << *hijo1;
	////for (it = prueba2->children.begin(); it < prueba2->children.end(); it++) {
	////	cout << **it << endl;
	////}
	//cout << prueba->equals(*hijo1);
	//cout << (*prueba).eqStructure(*hijo1);
	Node<int>* otro = new Node<int>(*prueba);
	cout << (*prueba);
	cout << (*otro);
	//cout << (*hijo1 != *hijo2);
	//cout << (*hijo1 == *hijo2);
	//if (*hijo1 != *hijo2) {
	//	cout << "Bien";
	//}




	//Ask about: operators += etc if they are with another node (prob yes), about operator[] and about operator = maybe si esta bien o no porque no sé lo que hace la funcion y el copy y tal no hago una copia de los datos... solo del primero?
}


