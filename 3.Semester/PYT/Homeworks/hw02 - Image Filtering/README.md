# HW2: Image filtering

Your assignment is to implement a method that will take an image and a filter and applies a [convolution](https://en.wikipedia.org/wiki/Kernel_%28image_processing%29) between them. Only 2D filters (of any dimension) will be used and the method has to be able to handle both grayscale and RGB images. In case of RGB images, the filter is applied to each channel independently. When applying the filter, the pixels outside of the image boundary should be filled with zeros. You can assume that the kernels are square.

Only `numpy` and basic operations such as multiplication and sum can be used. So you cannot use `scipy`, for example.

### Code Structure:

```text
.
├── demo.ipynb
├── filtering
│   ├── filtering.py
│   ├── helpers.py
│   └── __init__.py
├── README.md
└── tests
    ├── __init__.py
    ├── lenna_gaussian_blur.png
    ├── lenna_gray_edge_detection.png
    ├── lenna.png
    ├── lenna_roberts_cross.png
    ├── secret_imgs
    └── test_filtering.py

3 directories, 11 files

```