from PIL import Image

image = Image.open("combo400.png").convert("L")

width,height = image.size

threshold = 128

white_pixels = []
dark_pixels = []

file_path = "img_to_maze_matrix.txt"

with open(file_path,'w') as outfile:
    for y in range(height):
        for x in range(width):
            pixel_value = image.getpixel((x,y))
            if pixel_value >= threshold:
                outfile.write("0 ")
            else:
                outfile.write("1 ")
        outfile.write("\n")
print("Data has been written to 'img_to_maze_matrix.txt'.")
