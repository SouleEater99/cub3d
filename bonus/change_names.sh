#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: <dir path> <extension> <new extension>"
    exit 1
fi

# Define the directory containing your .c files
directory="$1"

# Loop through all .c files in the directory
for file in "$directory"/$2; do
    # Skip files that already have "_bonus.c" in the name
    if [[ "$file" != *_bonus.c ]]; then
        # Rename the file by adding "_bonus" before the .c extension
        mv "$file" "${file%.c}$3"
        echo "Renamed: $(basename "$file") -> $(basename "${file%.c}$3")"
    fi
done

echo "Renaming complete."

