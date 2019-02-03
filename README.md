# UPC Bar Code Machine

* A work in progress.
* Currently can write scannable UPC type A barcodes to bitmap files with human-readable text.
* Will eventually read UPC type A barcodes from windows bitmap files.

## Cloning
```
git clone https://github.com/busterdash/upc-bar-code-machine
cd upc-bar-code-machine
git submodule update --init
```

## Compiling
* For simplicity, I use Orwell Dev-C++ to compile on Windows.
* I will provide a makefile in the future.

## Submodule(s)

### Bitmap FileIO:
* Submodule can be read about here: https://github.com/busterdash/bitmap-machine
* Writes windows bitmaps with a DIB of type ```BITMAPINFOHEADER```.
* Images compatible with Windows 3.1 and above.

This program is available to you as free software licensed under the GNU General Public License (GPL-3.0-or-later)
