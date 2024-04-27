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

#### GraphHandler
Widget that consists of 2 tabs - Time and Frequency signal representations. Plays the role of observer and notifies the graphs to be updated on reset. Derived from QTabWidget. Responsible for calculations (s(t), s(t) -> s(w))

#### Graph
Universal widget for creating different graphs.

## Input Constraints
0.1 < MF < 100; \
5 * MF < CF < 1000 * MF; \
0 < FD < CF; \
(CF + FD) * 100 < SF < 1e7; \
SF < MF * 5e5; \
