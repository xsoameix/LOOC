#   What's LOOC

LOOC is library with object oriented structure of c.

#   Example

*   Hash

        hash_init();
        void * hash = new(Hash);
        hash_set(hash, "a", "b");
        hash_get(hash, "a");
        delete(hash);

#   How to get LOOC

Use following command:

    $ git clone git@github.com:xsoameix/LOOC.git

#   How to compile and install

1.  If `./configure` does not exist or is older than configure.in,
    run autoconf to (re)generate configure.

2.  Run `./configure`, which will generate config.h and Makefile.

3.  Run `make`.

#   Copying

See the file `COPYING`.
