#pragma once
#include <QStringList>
#include <QProgressBar>

#include "readable.h"
#include "ProgressBarUse.h"
#include "DebugerSetter.h"

class FolderGenerator;

class FileReader : public Readable, public ProgressBarUse, public DebugerSetter{
public:
    FileReader(std::shared_ptr<FolderGenerator> folderGen, QProgressBar* pb) : ProgressBarUse(pb), folderGenerator(folderGen) {};

    virtual void copyFiles(bool override) = 0;
    virtual void readList(QStringList* filePaths) = 0;

protected:
    std::shared_ptr<FolderGenerator> folderGenerator;
};

