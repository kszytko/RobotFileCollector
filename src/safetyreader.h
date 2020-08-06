#pragma once
#include "filereader.h"
#include "foldergenerator.h"
#include "Robot.h"

#include <QMap>
#include <QStringList>
#include <QString>

class SafetyReader : public FileReader
{
public:
    SafetyReader(std::shared_ptr<FolderGenerator> folderGen, QProgressBar* pb) : FileReader(folderGen, pb){};

    // FolderReader interface
    void copyFiles(bool override) override;
    void readList(QStringList* filePaths) override;

    // Readable interface
    QStringList getList() override;

private:
    QString createSafetyFilePath(QString& path, Robot* robot);

private:
    QMap<QString, Robot*> files;
};

