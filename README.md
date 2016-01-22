# m_intcombo
General-purpose integer combinations library in the C89 language that runs
on all POSIX-compatible systems.

## Introduction
The `m_intcombo` library implements the idea of all possible combinations
where each element of the combination is drawn from a different set. To
simplify the idea and create an easy understandable abstraction
(homomorphism), the sets are not real object, only mere `intmax_t`
instances.

## Usage
### Initialization
The internal state of the combination is stored in a `struct m_intcombo`
instance. Before using any other functions, it is necessary to call the
`m_intcombo_init` function to properly initialise the data structure.

### Source set addition
In order to add a source set for the combination, use the `m_intcombo_add`
function. The source set is always an interval, specified by its low and
high bounds.

### Finalization 
After adding all source sets, the `m_intcombo_finalize` function needs to
be called. This function also returns (via an argument) a pointer to the
array of `intmax_t` variables that will contain the combination.

### Advancing & reset
In order to advance to the next combination, use the `m_intcombo_next`
function. Upon reaching the last combination, the function returns an
appropriate value. All further calls to the `m_intcombo_next` function
will not advance the combination. In order to reset the internal state,
use the `m_intcombo_reset` function.

### Resource freeing
After being finished with the combination, call the `m_intcombo_free` to
free the internal resources held by the internal data structures.

## Example
The following example reads the command line arguments in a form of
`L..H`, where L is the lower and H is the higher bound of the internal.
The example program prints all possible combinations that arise from the
specified source sets.

```c
#include <stdlib.h>
#include <stdio.h>
#include <m_intcombo.h>

int
main(int argc, char** argv)
{
  int i;
  int ret;
  struct m_intcombo ic;
  char* err_str;
  intmax_t* next;
  intmax_t lo;
  intmax_t hi;

  m_intcombo_init(&ic);

  for (i = 1; i < argc; i++) {
    sscanf(argv[i], "%lld..%lld", &lo, &hi);
    m_intcombo_add(&ic, lo, hi);
  }

  m_intcombo_finalize(&ic, &next);

  while ((ret = m_intcombo_next(&ic)) == M_INTCOMBO_OK) {
    for (i = 0; i < (argc-1); i++)
      printf("%lld ", next[i]);
    printf("\n");
  }

  m_intcombo_free(&ic);

  if (ret != M_INTCOMBO_END) {
    m_intcombo_error_string(ret, &err_str);
    fprintf(stderr, "ERROR: %s\n", err_str);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
```

Compile & run:
```sh
$ clang -o example example.c -lmintcombo
$ ./example 0..1 0..1 0..1
0 0 0 
1 0 0 
0 1 0 
1 1 0 
0 0 1 
1 0 1 
0 1 1 
1 1 1 
```

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3

If a platform does not appear to be in the previous list, it does not
mean that `m_set` will not work in such environment. It only means that
nobody tested it - you are encouraged to do so and report either success
or failure.

## Build & install
```
$ ninja
$ sudo ./install.sh
```

## License
2-clause BSD license. For more information please consult the
[LICENSE](LICENSE.md) file. In the case that you need a different license,
feel free to contact me.

## Author
Daniel Lovasko (daniel.lovasko@gmail.com)

