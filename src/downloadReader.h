#pragma once
#include "folderreader.h"
#include "foldergenerator.h"
#include <QFileInfo>

class DownloadReader : public FolderReader
{
public:
    DownloadReader(std::shared_ptr<FolderGenerator> folderGen, QProgressBar* pb) : FolderReader(folderGen, pb) {};
    void copyFiles(bool override) override;

private:
    // FolderReader interface
    QString findNameInDirectory(QString& directory) override;

    QString createOutputFilePath(QString& folderName, QFileInfo& fileInfo);
    QString getOutputPath(QFileInfo& file);

};

