#pragma once

class Command
{
protected:
    bool repeatable = true;
public:
    bool isRepeatable() { return repeatable; };
    virtual void execute() = 0;
};
