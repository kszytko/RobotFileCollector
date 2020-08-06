#pragma once
#include "folderreader.h"
#include "foldergenerator.h"

#include <QString>
#include <QFileInfo>

class MadaReader : public FolderReader
{
public:
    MadaReader(std::shared_ptr<FolderGenerator> folderGen, QProgressBar* pb) : FolderReader(folderGen, pb) {};
    void copyFiles(bool override) override;

private:
    // FolderReader interface
    QString findNameInDirectory(QString& dir) override;  

};

QString readFile(QFileInfo& fileInfo);
qint64 calculateFolderSize(QDir* dir);

