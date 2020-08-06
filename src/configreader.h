#pragma once
#include "filereader.h"
#include "foldergenerator.h"

#include <QString>

class ConfigReader :  public FileReader
{ 
public:
    ConfigReader(std::shared_ptr<FolderGenerator> folderGen, QProgressBar* pb) : FileReader(folderGen, pb){};

public:
    void copyFiles(bool override) override;
    void readList(QStringList* filePaths) override;

private:
    QString config, custom, options;
    QStringList* files;

    // Readable interface
public:
    QStringList getList() override;
};

