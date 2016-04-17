#include "task.h"

Task::Task()
{
	this->done = false;
}

Task::Task(const int idTask, const std::string name, const sf::Vector2f target)
{
	this->idTask = idTask;
	this->name = name;
	this->target = target;
	this->done = false;
}

Task::Task(const int idTask, const std::string name)
{
	this->idTask = idTask;
	this->name = name;
}