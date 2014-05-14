#include "options.ih"

void Options::setBoolMembers()
{
    // d_useSyslog is set in `setSyslogParams'

    d_daemon = not d_arg.option(0, "no-daemon");
    if (d_daemon && (d_terminate || d_list))
        fmsg << "--daemon incompatible with --list and --terminate";

    d_verbose = d_arg.option(0, "verbose");
    d_stdout = d_verbose || d_arg.option('s');

    d_log = d_arg.option(&d_logName, 'L');
}
