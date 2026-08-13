import os
from tkinter import Tk, filedialog
from PIL import Image

MOD_ID = input("what is the mod id e.g: arcticwoof.rated_layouts\n ?:")

def select_image(title):
    path = filedialog.askopenfilename(
        title=title,
        filetypes=[
            ("Images", "*.png *.jpg *.jpeg *.webp *.bmp"),
            ("All Files", "*.*")
        ]
    )

    if not path:
        raise Exception("No image selected")

    return path

def select_output_type():
    while True:
        print("Choose output type:")
        print("1. SwelvyBG")
        print("2. Sapphire")

        choice = input("> ").strip()

        if choice == "1":
            return "./previews"

        if choice == "2":
            return "./previews/sapphire"

        print("Invalid option. Enter 1 or 2.")

def main():
    root = Tk()
    root.withdraw()

    normal_path = select_image("Select normal image")
    geodify_path = select_image("Select geodify image")

    output_folder = select_output_type()

    preview_name = input("Enter preview name (example: CreatorLayer): ").strip()

    if not preview_name:
        raise Exception("Preview name cannot be empty")

    normal = Image.open(normal_path).convert("RGBA")
    geodify = Image.open(geodify_path).convert("RGBA")

    geodify = geodify.resize(normal.size)

    width, height = normal.size

    top_layer = Image.new("RGBA", normal.size, (0, 0, 0, 0))

    left_half = normal.crop(
        (0, 0, width // 2, height)
    )

    top_layer.paste(left_half, (0, 0))

    result = geodify.copy()
    result.alpha_composite(top_layer)

    os.makedirs(output_folder, exist_ok=True)

    filename = f"{MOD_ID}-{preview_name}Preview.png"

    output_path = os.path.join(
        output_folder,
        filename
    )

    result.save(output_path)

    print(f"Saved preview:")
    print(output_path)

if __name__ == "__main__":
    main()
