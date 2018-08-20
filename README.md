# bbmacro

*bbmacro -- C containers and useful macros*

### Contents of the package

`label.h`
> The macro header with non-fallthrough `switch` syntax and
> with the macros for avoiding direct usage of `goto`.

`ansicolor.h`
> The macro header for colorizing output using ANSI escape codes.
> Plain escape codes, low-level macros and high-level macros are provided.

`static.h`
> The macro header with portable attributes and miscellaneous useful macros.

`vector.h`
> The macro header with a vector type written in the C way.

`memory.h`
> The appendix to `vector.h` with the fully automatic memory management.

---
### System requirements

It would be good if your system supports ANSI escape codes.

---
### Installation

First of all, edit the file `Config` to fit your needs
(or set the variables from that file in a command line).
On a typical Linux machine you can keep it untouched.

You can check the compilability of some headers *(optional step)*:

    $ make proof

You can also run the provided demo programs *(optional step)*:

    $ make demo
    $ build/label
    $ build/palette
    $ build/ansicolor

And finally, install the header files
(you need the superuser privileges):

    # make install

---
### Development

To remove the `build` directory, run this command:

    $ make clean

To package all the sources into a tarball, run this command:

    $ make dist

---
### NOINCLUDE

In some header files (`*.h`), you find the following construction:

    #ifndef NOINCLUDE
    #define NOINCLUDE
    #include ...
    #include ...
    #undef NOINCLUDE
    #endif

This is caused by the simple rule of Rob Pike:
[*"Include files should never include include files"*
](http://doc.cat-v.org/bell_labs/pikestyle).

**If you want** to strictly follow this rule, you should:

* define NOINCLUDE in your compilations
(append `-DNOINCLUDE` to the command line options of your C compiler);

* in the header files, surround all necessary includes in the way shown.

It will force you to include all dependencies manually
in the source files (`*.c`).

If you do not appreciate this rule, just **don't care**.
