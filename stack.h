#ifndef __STACK_H__
#define __STACK_H__

/*
 * 提供后进先出的简单栈功能
 */
typedef unsigned long Item;

class Stack {
	private:
		enum {MAX = 10};
		Item items[MAX];
		int top;
	public:
		Stack();
		bool isempty() const;
		bool isfull() const;
		bool push(const Item & item);
		bool pop(Item & item);
};
#endif /*__STACK_H__*/
