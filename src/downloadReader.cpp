#include "downloadReader.h"
#include <QString>
#include <QDir>

#include "Robot.h"
#include "Debuger.h"

QString DownloadReader::findNameInDirectory(QString& path)
{
    QDir dir(path);
    auto dirName = dir.dirName();

    debuger->insert("Checking file: " + path);

    Robot robot("(\\d{3})(IR|\\+|_IR)(\\d{3})");
    robot.read(dirName);

    if (!robot.passed()){
        debuger->insert("Directory skipped: " + dirName);
        return {};
    }

    return robot.getST000_IR000();
}

void DownloadReader::copyFiles(bool override)
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QFileInfoList fileList;

    statusInit(folders.length());

    for(auto& folder : folders){
        debuger->insert("Copy into: " + folder.path);
        statusUpdate();

        dir.setPath(folder.path);
        if(!dir.exists())
            continue;

        fileList = dir.entryInfoList();

        for(auto& fileInfo : fileList){
            auto fileIn = fileInfo.filePath();
            auto fileOut = createOutputFilePath(folder.name, fileInfo);
            if(QFile::exists(fileOut)){
                if(!override)
                    continue;
                QFile::remove(fileOut);
            }
            QFile::copy(fileIn, fileOut);
        }
    }
}

QString DownloadReader::createOutputFilePath(QString& folderName, QFileInfo& fileInfo){
    return getOutputPath(fileInfo) +  BACK_SLASH + folderName + BACK_SLASH + fileInfo.fileName();
}

QString DownloadReader::getOutputPath(QFileInfo& file)
{
    auto fileName = file.fileName().toLower();
    if(fileName.startsWith("prog"))
        return  folderGenerator->getProgramsPath();

    if(fileName.startsWith("cell.src"))
        return  folderGenerator->getProgramsPath();

    return folderGenerator->getPathsPath();
}



