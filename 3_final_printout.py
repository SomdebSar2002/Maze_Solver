from PIL import Image, ImageDraw

def generate_maze_matrix_image(maze_matrix, node_coordinates):
    cell_size = 30

    width = len(maze_matrix[0]) * cell_size
    height = len(maze_matrix) * cell_size

    image = Image.new("RGB", (width, height), "white")
    draw = ImageDraw.Draw(image)

    wall_color = "black"
    path_color = "white"
    node_color = "green"
    counter = 0
    for row in range(len(maze_matrix)):
        for col in range(len(maze_matrix[0])):
            x1 = col * cell_size
            y1 = row * cell_size
            x2 = x1 + cell_size
            y2 = y1 + cell_size
            x, y = row, col
            is_in_pts = (x, y) in node_coordinates
            if maze_matrix[row][col] == 1:
                draw.rectangle([x1, y1, x2, y2], fill=wall_color)
            else:
                draw.rectangle([x1, y1, x2, y2], fill=path_color)
            if is_in_pts:
                draw.rectangle([x1, y1, x2, y2], fill=node_color)
                # node_label = f"({counter})"
                # counter+=1
                # draw.text((x1 + 5, y1 + 5), node_label, fill="black")

    return image

if __name__ == "__main__":
   
    maze_matrix = []
    file_path = "img_to_maze_matrix.txt"
    with open(file_path,'r') as infile:
        for line in infile:
            row = [int(val) for val in line.strip().split()]
            maze_matrix.append(row)

    # Coordinates of green nodes from the Python output
    file_path = 'node_cordinates.txt'

    node_coordinates = []
    with open(file_path, 'r') as infile:
        for line in infile:
            x, y = map(int, line.strip().split(','))
            node_coordinates.append((x, y))



    maze_matrix_image = generate_maze_matrix_image(maze_matrix, node_coordinates)

    # Save the image to a file
    maze_matrix_image.save("maze_with_labels.png")

    # Show the image
    maze_matrix_image.show()
