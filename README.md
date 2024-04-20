# LFM-Emulator
Emulator of Linear Frequency Modulation

## Input
- **MF** - Modulation frequency, Hz
- **CF** - Carrying frequency, Hz
- **DF** - Max deviation, Hz
- **dt** - descreetization (sampling) frequency, Hz

## Output
#### LFM Graph
- Graph of modified signal
- Graph of linear dependancy and current deviation

#### LFM Range
- Basically the range?

## Structure
#### SettingsWidget
Widget that consists of LineEdits, Reset and Pause/Continue buttons. On reset sends the LFMSettings struct to the main class which resends it to LFMGraph widget. Also responsible for all the input validations.

#### LFMGraphsHandlerWidget
QTabWidget that consists of 2 tabs - LFMRangeWidget and LFMGraphWidget. Plays the role of observer and notifies the graphs to be updated on reset. Also controls the elapsed time between frames for real-time simulation. Derived from QTabWidget. Tabs - LRF Graph and LRF Range

#### LFMGraphWidget
Consists of 2 AmplitudeGraphWidget - graph_lmf and graph_df. Responsible for calculating frame shifts by elapsed time between ticks based on settings data given. Also creates a vector of points based on the settings and initializes the graphs.

#### AmplitudeGraphWidget
Class for all cyclic function graphs that have and amplitude. Has an array of points which are to be connected on each frame. On advance_frame(uint shift) shifts the frame for **shift** frames to the left. Uses a vector of points to be initialized.

#### LFMRangeWidget
Class responsible for presentation of LFM range. Currently I do not know how to implement it...

## Input Constraints
Currently in progress...
- **MF** - ???
- **CF** - ???
- **DF** - ???
- **dt** - ???
