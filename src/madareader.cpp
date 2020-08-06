#include "madareader.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <filesystem>
#include <QDirIterator>

#include "Debuger.h"
#include "Robot.h"

const qint64 MAX_FILE_COUNT = 1000;
const qint64 MAX_FOLDER_SIZE = 10000000; // 10 MB

qint64 calculateFolderSize(QString path)
{
    QDir dir(path);
    QDirIterator it(dir, QDirIterator::Subdirectories);
    qint64 total = 0;
    qint64 fileCounter = 0;

    while (it.hasNext() && ++fileCounter < MAX_FILE_COUNT) {
        it.next();
        total += it.fileInfo().size();
    }
    return total;
}

void MadaReader::copyFiles(bool override)
{
    statusInit(folders.length());

    for(auto& folder : folders){
        auto folderIn = folder.path;
        auto folderOut = folderGenerator->getMadaPath() + BACK_SLASH + folder.name;

        statusUpdate();
        debuger->insert("Dir to copy: " + folderIn);

        QDir dir(folderOut);

        if(dir.exists()){
            if(!override)
                continue;
            dir.removeRecursively();
            debuger->insert("Dir removed: " + dir.path());
        }

        auto size = calculateFolderSize(folderIn);
        if(size > MAX_FOLDER_SIZE){
            debuger->insertError("Size of MADA directory is greater than 10MB. Folder not copied.");
            debuger->insertError("Exact size: " + QString::number(size / (1024 * 1024)) + " MB");
            continue;
        }

        try {
            std::filesystem::copy(folderIn.toStdString(), folderOut.toStdString(), std::filesystem::copy_options::recursive);
        } catch (const std::exception& e) {
            debuger->insertError("Copying folder not possible!");
            debuger->insertError(QString(e.what()));
        }

    }
}



QString MadaReader::findNameInDirectory(QString& path) {


    QDir dir(path);
    QFileInfo file(dir.filePath("RobotInfo.xml"));

    if (!file.exists()){
        debuger->insertError("RobotInfo.xml" " not found in" + path);
        return {};
    }
    QString xmlText = readFile(file);

    Robot robot("Instance Name=\"\\+\\+ST(\\d{3})\\+IR(\\d{3})");
    robot.read(xmlText);

    if (!robot.passed()){
        debuger->insertError("In RobotInfo.xml" " robot name not found!" + file.filePath());
       return {};
    }

    return robot.getST000_IR000();
}

QString readFile(QFileInfo& fileInfo)
{
    QFile file(fileInfo.filePath());
    if (!file.open(QIODevice::ReadOnly)){
        return {};
    }

    QTextStream in(&file);
    return in.readAll();
}




