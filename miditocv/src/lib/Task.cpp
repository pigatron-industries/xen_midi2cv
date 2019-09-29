#include "Task.h"

#include <Arduino.h>

void Task::init()
{
		ended = false;
		time = micros();
		interval = 1;
		lastExecutionTime = 0;
		lastExecutionDiff = 0;
}

void Task::run()
{
		time = micros();
		lastExecutionDiff = time - lastExecutionTime;

  	if(lastExecutionDiff >= interval)
  	{
				lastExecutionTime = time;
	  		execute();
  	}
}
