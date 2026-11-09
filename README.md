# StrLib
A string library made for C, made for learning object-oriented programming capabilities in C.
### What I learned from it:
**Opaque types** - C allows for types with no particular definition to be used in the code indirectly through pointers. They won't work in the executable if there is no implementation anywhere in the application.
Now, the opaque types are types defined in the header files to be used elsewhere.
If there is no concrete implementation in the same header, the type could be used in other files by the pointer alone. That also means that all the fields it carries are hidden.
We have to implement the opaque types in a different file.
If we don't, it will probably still compile to object files, but it won't be linkable.

One more thing I foumd is, there is no way to actually create true methods. The way I did it is very similar to how rust handles methods.

### Differences between Rust methods and this implementation:
- Rust has actual methods. Here, I used function pointers, with hidden functions in separate source files.
- Rust puts a reference to self in the beginning of the method definition as a parameter, and never again. In C, self appears in calls too.
- In C, to connect the hidden functions with the function pointers immitating methods, there has to be a init function call first.
