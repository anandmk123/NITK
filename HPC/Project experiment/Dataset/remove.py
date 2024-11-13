import pandas as pd

# Load the dataset from a CSV file
df = pd.read_csv('oe_3d_15_16.csv')

# Remove the text "Percent (per tile)" from the 'area_per_core' column
df['area_per_core'] = df['area_per_core'].str.replace('Percent \(per tile\)', '', regex=True)

# Save the cleaned DataFrame to a new CSV file (optional)
df.to_csv('cleaned_dataset.csv', index=False)

# Display the cleaned DataFrame (optional)
print(df)
