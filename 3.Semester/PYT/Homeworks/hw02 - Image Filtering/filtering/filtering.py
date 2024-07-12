"""
Filtering module - use apply_filter with provided image as numpy array, and kernel filter.

Will return numpy array of filtered image with provided kernel.

The kernel should be symmetrical.

Only RGB and grayscale images are supported.
"""

import numpy as np


def apply_filter(image: np.array, kernel: np.array) -> np.array:
    """ Apply given filter on image """
    # A given image has to have either 2 (grayscale) or 3 (RGB) dimensions
    assert image.ndim in [2, 3]
    # A given filter has to be 2 dimensional and square
    assert kernel.ndim == 2
    assert kernel.shape[0] == kernel.shape[1]

    if is_even_kernel(kernel):
        kernel = extend_to_odd_shape(kernel)

    is_grayscale_image = False
    if is_grayscale(image):
        is_grayscale_image = True
        image = np.expand_dims(image, axis=2)

    extended_image = add_offset_to_image(image, kernel_offset(kernel))
    filtered_image = apply_kernel(extended_image, kernel)

    if is_grayscale_image:
        return filtered_image[:, :, 0]
    return filtered_image


def is_grayscale(image: np.array) -> bool:
    """ Checks if image is grayscale """
    if image.ndim == 2:
        return True
    return False


def is_even_kernel(kernel: np.array) -> bool:
    """ Checks if kernel is even. """
    if kernel.shape[0] % 2 == 0:
        return True
    return False


def extend_to_odd_shape(kernel: np.array):
    """ Should be used when kernel is even. Takes ever kernel as argument, returns odd kernel, padded with zeros. """
    x, y = kernel.shape
    extended_kernel = np.zeros((x + 1, y + 1))
    extended_kernel[0:-1, 0:-1] = kernel
    return extended_kernel


def add_offset_to_image(image: np.array, offset: int) -> np.array:
    """ Add offset of the kernel to image, so the kernel can be applied - pads with zeros from each side. """
    height, width, channels = image.shape
    extended_image = np.zeros((height + 2 * offset, width + 2 * offset, channels))
    extended_image[offset: offset + height, offset: offset + width] = image
    return extended_image


def kernel_offset(kernel: np.array) -> int:
    """ Returns kernels offset from its origin - center. """
    return (kernel.shape[0] - 1) // 2


def apply_kernel(extended_image: np.array, extended_kernel: np.array) -> np.array:
    """ Applies kernel to the image and returns filtered image. """
    offset = kernel_offset(extended_kernel)
    height, width, channels = extended_image.shape
    filtered_image = np.zeros((height - 2 * offset, width - 2 * offset, channels))
    for z in range(channels):
        for x in range(offset, height - offset):
            for y in range(offset, width - offset):
                image_context = extended_image[x - offset: x + 1 + offset, y - offset: y + 1 + offset, z]
                filtered_image[x - offset, y - offset, z] = np.sum(image_context * extended_kernel)
    return np.clip(filtered_image, 0, 255).astype(np.uint8)
