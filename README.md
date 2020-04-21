# ft_printf

### Summary:
At 42, printf is one of many functions of the libc that we are forbidden to use.
It pushes us to create our own functions and really understand how it all works.
Recoding "printf" (from <stdio.h> library) is a chance to discover a feature of
the C language – variadic functions – and to practice detailed management of the
printing options.

### Prototype
```
int ft_printf( const char *restrict format, ... );
```

### Usage
```make``` then compile the program in which you want to use ft_printf with the ```libftprintf.a```

Conversions handled by ft_printf:
```
• %c %s %p
• %d %i %o %u %x %X with the following flags: hh, h, l and ll
• %f with the following flags: l and L
• %%
• flags #0-+ and space
• minimum field-width
• precision
```

Obtained mark for this project : 112/100
