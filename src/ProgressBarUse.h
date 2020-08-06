#pragma once
#include <QProgressBar>

class ProgressBarUse{
public:
    ProgressBarUse(QProgressBar* progressBar) : progressBar(progressBar){};

    void statusInit(int max){
        progressBar->setMaximum(max);
        step = 0;
    }

    void statusUpdate(){
        progressBar->setValue(++step);
    }

private:
    QProgressBar* progressBar;
    int step = 0;
};
