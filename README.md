# LFM-Emulator
Emulator of Linear Frequency Modulation

## Input
- **MF** - Modulation Frequency, Hz
- **CF** - Carrier Frequency, Hz
- **FD** - Frequency Deviation, Hz
- **SF** - Sampling Frequency, Hz

## Output
#### LFM Graph
- Graph of modified signal in time and frequency domains

## Structure
#### LFMSettingsWidget
Widget that consists of LineEdits, Reset button and instructions. On reset sends the LFMSettings struct to the main class which resends it to GraphHandler widget. Also responsible for all the input validations.
![image](https://github.com/Crucinio/LFM-Simulator/assets/109169672/67c8787b-07b2-46e1-8c78-14c322f4613f)


#### GraphHandler
Widget that consists of 2 tabs - Time and Frequency signal representations. Plays the role of observer and notifies the graphs to be updated on reset. Derived from QTabWidget. Responsible for calculations (s(t), s(t) -> s(w))
![image](https://github.com/Crucinio/LFM-Simulator/assets/109169672/2a9ccbfe-076d-48ca-814b-38045af559ee)


#### Graph
Universal widget for creating different graphs.
![image](https://github.com/Crucinio/LFM-Simulator/assets/109169672/d3ee118b-3346-48bf-99fd-b1cd9e5fda08)
![image](https://github.com/Crucinio/LFM-Simulator/assets/109169672/e71b027d-f97e-49f0-b07a-c29d219af258)



## Input Constraints
0.1 < MF < 100; \
5 * MF < CF < 1000 * MF; \
0 < FD < CF; \
(CF + FD) * 100 < SF < 1e7; \
SF < MF * 5e5;
