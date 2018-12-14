# FlCashRegister

FlCashRegister is a fully-featured POS system that does not use databases. This makes it increadibly easy to set up and use. There is no fooling around with a database.
Instead .axtf files are used. Although an axtf file is *not* a key-value based file, it can be used like one.

## AXTF Files

Axtf stands for **Ax**olotl **T**ransfer **F**ile. The axtf format is extremely simple. Each line is a vector. The items are separated by the ':' character.
In the current FlCashRegister implementation, there is no backslash escape support (like "value\:1:value\:2"), but that is planned and is part of the format.

## Compiling

The project is ***not working*** at this moment! It will compile but the full functionality is not complete, and will not be able to be used as a full POS system yet!
However, this has to be done by monday so I hope it's complete by then.

# Thanks

Thanks for checking out the repo. Feel free to clone/download/fork this repo and do whatever you want with it.
