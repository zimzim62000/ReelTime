#include "todo_list.h"

TodoList::TodoList()
{

}

bool TodoList::addTask(Task* task)
{
	this->todoList.push_back(task);
	return true;
}

std::vector<Task*> TodoList::getTodoList()
{
	return this->todoList;
}

void TodoList::deleteFirstTask()
{
	this->todoList.erase(this->todoList.begin());
}

int TodoList::countTodoList() const
{
	return this->todoList.size();
}

Task* TodoList::getFisrtTask() const
{
	return *this->todoList.begin();
}