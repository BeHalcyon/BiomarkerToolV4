# Biomarker-Tool-V4
海马体标注工具

## .dll and .lib Needed
for libtiff（安装libtiff之后生成）\
&emsp;&emsp;Debug:\
&emsp;&emsp;&emsp;&emsp;jpeg.dll\
&emsp;&emsp;&emsp;&emsp;libtiff.dll\
&emsp;&emsp;&emsp;&emsp;zlibd.dll\
&emsp;&emsp;&emsp;&emsp;libtiffd.lib\
&emsp;&emsp;Release:\
&emsp;&emsp;&emsp;&emsp;jpeg.dll\
&emsp;&emsp;&emsp;&emsp;libtiff.dll\
&emsp;&emsp;&emsp;&emsp;zlib.dll\
&emsp;&emsp;&emsp;&emsp;libtiff.lib

## 参考资料
1. Using the TIFF Library：http://www.libtiff.org/libtiff.html#Mman
2. TIFF Tag 含义: https://www.awaresystems.be/imaging/tiff/tifftags/baseline.html

## 可能的问题
1. 目前只支持压缩方式为**不压缩**的，即 `TIFFGetField(tif, TIFFTAG_COMPRESSION, &imageCompression);` 读取出来的 `imageCompression` 只能是1。
