#pragma once

namespace Core
{
namespace Containers
{

template <typename Type>
struct SinglyLinkedList
{
	struct Node
	{
		Type data;
		Node * next;
	};
	
	Node * head;
	
	void Insert (Node * previousNode, Node * newNode);
	
	void Remove (Node * previousNode, Node * deleteNode);
	
};

#include "SLinkedList.hpp"

}
}