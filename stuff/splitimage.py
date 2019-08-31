import os
import sys
import argparse
from PIL import Image


def split_image(image_path, output_dir, tile_size):
    try:
        image = Image.open(image_path)
    except IOError as e:
        print("Error: unable to open image. {}", e)
        return

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    image_name = os.path.splitext(os.path.basename(image_path))[0]
    width, height = image.size

    for j, top in enumerate(range(0, height, tile_size), 0):
        for i, left in enumerate(range(0, width, tile_size), 0):
            box = (left, top, left + tile_size, top + tile_size)
            image.crop(box).save(os.path.join(
                output_dir, "{}_{}_{}.png".format(image_name, j, i)))

    print("Done")


def main():
    parser = argparse.ArgumentParser(description='Image splitter')
    parser.add_argument('image_path', )
    parser.add_argument(
        '--output-dir', help="output directory for image parts")
    parser.add_argument(
        '--tile-size', help="square image part width and height in pixels", default=512)

    args = parser.parse_args()
    split_image(args.image_path, args.output_dir, args.tile_size)


if __name__ == '__main__':
    main()
