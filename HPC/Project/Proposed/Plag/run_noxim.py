import subprocess
import csv
import argparse
import itertools
import os
import re
from average_calculator import get_average_values

# Function to run the Noxim simulator with the given options and capture its output
def run_noxim(options):
    command = ['./noxim'] + options
    try:
        # Run the command and capture the output
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        output = result.stdout
        return output
    except FileNotFoundError:
        print("Noxim executable not found. Make sure it is in the correct directory.")
        return None

def delete_folder_contents(folder_path):
    """
    Delete all contents of the specified folder.
    
    :param folder_path: Path to the folder whose contents will be deleted.
    """
    # Check if the folder exists
    if os.path.exists(folder_path) and os.path.isdir(folder_path):
        # Iterate over all items in the folder
        for item in os.listdir(folder_path):
            item_path = os.path.join(folder_path, item)
            # Check if it's a file or directory and delete accordingly
            if os.path.isfile(item_path):
                os.remove(item_path)
            elif os.path.isdir(item_path):
                shutil.rmtree(item_path)
        print("The folder is deleted")
    else:
        print(f"The folder {folder_path} does not exist or is not a directory.")

# Function to extract various metrics from the Noxim output
def extract_metrics(output):
    metrics = {}
    
    # Using regular expressions to find the required metrics
    total_area_match = re.search(r"Total area\s*:\s*([\d\.eE\+\-]+) \(um\^2\)", output)
    avg_power_match = re.search(r"Avg power\s*:\s*([\d\.eE\+\-]+) \(J/cycle\)", output)
    avg_cores_power_match = re.search(r"Avg cores power\s*:\s*([\d\.eE\+\-]+) \(J/cycle\)", output)
    avg_routers_power_match = re.search(r"Avg routers power\s*:\s*([\d\.eE\+\-]+) \(J/cycle\)", output)
    avg_power_per_router_match = re.search(r"Avg power per router\s*:\s*([\d\.eE\+\-]+) \(J/cycle\)", output)
    layer_area_match = re.search(r"Layer area\s*:\s*([\d\.eE\+\-]+) \(um\^2\)", output)
    area_per_core_match = re.search(r"Area per core\s*:\s*([\d\.eE\+\-]+) \(um\^2\)", output)

    print(avg_power_match)
    # Capture the values if found
    metrics['total_area'] = float(total_area_match.group(1)) if total_area_match else None
    metrics['avg_power'] = float(avg_power_match.group(1)) if avg_power_match else None
    metrics['avg_cores_power'] = float(avg_cores_power_match.group(1)) if avg_cores_power_match else None
    metrics['avg_routers_power'] = float(avg_routers_power_match.group(1)) if avg_routers_power_match else None
    metrics['avg_power_per_router'] = float(avg_power_per_router_match.group(1)) if avg_power_per_router_match else None
    metrics['layer_area'] = float(layer_area_match.group(1)) if layer_area_match else None
    metrics['area_per_core'] = float(area_per_core_match.group(1)) if area_per_core_match else None

    print(metrics)
    averages = get_average_values('Router')
    metrics['Steady state temperature - L0'] = averages[1]
    metrics['Steady state temperature - L1'] = averages[3]
    metrics['Router Average Temperature - L0'] = averages[0]
    metrics['Router Average Temperature - L1'] = averages[2]

    averages = get_average_values('Core')
    metrics['Core Average Temperature - L0'] = averages[1]
    metrics['Core Average Temperature - L1'] = averages[3]

    averages = get_average_values('Mem')
    metrics['Memory Average Temperature - L0'] = averages[1]
    metrics['Memory Average Temperature - L1'] = averages[3]

    delete_folder_contents("./results/TEMP")

    return metrics

# Function to save input and output to a CSV file
def save_to_csv(options, metrics, csv_filename):
    file_exists = os.path.isfile(csv_filename)
    
    # Open the CSV file in append mode, write if file doesn't exist
    with open(csv_filename, mode='a', newline='') as file:
        writer = csv.writer(file)
        # Write headers if file is being created
        if not file_exists:
            writer.writerow([
                'DimX', 'DimY', 'DimZ', 'PIR', 'Distribution', 'Routing', 'Selection', 'Traffic', 'Buffer Size', 
                'Simulation Time', 'Warmup Time', 'Vertical', 'Throttling', 'Clean', 'Total Area (um^2)', 
                'Avg Power (J/cycle)', 'Avg Cores Power (J/cycle)', 'Avg Routers Power (J/cycle)', 
                'Avg Power per Router (J/cycle)', 'Layer Area (um^2)', 'Area per Core (um^2)', 'Steady state temperature - L0',
                'Steady state temperature - L1', 'Router Average Temperature - L0', 'Router Average Temperature - L1',
                'Core Average Temperature - L0', 'Core Average Temperature - L1', 'Memory Average Temperature - L0',
                'Memory Average Temperature - L1'
            ])
        # Write input data and extracted output
        writer.writerow(options + [
            metrics['total_area'], metrics['avg_power'], metrics['avg_cores_power'], 
            metrics['avg_routers_power'], metrics['avg_power_per_router'], metrics['layer_area'], 
            metrics['area_per_core'], metrics['Steady state temperature - L0'], metrics['Steady state temperature - L1'],
            metrics['Router Average Temperature - L0'], metrics['Router Average Temperature - L1'],
            metrics['Core Average Temperature - L0'],metrics['Core Average Temperature - L1'] ,
            metrics['Memory Average Temperature - L0'], metrics['Memory Average Temperature - L1']
        ])

# Function to generate the range of values for each parameter
def generate_ranges(args):
    dimx_range = range(args.dimx[0], args.dimx[1] + 1) if isinstance(args.dimx, list) and len(args.dimx) == 2 else [args.dimx[0]]
    dimy_range = range(args.dimy[0], args.dimy[1] + 1) if isinstance(args.dimy, list) and len(args.dimy) == 2 else [args.dimy[0]]
    dimz_range = range(args.dimz[0], args.dimz[1] + 1) if isinstance(args.dimz, list) and len(args.dimz) == 2 else [args.dimz[0]]
    
    # Allow for Poisson distribution as a special case for packet injection rate
    if args.pir is None:
        pir_range = [0.01]  # Default value
    else:
        if len(args.pir) == 1:
            pir_range = [args.pir[0]]  # Single constant value
        else:
            pir_range = [i / 100.0 for i in range(int(args.pir[0] * 100), int(args.pir[1] * 100) + 1)]

    # Generate all combinations of parameter ranges
    combinations = itertools.product(dimx_range, dimy_range, dimz_range, pir_range)
    
    # Filter combinations to ensure dimx <= dimy
    # valid_combinations = [(dimx, dimy, dimz, pir) for dimx, dimy, dimz, pir in combinations if dimx <= dimy]

    return combinations

def main():
    # Define command line arguments
    parser = argparse.ArgumentParser(description="Run Noxim simulator with ranges of values and record results.")
    
    # Ranges of values
    parser.add_argument('-dimx', nargs='+', type=int, help='Range for mesh X dimension (min max or constant)')
    parser.add_argument('-dimy', nargs='+', type=int, help='Range for mesh Y dimension (min max or constant)')
    parser.add_argument('-dimz', nargs='+', type=int, help='Range for mesh Z dimension (min max or constant)')
    parser.add_argument('-pir', nargs='+', type=float, help='Range for packet injection rate (min max or constant)')
    parser.add_argument('-dist', type=str, default='poisson', choices=['poisson', 'burst', 'pareto', 'custom'], help='Type of packet injection distribution (poisson, burst, pareto, custom)')
    
    # Output CSV file
    parser.add_argument('-csv', type=str, default='noxim_output.csv', help='CSV filename to record data')

    args = parser.parse_args()

    # Generate all combinations of input ranges
    all_combinations = generate_ranges(args)

    for combination in all_combinations:
        dimx, dimy, dimz, pir = combination
        
        # Build Noxim command options including packet injection rate and distribution type
        options = [
            str(dimx), str(dimy), str(dimz), str(pir), args.dist,  # Input values
            'xyz', 'thermal', 'random',  # Routing, selection, traffic
            '4',  # Buffer size
            '200000', '10000',  # Simulation and warmup time
            'mesh', 'normal', '3000'  # Vertical, throttling, and clean time
        ]

        # Run Noxim simulator with the current combination
        output = run_noxim([
            '-routing', 'oe_3d',
            '-sel', 'thermal',  
            '-dimx', str(dimx),
            '-dimy', str(dimy),
            '-dimz', str(dimz),
            '-sim', '200000',
            '-warmup', '10000',
            '-size', '2', '4',
            '-buffer', '4',
            '-traffic', 'random',
            '-vertical', 'mesh',
            '-throt', 'normal',
            '-clean', '3000',
            '-pir', str(pir),
            args.dist,           
        ])

        if output:
            # Extract metrics from the output
            metrics = extract_metrics(output)
            
            # Save all options and extracted output to CSV if all metrics are found
            if all(value is not None for value in metrics.values()):
                save_to_csv(options, metrics, args.csv)
                print(f"Simulation completed for options: {options}")
            else:
                print(f"Some metrics not found in output for options: {options}")
        else:
            print(f"Error running Noxim with options: {options}")

if __name__ == "__main__":
    main()