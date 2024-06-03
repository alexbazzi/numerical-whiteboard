import matplotlib.pyplot as plt
import pandas as pd

# Load the data from the CSV file
data = pd.read_csv('filter_data.csv')

# Plot position estimates vs true positions
plt.figure(figsize=(12, 6))
plt.subplot(3, 1, 1)
plt.plot(data['true_position'], label='True Position')
plt.plot(data['position_prediction'], label='Position Prediction', linestyle='--')
plt.plot(data['position_estimate'], label='Position Estimate', linestyle='-.')
plt.xlabel('Time Step')
plt.ylabel('Position')
plt.legend()
plt.grid(axis='both')
plt.title('Position Estimates and Predictions')

# Plot velocity estimates vs true velocities
plt.subplot(3, 1, 2)
plt.plot(data['velocity_prediction'], label='Velocity Prediction', linestyle='--')
plt.plot(data['velocity_estimate'], label='Velocity Estimate', linestyle='-.')
plt.xlabel('Time Step')
plt.ylabel('Velocity')
plt.legend()
plt.grid(axis='both')
plt.title('Velocity Estimates and Predictions')

# Plot acceleration estimates vs true accelerations
plt.subplot(3, 1, 3)
plt.plot(data['acceleration_prediction'], label='Acceleration Prediction', linestyle='--')
plt.plot(data['acceleration_estimate'], label='Acceleration Estimate', linestyle='-.')
plt.xlabel('Time Step')
plt.ylabel('Acceleration')
plt.legend()
plt.grid(axis='both')
plt.title('Acceleration Estimates and Predictions')

plt.tight_layout()

# Save the figure as a png
plt.savefig('filter_data_plots.png')

plt.show()

