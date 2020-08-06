#include "configreader.h"
#include "Debuger.h"

#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <QFile>

void ConfigReader::copyFiles(bool override)
{
    QDirIterator directories(folderGenerator->getMadaPath(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    QString path, newConfigPath, newCustomPath, newOptionPath;

    if(!override)
        return;

    statusInit(10);

    while (directories.hasNext()) {
        path = directories.next();

        statusUpdate();
        debuger->insert("Copying data into: " + path);

        newConfigPath = path + "/KRC/R1/Mada/$config.dat";
        newCustomPath = path + "/KRC/Steu/Mada/$custom.dat";
        newOptionPath = path + "/KRC/Steu/Mada/$option.dat";

        QFile::remove(newConfigPath);
        QFile::remove(newCustomPath);
        QFile::remove(newOptionPath);

        QFile::copy(config ,newConfigPath);
        QFile::copy(custom, newCustomPath);
        QFile::copy(options, newOptionPath);
    }
}

void ConfigReader::readList(QStringList* paths)
{
    for(auto& path : *paths){
        if(path.endsWith("$config.dat"))
            debuger->insert("CONFIG: config.dat readed.");
            config = path;
        if(path.endsWith("$custom.dat"))
            debuger->insert("CONFIG: custom.dat readed.");
            custom = path;
        if(path.endsWith("$option.dat"))
            debuger->insert("CONFIG: option.dat readed.");
            options = path;
    }
}

QStringList ConfigReader::getList()
{
    QStringList list(*files);
    return list;
}
