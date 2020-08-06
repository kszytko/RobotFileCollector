#pragma once

#include <memory>
class Debuger;

class DebugerSetter{
public:
    void setDebuger(std::shared_ptr<Debuger> debuger_) { debuger = debuger_; }

protected:
    std::shared_ptr<Debuger> debuger;
};
