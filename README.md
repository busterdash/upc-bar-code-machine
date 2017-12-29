# UPC Bar Code Machine

* A work in progress.
* Currently can write scannable UPC type A barcodes to bitmap files with human-readable text.
* Will eventually read UPC type A barcodes from windows bitmap files.

## Cloning
```
git clone https://github.com/busterdash/sunlight-machine
cd sunlight-machine
git submodule update --init
```

## Compiling
* For simplicity, use Orwell Dev-C++ to compile on Windows.
* I will provide a makefile in the future.

## Submodule(s)

### Bitmap FileIO:
* Submodule can be read about here: https://github.com/busterdash/basic-bitmap-fileio
* Writes windows bitmaps with a DIB of type ```BITMAPINFOHEADER```.
* Images compatible with Windows 3.1 and above.
