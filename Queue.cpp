#include "precomp.h"
#include "Queue.h"

//You always know the max size of the queue.
//Whenever you add a new element you move the start -> forward.
//Suggestion: Balasz Fabian (Y1 PR)
//Pseudo Code 1: https://www.redblobgames.com/pathfinding/a-star/introduction.html
//Pseudo Code 2: https://en.wikipedia.org/wiki/Breadth-first_search
void Queue::enQueue(int node)
{
	data[front++] = node;
}

int Queue::deQueue()
{
	return data[rear++];
}

int Queue::getQueuedItem()
{
	return data[rear];
}

bool Queue::isEmpty()
{
	return rear == front;
}

int Queue::getSize()
{
	return front - rear;
}

