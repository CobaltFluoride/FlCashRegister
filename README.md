# FlCashRegister

FlCashRegister is a fully-featured POS system that does not use databases. This makes it increadibly easy to set up and use. There is no fooling around with a database.
Instead .axtf files are used. Although an axtf file is *not* a key-value based file, it *can* be used like one.

## AXTF Files

Axtf, pronounced axe-tiff, stands for **Ax**olotl **T**ransfer **F**ile. The axtf format is extremely simple. Each line is a vector. The items are separated by the ':' character.
In the current FlCashRegister implementation, there is no backslash escape support (like `Book Item:Donald's Adventure\:The Awakening`), but that is planned and is part of the format.

Just a reminder that axtf files are not key-value based.

## Example AXTF File

Here is an example AXTF File:

```
AXTF_VERSION:1.0
food:donut:milk:tea:coffee
32:87
Single item
Item 1:Item 2:Item 3:Item 4:Item 5
```

## Compiling

Please note that there are linux binaries in source/ and dist/

The project is ***not working*** at this moment! It will compile but the full functionality is not complete, and will not be able to be used as a full POS system yet!
However, this has to be done by monday so I hope it's complete by then.

- Go to the source directory: `cd source`
- Run `make`
- run `./mkdist` to copy appropriate files to ../dist

After following those steps, you can then go to the dist folder and run `./pos` to start the POS system.

# Thanks

Thanks for checking out the repo. Feel free to clone/download/fork this repo and do whatever you want with it.
