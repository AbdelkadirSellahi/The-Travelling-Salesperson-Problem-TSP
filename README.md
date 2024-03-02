# Travelling Salesman Problem (TSP) Solutions

This repository contains two versions of solutions for a variant of the Travelling Salesman Problem (TSP), specifically designed for a tourist planning to visit as many sites as possible in a city within a single day, from 08:00 to 19:00.

## Problem Description

The problem focuses on maximizing the total score of visited tourist sites within a limited timeframe. Each site has an associated visit duration and attractiveness score. The goal is to select a subset of sites that maximizes the sum of scores, considering travel times between sites, with the itinerary starting and ending at a designated "home" site (e.g., a hotel).

## Project Configuration
This section outlines the key configurations and design decisions made in this project:

| Configuration Item            | Options           |
|-------------------------------|-------------------|
| 😊 Use of Emojis              | Disabled          |
| 🧠 Programming Paradigm       | Procedural        |
| 🌐 Language                   | C++               |
| 📚 Project Type               | General Purpose   |
| 📖 Comment Style              | Descriptive       |
| 🛠️ Code Structure            | Modular           |
| 🚫 Error Handling Strategy    | Basic             |

These configurations guide the development and contribution process for this project, ensuring consistency and clarity in its development.

### Instance Description

Each problem instance is defined in a text file, containing:
- The starting point (site 0).
- A list of sites, each with a unique ID, a visit duration, and an attractiveness score.
- A time matrix representing travel times between any two sites.
- The time constraint for the itinerary (from 08:00 to 19:00).

The input file format for an instance is as follows:
1. The first line contains the number of sites \(N\).
2. The next \(N\) lines each contain the duration \(d_i\) and score \(c_i\) for site \(i\).
3. The following \(N \times N\) lines form the time matrix \(T\), with each line containing \(N\) entries representing the travel time from site \(i\) to site \(j\).

Users are encouraged to try out different instances to explore various scenarios and optimization outcomes. Additional instances can be found in the `Another-Instance` folder within this repository.

## Solution Versions

### Version 1 (`Solution_V1.cpp`)

- **Approach**: Utilizes a straightforward heuristic algorithm to select sites based on their scores and travel times.
- **Data Structures**: Employs vectors to manage site information.
- **Outcome**: Visited 14 sites with a total score of 1463 within the available time.

### Version 2 (`Solution_V2.cpp`)

- **Approach**: Implements a more advanced optimization technique, potentially incorporating dynamic programming or a more sophisticated heuristic.
- **Data Structures**: Uses linked lists for dynamic itinerary adjustment.
- **Outcome**: Achieved a higher efficiency, visiting 42 sites with a total score of 4079.

## Comparison

Version 2 significantly outperforms Version 1, demonstrating the effectiveness of using more complex algorithms and suitable data structures for optimizing the itinerary.

## Results
For detailed results of the optimization, including the sites visited, their arrival and departure times, and the final score achieved, please refer to the `Result.txt` file included in the project repository. This file provides a comprehensive breakdown of the itinerary created by the algorithms for both versions.

## Getting Started

Instructions for running the solutions and setting up the environment.

### Prerequisites

- C++ compiler (e.g., GCC, Clang)
- Make (optional for compilation)

### Running the Solutions

- Clone the repository to your local machine.
- Explore the instances folder to choose a problem instance you would like to solve.
- Compile the C++ files using your preferred compiler, e.g., `g++ Solution_V1.cpp -o Solution_V1`.
- Execute the compiled file, e.g., `./Solution_V1`, to run the program.
- Check the `Result.txt` file to see the output of the algorithm.

## Trying Different Instances

To test the algorithm with different sets of data, users can replace the instance file in the `Another-Instance` folder with their own or modify the existing files. Each instance should follow the format described in the Instance Description section.

## Contributing

Contributions are welcome. Please feel free to fork the repository, make changes, and submit pull requests.

## Authors
- [**ABDELKADIR Sellahi**](https://github.com/AbdelkadirSellahi)
