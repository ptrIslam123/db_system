#ifndef _COMMAND_H_
#define _COMMAND_H_

class command
{
public:
    virtual void execute() = 0;
    virtual bool is_it_commat() const = 0;
};

#endif // !_COMMAND_H_
