#ifndef OutputUpdateTask_h
#define OutputUpdateTask_h

#include <inttypes.h>

#include "../lib/Task.h"
#include "../drivers/CvOutputService.h"


class OutputUpdateTask : public Task {

public:
    OutputUpdateTask(CvOutputService& cvOutputService);
    void init();
    void execute();

private:
    CvOutputService& _cvOutputService;

};

#endif
