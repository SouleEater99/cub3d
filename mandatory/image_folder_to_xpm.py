from PIL import Image
import os
import sys

def convert_images_in_folder(input_folder, output_folder):
    try:
        # Ensure the output folder exists
        os.makedirs(output_folder, exist_ok=True)

        # Iterate over all files in the input folder
        for file_name in os.listdir(input_folder):
            input_path = os.path.join(input_folder, file_name)

            # Check if the file is an image (PNG or JPG)
            if file_name.lower().endswith(('.png', '.jpg', '.jpeg')):
                try:
                    # Open the image and convert to XPM
                    img = Image.open(input_path).convert("RGB")
                    output_file_name = os.path.splitext(file_name)[0] + ".xpm"
                    output_path = os.path.join(output_folder, output_file_name)
                    
                    # Save the image as XPM
                    img.save(output_path, format="XPM")
                    print(f"Converted: {file_name} -> {output_file_name}")
                except Exception as e:
                    print(f"Error processing {file_name}: {e}")
            else:
                print(f"Skipped (not an image): {file_name}")

        print(f"All images processed. Converted files saved to: {output_folder}")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python convert_to_xpm_folder.py <input_folder> <output_folder>")
    else:
        input_folder = sys.argv[1]
        output_folder = sys.argv[2]

        if not os.path.isdir(input_folder):
            print(f"Error: Input folder not found: {input_folder}")
        else:
            convert_images_in_folder(input_folder, output_folder)
