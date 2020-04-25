#include "OutputUpdateTask.h"


OutputUpdateTask::OutputUpdateTask(CvOutputService& cvOutputService) :
    _cvOutputService(cvOutputService) {
}

void OutputUpdateTask::init() {
    Task::init();
}

void OutputUpdateTask::execute() {
    _cvOutputService.update();
}
