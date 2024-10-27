import numpy as np
import re
import os

# Define the directory
directory = './results/TEMP'

# Function to find the file starting with the given pattern and read its content
def read_core_file(directory, pattern):
    for filename in os.listdir(directory):
        if filename.startswith(pattern):
            with open(os.path.join(directory, filename), 'r') as file:
                return file.read()
    return None  # Return None if no matching file is found

# Function to extract XY matrices and calculate their averages
def extract_xy_averages(content, matrix_type):
    # Find all XY matrices using regex
    matches = re.findall(rf'{matrix_type} = \[\s*([\s\S]*?)\]', content)
    
    averages = []

    for matrix_str in matches[-2:]:  # Get the last two matrices
        matrix_str = matrix_str.strip()
        
        # Split into lines and convert to a 2D array
        matrix = []
        for line in matrix_str.splitlines():
            if line.strip():  # Skip empty lines
                row = [float(x) for x in line.split() if x]  # Convert to float
                matrix.append(row)

        # Convert to numpy array for averaging
        matrix_array = np.array(matrix)

        # Exclude the last row and last column
        truncated_array = matrix_array[:-1, :-1]

        # Calculate the average value of the truncated matrix
        average_value = truncated_array.mean()
        averages.append(average_value)

    return averages

# Main function to get averages from the file
def get_average_values(filename_pattern):
    # Read the content of the file
    content = read_core_file(directory, filename_pattern)

    if content:
        # Get the average values of the last two XY0 matrices
        average_xy0_values = extract_xy_averages(content, 'XY0')

        # Get the average values of the last two XY1 matrices
        average_xy1_values = extract_xy_averages(content, 'XY1')

        # Combine averages into a single array
        all_averages = average_xy0_values + average_xy1_values  # Concatenate the lists
        
        return all_averages  # Return the averages array
    else:
        return None  # Return None if no file found

averages = get_average_values('Mem')
if averages is not None:
    print("Averages array:", averages)
else:
    print("No file found starting with the specified pattern in the directory.")
