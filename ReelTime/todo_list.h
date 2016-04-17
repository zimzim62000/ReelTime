#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "task.h"


class TodoList
{
public:
	TodoList();
	bool addTask(Task* task);
	std::vector<Task*> getTodoList();
	void deleteFirstTask();
	int countTodoList() const;
	Task* getFisrtTask() const;

private:
	std::vector<Task*> todoList;
};