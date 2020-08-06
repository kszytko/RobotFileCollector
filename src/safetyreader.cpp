#include "safetyreader.h"
#include <QDirIterator>
#include <QFile>
#include <QRegExp>
#include <QFileInfo>

#include "Debuger.h"

void SafetyReader::copyFiles(bool override)
{
    QDirIterator directories(folderGenerator->getMadaPath(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QString path, dirName, newFilePath;


    statusInit(10);

    while (directories.hasNext()) {
        path = directories.next();
        dirName = directories.fileName();

        statusUpdate();

        if(!files.contains(dirName))
            continue;

        auto robot = files[dirName];
        newFilePath = createSafetyFilePath(path, robot);

        debuger->insert("Copying file: " + newFilePath);

        QFile::remove(newFilePath);

        try {
            QFile::copy(robot->getPath() ,newFilePath);
        } catch (const std::exception& e) {
            debuger->insertError("Copying file not possible!");
            debuger->insertError(QString(e.what()));
        }

    }
}

void SafetyReader::readList(QStringList* paths)
{
    QFileInfo fileInfo;
    QRegExp rx;
    QString name;

    statusInit(paths->length());

    Robot robot("(\\d{3})(IR|\\+)(\\d{3})");

    for(auto& path : *paths){
        statusUpdate();
        debuger->insert("Checking file: " + path);

        fileInfo.setFile(path);
        name = fileInfo.fileName();
        robot.read(name);

        if (!robot.passed()){
            debuger->insertError("Name shoud have value like:  010IR001 or 010++001 etc.");
            debuger->insertError("NAME NOT VALID: " + path);
            continue;
        }

        robot.setPath(path);
        files.insert(robot.getST000_IR000(), new Robot(robot));
    }
}

QStringList SafetyReader::getList()
{
    auto keys = files.keys();
    QStringList list(keys);
    return list;
}

QString SafetyReader::createSafetyFilePath(QString& path, Robot* robot){
    return path + BACK_SLASH + robot->get000IR000() + ".xml";
}





