#ifndef LIBNS_H
#define LIBNS_H
struct message_result
{
    unsigned char version;
    unsigned char code;
    signed short flag; //Зарезервировано
    unsigned int size;
    enum : unsigned char{
        OK = 0,
        ERROR_FILENOTFOUND = 1,
        ERROR_DEPNOTFOUND = 2,
        ERROR_PKGNOTFOUND = 3,
        ERROR_PKGINCORRECT = 4,
        ERROR_CMDINCORRECT = 5
    };
    enum flags : unsigned int
    {
        FLAG_EVENT = 1
    };
};

enum class cmds : unsigned char
{
    none = 0,
    stop = 1,
    setconfig = 2,
    loadmodule = 3,
    su = 4,
    listen = 5,
    MAX_COMMANDS = 6
};
namespace flags
{
    enum : unsigned short{
        multiparams = 1 >> 0,
        old_command = 1 >> 1
    };
}
namespace cmdflags{

}

struct message_head
{
    unsigned char version;
    unsigned char cmd;
    unsigned short flag;
    unsigned int cmdflags;
    unsigned int size;
};
#endif // LIBNS_H
