#pragma once

class Queue
{
public:

	int rear = 0, front = 0;
	int data[100] = {};

	void enQueue(int d);
	int deQueue();

	int getQueuedItem();

	bool isEmpty();
	int getSize();

private:

};