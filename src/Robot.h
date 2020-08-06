#pragma once

#include <QString>
#include <QRegExp>

class Robot{
public:
    Robot(QString regex) : re(regex){};

    void read(QString& text){
        re.indexIn(text);

        if(!passed())
            return;
        station = re.cap(1);
        robot = re.cap(re.captureCount());
    }

    bool passed(){
        return re.isValid();
    }

    QString get000IR000(){
        return station + "IR" + robot;
    }

    QString getST000_IR000(){
        return "ST" + station + "_IR" + robot;
    }

    void setPath(QString path) {
        this->path = path;
    }

    QString getPath() const {
        return path;
    }

private:
    QString station;
    QString robot;
    QString path;

    QRegExp re;
};
