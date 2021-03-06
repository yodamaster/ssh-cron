#ifndef INCLUDED_DAEMON_
#define INCLUDED_DAEMON_

#include <bobcat/fork>
#include <bobcat/sharedmemory>
#include <bobcat/signal>

#include "../ipcfunction/ipcfunction.h"
#include "../crondata/crondata.h"
#include "../cron/cron.h"

class Options;

namespace FBB
{
    class SharedCondition;
    class SharedStream;
}

class Daemon: public IPCFunction, public FBB::Fork, public FBB::SignalHandler
{
    struct IPCInfo;

    Options &d_options;
    CronData d_cronData;
    Cron d_cron;

    FBB::SharedMemory d_shmem;

    public:
        Daemon();
        void run();

    private:
        std::ostream &idmsg() const;    // imsg inserts basename :
        std::ostream &basename() const; // options.msg() inserts basename :

        void foreground();          // don't fork, just call the child process
        void daemonize();           // run the daemon in the background
        void ipc();                 // do the other commands, involving ipc

        void createIPCfile();
        void cleanup();

        void parentProcess()                override;
        void childProcess()                 override;
        void signalHandler(size_t signum)   override;

        void terminate() const;
        IPCInfo getIPCInfo() const;
        void getPassPhrase();
        std::string askPassPhrase();

        void reload();
        void listRequest();
        bool list(std::istream &in);

        static void enterThread(Daemon *obj);

};
        
#endif


